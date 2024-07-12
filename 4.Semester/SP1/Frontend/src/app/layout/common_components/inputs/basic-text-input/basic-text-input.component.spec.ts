import { ComponentFixture, TestBed } from '@angular/core/testing'

import { BasicTextInputComponent } from './basic-text-input.component'

describe('BasicTextInputComponent', () => {
  let component: BasicTextInputComponent
  let fixture: ComponentFixture<BasicTextInputComponent>

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [BasicTextInputComponent],
    }).compileComponents()

    fixture = TestBed.createComponent(BasicTextInputComponent)
    component = fixture.componentInstance
    fixture.detectChanges()
  })

  it('should create', () => {
    expect(component).toBeTruthy()
  })
})
