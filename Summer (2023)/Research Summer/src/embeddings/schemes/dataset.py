from pydantic import BaseModel


class KeywordData(BaseModel):
    keyword: str
    matches: set[tuple[str, int]]
    

class Case(BaseModel):
    case_id: int
    text: str
    keywords: list[KeywordData]


class Dataset(BaseModel):
    cases: list[Case]
