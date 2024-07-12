import { Injectable } from '@angular/core'
import { Observable, Subject } from 'rxjs'
import { ApiService } from 'src/app/api/api.service'

@Injectable({
  providedIn: 'root',
})
export class DocumentService {
  private documentContentSubject = new Subject<string>()

  constructor(private apiService: ApiService) {}

  /**
   *
   * @param isSubmitter is document opened in app by submitter?, true = submitter
   * @param documentPublicUUID
   */
  fetchDocumentContent(isSubmitter: boolean, documentPublicUUID: string): void {
    this.apiService
      .getSelectedDocument(isSubmitter, documentPublicUUID.toString())
      .subscribe((data) => {
        this.documentContentSubject.next(data.content)
      })
  }

  /**
   * @returns Document content as observable (as of now plain text).
   */
  getDocumentContent(): Observable<string> {
    console.log('getting: ' + this.documentContentSubject)
    return this.documentContentSubject.asObservable()
  }
}
