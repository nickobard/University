import { ComponentFixture, TestBed } from '@angular/core/testing'

import { DiscussionWindowComponent } from './discussion-window.component'

describe('DiscussionWindowComponent', () => {
  let component: DiscussionWindowComponent
  let fixture: ComponentFixture<DiscussionWindowComponent>

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [DiscussionWindowComponent],
    }).compileComponents()

    fixture = TestBed.createComponent(DiscussionWindowComponent)
    component = fixture.componentInstance
    fixture.detectChanges()
  })

  it('should create', () => {
    expect(component).toBeTruthy()
  })
})
