import pandas as pd
import numpy as np
from sklearn.metrics import precision_recall_curve
from sklearn.metrics import PrecisionRecallDisplay
import statistics
from sklearn.metrics import accuracy_score, auc
import logging
from evaluators.base import Evaluator
from utils.smilarity import SimilarityFunction


class Statistics:
    def __init__(self, evaluator: Evaluator):
        self.evaluator: Evaluator = evaluator
        self.data: pd.DataFrame = evaluator.data.copy()
        self.reset_statistics()

    def get_oov(self) -> pd.DataFrame:
        return self.data[self.data.OOV == True]

    def get_lost(self) -> pd.DataFrame:
        return self.data[self.data.Lost == True]

    def remove_oov(self) -> pd.DataFrame:
        oov_rows = self.get_oov()
        self.data = self.data[self.data.OOV == False]

        self.data.reset_index(inplace=True, drop=True)
        oov_rows.reset_index(inplace=True, drop=True)

        return oov_rows

    def remove_lost(self) -> pd.DataFrame:
        lost_rows = self.get_lost()
        self.data = self.data[self.data.Lost == False]

        self.data.reset_index(inplace=True, drop=True)
        lost_rows.reset_index(inplace=True, drop=True)

        return lost_rows

    def reset_statistics(self) -> None:
        self.y_true = None
        self.y_scores = None
        self.y_pred = None
        self.precision = None
        self.recall = None
        self.thresholds = None
        self.f1_score = None
        self.PRC = None

    def calculate_f1_scores(self) -> None:
        def calculate_f1_score(precision: float, recall: float) -> float:
            args = [precision, recall]
            return statistics.harmonic_mean(args)

        calculate_f1_scores = np.vectorize(calculate_f1_score)
        self.f1_score = calculate_f1_scores(self.precision, self.recall)
        logging.debug(f"f1_scores array: \n{self.f1_score}")

    def statistics_argmax(self) -> int:
        return np.argmax(self.f1_score)

    def substitute_oov_and_lost_values(self) -> None:
        min_val = min(self.data[self.data.Similarity.notna()].Similarity)
        self.data.fillna(value=min_val, inplace=True)

    def complement_similarity(self) -> None:
        similairty_scores = self.data.Similarity
        max_similarity = max(similairty_scores)
        complement = similairty_scores.apply(lambda score: max_similarity - score)
        self.data.Similarity = complement

    def prepare_data(self) -> None:
        if self.evaluator.similarity_method == SimilarityFunction.euclidean_distance:
            self.complement_similarity()
        self.substitute_oov_and_lost_values()

    def calculate_statistics(self) -> pd.DataFrame:
        self.prepare_data()
        self.calculate_PRC()
        self.calculate_f1_scores()
        argmax = self.statistics_argmax()
        best_threshold = self.thresholds[argmax]
        self.score_predictions(best_threshold)
        return self.final_statistics(argmax)

    def final_statistics(self, argmax: int) -> pd.DataFrame:
        logging.debug(f"First threshold: {self.thresholds[0]}")
        logging.debug(f"Argmax value: {argmax}")
        logging.debug(f"Best threshold: {self.thresholds[argmax]}")

        data = {
            "Threshold": self.thresholds[argmax],
            "Precision": self.precision[argmax],
            "Recall": self.recall[argmax],
            "F1 Score": self.f1_score[argmax],
            "Accuracy": accuracy_score(self.y_true, self.y_pred),
            "AUC-PR": auc(x=self.recall, y=self.precision),
        }

        logging.debug(data)
        df = pd.DataFrame(data=data, index=[self.evaluator.model_name])
        df.index.name = "Methods"
        return df

    def score_predictions(self, threshold: float) -> None:
        calculate_predictions = np.vectorize(
            lambda score: 0 if score < threshold else 1
        )

        logging.debug(self.y_scores)

        self.y_pred = calculate_predictions(self.y_scores)

    def display_PRC(self) -> None:
        if self.PRC is None:
            self.PRC = PrecisionRecallDisplay(
                precision=self.precision, recall=self.recall
            )
        self.PRC.plot()

    def calculate_PRC(self) -> None:
        self.y_true = self.data.Classification.to_numpy()
        self.y_scores = self.data.Similarity.to_numpy()
        self.precision, self.recall, self.thresholds = precision_recall_curve(
            self.y_true, self.y_scores
        )
        logging.debug(f"Shape of thresholds array: {np.shape(self.thresholds)}")
        logging.debug(f"Thresholds array: \n{self.thresholds}")
