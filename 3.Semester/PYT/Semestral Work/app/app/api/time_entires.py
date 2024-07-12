from typing import List

from fastapi import APIRouter, Depends, HTTPException, status

import schemas
from services import TimeEntryService

router = APIRouter()


@router.get("/", response_model=List[schemas.TimeEntry])
def get_time_entries_multi(
        skip: int = 0,
        limit: int = 100,
        service: TimeEntryService = Depends(TimeEntryService)):
    entries = service.get_time_entries_multi(skip=skip, limit=limit)
    if len(entries) == 0:
        raise HTTPException(status_code=status.HTTP_404_NOT_FOUND,
                            detail="No time entry")
    return entries


@router.post("/", response_model=schemas.TimeEntry)
def get_all_time_entries(
        create_entry: schemas.TimeEntryCreateClosed,
        service: TimeEntryService = Depends(TimeEntryService)):
    created = service.create_closed_time_entry(create_entry)
    return created


@router.delete("/", response_model=List[schemas.TimeEntry])
def delete_time_entries_multi(
        entries_ids: List[int],
        service: TimeEntryService = Depends(TimeEntryService)
):
    deleted_entries = service.delete_time_entries(entries_ids)
    return deleted_entries


@router.put("/{entry_id}", response_model=schemas.TimeEntry)
def update_time_entry_by_id(
        entry_id: int,
        update_entry: schemas.TimeEntryUpdate,
        service: TimeEntryService = Depends(TimeEntryService)
):
    updated = service.update_time_entry(entry_id, update_entry)
    if updated is None:
        raise HTTPException(status_code=status.HTTP_404_NOT_FOUND,
                            detail=f"Not found entry with id {entry_id}")
    return updated


@router.delete("/{entry_id}", response_model=schemas.TimeEntry)
def delete_time_entry_by_id(
        entry_id: int,
        service: TimeEntryService = Depends(TimeEntryService)
):
    deleted = service.delete_time_entry(entry_id)
    if deleted is None:
        raise HTTPException(status_code=status.HTTP_404_NOT_FOUND,
                            detail=f"Not found entry with id {entry_id}")
    return deleted


@router.get("/running", response_model=schemas.TimeEntry)
def read_running_entry(service: TimeEntryService = Depends(TimeEntryService)):
    running_entry = service.crud.get_first_running_entry()
    if running_entry is None:
        raise HTTPException(status_code=status.HTTP_404_NOT_FOUND,
                            detail="No running time entry")
    return running_entry


@router.post("/running", response_model=schemas.TimeEntry)
def create_running_time_entry(
        *,
        service: TimeEntryService = Depends(TimeEntryService),
        entry_in: schemas.TimeEntryCreateOpened
):
    if service.has_running_time_entry():
        raise HTTPException(status_code=status.HTTP_409_CONFLICT,
                            detail="Already exists running time entry")
    return service.start_new_running_entry(entry_in)


@router.put("/running/stop", response_model=schemas.TimeEntry)
def stop_running_time_entry(entry_close: schemas.TimeEntryClose,
                            service: TimeEntryService = Depends(TimeEntryService)
                            ):
    if not service.has_running_time_entry():
        raise HTTPException(status_code=status.HTTP_400_BAD_REQUEST,
                            detail="There is no running time entry")
    return service.stop_running_entry(entry_close=entry_close)
