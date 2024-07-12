"""
This module defines class DiscussionService that work with Discussion
"""
from datetime import datetime
from typing import Annotated, Type
from uuid import UUID
from fastapi import Depends
from sqlalchemy.orm import Session
from db import get_db
import crud
import schemas

import models.document

from services import AbstractCommentService


class CommentService(AbstractCommentService):
    """
    Class CommentService represent service that work with Comment
    """

    def __init__(self, db: Annotated[Session, Depends(get_db)]):
        self.document_crud = crud.Document(db)
        self.discussion_crud = crud.Discussion(db)
        super().__init__(crud.Comment(db))

    def create_comment(self, comment: schemas.CommentCreate,
                       discussion: schemas.DiscussionCreate | None)\
            -> models.Comment | None:
        if discussion is not None:
            discussion_in_db = self.discussion_crud.create(obj_in=discussion)
            comment.discussion_uuid = discussion_in_db.uuid

        if comment.discussion_uuid is None:
            return None

        return self.crud.create(obj_in=comment)

    def update(self, uuid: UUID,
               obj_in: schemas.CommentUpdate) -> \
            models.Comment | None:
        obj_to_update = self.get(uuid)
        if obj_to_update is None:
            return None
        comment_update = schemas.utils.as_dict(obj_in)
        comment_update['last_edited_at'] = datetime.utcnow()
        return self.crud.update(db_obj=obj_to_update, obj_in=comment_update)

    def get_by_discussion_uuid_all(self, discussion_uuid: UUID) -> list[Type[models.Comment]]:
        return self.crud.get_by_discussion_uuid_all(discussion_uuid)

    def get_by_discussion_uuid_multi(self, discussion_uuid: UUID,
                                     skip: int = 0, limit: int = 100) -> list[Type[models.Comment]]:
        return self.crud.get_by_discussion_uuid_multi(discussion_uuid, skip, limit)
