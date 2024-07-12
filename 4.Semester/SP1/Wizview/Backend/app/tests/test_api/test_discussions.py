"""Module for discussions api integration tests."""
from uuid import uuid4, UUID

import pytest
from starlette.testclient import TestClient

from api.discussions import router as discussions_router
from api.comments import router as comments_router
import schemas
from models import DiscussionState
from .test_documents import submit_document


# pylint: disable=redefined-outer-name
# reason: using fixtures as variables is a standard for pytest


@pytest.fixture(scope="module")
def crosslink():
    """Crosslink schema."""
    return schemas.Crosslink(
        start_index=5,
        end_index=7,
        element_ids=["1,2,3"]
    )


@pytest.fixture(scope="module")
def discussion_create_schema(crosslink):
    """Discussion create schema."""
    return schemas.DiscussionCreate(
        document_uuid=uuid4(),
        crosslink=crosslink
    )


@pytest.fixture(scope="module")
def discussion_update_schema():
    """Discussion create schema."""
    return schemas.DiscussionUpdate(
        state=DiscussionState.RESOLVED
    )


@pytest.fixture(scope="module")
def comment_create_schema():
    """Comment create schema of first comment in discussion."""
    return schemas.CommentCreate(
        content="My first comment."
    )


@pytest.fixture(scope="module")
def comment_and_discussion_create_schema(comment_create_schema, discussion_create_schema):
    """CommentAndDiscussion create schema."""
    return schemas.CommentAndDiscussionCreate(
        comment=comment_create_schema,
        discussion=discussion_create_schema
    )


def get_discussion(client: TestClient, uuid: UUID) -> schemas.Discussion | None:
    """Get discussion by uuid and return Discussion schema if successful."""
    response_get = client.get(f"{discussions_router.prefix}/{uuid}")
    return schemas.Discussion(**response_get.json()) if response_get.status_code == 200 else None


def create_comment_and_discussion(
        client: TestClient, comment_and_discussion_create_schema
) -> tuple[UUID, schemas.Comment | None]:
    """Create comment and discussion and return document_uuid and Comment schema if successful."""
    document_uuid = submit_document(client, "Document content")
    comment_and_discussion_create_schema.discussion.document_uuid = document_uuid
    response_create = client.post(
        comments_router.prefix,
        content=comment_and_discussion_create_schema.json(exclude_unset=True)
    )
    return (
        document_uuid,
        schemas.Comment(**response_create.json()) if response_create.status_code == 201 else None
    )


def test_create_comment_and_discussion_and_update_discussion(
        client, comment_and_discussion_create_schema, discussion_update_schema
):
    """Create comment and discussion, update discussion."""
    document_uuid, comment = create_comment_and_discussion(
        client, comment_and_discussion_create_schema
    )
    assert comment is not None
    discussion = get_discussion(client, comment.discussion_uuid)
    assert discussion is not None
    assert discussion.document_uuid == document_uuid
    assert discussion.state == DiscussionState.OPEN
    response_update = client.put(
        f"{discussions_router.prefix}/{discussion.uuid}",
        content=discussion_update_schema.json(exclude_unset=True)
    )
    assert response_update.status_code == 200
    discussion_updated = schemas.Discussion(**response_update.json())
    assert discussion_updated.uuid == discussion.uuid
    assert discussion_updated.document_uuid == document_uuid
    assert discussion_updated.state == discussion_update_schema.state
    if discussion_update_schema.state == DiscussionState.RESOLVED:
        assert discussion_updated.resolved_at is not None
