import { NgModule } from '@angular/core'
import { BrowserModule } from '@angular/platform-browser'
import { CommonModule } from '@angular/common'

import { AppRoutingModule } from './app-routing.module'
import { AppComponent } from './app.component'
import { ItemCardComponent } from './layout/common_components/cards/item-card/item-card.component'
import { TextSelectorComponent } from './layout/common_components/inputs/text-selector/text-selector.component'
import { CommentComponent } from './layout/common_components/comments/comment/comment.component'

import { MatFormFieldModule } from '@angular/material/form-field'
import { MatInputModule } from '@angular/material/input'
import { ReactiveFormsModule } from '@angular/forms'
import { FormsModule } from '@angular/forms'
import {
  BrowserAnimationsModule,
  NoopAnimationsModule,
} from '@angular/platform-browser/animations'
import { DocGridComponent } from './layout/main_dashboard/doc-grid/doc-grid.component'
import { SearchInputComponent } from './layout/common_components/inputs/search-input/search-input.component'
import { MatIconModule } from '@angular/material/icon'
import { FiltersCheckboxComponent } from './layout/common_components/inputs/filters-checkbox/filters-checkbox.component'
import { MatCheckboxModule } from '@angular/material/checkbox'
import { SearchButtonComponent } from './layout/common_components/buttons/search-button/search-button.component'
import { MatButtonModule } from '@angular/material/button'
import { SearchAndFilterComponent } from './layout/main_dashboard/search-and-filter/search-and-filter.component'
import { NavbarComponent } from './layout/common_components/navbar/navbar.component'
import { MatSlideToggleModule } from '@angular/material/slide-toggle'
import { HttpClientModule } from '@angular/common/http'
import { DocReviewerComponent } from './layout/doc_reviewer/doc-reviewer/doc-reviewer.component'
import { DocumentViewComponent } from './layout/common_components/document/document-view/document-view.component'
import { MainDashboardComponent } from './layout/main_dashboard/main-dashboard/main-dashboard.component'
import { DocSubmitterComponent } from './layout/doc_submitter/doc-submitter/doc-submitter.component'
import { SimpleButtonComponent } from './layout/common_components/buttons/simple-button/simple-button.component'
import { BasicTextInputComponent } from './layout/common_components/inputs/basic-text-input/basic-text-input.component'
import { MatGridListModule } from '@angular/material/grid-list'
import { MatCardModule } from '@angular/material/card'
import { DiscussionPosterComponent } from './layout/common_components/discussion_poster/discussion-poster/discussion-poster.component'
import { MatListModule } from '@angular/material/list'
import { CommentBasicComponent } from './layout/common_components/comments/comment_basic/comment-basic/comment-basic.component'
import { DiscussionCommentComponent } from './layout/common_components/comments/discussion-comment/discussion-comment.component'
import { DiscussionWindowComponent } from './layout/common_components/comments/discussion-window/discussion-window.component'
import { MatToolbarModule } from '@angular/material/toolbar'
import {
  MatButtonToggleGroup,
  MatButtonToggleModule,
} from '@angular/material/button-toggle'
@NgModule({
  declarations: [
    AppComponent,
    ItemCardComponent,
    CommentComponent,
    TextSelectorComponent,
    DocGridComponent,
    SearchInputComponent,
    FiltersCheckboxComponent,
    SearchButtonComponent,
    SearchAndFilterComponent,
    NavbarComponent,
    DocReviewerComponent,
    DocumentViewComponent,
    MainDashboardComponent,
    DocSubmitterComponent,
    SimpleButtonComponent,
    BasicTextInputComponent,
    DiscussionPosterComponent,
    CommentBasicComponent,
    DiscussionCommentComponent,
    DiscussionWindowComponent,
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    MatFormFieldModule,
    MatInputModule,
    ReactiveFormsModule,
    FormsModule,
    BrowserAnimationsModule,
    MatIconModule,
    MatCheckboxModule,
    MatButtonModule,
    MatSlideToggleModule,
    HttpClientModule,
    MatGridListModule,
    MatGridListModule,
    MatCardModule,
    MatListModule,
    BrowserAnimationsModule,
    NoopAnimationsModule,
    MatToolbarModule,
    MatButtonToggleModule,
  ],
  providers: [],
  bootstrap: [AppComponent],
})
export class AppModule {}
