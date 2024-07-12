"""Shortcuts to easily import schemes."""
from .comment import Comment, CommentCreate, CommentUpdate, CommentInDB
from .discussion import Discussion, DiscussionCreate, DiscussionUpdate, DiscussionInDB, Crosslink
from .comment_and_discussion import CommentAndDiscussionCreate
from .document import Document, DocumentSubmitter, DocumentCreate, \
    DocumentUpdate, DocumentInDB
from .utils import as_dict

__all__ = [
    'Document', 'DocumentSubmitter', 'DocumentCreate', 'DocumentUpdate',
    'DocumentInDB',
    'Discussion', 'DiscussionCreate', 'DiscussionUpdate', 'DiscussionInDB', 'Crosslink',
    'Comment', 'CommentCreate', 'CommentUpdate', 'CommentInDB',
    'CommentAndDiscussionCreate'
]
