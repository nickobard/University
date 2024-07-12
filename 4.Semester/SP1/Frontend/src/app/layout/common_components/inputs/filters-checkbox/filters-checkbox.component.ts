import { Component, OnInit } from '@angular/core'
import { FormBuilder } from '@angular/forms'
import { FilterCheckboxService } from './filter-checkbox.service'
import { FilterData } from 'src/app/objects/filter-data'

@Component({
  selector: 'app-filters-checkbox',
  templateUrl: './filters-checkbox.component.html',
  styleUrls: ['./filters-checkbox.component.scss'],
})
export class FiltersCheckboxComponent implements OnInit {
  filters = this._formBuilder.group({
    submitted_by_me: [false],
    opened: [false],
    closed: [false],
  })

  constructor(
    private _formBuilder: FormBuilder,
    private filtersCheckBoxService: FilterCheckboxService
  ) {}

  ngOnInit(): void {
    this.filters.valueChanges.subscribe((values) => {
      this.filtersCheckBoxService.updateCheckboxValues({
        submitted_by_me: values.submitted_by_me!,
        opened: values.opened!,
        closed: values.closed!,
      })
    })
  }
}
