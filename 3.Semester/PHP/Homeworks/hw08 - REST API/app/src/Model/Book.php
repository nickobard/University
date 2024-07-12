<?php declare(strict_types=1);

namespace Books\Model;

class Book extends AbstractModel
{
    private string $name;

    private string $author;

    private string $publisher;

    private string $isbn;

    private int $pages;

    /**
     * @param string $name
     * @param string $author
     * @param string $publisher
     * @param string $isbn
     * @param int $pages
     */
    public function __construct(string $name, string $author, string $publisher, string $isbn, int $pages)
    {
        $this->name = $name;
        $this->author = $author;
        $this->publisher = $publisher;
        $this->isbn = $isbn;
        $this->pages = $pages;
    }

    /**
     * @return string
     */
    public function getName(): string
    {
        return $this->name;
    }

    /**
     * @param string $name
     * @return Book
     */
    public function setName(string $name): Book
    {
        $this->name = $name;
        return $this;
    }

    /**
     * @return string
     */
    public function getAuthor(): string
    {
        return $this->author;
    }

    /**
     * @param string $author
     * @return Book
     */
    public function setAuthor(string $author): Book
    {
        $this->author = $author;
        return $this;
    }

    /**
     * @return string
     */
    public function getPublisher(): string
    {
        return $this->publisher;
    }

    /**
     * @param string $publisher
     * @return Book
     */
    public function setPublisher(string $publisher): Book
    {
        $this->publisher = $publisher;
        return $this;
    }

    /**
     * @return string
     */
    public function getIsbn(): string
    {
        return $this->isbn;
    }

    /**
     * @param string $isbn
     * @return Book
     */
    public function setIsbn(string $isbn): Book
    {
        $this->isbn = $isbn;
        return $this;
    }

    /**
     * @return int
     */
    public function getPages(): int
    {
        return $this->pages;
    }

    /**
     * @param int $pages
     * @return Book
     */
    public function setPages(int $pages): Book
    {
        $this->pages = $pages;
        return $this;
    }


    /** @inheritDoc */
    public static final function getTableName(): string
    {
        return "book";
    }

    /** @inheritDoc */
    public static final function fromArray(array $data): ?AbstractModel
    {
        if (!isset($data['id'])
            || !isset($data['name'])
            || !isset($data['author'])
            || !isset($data['publisher'])
            || !isset($data['isbn'])
            || !isset($data['pages'])) {
            return null;
        }

        $book = new Book($data['name'], $data['author'], $data['publisher'], $data['isbn'], $data['pages']);
        $book->id = $data['id'];

        return $book;
    }

    /** @inheritDoc */
    public function toArray(): array
    {
        return [
            'id' => $this->id,
            'name' => $this->name,
            'author' => $this->author,
            'publisher' => $this->publisher,
            'isbn' => $this->isbn,
            'pages' => $this->pages
        ];
    }
}
