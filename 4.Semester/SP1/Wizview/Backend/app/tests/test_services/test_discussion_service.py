"""
Module for testing comment service
"""
from uuid import uuid4
from services import DiscussionService

import pytest
import models
import schemas
from ..utils import as_dict


# pylint: disable=redefined-outer-name
# reason: using fixtures as variables is a standard for pytest


@pytest.fixture()
def service_discussion(db_session) -> DiscussionService:
    """Return CommentService."""
    return DiscussionService(db=db_session)


@pytest.fixture(scope="module")
def discussion_update() -> schemas.DiscussionUpdate:
    """Return update_schema_data for comment."""
    return schemas.DiscussionUpdate(
        state=models.DiscussionState.RESOLVED
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


def create_discussion(service_discussion,
                      document_create,
                      discussion_create) -> models.Discussion:
    """
    Additional function for creating a discussion
    """
    doc_in_db = service_discussion.document_crud.create(document_create)
    discussion_create.document_uuid = doc_in_db.uuid
    discussion_in_db = service_discussion.create(discussion_create)
    assert discussion_in_db is not None
    assert discussion_in_db.document is not None
    assert discussion_in_db.document_uuid is not None
    return discussion_in_db


def test_create(service_discussion,
                document_create,
                discussion_create):
    """
    Test for create method in DiscussionService
    """
    create_discussion(service_discussion,
                      document_create,
                      discussion_create)


def test_get_created_discussion(service_discussion,
                                document_create,
                                discussion_create):
    """
    Test for get method in DiscussionService
    """
    discussion_in_db = create_discussion(service_discussion,
                                         document_create,
                                         discussion_create)

    db_obj = service_discussion.get(discussion_in_db.uuid)
    assert db_obj is not None


def test_delete_created_discussion(service_discussion,
                                   document_create,
                                   discussion_create):
    """
    Test for remove method in DiscussionService
    """
    discussion_in_db = create_discussion(service_discussion,
                                         document_create,
                                         discussion_create)

    db_obj_removed = service_discussion.remove(discussion_in_db.uuid)
    assert discussion_in_db == db_obj_removed


def test_delete_nonexistent_discussion(service_discussion,
                                       document_create,
                                       discussion_create):
    """
    Test for remove method in DiscussionService
    for nonexistent discussion
    """
    discussion_in_db = create_discussion(service_discussion,
                                         document_create,
                                         discussion_create)

    db_obj_removed = service_discussion.remove(discussion_in_db.uuid)
    assert db_obj_removed is not None

    db_obj_removed = service_discussion.remove(discussion_in_db.uuid)
    assert db_obj_removed is None

    db_obj_removed = service_discussion.remove(None)
    assert db_obj_removed is None


def test_update(service_discussion,
                document_create,
                discussion_create,
                discussion_update):
    """
    Test for update method in DiscussionService
    """
    discussion_in_db = create_discussion(service_discussion,
                                         document_create,
                                         discussion_create)

    db_obj_to_update = service_discussion.get(discussion_in_db.uuid)
    db_obj_updated = service_discussion.update(db_obj_to_update.uuid, discussion_update)

    # only for testing
    discussion_update.crosslink = db_obj_updated.crosslink

    db_obj_updated_data = as_dict(db_obj_updated)

    for field, value in discussion_update:
        assert db_obj_updated_data[field] == value
    for field, value in discussion_create:
        if field not in discussion_update.dict():
            assert db_obj_updated_data[field] == value


def test_get_by_document_uuid_all(service_discussion,
                                  document_create,
                                  discussion_create):
    """
    Test for get_by_document_uuid_all method in DiscussionService
    """
    doc_in_db = service_discussion.document_crud.create(document_create)
    discussion_create.document_uuid = doc_in_db.uuid

    nr_of_discussion = 3
    discussions = []
    for _ in range(nr_of_discussion):
        discussions.append(service_discussion.create(discussion_create))
    assert doc_in_db is not None
    assert doc_in_db.discussions != []

    discussion_list = service_discussion.get_by_document_uuid_all(doc_in_db.uuid)
    assert len(discussion_list) == nr_of_discussion
    for diss_id, discussion in enumerate(discussion_list):
        assert discussion == discussions[diss_id]
