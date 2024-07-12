import { Component, Input, OnInit } from '@angular/core'
import { ItemCardComponent } from '../../common_components/cards/item-card/item-card.component'
import { PreviewData } from 'src/app/objects/preview-data'
import { CARDS } from 'src/test-data/preview-data'
import { DocGridService } from './doc-grid.service'
import { BehaviorSubject, map } from 'rxjs'
import { AdapterService } from 'src/app/services/adapter.service'
@Component({
  selector: 'app-doc-grid',
  templateUrl: './doc-grid.component.html',
  styleUrls: ['./doc-grid.component.scss'],
})
export class DocGridComponent implements OnInit {
  previewData: BehaviorSubject<PreviewData[]> = new BehaviorSubject<
    PreviewData[]
  >([])
  previewDataArray: PreviewData[] = []

  constructor(
    private docGridService: DocGridService,
    private adapter: AdapterService
  ) {}

  ngOnInit(): void {
    this.docGridService.getData()
    this.docGridService.getPreviewData().subscribe((data) => {
      this.previewDataArray = data
    })
  }
}
