from gensim.models import KeyedVectors


def scored_words_with_matches(words: list[str], keyword: str, threshold: float, model: KeyedVectors) -> tuple[dict[str, float], set[str]]:
    scores = dict()
    matches = set()
    for word in words:
        if word not in scores:
            similarity = model.similarity(word, keyword)
            scores[word] = similarity
            if similarity > threshold:
                matches.add(word)
    return scores, matches


def scored_words(words: list[str], keyword: str, model: KeyedVectors) -> dict[str, float]:
    scores = dict()
    for word in words:
        if word not in scores:
            similarity = model.similarity(word, keyword)
            scores[word] = similarity
    return scores


def find_matches(words: list[str], keyword: str, model: KeyedVectors, threshold: float) -> list[str]:
    matches = []
    for word in words:
        similarity = model.similarity(word, keyword)
        if similarity > threshold:
            matches.append(word)
    return matches
