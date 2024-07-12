"""
API controllers for discussions.
"""
from uuid import UUID
from typing import List, Any, Annotated

from fastapi import APIRouter, Depends, status, Query, Path, Body

import schemas
from api import utils
from services import DiscussionService

router = APIRouter(
    prefix='/discussions',
    tags=[utils.fastapi_docs.DISCUSSION_TAG['name']]
)


@router.get("/",
            response_model=List[schemas.Discussion],
            responses={
                **utils.EntityNotFoundException.RESPONSE,
            },
            status_code=status.HTTP_200_OK)
async def get_document_discussions(
        service: Annotated[DiscussionService, Depends(DiscussionService)],
        document_uuid: Annotated[UUID, Query()]
) -> Any:
    """
    Get all discussions containing comments of document with uuid equal to document_uuid.

    :param service: Discussion service.
    :param document_uuid: uuid of the document.
    """
    discussions = service.get_by_document_uuid_all(document_uuid)
    if discussions is None:
        raise utils.EntityNotFoundException(utils.Entity.DOCUMENT, document_uuid)
    return discussions


@router.get("/{discussion_uuid}",
            response_model=schemas.Discussion,
            responses={
                **utils.EntityNotFoundException.RESPONSE,
            },
            status_code=status.HTTP_200_OK)
async def get_discussion(
        service: Annotated[DiscussionService, Depends(DiscussionService)],
        discussion_uuid: Annotated[UUID, Path()]
) -> Any:
    """
    Get discussion with uuid equal to discussion_uuid.

    :param service: Discussion service.
    :param discussion_uuid: uuid of the discussion.
    """
    discussion = service.get(discussion_uuid)
    if not discussion:
        raise utils.EntityNotFoundException(utils.Entity.DISCUSSION, discussion_uuid)
    return discussion


@router.put("/{discussion_uuid}",
            response_model=schemas.Discussion,
            status_code=status.HTTP_200_OK,
            responses={
                **utils.EntityNotFoundException.RESPONSE,
            })
async def update_discussion(
        service: Annotated[DiscussionService, Depends(DiscussionService)],
        discussion_uuid: Annotated[UUID, Path()],
        discussion: Annotated[schemas.DiscussionUpdate, Body()]
) -> Any:
    """
    Update discussion with uuid equal to discussion_uuid.

    :param service: Discussion service.
    :param discussion_uuid: uuid of the discussion.
    :param discussion: Discussion update schema.
    """
    discussion_updated = service.update(discussion_uuid, discussion)
    if not discussion_updated:
        raise utils.EntityNotFoundException(utils.Entity.DISCUSSION, discussion_uuid)
    return discussion_updated
