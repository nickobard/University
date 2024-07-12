import { TestBed } from '@angular/core/testing'

import { DiscussionWindowService } from './discussion-window.service'

describe('DiscussionWindowService', () => {
  let service: DiscussionWindowService

  beforeEach(() => {
    TestBed.configureTestingModule({})
    service = TestBed.inject(DiscussionWindowService)
  })

  it('should be created', () => {
    expect(service).toBeTruthy()
  })
})
