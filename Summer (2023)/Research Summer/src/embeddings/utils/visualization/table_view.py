import pandas as pd
from schemes import CaseMetrics, KeywordMetrics, CategoryMetrics


class TableView:
    def __init__(
        self,
        show_keywords_total: bool = False,
        show_categories_total: bool = False,
        show_cases_total: bool = True,
    ) -> None:
        self.table: pd.DataFrame | None = None
        self.show_keywords_total: bool = show_keywords_total
        self.show_categories_total: bool = show_categories_total
        self.show_cases_total: bool = show_cases_total

    def set_show_properties(
        self,
        show_keywords_total: bool = False,
        show_categories_total: bool = False,
        show_cases_total: bool = True,
    ) -> None:
        self.show_keywords_total: bool = show_keywords_total
        self.show_categories_total: bool = show_categories_total
        self.show_cases_total: bool = show_cases_total

    def create_cases_table_view(self, cases: list[CaseMetrics]) -> pd.DataFrame:
        self.table = pd.DataFrame(
            columns=[
                "Case ID",
                "Category",
                "Keyword",
                "Precision",
                "Recall",
                "F-Score",
                "Accuracy",
            ]
        )

        for case in cases:
            for category in case.categories:
                for keyword in category.keywords:
                    self.append_keyword_metrics(keyword, category, case)
                if self.show_keywords_total:
                    self.append_category_metrics(category, case)
            if self.show_categories_total:
                self.append_case_metrics(case)
        self.table.set_index(["Case ID", "Category", "Keyword"], inplace=True)
        return self.table

    def append_keyword_metrics(
        self, keyword: KeywordMetrics, category: CategoryMetrics, case: CaseMetrics
    ) -> None:
        self.table.loc[len(self.table)] = [
            case.id,
            category.category,
            keyword.keyword,
            keyword.info.metrics.precision,
            keyword.info.metrics.recall,
            keyword.info.metrics.f_score,
            keyword.info.metrics.accuracy,
        ]

    def append_category_metrics(
        self, category: CategoryMetrics, case: CaseMetrics
    ) -> None:
        self.table.loc[len(self.table)] = [
            case.id,
            category.category,
            "Total",
            category.info.metrics.precision,
            category.info.metrics.recall,
            category.info.metrics.f_score,
            category.info.metrics.accuracy,
        ]

    def append_case_metrics(self, case: CaseMetrics) -> None:
        self.table.loc[len(self.table)] = [
            case.id,
            "Total",
            "",
            case.info.metrics.precision,
            case.info.metrics.recall,
            case.info.metrics.f_score,
            case.info.metrics.accuracy,
        ]
