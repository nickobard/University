from db.base_class import Base
from db.session import engine


def init_db() -> None:
    Base.metadata.create_all(bind=engine)
