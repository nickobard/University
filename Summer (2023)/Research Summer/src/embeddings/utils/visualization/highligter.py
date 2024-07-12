import re
from schemes import CaseEvaluation, KeywordDataEvaluation
from IPython.display import display, Markdown
import numpy as np
from typing import Callable


class Highlighter:
    def __init__(self, case: CaseEvaluation) -> None:
        self.case: CaseEvaluation = case
        self.highlighted_data: dict[str, str] = dict()

    def reload_case(self, case: CaseEvaluation) -> None:
        self.case = case
        self.highlighted_data = dict()

    def highlight_case(self, show_scores: bool = False) -> None:
        for category_evaluation in self.case.categories:
            for keyword_evaluation in category_evaluation.keywords:
                keyword = keyword_evaluation.keyword
                highlighted_text = self.__highlight_text(
                    self.case.text, keyword_evaluation, show_scores=show_scores
                )
                self.highlighted_data[keyword] = highlighted_text

    def display(self, show_threshold: bool = True) -> None:
        for keyword, highlighted_text in self.highlighted_data.items():
            print(f"Keyword: {keyword}")
            if show_threshold:
                print(f"Threshold: {self.case.threshold}")
            display(Markdown(highlighted_text))
            print()

    def display_by_keyword(self, input_keyword: str) -> None:
        for keyword, highlighted_text in self.highlighted_data.items():
            if keyword == input_keyword:
                print(f"Keyword: {keyword}")
                display(Markdown(highlighted_text))
                print()
                return
        print(f"Keyword {input_keyword} is not found.")

    @staticmethod
    def __highlight_words(
        text: str,
        words_to_highlight: dict[str, float | np.float32],
        wrapper: Callable = lambda word: word,
        show_scores: bool = False,
    ) -> str:
        for word, score in words_to_highlight.items():
            wrapped = wrapper(word)
            if show_scores:
                wrapped += f"<sub>({score:.2f})</sub>"
            text = re.sub(r"\b" + word + r"\b", wrapped, text, flags=re.IGNORECASE)
        return text

    @staticmethod
    def __highlight_text(
        text: str, keyword_data: KeywordDataEvaluation, show_scores: bool = False
    ):
        def TP_wrapper(
            word: str,
        ):
            return (
                '<span style="color:LightGreen; font-weight:bold;">'
                + str.upper(word)
                + "</span>"
            )

        highlighted_text = Highlighter.__highlight_words(
            text, keyword_data.TP, wrapper=TP_wrapper, show_scores=show_scores
        )

        def FP_wrapper(
            word: str,
        ):
            return (
                '<s><span style="color:orange; font-weight:bold;">'
                + str.upper(word)
                + "</span></s>"
            )

        highlighted_text = Highlighter.__highlight_words(
            highlighted_text,
            keyword_data.FP,
            wrapper=FP_wrapper,
            show_scores=show_scores,
        )

        def FN_wrapper(word: str):
            return (
                '<span style="color:LightBlue; font-weight:bold;">' + word + "</span>"
            )

        highlighted_text = Highlighter.__highlight_words(
            highlighted_text,
            keyword_data.FN,
            wrapper=FN_wrapper,
            show_scores=show_scores,
        )
        return highlighted_text
