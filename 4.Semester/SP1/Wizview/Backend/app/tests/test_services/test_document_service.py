"""
Module for testing document service
"""
import pytest

from services import DocumentService
from models import Document, DocumentType, DocumentState
from schemas import DocumentCreate, DocumentUpdate
from ..utils import as_dict


# pylint: disable=redefined-outer-name
# reason: using fixtures as variables is a standard for pytest

@pytest.fixture()
def service_document(db_session) -> DocumentService:
    """Return DocumentService."""
    return DocumentService(db=db_session)


@pytest.fixture(scope="module")
def document_create() -> DocumentCreate:
    """Return create_schema_data for document."""
    return DocumentCreate(
        title="Good code, bad code.",
        content="<h1>Write always a good code.</h1>",
        doc_type=DocumentType.HTML
    )


@pytest.fixture(scope="module")
def document_update() -> DocumentUpdate:
    """Return update_schema_data for document."""
    return DocumentUpdate(
        title="Message for all coders in the world.",
        doc_state=DocumentState.CLOSED
    )


def open_test_file(path: str) -> str:
    """
    Read testing file for test
    """
    with open(path, 'r', encoding='utf-8') as file:
        content = file.read()
    return content


@pytest.mark.parametrize("path,title", [
    ("test_services/test_data/knowledge_models/common_dsw/"
     "horizone_europe_dmp/DSW_project_name.html",
     "DSW_project_name"),
    ("test_services/test_data/knowledge_models/common_dsw/"
     "questionnaire_report/DSW_project_name.html",
     "DSW_project_name"),
    ("test_services/test_data/knowledge_models/life_sciences_dsw/"
     "horizone_europe_dmp/DSW project name.html",
     "DSW project name"),
    ("test_services/test_data/knowledge_models/life_sciences_dsw/"
     "questionnaire_report/DSW project name.html",
     "DSW project name"),
], ids=["html1", "html2", "html3", "html4"])
def test_document_submission_type_html(service_document, path, title):
    """
    Test for document_submission method in DocumentService for html type
    """
    content = open_test_file(path)
    document = service_document.submit_document(payload=content)
    assert isinstance(document, Document)
    assert document.uuid is not None
    assert document.title == title
    assert document.doc_type == DocumentType.HTML
    assert document.content == content


@pytest.mark.parametrize("path,title", [
    ("test_services/test_data/knowledge_models/common_dsw/"
     "ma_dmp_rda/DSW_project_name.json",
     "DSW_project_name"),
    ("test_services/test_data/knowledge_models/common_dsw/"
     "questionnaire_report/DSW_project_name.json",
     "DSW_project_name"),
    ("test_services/test_data/knowledge_models/life_sciences_dsw/"
     "ma_dmp_rda/DSW project name.json",
     "DSW project name"),
    ("test_services/test_data/knowledge_models/life_sciences_dsw/"
     "questionnaire_report/DSW project name.json",
     "DSW project name"),
], ids=["json1", "json2", "json3", "json4"])
def test_document_submission_type_json(service_document, path, title):
    """
    Test for document_submission method in DocumentService for json type
    """
    content = open_test_file(path)
    document = service_document.submit_document(payload=content)
    assert isinstance(document, Document)
    assert document.uuid is not None
    assert document.title == title
    assert document.doc_type == DocumentType.JSON
    assert document.content == content


def test_create_document(service_document, document_create):
    """
    Test for create method in DocumentService
    """
    obj = service_document.create(obj_in=document_create)
    assert obj is not None


def test_get_created_document(service_document, document_create):
    """
    Test for get method in DocumentService
    """
    obj = service_document.create(obj_in=document_create)
    assert obj is not None

    db_obj = service_document.get(obj.uuid)
    assert db_obj is not None


def test_delete_created_document(service_document, document_create):
    """
    Test for remove method in DocumentService
    """
    db_obj = service_document.create(obj_in=document_create)
    assert db_obj is not None

    db_obj_removed = service_document.remove(db_obj.uuid)

    assert db_obj == db_obj_removed


def test_delete_nonexistent_document(service_document, document_create):
    """
    Test for remove method in DocumentService
    for nonexistent document
    """
    db_obj = service_document.create(obj_in=document_create)
    assert db_obj is not None

    db_obj_removed = service_document.remove(db_obj.uuid)
    assert db_obj_removed is not None
    db_obj_removed = service_document.remove(db_obj.uuid)
    assert db_obj_removed is None
    db_obj_removed = service_document.remove(None)
    assert db_obj_removed is None


def test_update(service_document, document_create, document_update):
    """
    Test for update method in DocumentService
    """
    db_obj_created = service_document.create(obj_in=document_create)

    db_obj_to_update = service_document.get(db_obj_created.uuid)
    db_obj_updated = service_document.update(db_obj_to_update.uuid,
                                             document_update)

    db_obj_updated_data = as_dict(db_obj_updated)

    for field, value in document_update:
        assert db_obj_updated_data[field] == value
    for field, value in document_create:
        if field not in document_update.dict():
            assert db_obj_updated_data[field] == value


def test_get_by_state(service_document, document_create, document_update):
    """
    Testing updating document state and then getting that document by its state.
    """
    document = service_document.create(document_create)
    service_document.update(document.uuid, document_update)
    closed_documents = service_document.get_by_state_all(DocumentState.CLOSED)
    open_documents = service_document.get_by_state_all(DocumentState.OPEN)
    assert len(closed_documents) != 0
    assert any(closed_document.uuid == document.uuid for closed_document in closed_documents)
    assert not any(closed_document.uuid == document.uuid for closed_document in open_documents)
