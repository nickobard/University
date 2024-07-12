import asyncio

from fastapi import APIRouter, WebSocket, Depends
from starlette.websockets import WebSocketDisconnect

import schemas
from services import TimeEntryService

router = APIRouter()


@router.websocket("/track")
async def track_websocket(websocket: WebSocket,
                          service: TimeEntryService = Depends(TimeEntryService)):
    await websocket.accept()
    while True:

        running = service.get_running_time_entry()
        if running is not None:
            data = schemas.TimeEntry.from_orm(running).json()
        else:
            data = "{}"

        try:
            await websocket.send_text(data)
        except WebSocketDisconnect:
            break
        await asyncio.sleep(3)
