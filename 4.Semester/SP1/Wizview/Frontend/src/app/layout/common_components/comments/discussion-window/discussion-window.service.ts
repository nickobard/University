import { Injectable } from '@angular/core'
import { BehaviorSubject, map } from 'rxjs'
import { ApiService } from 'src/app/api/api.service'
import { DiscussionData } from 'src/app/objects/discussion-data'
import { AdapterService } from 'src/app/services/adapter.service'
@Injectable({
  providedIn: 'root',
})
export class DiscussionWindowService {
  private discussionsBehavioural: BehaviorSubject<DiscussionData[]> =
    new BehaviorSubject<DiscussionData[]>([])

  constructor(
    private apiService: ApiService,
    private adapter: AdapterService
  ) {}

  getDiscussionBehavioural() {
    return this.discussionsBehavioural
  }

  getDiscussionsData(docUUID: string) {
    this.apiService
      .getDiscussionsForDocument(docUUID)
      .pipe(
        map((apiData) =>
          apiData.map((apiItem) =>
            this.adapter.convertDiscussionFromAPI(apiItem)
          )
        )
      )
      .subscribe((data) => {
        this.discussionsBehavioural.next(data)
      })
  }
}
