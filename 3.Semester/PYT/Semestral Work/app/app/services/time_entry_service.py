from datetime import datetime
from typing import List

from fastapi import Depends

import models
import schemas
from crud.crud_time_entry import CRUDTimeEntry


class TimeEntryService:
    def __init__(self, crud=Depends(CRUDTimeEntry)):
        self.crud: CRUDTimeEntry = crud

    def get_time_entries_multi(self, skip: int = 0, limit: int = 100) -> List[models.TimeEntry]:
        return self.crud.get_time_entries_multi(skip=skip, limit=limit)

    def get_all_time_entries(self, closed: bool = True) -> List[models.TimeEntry]:
        return self.crud.get_time_entries_all(closed=closed)

    def get_running_time_entry(self) -> schemas.TimeEntry:
        return self.crud.get_first_running_entry()

    def start_new_running_entry(self,
                                time_entry: schemas.TimeEntryCreateOpened | None = None
                                ) -> models.TimeEntry | None:
        if self.has_running_time_entry():
            return None
        if time_entry is None:
            return self.crud.create_time_entry_opened(
                time_entry=schemas.TimeEntryCreateOpened(datetime_start=datetime.now()))
        if time_entry.datetime_start is None:
            time_entry.datetime_start = datetime.now()
        return self.crud.create_time_entry_opened(time_entry=time_entry)

    def stop_running_entry(self, entry_close=schemas.TimeEntryClose()) -> models.TimeEntry | None:
        db_obj = self.crud.get_first_running_entry()
        if db_obj is None:
            return None
        if entry_close.datetime_end is None:
            datetime_end = datetime.now()
        else:
            datetime_end = entry_close.datetime_end
        self.crud.update_time_entry_state(db_obj=db_obj, closed=True)
        self.crud.update_time_entry_data(db_obj=db_obj, obj_in={"datetime_end": datetime_end})
        return db_obj

    def update_running_entry(self, time_entry: schemas.TimeEntryUpdate) -> models.TimeEntry:
        db_obj = self.crud.get_first_running_entry()
        return self.crud.update_time_entry_data(db_obj=db_obj, obj_in=time_entry)

    def update_time_entry(self,
                          id_entry: int,
                          time_entry: schemas.TimeEntryUpdate) -> models.TimeEntry | None:
        db_obj = self.crud.get_time_entry_by_id(id_entry)
        if db_obj is None:
            return None
        return self.crud.update_time_entry_data(db_obj=db_obj, obj_in=time_entry)

    def get_time_entries_count(self, closed: bool | None = None) -> int:
        return len(self.crud.get_time_entries_all(closed=closed))

    def has_running_time_entry(self) -> bool:
        if self.crud.get_first_running_entry() is None:
            return False
        return True

    def delete_time_entries(self, to_delete: List[int]) -> List[models.TimeEntry]:
        return self.crud.delete_time_entry_by_id_multi(id_entries=to_delete)

    def delete_time_entry(self, entry_to_delete: int) -> models.TimeEntry:
        return self.crud.delete_time_entry_by_id(id_entry=entry_to_delete)

    def create_closed_time_entry(self,
                                 create_entry: schemas.TimeEntryCreateClosed
                                 ) -> models.TimeEntry:
        return self.crud.create_time_entry_closed(time_entry=create_entry)
