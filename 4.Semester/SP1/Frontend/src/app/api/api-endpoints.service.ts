import { Injectable } from '@angular/core'

@Injectable({
  providedIn: 'root',
})

/**
 * This class creates URL for reaching backed endpoints.
 */
export class ApiEndpointsService {
  private readonly HOST = 'http://0.0.0.0:8000/'

  constructor() {}

  getDocumentsUrl(): string {
    return this.HOST + 'documents/'
  }

  getCommentsUrl(docUUID: string): string {
    return this.HOST + docUUID + '/comments/'
  }

  getSelectedDocumentsURL(docUUID: string): string {
    return this.HOST + 'documents/' + docUUID
  }

  getSubmittersDocumentURL(docUUID: string): string {
    return this.HOST + 'documents/submitted/' + docUUID
  }

  getDiscussionsUrlForDocument(docUUID: string): string {
    return `${this.HOST}discussions/?document_uuid=${docUUID}`
  }

  getCommentPostURL() {
    return `${this.HOST}comments/`
  }

  getPutDiscussionForDocumentURL(discussionUUID: string) {
    return this.HOST + 'discussions/' + discussionUUID
  }
}
