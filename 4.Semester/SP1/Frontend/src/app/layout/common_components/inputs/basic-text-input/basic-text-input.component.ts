import { Component, EventEmitter, Output } from '@angular/core'

@Component({
  selector: 'app-basic-text-input',
  templateUrl: './basic-text-input.component.html',
  styleUrls: ['./basic-text-input.component.scss'],
})
export class BasicTextInputComponent {
  @Output() inputTextChanged = new EventEmitter<string>()
  textInput: string = ''

  constructor() {}

  onInput(event: Event) {
    const text = (event.target as HTMLTextAreaElement).value
    this.textInput = text
    this.inputTextChanged.emit(text)
  }

  public clearInput(): void {
    this.textInput = ''
  }
}
