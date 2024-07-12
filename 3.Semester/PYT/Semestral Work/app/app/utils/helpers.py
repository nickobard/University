import numpy as np
import pandas as pd


def parse_days(days):
    if days == 1:
        return f'{days} day'
    if days > 1:
        return f'{days} days'
    return np.nan


def parse_time(hours, minutes, seconds):
    int_hour = int(hours)
    int_minutes = int(minutes)
    int_seconds = int(seconds)
    if int_seconds == 0 and int_minutes == 0 and int_hour != 0:
        return f"{int_hour} hours" if int_hour > 1 else f"{int_hour} hour"
    return f"{int_hour:02d}:{int_minutes:02d}:{int_seconds:02d}"


def combine_days_and_time(days, time):
    if pd.isnull(days):
        return time
    if time == "00:00:00":
        return days
    return f'{days} {time}'


def parse_title(title):
    if pd.isnull(title) or str.isspace(title) or len(title) == 0:
        return "(no name)"
    return str.strip(title)
