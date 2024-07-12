from utils.smilarity import SimilarityFunction
from evaluators.base import Evaluator
from flair.embeddings import TransformerWordEmbeddings
from flair.data import Sentence
from nltk.corpus import stopwords
import numpy as np
import string
from schemes import Dataset, KeywordData
from flair.data import Token
from utils.preprocessing import tokenize_text


class FlairEvaluator(Evaluator):
    def __init__(
        self,
        model: TransformerWordEmbeddings,
        model_name: str,
        similarity_method: SimilarityFunction = SimilarityFunction.cosine,
    ):
        self.model = model
        super().__init__(model_name=model_name, similarity_method=similarity_method)

    def tokenize(self, corpus: str) -> list[tuple[str, np.array]]:
        reassembled_corpus = " ".join(tokenize_text(corpus))
        sentence = Sentence(reassembled_corpus)
        self.model.embed(sentence)

        # stop words removal
        filtered = [
            token
            for token in sentence
            if token.text.lower() not in set(stopwords.words("english"))
        ]
        # denoising
        denoised = [
            token
            for token in filtered
            if token.text.lower() not in string.punctuation
            and not token.text.lower().isnumeric()
            and not len(token.text) == 0
        ]

        return [
            (token.text.lower(), token.embedding.cpu().numpy()) for token in denoised
        ]

    def preprocess_corpus(self, corpus: str) -> tuple[list, list]:
        tokenized = self.tokenize(corpus)
        words, embeddings = zip(*tokenized)
        ordered = self.assign_order(words)
        return list(zip(ordered, embeddings))

    def evaluate_keyword(
        self, tokens: list[tuple], case_id: int, keyword_data: KeywordData
    ) -> None:
        keyword = keyword_data.keyword
        keyword_sentence = Sentence(keyword)
        self.model.embed(keyword_sentence)
        if len(keyword_sentence) > 1:
            raise NotImplementedError()
        else:
            keyword_embedding = self.exract_embedding(keyword_sentence[0])
        expected_matches = keyword_data.matches.copy()
        for token, embedding in tokens:
            if token in expected_matches:
                expected_matches.remove(token)
                classification = 1
            else:
                classification = 0
            similarity = self.similarity(v_embedding=keyword_embedding, w_embedding=embedding)
            self.data.loc[len(self.data)] = [
                case_id,
                keyword,
                token,
                classification,
                similarity,
                False,
                True if similarity is None else False,
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
    def exract_embedding(token: Token) -> np.array:
        return token.embedding.cpu().numpy()
