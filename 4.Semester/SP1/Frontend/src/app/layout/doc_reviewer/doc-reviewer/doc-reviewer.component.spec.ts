import { ComponentFixture, TestBed } from '@angular/core/testing'

import { DocReviewerComponent } from './doc-reviewer.component'

describe('DocReviewerComponent', () => {
  let component: DocReviewerComponent
  let fixture: ComponentFixture<DocReviewerComponent>

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [DocReviewerComponent],
    }).compileComponents()

    fixture = TestBed.createComponent(DocReviewerComponent)
    component = fixture.componentInstance
    fixture.detectChanges()
  })

  it('should create', () => {
    expect(component).toBeTruthy()
  })
})
