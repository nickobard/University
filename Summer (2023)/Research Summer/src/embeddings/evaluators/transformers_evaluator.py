from utils.smilarity import SimilarityFunction
from evaluators.base import Evaluator
from flair.data import Sentence
from nltk.corpus import stopwords
from nltk import sent_tokenize
import numpy as np
import string
from schemes import KeywordData
from flair.data import Token
from torch import Tensor
from transformers import PreTrainedModel, PreTrainedTokenizer
import torch
from numpy.typing import NDArray


class TransformersEvaluator(Evaluator):
    def __init__(
        self,
        model: PreTrainedModel,
        tokenizer: PreTrainedTokenizer,
        model_name: str,
        similarity_method: SimilarityFunction = SimilarityFunction.cosine,
        all_layers: bool = False,
    ):
        self.model = model
        self.tokenizer = tokenizer
        self.all_layers = all_layers
        super().__init__(model_name=model_name, similarity_method=similarity_method)

    def embed_tokens(self, corpus: str) -> tuple[list, list]:
        sentences: list[str] = sent_tokenize(corpus)
        all_tokens: list[str] = []
        all_embeddings: list[NDArray] = []
        for sentence in sentences:
            # tensor shape [1, words_number]
            tokens_ids: Tensor = self.tokenizer.encode(sentence, return_tensors="pt")
            tokens: list[str] = self.tokenizer.convert_ids_to_tokens(
                tokens_ids.squeeze(dim=0)
            )
            with torch.no_grad():
                outputs = self.model(input_ids=tokens_ids)
                # tensor shape [1, words_number, ]
                if self.all_layers:
                    hidden_states: tuple = outputs.hidden_states
                    token_embeddings = torch.stack(hidden_states, dim=0)
                    token_embeddings = torch.squeeze(token_embeddings, dim=1)
                    token_embeddings = token_embeddings.permute(1, 0, 2)
                    embeddings = []
                    for token in token_embeddings:
                        sum_vec = torch.sum(token, dim=0) / 13
                        embeddings.append(sum_vec)
                else:
                    embeddings_tensor: Tensor = outputs.last_hidden_state
                    embeddings = embeddings_tensor.squeeze(dim=0)
            tokens = self.remove_special_tokens(tokens)
            embeddings = self.remove_special_tokens(embeddings)
            aggregated_tokens, aggregated_embeddings = self.subword_aggregation(
                tokens, embeddings
            )
            all_tokens.extend(aggregated_tokens)
            all_embeddings.extend(aggregated_embeddings)
        return all_tokens, all_embeddings

    @staticmethod
    def subword_aggregation(
        tokens: list[str], embeddings: list[np.array]
    ) -> tuple[list[str], list[np.array]]:
        aggregated_tokens = []
        aggregated_embeddings = []

        subwords_count = 1
        subwords_sequence = False
        for t, e in zip(tokens, embeddings):
            if t.startswith("##"):
                subwords_sequence = True
                subwords_count += 1

                # remove '##' which specifies subword
                t = t[2:]

                # aggregate with previous token and embedding
                aggregated_tokens[-1] += t
                aggregated_embeddings[-1] += e
            else:
                if subwords_sequence:  # end of subword sequence
                    aggregated_embeddings[-1] /= subwords_count
                    subwords_count = 1
                    subwords_sequence = False
                # just append token - there is no subword sequence and the token is a whole word or start of new sequence
                aggregated_tokens.append(t)
                aggregated_embeddings.append(e)
        return aggregated_tokens, aggregated_embeddings

    @staticmethod
    def remove_special_tokens(tokens: list[str | NDArray]):
        return tokens[1:-1]

    def tokenize(self, corpus: str) -> list[tuple[str, NDArray]]:
        tokens, embeddings = self.embed_tokens(corpus)

        tokens = [token.lower() for token in tokens]

        filtered_tokens = []

        for t, e in zip(tokens, embeddings):
            if t in set(stopwords.words("english")):
                continue
            if t in string.punctuation or t.isnumeric() or len(t) == 0:
                continue
            filtered_tokens.append((t, e.cpu().numpy()))
        return filtered_tokens

    def preprocess_corpus(self, corpus: str) -> tuple[list, list]:
        tokenized = self.tokenize(corpus)
        words, embeddings = zip(*tokenized)
        ordered = self.assign_order(words)
        return list(zip(ordered, embeddings))

    def evaluate_keyword(
        self, tokens: list[tuple], case_id: int, keyword_data: KeywordData
    ) -> None:
        keyword = keyword_data.keyword
        keyword_embedding = self.get_keyword_embedding(keyword)
        expected_matches = keyword_data.matches.copy()
        for token, embedding in tokens:
            if token in expected_matches:
                expected_matches.remove(token)
                classification = 1
            else:
                classification = 0
            similarity = self.similarity(
                v_embedding=keyword_embedding, w_embedding=embedding
            )
            self.data.loc[len(self.data)] = [
                case_id,
                keyword,
                token,
                classification,
                similarity,
                False,
                False if similarity else True,
            ]
        for token in expected_matches:
            self.data.loc[len(self.data)] = [
                case_id,
                keyword,
                token,
                1,
                None,
                True,
                False,
            ]

    @staticmethod
    def embeddings_pooling(embeddings: list[NDArray]) -> NDArray:
        return sum(embeddings) / len(embeddings)

    def get_keyword_embedding(self, keyowrd: str) -> NDArray:
        self.embed_tokens(corpus=keyowrd)
        tokens_ids: Tensor = self.tokenizer.encode(keyowrd, return_tensors="pt")
        with torch.no_grad():
            outputs = self.model(input_ids=tokens_ids)
            # tensor shape [1, words_number, ]
            embeddings_tensor: Tensor = outputs.last_hidden_state
        embeddings = embeddings_tensor.squeeze(dim=0)
        embeddings = self.remove_special_tokens(embeddings)
        embedding = self.embeddings_pooling(embeddings)
        return embedding
