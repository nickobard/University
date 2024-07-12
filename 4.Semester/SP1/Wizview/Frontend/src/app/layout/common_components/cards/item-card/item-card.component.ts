import { Component, Input } from '@angular/core'
import { PreviewData } from '../../../../objects/preview-data'
import { ItemCardService } from './item-card.service'

@Component({
  selector: 'app-item-card',
  templateUrl: './item-card.component.html',
  styleUrls: ['./item-card.component.scss'],
})
export class ItemCardComponent {
  @Input() preview_data: PreviewData | undefined

  constructor(private itemCardService: ItemCardService) {}
  cardClick() {
    this.itemCardService.goToDocumentReviever(this.preview_data?.uuid!)
  }
}
