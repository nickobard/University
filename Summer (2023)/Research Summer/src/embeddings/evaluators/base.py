import json

from schemes import Dataset, KeywordData
import pandas as pd
import numpy as np
from collections import Counter
import logging
from utils.smilarity import SimilarityFunction, get_similarity_function
from abc import ABC, abstractmethod
from numpy.typing import NDArray

class Evaluator(ABC):
    def __init__(self, model_name: str, similarity_method: SimilarityFunction):
        self.model_name = model_name
        self.dataset: Dataset = None
        self.similarity_method = similarity_method
        self.reset_evaluator()

    @property
    def model_name(self) -> str:
        return f"{self._model_name}-{self.similarity_method.value}"

    @model_name.setter
    def model_name(self, model_name: str) -> None:
        self._model_name = model_name

    @property
    def similarity_method(self):
        return self._similarity_method

    @similarity_method.setter
    def similarity_method(self, similarity_method: SimilarityFunction):
        self._similarity_method = similarity_method
        self._similarity_function = get_similarity_function(similarity_method)
        
    def similarity(self, v_embedding: NDArray, w_embedding: NDArray) -> float | None:
        return self._similarity_function(v_embedding, w_embedding)

    def reset_evaluator(self) -> None:
        self.data = pd.DataFrame(
            columns=[
                "Case ID",
                "Keyword",
                "Word",
                "Classification",
                "Similarity",
                "Lost",
                "OOV",
            ]
        )

    def load_dataset(self, path: str) -> None:
        with open(path) as f:
            data = json.load(f)
        self.dataset = Dataset(cases=data)

    @abstractmethod
    def preprocess_corpus(self, corpus: str) -> list:
        pass

    @abstractmethod
    def evaluate_keyword(self, tokens, case_id: int, keyword_data: KeywordData) -> None:
        pass

    @staticmethod
    def assign_order(tokens: list[str]) -> list[tuple[str, int]]:
        counter: Counter = Counter()
        ordered_tokens: list[tuple[str, int]] = []
        for token in tokens:
            counter.update([token])
            current_order = counter[token] - 1
            ordered_tokens.append((token, current_order))
        return ordered_tokens

    def evaluate(self) -> pd.DataFrame:
        for case in self.dataset.cases:
            preprocessed = self.preprocess_corpus(case.text)
            for keyword_data in case.keywords:
                self.evaluate_keyword(
                    preprocessed,
                    case.case_id,
                    keyword_data,
                )

        return self.data
