import { ComponentFixture, TestBed } from '@angular/core/testing'

import { CommentBasicComponent } from './comment-basic.component'

describe('CommentBasicComponent', () => {
  let component: CommentBasicComponent
  let fixture: ComponentFixture<CommentBasicComponent>

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [CommentBasicComponent],
    }).compileComponents()

    fixture = TestBed.createComponent(CommentBasicComponent)
    component = fixture.componentInstance
    fixture.detectChanges()
  })

  it('should create', () => {
    expect(component).toBeTruthy()
  })
})
