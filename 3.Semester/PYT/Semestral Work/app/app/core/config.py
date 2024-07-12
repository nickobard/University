from typing import Dict, Any

from pydantic import BaseSettings, validator, PostgresDsn


# pylint: disable=locally-disabled

class Settings(BaseSettings):
    POSTGRES_SERVER: str = "localhost"
    POSTGRES_USER: str = "dev"
    POSTGRES_PASSWORD: str = "pass"
    POSTGRES_DB: str = "devdb"
    POSTGRES_PORT: str = "5432"
    SQLALCHEMY_SCHEME: str = "postgresql"
    SQLALCHEMY_DATABASE_URI: str | None = None

    # pylint: disable=no-self-argument
    # reason: pydantic validator doesn't work with self argument.
    @validator("SQLALCHEMY_DATABASE_URI", pre=True)
    def assemble_db_connection(cls, value: str | None, values: Dict[str, Any]) -> Any:
        if isinstance(value, str):
            return value
        return PostgresDsn.build(
            scheme=values.get("SQLALCHEMY_SCHEME"),
            user=values.get("POSTGRES_USER"),
            password=values.get("POSTGRES_PASSWORD"),
            host=values.get("POSTGRES_SERVER"),
            port=values.get("POSTGRES_PORT"),
            path=f"/{values.get('POSTGRES_DB') or ''}",
        )

    # pylint: enable=no-self-argument

    # pylint: disable=too-few-public-methods
    # reason: special class for pydantic configuration.
    class Config:
        env_file = ".env"

    # pylint: enable=too-few-public-methods


settings = Settings()
