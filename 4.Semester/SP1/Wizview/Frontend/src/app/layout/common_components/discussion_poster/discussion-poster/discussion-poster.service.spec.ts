import { TestBed } from '@angular/core/testing'

import { DiscussionPosterService } from './discussion-poster.service'

describe('DiscussionPosterService', () => {
  let service: DiscussionPosterService

  beforeEach(() => {
    TestBed.configureTestingModule({})
    service = TestBed.inject(DiscussionPosterService)
  })

  it('should be created', () => {
    expect(service).toBeTruthy()
  })
})
