import { Component, OnInit, ViewChild } from '@angular/core'
import { DiscussionPosterService } from './discussion-poster.service'
import { DiscussionData } from 'src/app/objects/discussion-data'
import { ActivatedRoute } from '@angular/router'
import { TextHighlightingService } from 'src/app/services/text-highlighting.service'
import { DiscussionWindowService } from '../../comments/discussion-window/discussion-window.service'
import { BasicTextInputComponent } from '../../inputs/basic-text-input/basic-text-input.component'
import { DiscussionState } from 'src/app/objects/discussion-state'

@Component({
  selector: 'app-discussion-poster',
  templateUrl: './discussion-poster.component.html',
  styleUrls: ['./discussion-poster.component.scss'],
})
export class DiscussionPosterComponent implements OnInit {
  btnPostDiscussionTxt = 'Post discussion'
  textNotSelected = 'PLEASE SELECT TEXT'
  textSelected = 'TEXT SELECTED'
  btnUnselectTxt = 'Unselect'
  btnHighlightText = 'Highlight'
  highlighted = false
  textToShow = this.textNotSelected
  textIsSelected = false
  documentUUID: string = ''
  textInput = ''
  @ViewChild('textInput', { static: false }) textInputComponent:
    | BasicTextInputComponent
    | undefined

  constructor(
    private posterService: DiscussionPosterService,
    private route: ActivatedRoute,
    private textHighlingtService: TextHighlightingService,
    private discussionWindowService: DiscussionWindowService
  ) {}

  onInputTextChanged(text: string) {
    this.textInput = text
  }

  ngOnInit(): void {
    this.subscribeToRouteParams()
    this.subscribeToIsSelected()
  }

  /**
   * If user decides to "unselect" the selected text, this function cleares the data about the selection.
   */
  deleteSelection() {
    if (this.highlighted) {
      //resets color of text
      this.highlightSelectedText()
    }
    this.posterService.deleteSelection()
    this.changeTextOnSelection()
  }

  /**
   * Calls services which will post new comment (as new discussion).
   * @returns
   */
  postDiscussion() {
    const selectionData = this.posterService.getSelectionData()
    if (selectionData == undefined) return
    const discussionData: DiscussionData = {
      selectionData: this.posterService.getSelectionData()!,
      uuid: '',
      content: this.textInput,
      comments: [],
      document_uuid: this.documentUUID,
      discussionState: DiscussionState.OPEN, // always OPEN for posting new discussion
    }
    this.posterService.postDiscussion(discussionData)
    //update
    this.discussionWindowService.getDiscussionsData(this.documentUUID)
    this.posterService.deleteSelection()
    this.clearInput()
  }

  /**
   * @returns Highlights text
   */
  highlightSelectedText() {
    if (!this.textIsSelected) return
    if (this.highlighted) {
      this.btnHighlightText = 'Highlight'
    } else {
      this.btnHighlightText = 'Unhighlight'
    }
    this.highlighted = !this.highlighted
    const selectionData = this.posterService.getSelectionData()
    this.textHighlingtService.highlightSelectionMultipleElements(
      selectionData!.initialIndex!,
      selectionData!.stopIndex!,
      selectionData!.elementsIds!
    )
  }

  private changeTextOnSelection() {
    if (this.textIsSelected) {
      this.textToShow = this.textSelected
    } else {
      this.textToShow = this.textNotSelected
    }
  }

  private subscribeToRouteParams() {
    this.route.params.subscribe((params) => {
      const uuid = params['public_document_uuid']
      this.documentUUID = uuid
    })
  }

  /**
   * Subscribes to isSelected in posterService, this variable signs whether user has already selected the text in document.
   */
  private subscribeToIsSelected() {
    this.posterService.isSelected.subscribe((isSelected) => {
      this.textIsSelected = isSelected
      this.changeTextOnSelection()
    })
  }

  /**
   * Clears input from input.
   */
  private clearInput() {
    if (this.textInputComponent) {
      this.textInputComponent.clearInput()
    }
  }
}
