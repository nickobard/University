import { HttpClient } from '@angular/common/http'
import { Injectable } from '@angular/core'
import { ApiEndpointsService } from './api-endpoints.service'
import { ApiPreviewData } from '../objects/api-preview-data'
import { ApiDiscussionData } from '../objects/api-discussion-data'

@Injectable({
  providedIn: 'root',
})
export class ApiService {
  constructor(
    private http: HttpClient,
    private apiEndpointsServie: ApiEndpointsService
  ) {}

  getAllDocuments() {
    return this.http.get<ApiPreviewData[]>(
      this.apiEndpointsServie.getDocumentsUrl()
    )
  }

  /**
   * Fetches document content.
   * @param isSubmitter
   * @param docUUID
   * @returns
   */
  getSelectedDocument(isSubmitter: boolean, docUUID: string) {
    if (isSubmitter)
      return this.http.get<ApiPreviewData>(
        this.apiEndpointsServie.getSubmittersDocumentURL(docUUID)
      )
    else
      return this.http.get<ApiPreviewData>(
        this.apiEndpointsServie.getSelectedDocumentsURL(docUUID)
      )
  }

  getSubmitterDocument(docUUID: string) {
    return this.http.get<ApiPreviewData>(
      this.apiEndpointsServie.getSubmittersDocumentURL(docUUID)
    )
  }

  /**
   * Fetches all discussions for document (including comments)
   * @param docUUID
   * @returns
   */
  getDiscussionsForDocument(docUUID: string) {
    return this.http.get<ApiDiscussionData[]>(
      this.apiEndpointsServie.getDiscussionsUrlForDocument(docUUID)
    )
  }

  /**
   * Posts new comment, whether it is a new comment to a existing discussion, or completely new discussion,
   * needs to be set already in parameter.
   * @param apiPostComment
   */
  postComment(apiPostComment: Object) {
    console.log(this.apiEndpointsServie.getCommentPostURL())
    console.log(JSON.stringify(apiPostComment))
    this.http
      .post(this.apiEndpointsServie.getCommentPostURL(), apiPostComment)
      .subscribe()
  }

  putDiscussionForDocument(apiDiscussionPut: Object, discussionUUID: string) {
    console.log(JSON.stringify(apiDiscussionPut))
    this.http
      .put(
        this.apiEndpointsServie.getPutDiscussionForDocumentURL(discussionUUID),
        apiDiscussionPut
      )
      .subscribe()
  }
}
