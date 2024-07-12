"""Utils for API."""
from enum import Enum
from uuid import UUID

from fastapi import status, Request, responses
from fastapi.responses import Response
from pydantic import BaseModel

from core import settings
import models
from services import DocumentService


class Message(BaseModel):
    """Model for response message."""
    message: str


class Entity(Enum):
    """Enum for entity names."""
    DOCUMENT = "Document"
    DISCUSSION = "Discussion"
    COMMENT = "Comment"


# pylint: disable=unused-argument
# reason: Exception handlers require request and exception parameter.

def get_exception_response_detail(status_code: int, desc: str) -> dict:
    """Get exception response detail for openAPI documentation.

    :param status_code: Status code of the exception.
    :param desc: Description of the exception.

    :return dict: Exception response detail.
    """
    return {
        status_code: {
            "model": Message,
            "description": desc
        }
    }


class MethodNotAllowedException(Exception):
    """Exception for not allowed methods."""
    STATUS_CODE = status.HTTP_405_METHOD_NOT_ALLOWED
    DESCRIPTION = "Method not allowed."
    RESPONSE = get_exception_response_detail(STATUS_CODE, DESCRIPTION)

    def __init__(self, entity: Entity):
        self.entity = entity


def method_not_allowed_exception_handler(
        request: Request, exc: MethodNotAllowedException
) -> responses.JSONResponse:
    """Exception handler for MethodNotAllowedException.

    :param request: Request that caused the exception.
    :param exc: The exception.
    """
    return responses.JSONResponse(
        status_code=exc.STATUS_CODE,
        content={
            "message": f"Method {request.method} is not allowed for entity {exc.entity.value}"
        },
    )


class EntityNotFoundException(Exception):
    """Exception for when entity is not found in database."""
    STATUS_CODE = status.HTTP_404_NOT_FOUND
    DESCRIPTION = "Entity not found."
    RESPONSE = get_exception_response_detail(STATUS_CODE, DESCRIPTION)

    def __init__(self, entity: Entity, entity_uuid: UUID):
        self.entity = entity
        self.entity_uuid = entity_uuid


def entity_not_found_exception_handler(
    request: Request, exc: EntityNotFoundException
) -> responses.JSONResponse:
    """Exception handler for EntityNotFoundException.

    :param request: Request that caused the exception.
    :param exc: The exception.
    """
    return responses.JSONResponse(
        status_code=exc.STATUS_CODE,
        content={
            "message": f"Entity {exc.entity.value} with uuid {exc.entity_uuid} was not found."
        },
    )


class NotImplementedException(Exception):
    """Exception for when a functionality is not yet implemented."""
    STATUS_CODE = status.HTTP_501_NOT_IMPLEMENTED
    DESCRIPTION = "Method not implemented."
    RESPONSE = get_exception_response_detail(STATUS_CODE, DESCRIPTION)


def not_implemented_exception_handler(
    request: Request, exc: NotImplementedException
) -> responses.JSONResponse:
    """Exception handler for NotImplementedException.

    :param request: Request that caused the exception.
    :param exc: The exception.
    """
    return responses.JSONResponse(
        status_code=exc.STATUS_CODE,
        content={
            "message": exc.DESCRIPTION
        },
    )

# pylint: enable=unused-argument


# pylint: disable=too-few-public-methods
# reason: no more public methods needed.
class DSWRequest:
    """Validate request token, get data from request and return response to DSW."""

    def __init__(self, service: DocumentService, content: str):
        self.service = service
        self.content = content

    def validate_and_submit_document(self) -> Response:
        """Validate request token, get data from request and return response to DSW."""
        if not self.__validate_token():
            return responses.PlainTextResponse(
                status_code=status.HTTP_401_UNAUTHORIZED,
                content='Unauthorized submission request.\n\n'
                        'The submission service is not configured properly.\n'
            )
        self.__get_request_data()
        return responses.JSONResponse(
            status_code=status.HTTP_201_CREATED,
            headers={
                'Location': self.location,
            },
            content={
                'location': self.location,
            }
        )

    def __validate_token(self) -> bool:
        """
        Validates DSW request token.

        :return: True if token valid, False otherwise.
        """
        # TODO - validate request token.
        return True

    def __get_request_data(self) -> None:
        """
        Get data from DSW request.

        :return: None.
        """
        self.document = self.service.submit_document(str(self.content))
        self.location = f'{settings.FRONTEND_SUBMITTER_VIEW_PATH}{self.document.uuid}' \
                        f'?submission_uuid={self.document.uuid_submission}'


class FastApiDocs:
    """Information for fastapi documentation."""
    NAME = "Data Stewardship Review"
    DESCRIPTION = """Data Stewardship Review API is a **REST API** that offers you an access to
    our application's documents, discussions, comments and more!"""
    VERSION = "1.0.0"
    DOCUMENT_TAG = {
        "name": "documents",
        "description": "Operations with documents. The POST operation is customized to "
                       "work with sharing a document from DSW.",
    }
    DISCUSSION_TAG = {
        "name": "discussions",
        "description": "Operations with discussions.",
    }
    COMMENT_TAG = {
        "name": "comments",
        "description": "Operations with comments. POST method can also create a Discussion.",
    }

    def get_tags_metadata(self):
        """Get tags metadata."""
        return [
            self.DOCUMENT_TAG,
            self.DISCUSSION_TAG,
            self.COMMENT_TAG
        ]


fastapi_docs = FastApiDocs()

# pylint: enable=too-few-public-methods
