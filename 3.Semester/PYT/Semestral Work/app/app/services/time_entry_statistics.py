from datetime import datetime
from fastapi import Depends
from pandas import DataFrame

import models
from db.session import get_connection
from sqlalchemy import text
import pandas as pd
from utils import parse_days, parse_time, combine_days_and_time, parse_title


class TimeEntryStatistics:
    def __init__(self, connection=Depends(get_connection)):
        self.connection = connection
        self.data = pd.read_sql_query(
            sql=text(f"SELECT * FROM {models.TimeEntry.__tablename__}"),
            con=connection,
            parse_dates=["datetime_start", "datetime_end"],
        )

    @staticmethod
    def provided_data_ensurer(func):
        def data_ensurer(*args, **kwargs):
            self = args[0]
            if 'df' not in kwargs:
                return func(*args, **kwargs, df=self.data)
            return func(*args, **kwargs)

        return data_ensurer

    @provided_data_ensurer
    def get_closed_entries(self, *, df: DataFrame | None = None) -> DataFrame:
        return df[df.closed_entry == 1]

    @provided_data_ensurer
    def get_opened_entries(self, *, df: DataFrame | None = None) -> DataFrame:
        return df[df.closed_entry == 0]

    @provided_data_ensurer
    def parse_dates_to_format(self, datetime_format: str = "%d/%m/%Y %H:%M:%S", *,
                              df: DataFrame | None = None) -> DataFrame:
        datetime_start_formatted = df.datetime_start.dt.strftime(datetime_format)
        datetime_end_formatted = df.datetime_end.dt.strftime(datetime_format)

        return df.assign(datetime_start=datetime_start_formatted,
                         datetime_end=datetime_end_formatted)

    @provided_data_ensurer
    def get_duration_components_from_datetime(self, *, df: DataFrame | None = None) -> DataFrame:
        delta = pd.to_datetime(df.datetime_end) - pd.to_datetime(df.datetime_start)
        components = delta.dt.components
        return components.drop(['milliseconds', 'microseconds', 'nanoseconds'], axis=1)

    @provided_data_ensurer
    def get_duration_components_from_duration(self,
                                              *, df: DataFrame | None = None) -> DataFrame:
        components = df.duration.dt.components
        return components.drop(['milliseconds', 'microseconds', 'nanoseconds'], axis=1)

    @provided_data_ensurer
    def with_duration_column(self, *, df: DataFrame | None = None) -> DataFrame:
        delta = pd.to_datetime(df.datetime_end) - pd.to_datetime(df.datetime_start)
        return df.assign(duration=delta)

    @staticmethod
    def format_duration_components(components_df: DataFrame) -> DataFrame:

        components_df.days = components_df.days.map(parse_days)
        components_df['time'] = components_df.apply(
            lambda df: parse_time(hours=df.hours, minutes=df.minutes, seconds=df.seconds),
            axis=1)
        components_df['formatted_datetime'] = components_df.apply(
            lambda df: combine_days_and_time(df.days, df.time),
            axis=1)
        return components_df.formatted_datetime

    @provided_data_ensurer
    def parse_task_titles(self, *, df: DataFrame | None = None) -> DataFrame:
        return df.title.map(parse_title)

    @provided_data_ensurer
    def get_closed_entries_with_duration(self, *, df: DataFrame | None = None) -> DataFrame:
        df = self.get_closed_entries(df=df)
        df = self.with_duration_column(df=df)
        return df

    @provided_data_ensurer
    def get_formatted_duration_from_datetime(self, *, df: DataFrame | None = None) -> DataFrame:
        components = self.get_duration_components_from_datetime(df=df)
        return self.format_duration_components(components_df=components)

    def get_formatted_duration_from_duration(self, df_with_duration: DataFrame) -> DataFrame:
        components = self.get_duration_components_from_duration(df=df_with_duration)
        return self.format_duration_components(components_df=components)

    @provided_data_ensurer
    def format_dataframe(self, df: DataFrame) -> DataFrame:
        df.title = self.parse_task_titles(df=df)
        df.duration = self.get_formatted_duration_from_datetime(df=df)
        df = self.parse_dates_to_format(df=df)
        return df

    @provided_data_ensurer
    def get_from_datetime_interval(self,
                                   date_from: str | None = None,
                                   date_to: str | None = None,
                                   *,
                                   df: DataFrame | None = None) -> DataFrame:
        try:
            from_bound = datetime.fromisoformat(date_from)
            df = df[df.datetime_start >= from_bound]
        except (ValueError, TypeError):
            pass

        try:
            to_bound = datetime.fromisoformat(date_to)
            df = df[df.datetime_end <= to_bound]
        except (ValueError, TypeError):
            pass

        return df

    @staticmethod
    def aggregate_duration_by_same_title(df: DataFrame) -> DataFrame:
        return df.groupby(['title'])['duration'].sum().reset_index()

    @staticmethod
    def apply_task_duration_threshold(df: DataFrame, threshold: int = 0.05) -> DataFrame:
        duration_sum = df.duration.sum()
        threshold_duration = duration_sum * threshold
        under_threshold = df[df.duration <= threshold_duration]

        df.loc[under_threshold.index, 'title'] = 'Other'
        df = TimeEntryStatistics.aggregate_duration_by_same_title(df=df)
        return df[['title', 'duration']].groupby(['title']).sum().reset_index()
