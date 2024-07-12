import { Injectable } from '@angular/core'
import { ApiService } from 'src/app/api/api.service'
import { ApiPostComment } from 'src/app/objects/api-post-comment'
import { SelectionData } from 'src/app/objects/selection-data'
import { DiscussionState } from 'src/app/objects/discussion-state'
import { AdapterService } from 'src/app/services/adapter.service'
import { DiscussionData } from 'src/app/objects/discussion-data'

@Injectable({
  providedIn: 'root',
})
export class DiscussionCommentService {
  constructor(private api: ApiService, private adapter: AdapterService) {}

  postCommentToDiscussion(
    _content: string,
    docUUID: string,
    _discussionUUID: string
  ) {
    this.api.postComment({
      comment: {
        content: _content,
        discussion_uuid: _discussionUUID,
      },
    })
  }

  updateDiscussionState(discussionData: DiscussionData) {
    const _crosslink = this.adapter.convertSelectionToCrosslink(
      discussionData.selectionData
    )
    const _state = this.adapter.convertStateToApiString(
      discussionData.discussionState
    )
    this.api.putDiscussionForDocument(
      {
        crosslink: _crosslink,
        state: _state,
      },
      discussionData.uuid
    )
  }
}
