import pytest
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
from fastapi.testclient import TestClient

from db.base_class import Base
from db.session import get_db
from main import app
from models import TimeEntry

SQLALCHEMY_DATABASE_URL = "sqlite:///./test.db"

engine = create_engine(
    SQLALCHEMY_DATABASE_URL, connect_args={"check_same_thread": False}
)
TestingSessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=engine)

Base.metadata.create_all(bind=engine)


def override_get_db():
    db = TestingSessionLocal()
    try:
        yield db
    finally:
        db.close()


@pytest.fixture(scope="module")
def testing_db():
    db = TestingSessionLocal()
    try:
        yield db
    finally:
        db.close()


@pytest.fixture(scope="module")
def setup(testing_db):
    testing_db.query(TimeEntry).delete()
    testing_db.commit()
    yield
    # teardown
    testing_db.query(TimeEntry).delete()
    testing_db.commit()


app.dependency_overrides[get_db] = override_get_db
client = TestClient(app)


def test_getting_nonexistent_running_entry(setup):
    response = client.get("/api/entries/running")
    assert response.status_code == 404
    assert response.json() == {"detail": "No running time entry"}


def test_getting_nonexistent_entries(setup):
    response = client.get("/api/entries")
    assert response.status_code == 404
    assert response.json() == {"detail": "No time entry"}


def test_starting_and_stopping_time_entry():
    response = client.post("/api/entries/running", json={})
    assert response.status_code == 200
    assert response.json()['id'] == 1
    assert response.json()['title'] is None
    assert response.json()['datetime_start'] is not None
    assert response.json()['datetime_end'] is None

    response = client.put("/api/entries/running/stop", json={})
    assert response.status_code == 200
    assert response.json()['id'] == 1
    assert response.json()['title'] is None
    assert response.json()['datetime_start'] is not None
    assert response.json()['datetime_end'] is not None

    response = client.get("/api/entries/running")
    assert response.status_code == 404
    assert response.json()['detail'] == "No running time entry"
