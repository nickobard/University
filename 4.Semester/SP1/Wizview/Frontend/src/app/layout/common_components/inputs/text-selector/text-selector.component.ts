import { Component } from '@angular/core'
import { SelectionData } from 'src/app/objects/selection-data'
import { TextSelectorService } from './text-selector.service'
import { MatFormField } from '@angular/material/form-field'
import { MatFormFieldControl } from '@angular/material/form-field'

@Component({
  selector: 'app-text-selector',
  templateUrl: './text-selector.component.html',
  styleUrls: ['./text-selector.component.scss'],
})
export class TextSelectorComponent {
  selections: SelectionData[] = []
  activatedLinksId: number[] = []
  link_id = 0
  commentText = ''
  TEXT_ID = 'selection'

  constructor(private textSelectorService: TextSelectorService) {}

  submitComment() {
    console.log(this.selections)
    console.log(this.commentText)
    // text needs to be converted for backend
  }

  onSelection(event: MouseEvent) {
    const selection = window.getSelection()
    const selectedElementsIds =
      this.textSelectorService.getSelectedParagraphIDs(selection!)

    this.selections.push(
      this.textSelectorService.getSelectionData(
        selection!,
        this.TEXT_ID,
        this.link_id,
        selectedElementsIds
      )
    )
    this.commentText += `#${this.link_id}#`
    this.link_id++
  }
}
