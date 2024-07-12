# Task 8: REST API

Your task is to create a simple REST API for managing books. The API allows viewing existing books, creating new ones, and updating or deleting existing ones.

Choose a persistent storage of your choice (e.g., SQLite or file) to store information about books. Each book consists of the following fields:

- `id`
- `name`
- `author`
- `publisher`
- `isbn`
- `pages`

Anyone can view existing records. Only authorized users can perform operations that modify records, verified via HTTP Basic Auth. For this task, hardcode the user `admin` with password `pas$word`.

The skeleton of the application is provided in `public/index.php`.

You do not need to implement everything in one script; you have the `Books` namespace set up in the `src` folder, so create additional classes as needed to keep the code organized.

## Running the Application

If you are using the [pre-prepared Docker setup](https://gitlab.fit.cvut.cz/BI-PHP/bi-php-docker), it already includes an example application. To replace it with HW-08, adjust paths in the configuration (see [README at the end](https://gitlab.fit.cvut.cz/BI-PHP/bi-php-docker#kde-se-mohu-pod%C3%ADvat-na-uk%C3%A1zkovou-aplikaci)) or directly insert HW08 sources into `/src/` in Docker.

If you are not using Docker, you can run the application using the PHP built-in server: `$ php -S localhost:8080 -t public public/index.php`, or any custom web server.

---

## List of Stored Books (1 point)

**Request**

```text
GET /books
```


**Success Response**

Returns a list of stored books. If no books are stored, it returns an empty list. The list of books includes only `id`, `name`, and `author`.

```text
< 200 OK

[{
    "id": 1,
    "name": "The Little Prince",
    "author": "Antoine de Saint-Exupéry"  
}, {
    ...
}]
```


---

## Book Details (0.5 points)

**Request**

```text
GET /books/
```


**Success Response**

Returns the details of a book, including all fields.

```text
< 200 OK

{
    "id": 1,
    "name": "The Little Prince",
    "author": "Antoine de Saint-Exupéry",
    "publisher": "Mariner Books",
    "isbn": "978-0156012195",
    "pages": 96
}
```


**Error Response**

Returns HTTP error 404 if the `id` does not exist.

```text
< 404 Not Found
```

---

## Create a New Book 🔐 (2 points)

**Request**

Only an authorized user can create a new book, verified via HTTP Basic Auth. All information about the book must be sent.

```text
> POST /books

Authorization: Basic <token>
Content-Type: application/json


{
    "name": "The Little Prince",
    "author": "Antoine de Saint-Exupéry",
    "publisher": "Mariner Books",
    "isbn": "978-0156012195",
    "pages": 96
}
```

**Success Response**

The server automatically generates the `id` of the new book and returns a `Location` header containing the URL of the new book.

```text
< 201 Created

Location: /books/
```


**Unauthorized Error Response**

Returns HTTP error 401 if the user does not provide the correct token or does not provide one at all.

```text
< 401 Unauthorized
```


**Bad Request Error Response**

Returns HTTP error 400 if the request does not contain all information about the book. Optionally, you can return information about the missing data in JSON format.

```text
< 400 Bad Request
```


---

## Update an Existing Book 🔐 (1.5 points)

**Request**

Only an authorized user can update an existing book, verified via HTTP Basic Auth. The entire set of information must be resent, completely replacing the existing record; the `id` remains the same.

```text
> PUT /books/:id

Authorization: Basic <token>
Content-Type: application/json


{
    "name": "The Little Prince",
    "author": "Antoine de Saint-Exupéry",
    "publisher": "Mariner Books",
    "isbn": "978-0156012195",
    "pages": 96
}
```


**Success Response**

Returns HTTP status 204 with no content upon successful update.

```text
< 204 No Content
```


**Unauthorized Error Response**

Returns HTTP error 401 if the user does not provide the correct token or does not provide one at all.

```text
< 401 Unauthorized
```


**Not Found Error Response**

Returns HTTP error 404 if the user is correctly authorized but tries to update a non-existing record.

```text
< 404 Not Found
```


**Bad Request Error Response**

Similar to creating a new book, verify that all data is sent in the request.

```text
< 400 Bad Request
```


---

## Delete a Book 🔐 (1 point)

**Request**

Only an authorized user can delete a book.

```text
> DELETE /books/:id

Authorization: Basic <token>
```


**Success Response**

Returns HTTP status 204 with no content upon successful deletion.

```text
< 204 No Content
```


**Unauthorized Error Response**

Returns HTTP error 401 if the user does not provide the correct token or does not provide one at all.

```text
< 401 Unauthorized
```


**Not Found Error Response**

Returns HTTP error 404 if the user is correctly authorized but tries to delete a non-existing record.

```text
< 404 Not Found
```