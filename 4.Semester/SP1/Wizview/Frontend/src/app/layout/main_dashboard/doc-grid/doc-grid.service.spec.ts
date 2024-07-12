import { TestBed } from '@angular/core/testing'

import { DocGridService } from './doc-grid.service'

describe('DocGridService', () => {
  let service: DocGridService

  beforeEach(() => {
    TestBed.configureTestingModule({})
    service = TestBed.inject(DocGridService)
  })

  it('should be created', () => {
    expect(service).toBeTruthy()
  })
})
