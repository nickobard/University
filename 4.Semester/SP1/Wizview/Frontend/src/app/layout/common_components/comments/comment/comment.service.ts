import { Injectable } from '@angular/core'
import { SelectionData } from 'src/app/objects/selection-data'
import { TextHighlightingService } from 'src/app/services/text-highlighting.service'
import { TextSelectorService } from '../../inputs/text-selector/text-selector.service'

@Injectable({
  providedIn: 'root',
})
export class CommentService {
  constructor(private textHighlightingService: TextHighlightingService) {}

  changeCommentState() {
    console.log('clicked from service')
  }

  replaceTokensWithLinks(
    delimiters: string[],
    href: string,
    linkInnerTexts: string[],
    commentTextId: string,
    text: String,
    selections: SelectionData[]
  ) {
    const output = document.getElementById(commentTextId)
    output?.appendChild(
      this.recConstructCommentText(
        delimiters,
        href,
        linkInnerTexts,
        text,
        selections
      )
    )
  }

  private tokenizeText(text: String, delimiters: string[]): string[] {
    let tokens: String[] = [text]

    for (const delimiter of delimiters) {
      tokens = tokens.flatMap((token) => token.split(delimiter))
    }
    return tokens
      .filter((token) => token.trim() !== '')
      .map((token) => token.toString())
  }

  private getLinkInnerText(
    delimiter: string,
    delimiters: string[],
    linkInnerTexts: string[]
  ): string {
    const index = delimiters.indexOf(delimiter)
    if (index == -1) {
      return ''
    }
    return linkInnerTexts[index]
  }

  private splitStringByFirstToken(s: String, tokens: string[]): String[] {
    let index = -1
    let token: string | undefined

    for (const t of tokens) {
      const i = s.indexOf(t)
      if (i !== -1 && (i < index || index === -1)) {
        index = i
        token = t
      }
    }

    if (index === -1 || !token) {
      // Token not found in string
      return [s, '']
    }

    return [s.slice(0, index), token, s.slice(index + token.length)]
  }

  private getSelection(
    delimiter: string,
    delimiters: string[],
    selections: SelectionData[]
  ): SelectionData {
    const id = parseInt(delimiter.replace(/#/g, ''))
    for (const sel of selections) {
      if (sel.id === id) {
        return sel
      }
    }
    return selections[0] // default return value if no matching selection is found
  }

  private recConstructCommentText(
    delimiters: string[],
    href: string,
    linkInnerTexts: string[],
    text: String,
    selections: SelectionData[]
  ) {
    if (text == '') return document.createElement('p')

    const splitted = this.splitStringByFirstToken(text, delimiters)
    const token = splitted[0]
    const delim = splitted[1]

    const paragraph = document.createElement('p')
    paragraph.style.display = 'inline-block'
    paragraph.textContent = token.toString()

    const link = document.createElement('a')
    link.href = href
    link.innerText = this.getLinkInnerText(
      delim.toString(),
      delimiters,
      linkInnerTexts
    )
    link.addEventListener('click', () => {
      this.textHighlightingService.onClickLinkInComment(
        this.getSelection(delim.toString(), delimiters, selections)
      )
    })

    paragraph.appendChild(link)
    paragraph.appendChild(
      this.recConstructCommentText(
        delimiters,
        href,
        linkInnerTexts,
        splitted[2] ?? '',
        selections
      )
    )
    return paragraph
  }
}
