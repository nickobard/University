"""
Module for testing comment service
"""
from uuid import uuid4
from services import CommentService

import pytest

import models
import schemas
from ..utils import as_dict


# pylint: disable=redefined-outer-name
# reason: using fixtures as variables is a standard for pytest


@pytest.fixture()
def service_comment(db_session) -> CommentService:
    """Return CommentService."""
    return CommentService(db=db_session)


@pytest.fixture(scope="module")
def comment_update() -> schemas.CommentUpdate:
    """Return update_schema_data for comment."""
    return schemas.CommentUpdate(
        content="Message for all coders in the world."
    )


@pytest.fixture
def document_create() -> schemas.DocumentCreate:
    """Return document_create for document."""
    return schemas.DocumentCreate(
        title="title",
        doc_type=models.DocumentType.HTML,
        content="Test content"
    )


@pytest.fixture
def discussion_create() -> schemas.DiscussionCreate:
    """Return discussion_create for discussion."""
    test_crosslink = schemas.Crosslink(
        start_index=0,
        end_index=1,
        element_ids=[]
    )

    return schemas.DiscussionCreate(
        crosslink=test_crosslink,
        document_uuid=uuid4()
    )


@pytest.fixture
def comment_create() -> schemas.CommentCreate:
    """Return comment_create for comment."""
    return schemas.CommentCreate(
        discussion_uuid=None,
        content="Test comment create"
    )


def create_comment(service_comment,
                   document_create,
                   discussion_create,
                   comment_create) -> models.Comment:
    """
    Additional function for creating a comment
    """
    doc_in_db = service_comment.document_crud.create(document_create)
    discussion_create.document_uuid = doc_in_db.uuid
    com_in_db = service_comment.create_comment(comment_create, discussion_create)
    assert com_in_db is not None
    assert com_in_db.discussion is not None
    assert com_in_db.discussion_uuid is not None
    return com_in_db


def test_comment_create_with_new_discussion(service_comment,
                                            document_create,
                                            discussion_create,
                                            comment_create):
    """
    Test for comment_create method in CommentService
    with create new discussion
    """
    create_comment(service_comment, document_create,
                   discussion_create, comment_create)


def test_comment_create_with_exist_discussion(service_comment,
                                              document_create,
                                              discussion_create,
                                              comment_create):
    """
    Test for comment_create method in CommentService
    with exist discussion
    """
    com_in_db = create_comment(service_comment, document_create,
                               discussion_create, comment_create)
    comment_create.discussion_uuid = com_in_db.discussion_uuid
    new_com_in_db = service_comment.create_comment(comment_create, None)
    assert new_com_in_db is not None
    assert new_com_in_db.discussion is not None
    assert new_com_in_db.discussion_uuid is not None


def test_get_created_comment(service_comment,
                             document_create,
                             discussion_create,
                             comment_create):
    """
    Test for get method in CommentService
    """
    com_in_db = create_comment(service_comment, document_create,
                               discussion_create, comment_create)

    db_obj = service_comment.get(com_in_db.uuid)
    assert db_obj is not None


def test_delete_created_comment(service_comment,
                                document_create,
                                discussion_create,
                                comment_create):
    """
    Test for remove method in CommentService
    """
    com_in_db = create_comment(service_comment, document_create,
                               discussion_create, comment_create)

    db_obj_removed = service_comment.remove(com_in_db.uuid)
    assert com_in_db == db_obj_removed


def test_delete_nonexistent_comment(service_comment,
                                    document_create,
                                    discussion_create,
                                    comment_create):
    """
    Test for remove method in CommentService
    for nonexistent comment
    """
    com_in_db = create_comment(service_comment, document_create,
                               discussion_create, comment_create)

    db_obj_removed = service_comment.remove(com_in_db.uuid)
    assert db_obj_removed is not None

    db_obj_removed = service_comment.remove(com_in_db.uuid)
    assert db_obj_removed is None

    db_obj_removed = service_comment.remove(None)
    assert db_obj_removed is None


def test_update(service_comment,
                document_create,
                discussion_create,
                comment_create,
                comment_update):
    """
    Test for update method in CommentService
    """
    com_in_db = create_comment(service_comment, document_create,
                               discussion_create, comment_create)
    comment_create.discussion_uuid = com_in_db.discussion_uuid
    new_com_in_db = service_comment.create_comment(comment_create, None)
    assert new_com_in_db is not None
    assert new_com_in_db.discussion is not None
    assert new_com_in_db.discussion_uuid is not None

    db_obj_to_update = service_comment.get(com_in_db.uuid)
    db_obj_updated = service_comment.update(db_obj_to_update.uuid, comment_update)

    db_obj_updated_data = as_dict(db_obj_updated)

    for field, value in comment_update:
        assert db_obj_updated_data[field] == value
    for field, value in comment_create:
        if field not in comment_update.dict():
            assert db_obj_updated_data[field] == value


def test_get_by_discussion_uuid_all(service_comment,
                                    document_create,
                                    discussion_create,
                                    comment_create):
    """
    Test for get_by_discussion_uuid_all method in CommentService
    """
    doc_in_db = service_comment.document_crud.create(document_create)
    discussion_create.document_uuid = doc_in_db.uuid
    dis_in_db = service_comment.discussion_crud.create(discussion_create)
    comment_create.discussion_uuid = dis_in_db.uuid

    nr_of_comments = 3
    comments = []
    for _ in range(nr_of_comments):
        comments.append(service_comment.create_comment(comment_create, None))
    assert dis_in_db is not None
    assert dis_in_db.comments != []

    comments_list = service_comment.get_by_discussion_uuid_all(dis_in_db.uuid)
    assert len(comments_list) == nr_of_comments
    for comm_id, comment in enumerate(comments_list):
        assert comment == comments[comm_id]
