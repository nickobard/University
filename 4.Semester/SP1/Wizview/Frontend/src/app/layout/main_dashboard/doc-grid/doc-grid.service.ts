import { Injectable, OnInit } from '@angular/core'
import { BehaviorSubject, map } from 'rxjs'
import { ApiService } from 'src/app/api/api.service'
import { PreviewData } from 'src/app/objects/preview-data'
import { AdapterService } from 'src/app/services/adapter.service'

@Injectable({
  providedIn: 'root',
})
export class DocGridService {
  private previewData: BehaviorSubject<PreviewData[]> = new BehaviorSubject<
    PreviewData[]
  >([])

  constructor(
    private apiService: ApiService,
    private adapter: AdapterService
  ) {}

  /**
   * Calls service functions which will fetch document previewData.
   * This data is subscribed and set
   */
  getData() {
    this.apiService
      .getAllDocuments()
      .pipe(
        map((apiData) =>
          apiData.map((apiItem) => this.adapter.convertFromAPI(apiItem))
        )
      )
      .subscribe((data) => {
        this.previewData.next(data)
      })
  }

  getPreviewData() {
    return this.previewData
  }
}
