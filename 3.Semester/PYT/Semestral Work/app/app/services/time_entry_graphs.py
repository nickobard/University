from pandas import DataFrame
import plotly.express as px


class TimeEntryGraphService:

    @staticmethod
    def get_test_graph():
        fig = px.line(x=range(10), y=range(10))
        return fig.to_html()

    @staticmethod
    def tasks_duration_percentage_pie_graph(df: DataFrame):

        fig = px.pie(data_frame=df, values=df.duration, names=df.title, labels={
            'title': 'Task title',
            'duration': 'Task duration in seconds',
        },
                     title='Task duration percentage')
        return fig.to_html()

    @staticmethod
    def tasks_duration_value_bar_graph(df: DataFrame):
        fig = px.bar(data_frame=df, y=df.duration, x=df.title, text=df.formatted_duration, labels={
            'title': 'Task title',
            'duration': 'Task duration in seconds',
            'formatted_duration': 'Task duration'
        },
                     title="Tasks durations")
        return fig.to_html()
