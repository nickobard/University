import uvicorn
from fastapi import FastAPI
from fastapi.staticfiles import StaticFiles
from fastapi.responses import RedirectResponse

from api import api_router
from db.init_db import init_db
from views.views import views_router

init_db()

app = FastAPI()
app.include_router(api_router, prefix="/api")
app.include_router(views_router)
app.mount("/static", StaticFiles(directory="../static"), name="static")


@app.get("/")
def root():
    return RedirectResponse("/track")


if __name__ == "__main__":
    uvicorn.run("main:app", host="localhost", port=8000, reload=True)
