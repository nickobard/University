from datetime import datetime

from pydantic import BaseModel


# pylint: disable=locally-disabled

# pylint: disable=too-few-public-methods
# reason: pydantic schemas do not need methods, but should be classes

class TimeEntryBase(BaseModel):
    title: str | None = None

    class Config:
        orm_mode = True


class TimeEntry(TimeEntryBase):
    id: int
    datetime_start: datetime
    datetime_end: datetime | None = None
    closed_entry: bool


class TimeEntryClose(TimeEntryBase):
    datetime_end: datetime | None = None


class TimeEntryCreate(TimeEntryBase):
    datetime_start: datetime


class TimeEntryCreateClosed(TimeEntryCreate):
    datetime_end: datetime


class TimeEntryCreateOpened(TimeEntryCreate):
    datetime_start: datetime | None = None
    datetime_end: None = None


class TimeEntryUpdate(TimeEntryBase):
    datetime_start: datetime | None = None
    datetime_end: datetime | None = None
