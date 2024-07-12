"""
This module defines an abstract base class AbstractDiscussionService that work with Discussion
"""

from abc import ABC, abstractmethod
from typing import Type
from uuid import UUID
from services import CrudServiceBase

import models
import schemas
import crud


class AbstractDiscussionService(CrudServiceBase[
                                    models.Discussion,
                                    crud.Discussion,
                                    schemas.DiscussionCreate,
                                    schemas.DiscussionUpdate,
                                ], ABC):
    """
    This abstract class defines the interface for a discussion service
    that provides CRUD operations for a specific DiscussionModel.
    """

    @abstractmethod
    def get_by_document_uuid_all(self, document_uuid: UUID) -> list[Type[models.Discussion]]:
        """
        Retrieves all Discussion instances with the given document_uuid.
        :param document_uuid: The UUID of the Document.
        :return: A list of Discussion instances with the given document_uuid.
        """

    @abstractmethod
    def get_by_document_uuid_multi(self, document_uuid: UUID, skip: int = 0,
                                   limit: int = 100) -> list[Type[models.Discussion]]:
        """
        Retrieves a limited number of Discussion instances with the given document_uuid,
        skipping a specified number of entries.
        :param document_uuid: The UUID of the Document.
        :param skip: The number of Discussion instances to skip.
        :param limit: The maximum number of Discussion instances to return.
        :return: A list of Discussion instances with the given document_uuid.
        """

    @abstractmethod
    def get_by_document_uuid_and_state_all(self, document_uuid: UUID,
                                           state: models.DiscussionState)\
            -> list[Type[models.Discussion]]:
        """
        Retrieves all Discussion instances with the given document_uuid and given state.
        :param document_uuid: The UUID of the Document.
        :param state: The state of the Discussion
        :return: A list of Discussion instances with the given document_uuid.
        """
