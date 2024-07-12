from nltk.tokenize import sent_tokenize, word_tokenize
from nltk.corpus import stopwords
from collections import Counter
import string
from gensim.models import KeyedVectors


def preprocess_text(text: str) -> list[str]:
    words: list[str] = tokenize_text(text)
    words = simple_denoise(words)
    words = lower_case(words)
    words = stop_words_removal(words)
    words = unique(words)
    return words


def split_by_OOV(words: list[str], model: KeyedVectors) -> tuple[list[str], list[str]]:
    OOV_words = []
    filtered_words = []

    for word in words:
        if word in model:
            filtered_words.append(word)
        else:
            OOV_words.append(word)

    return filtered_words, OOV_words


def lower_case(words: list[str]) -> list[str]:
    return [word.lower() for word in words]


def stop_words_removal(words: list[str]) -> list[str]:
    return [word for word in words if word not in set(stopwords.words("english"))]


def simple_denoise(words: list[str]) -> list[str]:
    return [
        word
        for word in words
        if word not in string.punctuation
        and not word.isnumeric()
        and not len(word) == 0
    ]


def unique(words: list[str]) -> list[str]:
    return list(Counter(words))


def tokenize_text(text: str) -> list[str]:
    sentences = sent_tokenize(text)
    words_lists = [word_tokenize(sentence) for sentence in sentences]
    flat_words = [word for sublist in words_lists for word in sublist]
    return flat_words
