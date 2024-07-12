import { Injectable } from '@angular/core'
import { SelectionData } from '../objects/selection-data'

@Injectable({
  providedIn: 'root',
})
export class TextHighlightingService {
  constructor() {}

  static highlightedMap = new Map<string, boolean>()
  static HIGHLIGHT_COLOR = 'cyan'
  static NOT_HIGHLIGHT_COLOR = 'white'
  static currentBackgroundColor = 'white'

  onClickLinkInComment(selection: SelectionData) {
    this.highlightSelectionMultipleElements(
      selection.initialIndex,
      selection.stopIndex,
      selection.elementsIds
    )
  }

  //Works iff id's of paragraph are convertable to number and if they are in a row
  private getSelectedElementsIDsByIteration(
    selection: globalThis.Selection
  ): string[] {
    const allParagraphIds = this.getAllParagraphIds()
    const ids: string[] = []
    const from = Number(selection?.anchorNode?.parentElement?.id)
    const to = Number(selection?.focusNode?.parentElement?.id)
    for (let i = from!; i! <= to!; i++) {
      ids.push(String(i))
    }
    return ids
  }

  private getAllParagraphIds(): string[] {
    const paragraphs = document.getElementsByTagName('p')
    const ids: string[] = []

    for (let i = 0; i < paragraphs.length; i++) {
      const id = paragraphs[i].id
      if (id) {
        ids.push(id)
      }
    }

    return ids
  }

  /**
   * highlights text which is selected through multiple paragraphs.
   * IMPORTANT: paragraph in which selection starts must be at the 0th index in @elementsIds,
   * paragraph in which selection ends must be the last element of @elementsIds !!!
   * @param initialIndex
   * @param stopIndex
   * @param elementsIds id of paragraphs in which text is located.
   * @returns
   */
  highlightSelectionMultipleElements(
    initialIndex: number,
    stopIndex: number,
    elementsIds: string[]
  ) {
    this.setHighlightColor(initialIndex, stopIndex)
    if (elementsIds.length == 1) {
      this.highlightSelectionFromTo(initialIndex, stopIndex, elementsIds[0])
      return
    }
    const firstElem = document.getElementById(elementsIds[0]) as HTMLElement
    this.highlightSelectionFromTo(
      initialIndex,
      firstElem.textContent ? firstElem.textContent.length : 0,
      firstElem.id
    )
    for (var i = 1; i < elementsIds.length - 1; i++) {
      this.highlightSelectionFromTo(
        0,
        document.getElementById(elementsIds[i])?.textContent?.length!,
        elementsIds[i]
      )
    }
    this.highlightSelectionFromTo(
      0,
      stopIndex,
      elementsIds[elementsIds.length - 1]
    )
  }

  private setHighlightColor(initialIndex: number, stopIndex: number) {
    // Generate a hash for the key
    const hash = this.getHash(initialIndex, stopIndex)

    // Check if the key already exists in the map
    const existingValue = TextHighlightingService.highlightedMap.get(hash)
    if (existingValue !== undefined) {
      // Key exists -> toggle the highlight
      TextHighlightingService.currentBackgroundColor = existingValue
        ? TextHighlightingService.NOT_HIGHLIGHT_COLOR
        : TextHighlightingService.HIGHLIGHT_COLOR
      TextHighlightingService.highlightedMap.set(hash, !existingValue)
    } else {
      // Key doesn't exist -> add it to the map
      TextHighlightingService.currentBackgroundColor =
        TextHighlightingService.HIGHLIGHT_COLOR
      TextHighlightingService.highlightedMap.set(hash, true)
    }
  }

  private getHash(initialIndex: number, stopIndex: number): string {
    return `${initialIndex}:${stopIndex}`
  }

  /**
   * Highlights selection, which is located within 1 paragraph
   * @param initialIndex
   * @param stopIndex
   * @param paragraphId
   */
  private highlightSelectionFromTo(
    initialIndex: number,
    stopIndex: number,
    paragraphId: string
  ) {
    const paragraph = document.getElementById(paragraphId) as HTMLElement
    const text = paragraph.textContent!
    console.log(TextHighlightingService.currentBackgroundColor)
    //this.highlightedIndexes = [initialIndex,stopIndex];
    const markedText = `${text.slice(
      0,
      initialIndex
    )}<mark style="background-color:
      ${TextHighlightingService.currentBackgroundColor};">${text.slice(
      initialIndex,
      stopIndex
    )}</mark>${text.slice(stopIndex)}`

    paragraph.innerHTML = markedText
  }
}
