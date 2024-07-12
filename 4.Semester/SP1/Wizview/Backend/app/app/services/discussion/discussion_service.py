"""
This module defines class DiscussionService that work with Discussion
"""
from datetime import datetime
from typing import Annotated, Type
from uuid import UUID
from fastapi import Depends

import crud
import models
import schemas
from db import get_db

from services import AbstractDiscussionService
from sqlalchemy.orm import Session


class DiscussionService(AbstractDiscussionService):
    """
    Class DiscussionService represent service that work with Discussion
    """

    def __init__(self, db: Annotated[Session, Depends(get_db)]):
        self.document_crud = crud.Document(db)
        super().__init__(crud.Discussion(db))

    def update(self, uuid: UUID,
               obj_in: schemas.DiscussionUpdate) ->\
            models.Discussion | None:
        obj_to_update = self.get(uuid)
        if obj_to_update is None:
            return None
        discussion_update = schemas.utils.as_dict(obj_in)
        if obj_in.state == models.DiscussionState.RESOLVED:
            discussion_update['resolved_at'] = datetime.utcnow()
        return self.crud.update(db_obj=obj_to_update, obj_in=discussion_update)

    def get_by_document_uuid_all(self, document_uuid: UUID) -> list[Type[models.Discussion]] | None:
        return self.crud.get_by_document_uuid_all(document_uuid)

    def get_by_document_uuid_multi(self, document_uuid: UUID, skip: int = 0,
                                   limit: int = 100) -> list[Type[models.Discussion]]:
        return self.crud.get_by_document_uuid_multi(document_uuid, skip, limit)

    def get_by_document_uuid_and_state_all(self, document_uuid: UUID,
                                           state: models.DiscussionState) \
            -> list[Type[models.Discussion]]:
        return self.crud.get_by_document_uuid_and_state_all(document_uuid, state)
