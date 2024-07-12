"""
This module defines an abstract base class AbstractDocumentService that work with Document
"""

from abc import ABC, abstractmethod
from uuid import UUID
from typing import Type

from services import CrudServiceBase

import models
import schemas
import crud


class AbstractDocumentService(CrudServiceBase[
                                  models.Document,
                                  crud.Document,
                                  schemas.DocumentCreate,
                                  schemas.DocumentUpdate
                              ], ABC):
    """
    This abstract class defines the interface for a document service
    that provides CRUD operations for a specific DocumentModel.
    """

    @abstractmethod
    def submit_document(self, payload: str) -> models.Document:
        """
        Submit document from DSW, find out what type of document this is,
        save it to db and return its model.
        :param payload: Unparsed document content.
        :return: DocumentModel.
        """

    @abstractmethod
    def get_by_submission_uuid(self, document_uuid_submission: UUID) -> models.Document | None:
        """
        Get document by its submission uuid.
        :param document_uuid_submission: Submission uuid of the document.
        :return: Document with uuid_submission equal to document_uuid_submission or
        None if no such document exists.
        """

    @abstractmethod
    def get_by_state_all(self, doc_state: models.DocumentState) -> list[Type[models.Document]]:
        """
        Retrieves all Document instances with the given state.
        :param doc_state: The state of the Documents.
        :return: A list of Document instances with the given state.
        """

    @abstractmethod
    def get_by_state_multi(self, doc_state: models.DocumentState,
                           skip: int = 0, limit: int = 100) -> list[Type[models.Document]]:
        """
        Retrieves a limited number of Document instances with the given state,
        skipping a specified number of entries.
        :param doc_state: The state of the Documents.
        :param skip: The number of Document instances to skip.
        :param limit: The maximum number of Document instances to return.
        :return: A list of Document instances.
        """

    @abstractmethod
    def get_by_type_multi(self, doc_type: models.DocumentType,
                          skip: int = 0, limit: int = 100) -> list[Type[models.Document]]:
        """
        Retrieves a limited number of Document instances with the given type,
        skipping a specified number of entries.
        :param doc_type: The type of the Documents.
        :param skip: The number of Document instances to skip.
        :param limit: The maximum number of Document instances to return.
        :return: A list of Document instances.
        """

    @abstractmethod
    def get_by_type_all(self, doc_type: models.DocumentType) -> list[Type[models.Document]]:
        """
        Retrieves all Document instances with the given type.
        :param doc_type: The type of the Documents.
        :return: A list of Document instances with the given type.
        """
