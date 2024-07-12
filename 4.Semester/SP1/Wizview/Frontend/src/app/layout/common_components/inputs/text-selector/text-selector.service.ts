import { Injectable } from '@angular/core'
import { TextHighlightingService } from 'src/app/services/text-highlighting.service'
import { SelectionData } from 'src/app/objects/selection-data'

@Injectable({
  providedIn: 'root',
})
export class TextSelectorService {
  constructor(private textHighlightingService: TextHighlightingService) {}

  getSelectionData(
    selection: globalThis.Selection,
    linkHref: string,
    linkId: number,
    paragraphIds: string[]
  ) {
    const range = selection!.getRangeAt(0)

    const link = document.createElement('a')
    link.href = '#' + linkHref
    link.innerText = `${linkId}`
    link.id = `${linkId}`

    link.addEventListener('click', () => {
      this.textHighlightingService.highlightSelectionMultipleElements(
        range.startOffset,
        range.endOffset,
        paragraphIds
      )
    })

    const s: SelectionData = {
      id: linkId,
      initialIndex: range.startOffset,
      stopIndex: range.endOffset,
      elementsIds: paragraphIds,
    }
    return s
  }

  getSelectedParagraphIDs(selection: globalThis.Selection): string[] {
    return this.getSelectedElementsIDsByNextElementSibling(selection)
  }

  private getSelectedElementsIDsByNextElementSibling(
    selection: globalThis.Selection
  ): string[] {
    var id: string[] = []
    var curr: Element | null | undefined = selection?.anchorNode?.parentElement
    console.log(curr)
    while (curr?.id != selection?.focusNode?.parentElement?.id) {
      id.push(curr!.id)
      curr = curr?.nextElementSibling
    }
    id.push(curr!.id)
    return id
  }
}
