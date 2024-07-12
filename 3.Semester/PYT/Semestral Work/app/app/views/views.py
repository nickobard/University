from fastapi import APIRouter, Request, Depends, Query
from fastapi.responses import HTMLResponse
from fastapi.templating import Jinja2Templates

from utils import date_query_params, order_query_params
from services import TimeEntryService, TimeEntryStatistics, TimeEntryGraphService
import markdown

views_router = APIRouter()

templates = Jinja2Templates(directory="../templates")


@views_router.get("/track", response_class=HTMLResponse)
async def track_page(request: Request,
                     service: TimeEntryService = Depends(TimeEntryService),
                     statistics: TimeEntryStatistics = Depends(TimeEntryStatistics),
                     dt_query=Depends(date_query_params),
                     order_query=Depends(order_query_params)
                     ):
    running_entry = service.get_running_time_entry()
    entries = statistics.get_from_datetime_interval(date_from=dt_query['from'],
                                                    date_to=dt_query['to'])

    entries = statistics.get_closed_entries_with_duration(df=entries)
    if not entries.empty:
        entries = entries.sort_values(by=order_query['col'],
                                      ascending=bool(order_query['order'] == 'ascending'))
        entries = statistics.format_dataframe(df=entries)
    return templates.TemplateResponse("track.html", {"request": request,
                                                     "running": running_entry,
                                                     "entries": entries.to_dict('records'),
                                                     "page": "track"})


@views_router.get("/analysis", response_class=HTMLResponse)
async def analysis_page(request: Request,
                        dt_query=Depends(date_query_params),
                        statistics: TimeEntryStatistics = Depends(TimeEntryStatistics),
                        graphs_service: TimeEntryGraphService = Depends(TimeEntryGraphService)

                        ):
    graphs = []
    entries = statistics.get_closed_entries_with_duration()
    entries = statistics.get_from_datetime_interval(df=entries,
                                                    date_from=dt_query['from'],
                                                    date_to=dt_query['to'])
    entries.title = statistics.parse_task_titles(df=entries)
    if entries.empty:
        return templates.TemplateResponse("analysis.html", {"request": request,
                                                            "graphs": graphs,
                                                            "page": "analysis"})
    grouped_by_title = statistics.aggregate_duration_by_same_title(df=entries)
    with_threshold = statistics.apply_task_duration_threshold(df=grouped_by_title)
    with_threshold['formatted_duration'] = statistics.get_formatted_duration_from_duration(
        df_with_duration=with_threshold
    )
    with_threshold.duration = with_threshold.duration.dt.total_seconds()

    graphs.append(graphs_service.tasks_duration_percentage_pie_graph(df=with_threshold))
    graphs.append(graphs_service.tasks_duration_value_bar_graph(df=with_threshold))

    return templates.TemplateResponse("analysis.html", {"request": request,
                                                        "graphs": graphs,
                                                        "page": "analysis"})


@views_router.get("/about", response_class=HTMLResponse)
async def about_page(request: Request,
                     pure_report: bool = Query(default=False)):
    if pure_report:
        return templates.TemplateResponse("report_base.html", {"request": request})
    return templates.TemplateResponse("about.html", {"request": request,
                                                     "page": "about"})
