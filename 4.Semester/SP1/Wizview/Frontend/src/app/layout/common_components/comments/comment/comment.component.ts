import { Component, Input, OnInit } from '@angular/core'
import { CommentService } from './comment.service'
import { CommentData } from 'src/app/objects/comment-data'
import { MatFormFieldControl } from '@angular/material/form-field'

@Component({
  selector: 'app-comment',
  templateUrl: './comment.component.html',
  styleUrls: ['./comment.component.scss'],
})
export class CommentComponent implements OnInit {
  @Input() comment_data: CommentData | undefined
  isOpen: Boolean | undefined
  isSubmitter: Boolean | undefined
  commentID: String | undefined
  username: String | undefined
  date: String | undefined
  textContent: String | undefined
  textUsernameColor: String | undefined
  textColor: String | undefined
  imgSrc: String | undefined
  backgroundColor: String | undefined
  textSpanClossed: String = 'Open comment'
  textSpanOpened: String = 'Close comment'
  textSpanState: String | undefined

  constructor(private commentService: CommentService) {}
  ngOnInit(): void {
    this.setInitialData()
    if (this.isOpen) {
      console.log(this.comment_data)
      this.setToStateOpen()
    } else {
      this.setToStateClose()
    }
  }

  setInitialData() {
    this.isOpen = this.comment_data?.is_open
    this.isSubmitter = this.comment_data?.is_submitter
    this.commentID = this.comment_data?.comment_id
    this.username = this.comment_data?.username
    this.date = this.comment_data?.date
    this.backgroundColor = this.comment_data?.background_color
    this.commentService.replaceTokensWithLinks(
      this.comment_data?.delimiters!,
      '#1',
      [' SHOW ', ' SHOW ', ' SHOW '],
      'text-comment',
      this.comment_data?.text_content ?? '',
      this.comment_data?.selections!
    )
  }

  setToStateClose() {
    this.imgSrc = this.comment_data?.img_closed_src
    this.textSpanState = this.textSpanClossed
    this.textUsernameColor = this.comment_data?.text_color_closed
    this.textColor = this.comment_data?.text_color_closed
  }

  setToStateOpen() {
    this.imgSrc = this.comment_data?.img_open_src
    this.textSpanState = this.textSpanOpened
    this.textUsernameColor = this.comment_data?.text_color_open
    this.textColor = this.comment_data?.text_color_open
  }

  changeStateClick() {
    if (this.isOpen) {
      // changing to state close
      this.setToStateClose()
      this.isOpen = !this.isOpen
      this.commentService.changeCommentState()
      return
    }
    // changing to state open
    this.setToStateOpen()
    this.isOpen = !this.isOpen
    this.commentService.changeCommentState()
  }
}
