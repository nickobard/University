"""
This module defines class DocumentService that work with Document
"""
from datetime import datetime
from typing import Annotated, Type
from uuid import UUID
from fastapi import Depends

import crud
import models
import schemas
from db import get_db

from services import AbstractDocumentService
from services.document.document_service_parser import DocumentServiceParser
from sqlalchemy.orm import Session


class DocumentService(AbstractDocumentService):
    """
    Class DocumentService represent service that work with Document
    """

    def __init__(self, db: Annotated[Session, Depends(get_db)]):
        super().__init__(crud.Document(db))

    def submit_document(self, payload: str) -> models.Document:
        parser = DocumentServiceParser()
        doc_type = parser.get_type(payload)
        title = parser.parse(payload, doc_type)

        doc_create = schemas.DocumentCreate(
            title=title,
            doc_type=doc_type,
            content=payload
        )

        doc_in_db = self.crud.create(obj_in=doc_create)
        return doc_in_db

    def update(self, uuid: UUID,
               obj_in: schemas.DocumentUpdate) -> models.Document | None:
        obj_to_update = self.get(uuid)
        if obj_to_update is None:
            return None

        document_update = schemas.utils.as_dict(obj_in)
        if obj_in.doc_state == models.DocumentState.CLOSED and \
                obj_to_update.doc_state == models.DocumentState.OPEN:
            document_update['closed_at'] = datetime.utcnow()

        if obj_in.doc_state == models.DocumentState.OPEN:
            document_update['closed_at'] = None

        return self.crud.update(db_obj=obj_to_update, obj_in=document_update)

    def get_by_submission_uuid(self, document_uuid_submission: UUID) -> models.Document | None:
        return self.crud.get_by_submission_uuid(document_uuid_submission)

    def get_by_state_all(self, doc_state: models.DocumentState) -> list[Type[models.Document]]:
        return self.crud.get_by_state_all(doc_state)

    def get_by_state_multi(self, doc_state: models.DocumentState,
                           skip: int = 0, limit: int = 100) -> list[Type[models.Document]]:
        return self.crud.get_by_state_multi(doc_state, skip, limit)

    def get_by_type_multi(self, doc_type: models.DocumentType,
                          skip: int = 0, limit: int = 100) -> list[Type[models.Document]]:
        return self.crud.get_by_type_multi(doc_type, skip, limit)

    def get_by_type_all(self, doc_type: models.DocumentType) -> list[Type[models.Document]]:
        return self.crud.get_by_type_all(doc_type)
