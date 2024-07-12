"""
API controllers for documents.
"""
from uuid import UUID
from typing import List, Any, Annotated

from fastapi import APIRouter, Depends, status, Body, Header, Path

from api import utils
import schemas
from services import DocumentService

router = APIRouter(
    prefix='/documents',
    tags=[utils.fastapi_docs.DOCUMENT_TAG['name']]
)


@router.post("/submit",
             status_code=status.HTTP_201_CREATED)
async def submit_document(service: Annotated[DocumentService, Depends(DocumentService)],
                          content: Annotated[str, Body(description="Document content",
                                                       media_type="text/plain")]) -> Any:
    """
    Submit document from DSW, save it to db and return its submitter uuid.

    :param service: Document service.
    :param content: Document content.

    :return: Fastapi response with status code and location of submitter view for document.
    """
    return utils.DSWRequest(service, content).validate_and_submit_document()


@router.get("/",
            response_model=List[schemas.Document],
            status_code=status.HTTP_200_OK)
async def get_all_documents(service: Annotated[DocumentService, Depends(DocumentService)]) -> Any:
    """
    Get all documents from database.

    :param service: Document service.

    :return: List of all documents or None if there are no documents in db.
    """
    return service.get_all()


@router.get("/{document_uuid}",
            response_model=schemas.Document,
            responses={
                **utils.EntityNotFoundException.RESPONSE,
            },
            status_code=status.HTTP_200_OK)
async def get_document(service: Annotated[DocumentService, Depends(DocumentService)],
                       document_uuid: Annotated[UUID, Path()]) -> Any:
    """
    Get document by its uuid.

    :param service: Document service.
    :param document_uuid: uuid of the document.

    :return: Document with uuid equal to document_uuid
             or None if no such document exists.
    """
    doc = service.get(document_uuid)
    if not doc:
        raise utils.EntityNotFoundException(utils.Entity.DOCUMENT, document_uuid)
    return doc


@router.put("/{document_uuid}",
            response_model=schemas.Document,
            status_code=status.HTTP_200_OK,
            responses={
                **utils.EntityNotFoundException.RESPONSE,
            })
async def update_document(service: Annotated[DocumentService, Depends(DocumentService)],
                          document_uuid: Annotated[UUID, Path()],
                          document: Annotated[schemas.DocumentUpdate, Body()]) -> Any:
    """
    Update document with uuid equal to document_uuid.

    :param service: Document service.
    :param document_uuid: uuid of the document.
    :param document: DocumentUpdate schema.
    """
    doc = service.update(document_uuid, document)
    if not doc:
        raise utils.EntityNotFoundException(utils.Entity.DOCUMENT, document_uuid)
    return doc


@router.delete("/{document_uuid}",
               response_model=schemas.DocumentSubmitter,
               responses={
                   **utils.EntityNotFoundException.RESPONSE,
               },
               status_code=status.HTTP_200_OK)
async def delete_document(service: Annotated[DocumentService, Depends(DocumentService)],
                          document_uuid: Annotated[UUID, Path()]) -> Any:
    """Delete document with uuid equal to document_uuid.

    :param service: Document service.
    :param document_uuid: uuid of the document.
    """
    doc = service.remove(document_uuid)
    if not doc:
        raise utils.EntityNotFoundException(utils.Entity.DOCUMENT, document_uuid)
    return doc


# pylint: disable=unused-argument
# reason: Controllers are still not implemented.

@router.get("/{document_uuid}/stats", status_code=status.HTTP_200_OK,
            include_in_schema=False)
async def get_document_stats(service: Annotated[DocumentService, Depends(DocumentService)],
                             document_uuid: Annotated[UUID, Path()]) -> Any:
    """
    Get document stats of document with uuid equal to document_uuid.

    :param service: Document service.
    :param document_uuid: uuid of the document.
    """
    # TODO - Get document stats controller
    raise utils.NotImplementedException()


@router.post("/{document_uuid}/reviews", status_code=status.HTTP_201_CREATED,
             include_in_schema=False)
async def add_document_review(service: Annotated[DocumentService, Depends(DocumentService)],
                              document_uuid: Annotated[UUID, Path()]) -> Any:
    """
    Add document review to document with uuid equal to document_uuid.

    :param service: Document service.
    :param document_uuid: uuid of the document.
    """
    # TODO - Add document review controller
    raise utils.NotImplementedException()
