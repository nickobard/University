from fastapi import APIRouter
from api import time_entires, web_sockets

api_router = APIRouter()
api_router.include_router(time_entires.router, prefix="/entries")
api_router.include_router(web_sockets.router, prefix="/ws")


@api_router.get("/")
def api_root():
    return {"message": "Hello from api!"}
