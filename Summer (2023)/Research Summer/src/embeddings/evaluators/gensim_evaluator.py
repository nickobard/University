from utils.smilarity import SimilarityFunction
from evaluators.base import Evaluator
from gensim.models import KeyedVectors
from utils.preprocessing import (
    tokenize_text,
    lower_case,
    stop_words_removal,
    simple_denoise,
)
import logging
from schemes import KeywordData


class GensimEvaluator(Evaluator):
    def __init__(
        self,
        model: KeyedVectors,
        model_name: str,
        similarity_method: SimilarityFunction = SimilarityFunction.cosine,
    ):
        self.model: KeyedVectors = model
        super().__init__(model_name=model_name, similarity_method=similarity_method)

    def tokenize(self, corpus: str) -> list[str]:
        tokenized = tokenize_text(corpus)
        tokenized = lower_case(tokenized)
        tokenized = stop_words_removal(tokenized)
        tokenized = simple_denoise(tokenized)
        return tokenized

    def preprocess_corpus(self, corpus: str) -> list[tuple[str, int]]:
        tokenized = self.tokenize(corpus)
        ordered = self.assign_order(tokenized)
        return ordered

    def evaluate_keyword(
        self, tokens: list[tuple[str, int]], case_id: int, keyword_data: KeywordData
    ) -> None:
        keyword = keyword_data.keyword
        if keyword not in self.model:
            keyword_embedding = None
        else:
            keyword_embedding = self.model[keyword]
        expected_matches = keyword_data.matches.copy()
        for token in tokens:
            if token in expected_matches:
                expected_matches.remove(token)
                classification = 1
            else:
                classification = 0
            if keyword_embedding is None:
                similarity = None
            else:
                similarity = self.similarity(
                    keyword_embedding=keyword_embedding, token=token
                )
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

    def similarity(self, keyword_embedding, token) -> float | None:
        word = token[0]
        if word not in self.model:
            return None
        word_embedding = self.model[word]
        return self._similarity_function(keyword_embedding, word_embedding)
