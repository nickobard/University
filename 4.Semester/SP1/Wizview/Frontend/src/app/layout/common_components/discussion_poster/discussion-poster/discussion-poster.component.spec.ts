import { ComponentFixture, TestBed } from '@angular/core/testing'

import { DiscussionPosterComponent } from './discussion-poster.component'

describe('DiscussionPosterComponent', () => {
  let component: DiscussionPosterComponent
  let fixture: ComponentFixture<DiscussionPosterComponent>

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [DiscussionPosterComponent],
    }).compileComponents()

    fixture = TestBed.createComponent(DiscussionPosterComponent)
    component = fixture.componentInstance
    fixture.detectChanges()
  })

  it('should create', () => {
    expect(component).toBeTruthy()
  })
})
