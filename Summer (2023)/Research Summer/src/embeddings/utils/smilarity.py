import numpy as np
from enum import Enum
from scipy.spatial.distance import euclidean
from numpy.linalg import norm
from typing import Callable


class SimilarityFunction(Enum):
    cosine = "cos"
    dot_product = "dot"
    euclidean_distance = "euc"


def cosine_similarity(v1, v2) -> float:
    return np.dot(v1, v2) / (norm(v1) * norm(v2))


similarity_functions = {
    SimilarityFunction.cosine.value: cosine_similarity,
    SimilarityFunction.dot_product.value: np.dot,
    SimilarityFunction.euclidean_distance.value: euclidean,
}


def get_similarity_function(type: SimilarityFunction) -> Callable:
    return similarity_functions[type.value]
