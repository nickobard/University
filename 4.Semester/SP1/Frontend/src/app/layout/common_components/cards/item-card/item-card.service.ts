import { Injectable } from '@angular/core'
import { Router } from '@angular/router'
import { DocumentService } from '../../document/document-view/document.service'

@Injectable({
  providedIn: 'root',
})
export class ItemCardService {
  constructor(private router: Router, private docService: DocumentService) {}

  goToDocumentReviever(publicUUID: String) {
    this.router.navigate(['/documents', publicUUID], {
      queryParams: { documentUUID: publicUUID },
    })
  }
}
