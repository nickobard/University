import { NgModule } from '@angular/core'
import { RouterModule, Routes } from '@angular/router'
import { DocReviewerComponent } from './layout/doc_reviewer/doc-reviewer/doc-reviewer.component'
import { MainDashboardComponent } from './layout/main_dashboard/main-dashboard/main-dashboard.component'
import { DocSubmitterComponent } from './layout/doc_submitter/doc-submitter/doc-submitter.component'
import { DiscussionPosterComponent } from './layout/common_components/discussion_poster/discussion-poster/discussion-poster.component'

const routes: Routes = [
  { path: 'documents', component: MainDashboardComponent },
  {
    path: 'documents/:public_document_uuid',
    component: DocReviewerComponent,
    children: [
      {
        path: 'discussion/:public_document_uuid',
        component: DiscussionPosterComponent,
      },
    ],
  },
  {
    path: 'documents/submitted/:private_document_uuid',
    component: DocSubmitterComponent,
  },
]

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule],
})
export class AppRoutingModule {}
