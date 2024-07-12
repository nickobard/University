"""
Package for CRUD repositories for each domain type, used to handle
operations over database.
"""
from .crud_base import AbstractCRUDBase, CRUDBase
from .crud_document import AbstractCRUDDocument, CRUDDocument as Document
from .crud_discusion import AbstractCRUDDiscussion, CRUDDiscussion as Discussion
from .crud_comment import AbstractCRUDComment, CRUDComment as Comment

__all__ = [
    "AbstractCRUDBase",
    "CRUDBase",
    "AbstractCRUDDocument",
    "Document",
    "AbstractCRUDDiscussion",
    "Discussion",
    "AbstractCRUDComment",
    "Comment",
]
