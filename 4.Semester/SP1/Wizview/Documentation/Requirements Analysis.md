# Requirements Analysis

# 1. <span dir="">Participants</span>

Within the SP1 subject, only one type of user was implemented. Different document permissions will be implemented in SP2. Differentiating participants still makes sense for use case purposes.

## 1.1 <span dir="">Submitter</span>

<span dir="">Submits a file created using DSW to the application to get feedback from reviewers. Can submit additional documents to the application and manage their submitted documents (change status, delete). Can communicate with reviewers by reacting to comments on the document.</span>

## 1.2 <span dir="">Reviewer</span>

<span dir="">The reviewer adds ratings and comments to the documents assigned to them by the submitter. Can interact with their comments. Reviewers for individual documents will be assigned by an external authority managing DSR.</span>

# 2. <span dir="">Use Cases</span>

## 2.1 <span dir="">Document Manipulation</span>

<span dir="">This chapter describes how users of the application can create new documents, view them, and manipulate them.</span>

### **<span dir="">UC1 - Create Document</span>**

<span dir="">Allows users to submit a document from the DSW service to our application for other users to review and provide feedback.</span>

<span dir="">Documents cannot be edited or updated in our application. Each document modification will be represented as uploading a new document.</span>

**<span dir="">Main Scenario:</span>**

1. <span dir="">The submitter accesses the Data Stewardship Wizard by clicking Add Document in our application.</span>
2. <span dir="">The submitter selects a document from DSW.</span>
3. <span dir="">Submits the document to our application in the chosen supported format.</span>
4. <span dir="">The system creates the document in the application.</span>
5. <span dir="">The document appears in the dashboard and document list for the submitter and assigned reviewers, who will have access to its review.</span>

**<span dir="">Alternative Scenario:</span>**

1. <span dir="">The submitter opens the Data Stewardship Wizard in their browser.</span>
2. <span dir="">Continues from the second step of the main scenario.</span>

### **<span dir="">UC2 - Close Document</span>**

<span dir="">The submitter can close the document (no one will be able to interact with it). This can be done either from the document list or directly in the document detail. The reviewer cannot close the document. The document cannot be deleted or removed from the document list.</span>

### **<span dir="">UC3 - Reopen Document</span>**

<span dir="">If the submitter has closed the document, they have the option to reopen it later.</span>

<span dir="">This can be done either from the document list or directly in the document detail.</span>

<span dir="">The reviewer does not have this permission.</span>

### **<span dir="">UC4 - View Document List</span>**

<span dir="">The user can view a list of documents they have access to. They can filter them based on whether they are the submitter or the reviewer of the document.</span>

<span dir="">The user can hide already closed documents.</span>

<span dir="">Documents cannot be sorted arbitrarily; they will be sorted by status and creation date.</span>

### **<span dir="">UC5 - View Document</span>**

<span dir="">The user can view an individual document. The page will display both the document and comments on it. Additionally, the submitter will see the document's ratings from reviewers. All comments will be displayed by default, but the user will be able to hide comments in the "resolved" state.</span>

## 2.2 <span dir="">Comments and Ratings</span>

<span dir="">This chapter describes the interaction of the submitter and reviewers with the document, specifically how comments and ratings work. Ratings were not implemented in SP1. Comments can be replied to, creating a thread. Comments can be edited, deleted, and marked as resolved.</span>

### **<span dir="">UC6 - Add Comment and Engage in Discussion</span>**

<span dir="">The submitter and reviewer can add comments to a specific part of the document and respond to them.</span>

**<span dir="">Main Scenario:</span>**

1. <span dir="">The use case starts with the desire to comment on the document.</span>
2. <span dir="">Include (View Document)</span>
3. <span dir="">The user adds a comment to a specific part of the document.</span>
4. <span dir="">Users can engage in a discussion under this comment by adding more comments.</span>
5. <span dir="">Continues from the third step of this scenario.</span>

**<span dir="">Exceptions:</span>**

1. <span dir="">The user does not have to add any comments or participate in the discussion.</span>

**<span dir="">Alternative Scenario (reply to another comment):</span>**

<span dir="">The scenario starts from the third step of the main scenario if the user decides to engage in a discussion under an existing comment.</span>

1. <span dir="">The user adds a comment to an existing discussion.</span>

### **<span dir="">UC7 - Mark Comment as "Resolved"</span>**

<span dir="">The submitter can mark a comment as "resolved," preventing further discussion under it. The submitter can re-mark the comment as "open" (default state), allowing discussion under it again.
**Main Scenario:**</span>

1. <span dir="">Include (View Document)</span>
2. <span dir="">The submitter marks the comment as "resolved."</span>
3. <span dir="">No more comments can be added under it. Comments marked as "resolved" are still visible, including any discussion under them.</span>
4. <span dir="">The submitter can re-mark the comment as "open" (default state).</span>
5. <span dir="">Continues from the second step of this scenario or ends.</span>

### **<span dir="">UC8 - Add Document Rating</span>**

<span dir="">**Not implemented in SP1!**
The reviewer can rate the document's content after reading it using a rating system. The rating will be in the form of selecting 1-5 stars. The reviewer can change their rating. Each rating can be associated with a discussion thread, similar to comment threads on a part of the document.</span>

# 

# 3. <span dir="">General Requirements</span>

* <span dir="">N1 – Web Accessibility</span>
  * <span dir="">The system will be accessible as a web application viewable in a web browser; no special mobile device application is required. The application will be responsive to allow easy viewing on tablets and mobile devices.</span>
  * <span dir="">Priority: M</span>
  * <span dir="">Category: U</span>
* <span dir="">N2 - Responsive Design</span>
  * <span dir="">The application will be responsive to allow easy viewing on tablets and mobile devices.</span>
  * <span dir="">Priority: S</span>
  * <span dir="">Category: U</span>
* <span dir="">N3 – Integration within the DSW Portal</span>
  * <span dir="">The application will be open to further modifications, extensions, and integration with the DSW portal.</span>
  * <span dir="">Priority: W</span>
  * <span dir="">Category: S</span>
* <span dir="">N4 – Real-time Display of Current Comments</span>
  * <span dir="">When a document is opened, the application will always show current comments without the need to reload the page.</span>
  * <span dir="">Priority: C</span>
  * <span dir="">Category: U</span>
* <span dir="">N5 - Application Speed</span>
  * <span dir="">The application will operate with a response time of < 1s for displaying current comments. The time to open/close documents in the application will not exceed 5s.</span>
  * <span dir="">Priority: S</span>
  * <span dir="">Category: P</span>
* <span dir="">N6 - User Interface</span>
  * <span dir="">The application will be controllable via a user interface. It will provide standard features expected by regular web application users, specifically:</span>
    * <span dir="">Switching between dark and light modes.</span>
    * <span dir="">Sorting and filtering documents in the dashboard (the dashboard is the home page seen by the user after logging in, where documents related to the user (reviewer/submitter) are displayed. From here, the user can access other application features via buttons).</span>
    * <span dir="">Ensuring via dialog pop-up that the user really wants to perform an irreversible action (e.g., deleting a document) to prevent accidental deletion due to a "misclick".</span>
    * <span dir="">Ability to add a document rating by entering a specific number or using the mouse (adjustable progress bar).</span>
  * <span dir="">Priority: S</span>
  * <span dir="">Category: U</span>
* <span dir="">N7 - Localization</span>
  * <span dir="">The application will be available in several supported languages and easily extendable to additional supported languages.</span>
  * <span dir="">Priority: C</span>
  * <span dir="">Category: U</span>

## 4. <span dir="">Negative Delimitations - What the System Will Not Be Able to Do</span>

* <span dir="">NV1 - The application will not allow the creation of new documents</span>
  * <span dir="">It will only accept already created documents from DS Wizard</span>
* <span dir="">NV2 - The application will not allow modification of document content</span>
* <span dir="">NV3 - The application will not accept all types of documents created in DS Wizard</span>
  * <span dir="">It will primarily accept only HTML format documents; support for other formats is an extension.</span>
* <span dir="">NV4 - The application will not automatically check and evaluate the document content.</span>
* <span dir="">NV5 - The application will be available only as a web application, there will be no mobile or desktop version</span>
