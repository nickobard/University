"""
Module for testing comment crud
"""
import pytest

import crud
import schemas
import models


# Using fixtures as variables is a standard for pytest
# pylint: disable=redefined-outer-name

@pytest.fixture()
def comment_crud(db_session):
    """Return comment crud."""
    return crud.Comment(db=db_session)


@pytest.fixture()
def document(db_session):
    """Return new document in DB."""
    create_schema = schemas.DocumentCreate(
        title="title",
        doc_type=models.DocumentType.HTML,
        content="Test content"
    )

    document_crud = crud.Document(db=db_session)
    return document_crud.create(create_schema)


@pytest.fixture()
def discussion(db_session, document):
    """Return new discussion in DB."""
    test_crosslink = schemas.Crosslink(
        start_index=0,
        end_index=1,
        element_ids=[]
    )
    create_schema = schemas.DiscussionCreate(
        crosslink=test_crosslink,
        document_uuid=document.uuid
    )
    discussion_crud = crud.Discussion(db=db_session)
    return discussion_crud.create(create_schema)


@pytest.fixture()
def comment_create(discussion) -> schemas.CommentCreate:
    """Return new comment."""
    return schemas.CommentCreate(
        discussion_uuid=discussion.uuid,
        content="Test comment create"
    )


def test_create_comment(comment_crud, comment_create):
    """test creating comment"""
    comment = comment_crud.create(obj_in=comment_create)
    assert comment is not None
    assert comment.discussion_uuid is not None


def test_get_created_comment(comment_crud, comment_create):
    """test getting created comment"""
    comment = comment_crud.create(obj_in=comment_create)
    db_comment = comment_crud.get(comment.uuid)
    assert db_comment is not None


def test_delete_comment(comment_crud, comment_create):
    """test deleting document"""
    comment = comment_crud.create(obj_in=comment_create)
    removed_comment = comment_crud.remove(comment.uuid)
    assert removed_comment is not None
    assert removed_comment.uuid == comment.uuid


def test_get_by_discussion_uuid_all(comment_crud, comment_create):
    """test getting comments by discussion_uuid"""
    comments = [comment_crud.create(obj_in=comment_create) for _ in range(5)]
    retrieved_comments = comment_crud.get_by_discussion_uuid_all(comment_create.discussion_uuid)
    assert len(retrieved_comments) == 5
    assert all(comment.uuid in [c.uuid for c in retrieved_comments] for comment in comments)


def test_create_reply_comment(comment_crud, comment_create, discussion):
    """testing creating reply comment"""
    parent_comment = comment_crud.create(obj_in=comment_create)
    child_comment_create = schemas.CommentCreate(
        content="This is a child comment.",
        discussion_uuid=discussion.uuid,
        replied_comment_uuid=parent_comment.uuid
    )
    child_comment = comment_crud.create(obj_in=child_comment_create)

    assert child_comment.replied_comment_uuid == parent_comment.uuid


"""
Im not sure how should this work.

def test_delete_comment_replied_comment(comment_crud, comment_create, discussion):
    parent_comment = comment_crud.create(obj_in=comment_create)
    child_comment_create = schemas.CommentCreate(
        content="This is a child comment.",
        discussion_uuid=discussion.uuid,
        replied_comment_uuid=parent_comment.uuid
    )
    child_comment = comment_crud.create(obj_in=child_comment_create)
    removed_parent_comment = comment_crud.remove(parent_comment.uuid)

    assert removed_parent_comment is not None
    assert removed_parent_comment == parent_comment
    assert child_comment is not None
    assert child_comment.replied_comment_uuid is None
    assert child_comment.replied_comment is None
"""
