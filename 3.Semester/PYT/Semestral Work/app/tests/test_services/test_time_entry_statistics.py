import pandas as pd
import pytest
from sqlalchemy import create_engine, text
from sqlalchemy.orm import sessionmaker
from datetime import datetime

import models
from crud import CRUDTimeEntry
from db.base_class import Base
from models import TimeEntry
from services import TimeEntryService, TimeEntryStatistics

SQLALCHEMY_DATABASE_URL = "sqlite:///:memory:"

engine = create_engine(
    SQLALCHEMY_DATABASE_URL, connect_args={"check_same_thread": False}
)
TestingSessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=engine)

Base.metadata.create_all(bind=engine)


@pytest.fixture(scope="module")
def setup():
    testing_db = TestingSessionLocal()
    # delete all data if exist
    testing_db.query(TimeEntry).delete()
    testing_db.commit()
    # add some test data
    testing_db.add_all([
        models.TimeEntry(
            datetime_start=datetime(year=2022, month=1, day=1, hour=13, minute=23, second=2, microsecond=123),
            datetime_end=datetime(year=2022, month=1, day=1, hour=14),
            title="task 1",
            closed_entry=True),
        models.TimeEntry(datetime_start=datetime(year=2022, month=1, day=1, hour=15),
                         datetime_end=datetime(year=2022, month=1, day=1, hour=16),
                         title="task 2",
                         closed_entry=True),
        models.TimeEntry(datetime_start=datetime(year=2022, month=1, day=1, hour=17),
                         datetime_end=datetime(year=2022, month=1, day=1, hour=20),
                         title="task 3",
                         closed_entry=True),
        models.TimeEntry(datetime_start=datetime(year=2022, month=1, day=1, hour=21),
                         title="task 4",
                         closed_entry=False),
        models.TimeEntry(datetime_start=datetime(year=2022, month=1, day=2, hour=20),
                         datetime_end=datetime(year=2022, month=1, day=3, hour=20),
                         title="task 3",
                         closed_entry=True)
    ])
    testing_db.commit()
    yield
    # teardown - delete all data after all tests
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
def testing_conn():
    connection = engine.connect()
    try:
        yield connection
    finally:
        connection.close()


@pytest.fixture
def testing_service(testing_db):
    return TimeEntryService(crud=CRUDTimeEntry(db=testing_db))


@pytest.fixture
def testing_statistics(testing_conn):
    return TimeEntryStatistics(connection=testing_conn)


def test_creating_dataframe_from_connection(testing_conn, setup):
    df = pd.read_sql_query(
        sql=text(f"SELECT * FROM {models.TimeEntry.__tablename__}"),
        con=testing_conn
    )
    assert df.title[0] == 'task 1'


def test_dataframe_has_data(setup, testing_statistics):
    result = testing_statistics.get_closed_entries()
    assert result.shape[0] == 4
    assert result.title[0] == 'task 1'
    assert result.title[1] == 'task 2'
    assert result.title[2] == 'task 3'
    assert result.title[2] != 'task 1'
    assert result.datetime_end[1] != "surely not this"
    assert result.datetime_start[1] != "surely not this"


def test_get_opened_entries(setup, testing_statistics):
    result = testing_statistics.get_opened_entries()
    assert result.shape[0] == 1
    assert result.title[3] == 'task 4'
    assert result.closed_entry[3] == 0


def test_statistics_init_parsed_date(setup, testing_statistics):
    closed_entries = testing_statistics.get_closed_entries()
    result = testing_statistics.parse_dates_to_format(df=closed_entries)
    assert result.datetime_start[0] == "01/01/2022 13:23:02"


def test_getting_duration_dataframe(setup, testing_statistics):
    data = testing_statistics.get_closed_entries()
    data = testing_statistics.get_duration_components_from_datetime(df=data)
    assert data.days[0] == 0
    assert data.hours[0] == 0
    assert data.minutes[0] == 36
    assert data.seconds[0] == 57


def test_formatting_duration_dataframe(setup, testing_statistics):
    data = testing_statistics.get_closed_entries()
    data = testing_statistics.get_duration_components_from_datetime(df=data)
    result = testing_statistics.format_duration_components(data)
    assert result[0] == "00:36:57"
    assert result[4] == "1 day"


def test_parsing_title(testing_statistics):
    result = testing_statistics.parse_task_titles(df=pd.DataFrame(["", "  \t", "   s   "], columns=["title"]))
    assert result[0] == "(no name)"
    assert result[1] == "(no name)"
    assert result[2] == "s"


def test_sorting_by_id(setup, testing_statistics):
    df = testing_statistics.get_closed_entries_with_duration()
    df = df.sort_values(by='id', ascending=False)
    df = testing_statistics.format_dataframe(df=df)
    assert df.id.iloc[0] == 5
    assert df.id.iloc[1] == 3
    assert df.id.iloc[2] == 2
    assert df.id.iloc[3] == 1


def test_getting_from_invalid_interval_same_df(setup, testing_statistics):
    shape_before = testing_statistics.data.shape
    result = testing_statistics.get_from_datetime_interval(date_from="", date_to="")
    assert result.shape == shape_before
    result = testing_statistics.get_from_datetime_interval()
    assert result.shape == shape_before


def test_group_by_title(setup, testing_statistics):
    df = testing_statistics.get_closed_entries_with_duration()
    df = testing_statistics.aggregate_duration_by_same_title(df=df)
    assert df.shape == (3, 2)
    assert df.iloc[2].duration == pd.to_timedelta("1 days 03:00:00")
