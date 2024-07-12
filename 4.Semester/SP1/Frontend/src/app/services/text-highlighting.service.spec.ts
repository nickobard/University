import { TestBed } from '@angular/core/testing'

import { TextHighlightingService } from './text-highlighting.service'

describe('TextHighlightingService', () => {
  let service: TextHighlightingService

  beforeEach(() => {
    TestBed.configureTestingModule({})
    service = TestBed.inject(TextHighlightingService)
  })

  it('should be created', () => {
    expect(service).toBeTruthy()
  })
})
