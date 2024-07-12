from db.base_class import Base
from sqlalchemy import Column, Integer, String, DateTime, Boolean


# pylint: disable=locally-disabled

# pylint: disable=too-few-public-methods
# reason: sqlalchemy model does not need methods, but should be a class
class TimeEntry(Base):
    __tablename__ = "time_entries"

    id = Column(Integer, primary_key=True, index=True)
    title = Column(String, nullable=True)
    datetime_start = Column(DateTime, nullable=False)
    datetime_end = Column(DateTime, nullable=True)
    closed_entry = Column(Boolean, index=True, nullable=False, default=False)
