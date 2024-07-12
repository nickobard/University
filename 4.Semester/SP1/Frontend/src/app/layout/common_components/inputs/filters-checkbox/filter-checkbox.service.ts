import { Injectable } from '@angular/core'
import { FilterData } from 'src/app/objects/filter-data'

@Injectable({
  providedIn: 'root',
})
export class FilterCheckboxService {
  filterData: FilterData = {
    submitted_by_me: false,
    opened: false,
    closed: false,
  }

  constructor() {}

  getFilterValues(): FilterData {
    return this.filterData
  }

  updateCheckboxValues(filterData: FilterData) {
    this.filterData = filterData
    console.log(this.filterData)
  }

  getCheckboxValues() {
    const sel = document.querySelector('filters')
  }
}
