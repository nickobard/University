import {
  ChangeDetectorRef,
  Component,
  Input,
  OnChanges,
  OnInit,
  SimpleChanges,
} from '@angular/core'
import { DiscussionData } from 'src/app/objects/discussion-data'
import { DiscussionCommentService } from './discussion-comment.service'
import { TextHighlightingService } from 'src/app/services/text-highlighting.service'
import { DiscussionWindowService } from '../discussion-window/discussion-window.service'
import { DiscussionState } from 'src/app/objects/discussion-state'
import { AdapterService } from 'src/app/services/adapter.service'

@Component({
  selector: 'app-discussion-comment',
  templateUrl: './discussion-comment.component.html',
  styleUrls: ['./discussion-comment.component.scss'],
})
export class DiscussionCommentComponent implements OnInit {
  content = 'Lorem ipsum dolor sit amet, consectetur adipiscing elit.'
  answersShown = false
  answerInputShown = false
  highlighted = false
  btnAnswerText = 'Answer'
  btnSeeCommentsText = 'SeeComments'
  btnPostCommentText = 'Post comment'
  btnHighlightText = 'Highlight'
  btnChangeDiscussionState = ''
  numOfComments = 0
  @Input() discussionData: DiscussionData | undefined
  textInput = ''
  showResolved = false

  constructor(
    private discussionCommentService: DiscussionCommentService,
    private textHighlingtService: TextHighlightingService,
    private discussionWindowService: DiscussionWindowService,
    private adapter: AdapterService,
    private cdr: ChangeDetectorRef
  ) {}

  ngOnInit(): void {
    this.numOfComments = this.discussionData?.comments.length! | 0
    this.btnSeeCommentsText = 'See Comments (' + this.numOfComments + ')'
    this.setDiscussionState()
    if (this.discussionData?.discussionState === DiscussionState.OPEN) {
      this.showResolved = false
    } else if (
      this.discussionData?.discussionState === DiscussionState.RESOLVED
    ) {
      this.showResolved = true
    }
    console.log('oninit:' + this.showResolved)
  }

  showAnswerInput() {
    this.answerInputShown = !this.answerInputShown
  }

  showAnswers() {
    this.answersShown = !this.answersShown
  }

  onInputTextChanged(text: string) {
    this.textInput = text
  }

  highlightSelectedText() {
    if (this.highlighted) {
      this.btnHighlightText = 'Highlight'
    } else {
      this.btnHighlightText = 'Unhighlight'
    }
    this.highlighted = !this.highlighted
    this.textHighlingtService.highlightSelectionMultipleElements(
      this.discussionData?.selectionData.initialIndex!,
      this.discussionData?.selectionData.stopIndex!,
      this.discussionData?.selectionData.elementsIds!
    )
  }

  postCommentToDiscussion() {
    this.discussionCommentService.postCommentToDiscussion(
      this.textInput,
      this.discussionData?.document_uuid!,
      this.discussionData?.uuid!
    )
    //update
    this.discussionWindowService.getDiscussionsData(
      this.discussionData?.document_uuid!
    )
  }

  changeDiscussionState() {
    console.log('change 1:' + this.showResolved)
    console.log(this.showResolved)
    if (this.discussionData?.discussionState === DiscussionState.OPEN) {
      this.discussionData!.discussionState = DiscussionState.RESOLVED
      this.showResolved = true
    } else if (
      this.discussionData?.discussionState === DiscussionState.RESOLVED
    ) {
      this.discussionData!.discussionState = DiscussionState.OPEN
      this.showResolved = false
    }
    console.log('change 2:' + this.showResolved)
    this.cdr.detectChanges()
    this.setDiscussionState()

    this.discussionCommentService.updateDiscussionState(this.discussionData!)
    this.cdr.detectChanges()
  }

  private setDiscussionState() {
    const txt =
      this.discussionData!.discussionState === DiscussionState.OPEN
        ? 'resolved'
        : 'open'
    this.btnChangeDiscussionState = 'Mark discussion as ' + txt
    this.cdr.detectChanges()
  }
}
