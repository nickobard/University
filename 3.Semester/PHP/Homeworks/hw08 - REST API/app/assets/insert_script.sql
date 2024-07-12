drop table if exists book;

create table book
(
    name      text not null,
    author    text,
    publisher text,
    isbn      text,
    pages     integer,
    id        serial
        constraint product_pk
            primary key
);

alter table book
    owner to dev;

insert into book (name, author, publisher, isbn, pages)
values ('The Little Prince 1', 'Antoine de Saint-Exupéry', 'Mariner Books', '978-0156012195', 96),
       ('The Little Prince 2', 'Antoine de Saint-Exupéry', 'Mariner Books', '978-0156012196', 106),
       ('The Little Prince 3', 'Antoine de Saint-Exupéry', 'Mariner Books', '978-0156012197', 23)