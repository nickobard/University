import { Injectable } from '@angular/core'
import { Subject } from 'rxjs'
import { ApiService } from 'src/app/api/api.service'
import { DiscussionData } from 'src/app/objects/discussion-data'
import { SelectionData } from 'src/app/objects/selection-data'
import { AdapterService } from 'src/app/services/adapter.service'
import { ApiPostComment } from 'src/app/objects/api-post-comment'

@Injectable({
  providedIn: 'root',
})
export class DiscussionPosterService {
  constructor(private api: ApiService, private adapter: AdapterService) {}
  isSelected = new Subject<boolean>()

  private selection: SelectionData | undefined

  getSelectionData() {
    return this.selection
  }

  setSelection(selection: SelectionData) {
    this.isSelected.next(true)
    this.selection = selection
  }

  deleteSelection() {
    this.isSelected.next(false)
    this.selection = undefined
  }

  /**
   * Postes comment (as new discussion) -> new discussion will be posted.
   * @param discussionData
   */
  postDiscussion(discussionData: DiscussionData) {
    const postData: ApiPostComment = {
      comment: {
        content: discussionData.content.toString(),
      },
      discussion: this.adapter.convertDiscussionToAPI(discussionData),
    }
    this.api.postComment(postData)
  }
}
