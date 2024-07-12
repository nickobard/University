import { ComponentFixture, TestBed } from '@angular/core/testing'

import { DocSubmitterComponent } from './doc-submitter.component'

describe('DocSubmitterComponent', () => {
  let component: DocSubmitterComponent
  let fixture: ComponentFixture<DocSubmitterComponent>

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [DocSubmitterComponent],
    }).compileComponents()

    fixture = TestBed.createComponent(DocSubmitterComponent)
    component = fixture.componentInstance
    fixture.detectChanges()
  })

  it('should create', () => {
    expect(component).toBeTruthy()
  })
})
