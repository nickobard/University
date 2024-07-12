"""
API controllers for comments.
"""
from uuid import UUID
from typing import Any, Annotated

from fastapi import APIRouter, Depends, status, responses, Body, Path

import schemas
from api import utils
from services import CommentService

router = APIRouter(
    prefix='/comments',
    tags=[utils.fastapi_docs.COMMENT_TAG['name']]
)


@router.post("/",
             response_model=schemas.Comment,
             responses={
                 400: {"model": utils.Message, "description": "Couldn't create comment."},
             },
             status_code=status.HTTP_201_CREATED,
             description="""
If **discussion is passed** - Create a discussion and a comment to document with 
    uuid equal to discussion.document_uuid.

If **discussion is None** - Add comment to discussion with uuid equal to
    comment.discussion_uuid.
"""
             )
async def post_comment(service: Annotated[CommentService, Depends(CommentService)],
                       comment_and_discussion: schemas.CommentAndDiscussionCreate) -> Any:
    """
    If **discussion is passed** - Create a discussion and a comment to document
        with uuid equal to discussion.document_uuid.

    If **discussion is None** - Add comment to discussion with uuid equal to
        comment.discussion_uuid.

    :param service: Comment service.
    :param comment_and_discussion: CommentCreate schema and voluntary DiscussionCreate schema.
    """
    comment = service.create_comment(
        comment_and_discussion.comment, comment_and_discussion.discussion
    )
    if not comment:
        return responses.JSONResponse(
            status_code=status.HTTP_400_BAD_REQUEST,
            content={
                'message': "Could not create comment, probably due to invalid "
                           "discussion_uuid or document_uuid."
            }
        )
    return comment


@router.put("/{comment_uuid}",
            response_model=schemas.Comment,
            status_code=status.HTTP_200_OK,
            responses={
                **utils.EntityNotFoundException.RESPONSE,
            })
async def update_comment(service: Annotated[CommentService, Depends(CommentService)],
                         comment_uuid: Annotated[UUID, Path()],
                         comment: Annotated[schemas.CommentUpdate, Body()]) -> Any:
    """
    Update comment with uuid equal to comment_uuid.

    :param service: Comment service.
    :param comment_uuid: id of the comment.
    :param comment: CommentUpdate schema.
    """
    comment = service.update(comment_uuid, comment)
    if not comment:
        raise utils.EntityNotFoundException(utils.Entity.COMMENT, comment_uuid)
    return comment
