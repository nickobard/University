"""Module for unit testing documents controllers."""
from uuid import UUID, uuid4
from datetime import datetime

import pytest
from fastapi import FastAPI
from fastapi.encoders import jsonable_encoder
from fastapi.testclient import TestClient

import models
from core import settings
from api.documents import router
from services import DocumentService

app = FastAPI()
app.include_router(router)


@pytest.fixture(name="client", scope="module")
def fastapi_client():
    """Return app TestClient."""
    return TestClient(app)


MODELS = [
    models.Document(
        uuid=uuid4(),
        uuid_submission=uuid4(),
        title="Test document 0",
        content="<html><body>Cau lidi</body></html",
        submitted_at=datetime.utcnow(),
        doc_state=models.DocumentState.OPEN,
        doc_type=models.DocumentType.HTML
    ), models.Document(
        uuid=uuid4(),
        uuid_submission=uuid4(),
        title="Test document 1",
        content="<html><body>Hello people</body></html",
        submitted_at=datetime.utcnow(),
        closed_at=datetime.utcnow(),
        doc_state=models.DocumentState.OPEN,
        doc_type=models.DocumentType.PLAIN_TEXT
    )
]


class DocumentServiceOverride(DocumentService):
    """Overriden DocumentService class for controller unit tests."""

    # pylint: disable=super-init-not-called
    # reason: overriding init to not create db session
    def __init__(self):
        pass

    def submit_document(self, payload: str):
        for doc in MODELS:
            if doc.content == payload:
                return doc
        return None

    def get(self, uuid: UUID):
        for doc in MODELS:
            if doc.uuid == uuid:
                return doc
        return None

    def get_all(self):
        return MODELS


app.dependency_overrides[DocumentService] = DocumentServiceOverride


def assert_document(res_doc: dict, test_doc: models.Document):
    """Assert response DocumentSubmitter dict with tested document.

    :param res_doc: Response document.
    :param test_doc: Tested document.
    """
    assert res_doc['uuid'] == test_doc['uuid']
    assert res_doc['title'] == test_doc['title']
    assert res_doc['doc_type'] == test_doc['doc_type']
    assert res_doc['doc_state'] == test_doc['doc_state']
    assert res_doc['content'] == test_doc['content']
    assert res_doc['submitted_at'] == test_doc['submitted_at']
    assert res_doc['closed_at'] == test_doc.get('closed_at')


def test_submit_document(client: TestClient):
    """Unit test for submit document controller."""
    test_doc_idx = 0
    response = client.post(
        "/documents/submit",
        json=MODELS[test_doc_idx].content
    )
    assert \
        f"{settings.FRONTEND_SUBMITTER_VIEW_PATH}" \
        f"{MODELS[test_doc_idx].uuid}?submission_uuid={MODELS[test_doc_idx].uuid_submission}"\
        == response.json()['location']


def test_get_document(client: TestClient):
    """Unit test for get document controller."""
    test_doc_idx = 0
    response = client.get(f"/documents/{MODELS[test_doc_idx].uuid}")
    assert response.status_code == 200
    assert_document(response.json(), jsonable_encoder(MODELS[test_doc_idx]))


def test_get_all_documents(client: TestClient):
    """Unit test for get all documents controller."""
    response = client.get("/documents")
    assert response.status_code == 200
    for i, res_doc in enumerate(response.json()):
        assert_document(res_doc, jsonable_encoder(MODELS[i]))
