from typing import Generator

from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker

from core.config import settings

engine = create_engine(settings.SQLALCHEMY_DATABASE_URI, pool_pre_ping=True)
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=engine)


def get_db() -> Generator:
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()


def get_connection() -> Generator:
    connection = engine.connect()
    try:
        yield connection
    finally:
        connection.close()
