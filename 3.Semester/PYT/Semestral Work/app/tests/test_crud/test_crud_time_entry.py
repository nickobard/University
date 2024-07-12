from datetime import datetime
import pandas as pd
import numpy as np

import pytest
from sqlalchemy import create_engine, text
from sqlalchemy.orm import sessionmaker

from crud import CRUDTimeEntry
from db.base_class import Base
from models import TimeEntry
from schemas import TimeEntryCreateOpened, TimeEntryUpdate, TimeEntryCreateClosed

SQLALCHEMY_DATABASE_URL = "sqlite:///:memory:"

engine = create_engine(
    SQLALCHEMY_DATABASE_URL, connect_args={"check_same_thread": False}
)
TestingSessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=engine)

Base.metadata.create_all(bind=engine)


@pytest.fixture(autouse=True)
def drop_all_data(testing_db):
    testing_db.query(TimeEntry).delete()
    testing_db.commit()


@pytest.fixture
def testing_db():
    db = TestingSessionLocal()
    try:
        yield db
    finally:
        db.close()


@pytest.fixture
def testing_connection():
    conn = engine.connect()
    try:
        yield conn
    finally:
        conn.close()


@pytest.fixture
def testing_crud(testing_db):
    return CRUDTimeEntry(db=testing_db)


@pytest.fixture
def with_some_data(testing_crud):
    testing_crud.create_time_entry_closed(
        time_entry=TimeEntryCreateClosed(datetime_start=datetime(year=2022, month=1, day=1, hour=13),
                                         datetime_end=(datetime(year=2022, month=1, day=1, hour=14)),
                                         title="task 1"))
    testing_crud.create_time_entry_closed(
        time_entry=TimeEntryCreateClosed(datetime_start=datetime(year=2022, month=1, day=1, hour=15),
                                         datetime_end=(datetime(year=2022, month=1, day=1, hour=16)),
                                         title="task 2"))
    testing_crud.create_time_entry_closed(
        time_entry=TimeEntryCreateClosed(datetime_start=datetime(year=2022, month=1, day=1, hour=17),
                                         datetime_end=(datetime(year=2022, month=1, day=1, hour=20)),
                                         title="task 3"))


def test_db_connection(testing_db):
    objects = testing_db.query(TimeEntry).all()
    assert len(objects) == 0


# @pytest.mark.skip
def test_is_empty(testing_crud):
    objects = testing_crud.get_time_entries_all()
    assert len(objects) == 0


def test_start_new_time_entry(testing_crud):
    test_datetime = datetime.now()
    created = testing_crud.create_time_entry_opened(
        time_entry=TimeEntryCreateOpened(title="test title", datetime_start=test_datetime))
    assert created.title == "test title"
    assert created.datetime_start == test_datetime
    assert created.datetime_end is None
    assert created.closed_entry is False


@pytest.fixture
def db_with_running_entry(testing_crud):
    test_datetime = datetime.now()
    created = testing_crud.create_time_entry_opened(
        time_entry=TimeEntryCreateOpened(title="test title", datetime_start=test_datetime))
    return created


def test_update_time_entry_state(testing_crud, db_with_running_entry):
    created = db_with_running_entry
    testing_crud.update_time_entry_state(db_obj=created, closed=True)
    assert created.title == "test title"
    assert created.datetime_start == created.datetime_start
    assert created.datetime_end is None
    assert created.closed_entry is True


def test_objects_count_after_update(testing_crud, db_with_running_entry):
    created = db_with_running_entry
    test_datetime_end = datetime.now()
    testing_crud.update_time_entry_state(db_obj=created, closed=True)
    testing_crud.update_time_entry_data(db_obj=created, obj_in=TimeEntryUpdate(title="new test title",
                                                                               datetime_end=test_datetime_end,
                                                                               ))
    objects = testing_crud.get_time_entries_all()
    assert len(objects) == 1


def test_update_time_entry(testing_crud, db_with_running_entry):
    created = db_with_running_entry
    test_datetime_end = datetime.now()
    testing_crud.update_time_entry_state(db_obj=created, closed=True)
    testing_crud.update_time_entry_data(db_obj=created, obj_in=TimeEntryUpdate(title="new test title",
                                                                               datetime_end=test_datetime_end,
                                                                               ))
    assert created.title == "new test title"
    assert created.datetime_start == created.datetime_start
    assert created.datetime_end == test_datetime_end
    assert created.closed_entry is True


def test_get_first_running_time_entry(testing_crud, db_with_running_entry):
    created = db_with_running_entry
    running = testing_crud.get_first_running_entry()
    assert created == running


def test_get_first_nonexistent_running_time_entry(testing_crud):
    running = testing_crud.get_first_running_entry()
    assert running is None


def test_created_objects(testing_crud, with_some_data):
    assert testing_crud.get_time_entry_by_id(1).title == "task 1"
    assert testing_crud.get_time_entry_by_id(2).title == "task 2"
    assert testing_crud.get_time_entry_by_id(3).title == "task 3"
    assert testing_crud.get_time_entry_by_id(4) is None


def test_datetime_of_existing_objects(testing_crud, with_some_data):
    obj = testing_crud.get_time_entry_by_id(1)
    assert obj.datetime_start.__str__() == "2022-01-01 13:00:00"


def test_pandas_connection(testing_connection, with_some_data):
    df = pd.read_sql(sql='SELECT * FROM time_entries', con=testing_connection)
    assert df.title[0] == "task 1"
    assert df.title[1] == "task 2"
    assert df.title[2] == "task 3"
    with pytest.raises(KeyError) as e:
        whatever = df.title[3]


def test_pandas_to_json_conversion(testing_connection, with_some_data):
    df = pd.read_sql(sql=text('SELECT * FROM time_entries WHERE id = :id'),
                     params={'id': 1},
                     con=testing_connection)
    json_string = df.to_json(orient='records')
    assert json_string == '[{"id":1,"title":"task 1","datetime_start":"2022-01-01 13:00:00.000000",' \
                          '"datetime_end":"2022-01-01 14:00:00.000000","closed_entry":1}]'
