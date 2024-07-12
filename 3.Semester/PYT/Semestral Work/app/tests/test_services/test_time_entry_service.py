import pytest
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker

from crud import CRUDTimeEntry
from db.base_class import Base
from models import TimeEntry
from schemas import TimeEntryCreateOpened
from services import TimeEntryService

SQLALCHEMY_DATABASE_URL = "sqlite:///:memory:"

engine = create_engine(
    SQLALCHEMY_DATABASE_URL, connect_args={"check_same_thread": False}
)
TestingSessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=engine)

Base.metadata.create_all(bind=engine)


@pytest.fixture(autouse=True)
def drop_all_data(testing_db):
    testing_db.query(TimeEntry).delete()


@pytest.fixture
def testing_db():
    db = TestingSessionLocal()
    try:
        yield db
    finally:
        db.close()


@pytest.fixture
def testing_service(testing_db):
    return TimeEntryService(crud=CRUDTimeEntry(db=testing_db))


def test_stopping_no_running_entry(testing_service):
    stopped = testing_service.stop_running_entry()
    assert stopped is None


def test_starting_time_entry(testing_service):
    entry = testing_service.start_new_running_entry()
    assert entry.title is None
    assert entry.datetime_start is not None
    assert entry.datetime_end is None


def test_has_running_time_entry_check_positive(testing_service):
    testing_service.start_new_running_entry()
    result = testing_service.has_running_time_entry()
    assert result is True


def test_starting_time_entry_twice(testing_service):
    testing_service.start_new_running_entry()
    new_entry = testing_service.start_new_running_entry()
    assert new_entry is None


def test_has_running_time_entry_check_negative(testing_service):
    result = testing_service.has_running_time_entry()
    assert result is False


def test_stop_running_entry(testing_service):
    running = testing_service.start_new_running_entry()
    stopped = testing_service.stop_running_entry()
    assert running.datetime_start == stopped.datetime_start
    assert running.id == stopped.id
    assert running.title == stopped.title
    assert stopped.datetime_end is not None
    assert stopped.datetime_end > running.datetime_start
    assert not stopped.datetime_end < running.datetime_start
    assert testing_service.has_running_time_entry() is False


@pytest.fixture
def with_some_data_in_db(testing_service):
    testing_service.start_new_running_entry()
    testing_service.stop_running_entry()
    testing_service.start_new_running_entry()
    testing_service.stop_running_entry()


def test_fixture_with_some_data_in_db(testing_service, with_some_data_in_db):
    count = testing_service.get_time_entries_count()
    assert count == 2
    assert count != 0


def test_stopping_no_running_entry_with_data(testing_service, with_some_data_in_db):
    stopped = testing_service.stop_running_entry()
    assert stopped is None


def test_starting_time_entry_with_data(testing_service, with_some_data_in_db):
    entry = testing_service.start_new_running_entry()
    assert entry.title is None
    assert entry.datetime_start is not None
    assert entry.datetime_end is None


def test_has_running_time_entry_check_positive_with_data(testing_service, with_some_data_in_db):
    testing_service.start_new_running_entry()
    result = testing_service.has_running_time_entry()
    assert result is True


def test_starting_time_entry_twice_with_data(testing_service, with_some_data_in_db):
    testing_service.start_new_running_entry()
    new_entry = testing_service.start_new_running_entry()
    assert new_entry is None


def test_has_running_time_entry_check_negative_with_data(testing_service, with_some_data_in_db):
    result = testing_service.has_running_time_entry()
    assert result is False


def test_stop_running_entry_with_data(testing_service, with_some_data_in_db):
    running = testing_service.start_new_running_entry()
    stopped = testing_service.stop_running_entry()
    assert running.datetime_start == stopped.datetime_start
    assert running.id == stopped.id
    assert running.title == stopped.title
    assert stopped.datetime_end is not None
    assert stopped.datetime_end > running.datetime_start
    assert not stopped.datetime_end < running.datetime_start
    assert testing_service.has_running_time_entry() is False
