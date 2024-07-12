import { Component, Input, OnInit } from '@angular/core'
import { DocumentService } from './document.service'
import { ActivatedRoute } from '@angular/router'
import { TextSelectorService } from '../../inputs/text-selector/text-selector.service'
import { DiscussionPosterService } from '../../discussion_poster/discussion-poster/discussion-poster.service'

@Component({
  selector: 'app-document-view',
  templateUrl: './document-view.component.html',
  styleUrls: ['./document-view.component.scss'],
})
export class DocumentViewComponent implements OnInit {
  documentContent: String | undefined
  @Input() isSubmitter = false
  public static TEXT_ID = 'selection'
  textIsSelected = false

  constructor(
    private docService: DocumentService,
    private route: ActivatedRoute,
    private textSelectorService: TextSelectorService,
    private posterService: DiscussionPosterService
  ) {}

  ngOnInit(): void {
    this.getDocumentContent()
    this.posterService.isSelected.subscribe((is) => {
      this.textIsSelected = is
    })
  }

  /**
   * Fetches content of document. UUID retrieved from route params.
   */
  getDocumentContent() {
    this.route.params.subscribe((params) => {
      let document_uuid = null

      if (this.isSubmitter) {
        document_uuid = params['private_document_uuid']
      } else {
        document_uuid = params['public_document_uuid']
      }

      this.docService.fetchDocumentContent(this.isSubmitter, document_uuid)
      this.docService
        .getDocumentContent()
        .subscribe((data) => (this.documentContent = data))
    })
  }

  /**
   * Called when text in document is selected with mouse.
   * Sets selection data, which is necessary to later highlight the text.
   * @param event
   */
  onSelection(event: MouseEvent) {
    if (this.textIsSelected) return
    const selection = window.getSelection()
    const selectedElementsIds =
      this.textSelectorService.getSelectedParagraphIDs(selection!)
    this.posterService.setSelection(
      this.textSelectorService.getSelectionData(
        selection!,
        DocumentViewComponent.TEXT_ID,
        0,
        selectedElementsIds
      )
    )
  }
}
