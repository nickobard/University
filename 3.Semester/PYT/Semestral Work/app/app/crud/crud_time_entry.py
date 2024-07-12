from typing import List, Any, Dict

from fastapi import Depends
from fastapi.encoders import jsonable_encoder
from sqlalchemy.orm import Session

import schemas
from db.session import get_db
from models import TimeEntry


# pylint: disable=locally-disabled

class CRUDTimeEntry:
    def __init__(self, db=Depends(get_db)):
        self.db: Session = db

    def get_time_entry_by_id(self, id_entry: int) -> TimeEntry | None:
        return self.db.query(TimeEntry).get(id_entry)

    def get_time_entries_multi(self, *, skip: int = 0, limit: int = 100) -> List[TimeEntry]:
        return self.db.query(TimeEntry).offset(skip).limit(limit).all()

    def get_first_running_entry(self) -> TimeEntry | None:
        # pylint: disable=singleton-comparison
        # reason: sqlalchemy doesn't work properly otherwise and cannot compare
        # its database model boolean with python boolean using `is` or `not` literals
        return self.db.query(TimeEntry).filter(TimeEntry.closed_entry == False).first()
        # pylint: enable=singleton-comparison

    def get_time_entries_all(self, closed: bool | None = None) -> List[TimeEntry]:
        if closed is not None:
            return self.db.query(TimeEntry).filter(TimeEntry.closed_entry == closed).all()
        return self.db.query(TimeEntry).all()

    def update_time_entry_state(self, *, closed: bool, db_obj: TimeEntry) -> TimeEntry:
        db_obj.closed_entry = closed
        self.db.commit()
        self.db.refresh(db_obj)
        return db_obj

    def update_time_entry_state_multi(self,
                                      *,
                                      closed: bool,
                                      db_objs: List[TimeEntry]) -> List[TimeEntry]:
        for db_obj in db_objs:
            db_obj.closed_entry = closed
        self.db.commit()
        self.db.refresh(db_objs)
        return db_objs

    def update_time_entry_data(self,
                               *,
                               db_obj: TimeEntry,
                               obj_in: schemas.TimeEntryUpdate | Dict[str, Any]
                               ) -> TimeEntry:
        obj_data = jsonable_encoder(db_obj)
        if isinstance(obj_in, dict):
            update_data = obj_in
        else:
            update_data = obj_in.dict(exclude_unset=True)
        for field in obj_data:
            if field in update_data:
                setattr(db_obj, field, update_data[field])
        self.db.commit()
        self.db.refresh(db_obj)
        return db_obj

    def create_time_entry_closed(self, *, time_entry: schemas.TimeEntryCreateClosed) -> TimeEntry:
        db_time_entry = TimeEntry(title=time_entry.title,
                                  datetime_start=time_entry.datetime_start,
                                  datetime_end=time_entry.datetime_end,
                                  closed_entry=True
                                  )
        self.db.add(db_time_entry)
        self.db.commit()
        self.db.refresh(db_time_entry)
        return db_time_entry

    def create_time_entry_opened(self, *, time_entry: schemas.TimeEntryCreateOpened):
        db_time_entry = TimeEntry(title=time_entry.title,
                                  datetime_start=time_entry.datetime_start,
                                  closed_entry=False
                                  )
        self.db.add(db_time_entry)
        self.db.commit()
        self.db.refresh(db_time_entry)
        return db_time_entry

    def delete_time_entry_by_id(self, *, id_entry: int) -> TimeEntry | None:
        db_time_entry = self.db.query(TimeEntry).get(id_entry)
        if db_time_entry is None:
            return None
        self.db.delete(db_time_entry)
        self.db.commit()
        return db_time_entry

    def delete_time_entry_by_id_multi(self, *, id_entries: List[int]) -> List[TimeEntry]:
        db_time_entries = []
        for id_entry in id_entries:
            db_time_entry = self.db.query(TimeEntry).get(id_entry)
            if db_time_entry is None:
                continue
            self.db.delete(db_time_entry)
            db_time_entries.append(db_time_entry)
        self.db.commit()
        return db_time_entries

    @staticmethod
    def is_running(db_obj: TimeEntry) -> bool:
        return db_obj.closed_entry is False

    @staticmethod
    def is_closed(db_obj: TimeEntry) -> bool:
        return not CRUDTimeEntry.is_running(db_obj)
