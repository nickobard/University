import { TestBed } from '@angular/core/testing'

import { FilterCheckboxService } from './filter-checkbox.service'

describe('FilterCheckboxService', () => {
  let service: FilterCheckboxService

  beforeEach(() => {
    TestBed.configureTestingModule({})
    service = TestBed.inject(FilterCheckboxService)
  })

  it('should be created', () => {
    expect(service).toBeTruthy()
  })
})
