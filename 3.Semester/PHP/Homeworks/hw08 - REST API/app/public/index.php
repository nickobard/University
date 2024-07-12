<?php declare(strict_types=1);

use Books\Middleware\JsonBodyParserMiddleware;
use Books\Middleware\SecurityMiddleware;
use Books\Model\Book;
use Psr\Http\Message\ResponseInterface as Response;
use Psr\Http\Message\ServerRequestInterface as Request;
use Slim\Factory\AppFactory;

require __DIR__ . '/../vendor/autoload.php';

$app = AppFactory::create();

$app->addRoutingMiddleware();
$app->addErrorMiddleware(true, true, true);
$app->add(new JsonBodyParserMiddleware());

$app->get('/', function (Request $request, Response $response) {
    $response->getBody()->write('Funguje to! Ale nic tady není.');
    return $response;
});

$app->get('/books', function (Request $request, Response $response, $args) {
    $books = Book::all();
    $serialized = [];
    foreach ($books as $book) {
        $serialized[] = [
            'id' => $book->getId(),
            'name' => $book->getName(),
            'author' => $book->getAuthor()
        ];
    }
    $payload = json_encode($serialized);
    $response->getBody()->write($payload);
    return $response->withHeader('Content-Type', 'application/json')->withStatus(200);
});

$app->get('/books/{bookId}', function (Request $request, Response $response, $args): Response {
    $book = Book::find(intval($args['bookId']));
    if (is_null($book)) {
        return $response->withStatus(404);
    }
    $payload = json_encode($book->toArray());
    $response->getBody()->write($payload);
    return $response->withHeader('Content-Type', 'application/json')->withStatus(200);
});


$app->post('/books', function (Request $request, Response $response, $args): Response {
    $data = $request->getParsedBody();
    if (!isset($data['name'])
        || !isset($data['author'])
        || !isset($data['publisher'])
        || !isset($data['isbn'])
        || !isset($data['pages'])) {
        return $response->withStatus(400);
    }

    $book = new Book($data['name'], $data['author'], $data['publisher'], $data['isbn'], intval($data['pages']));
    if (!$book->save()) {
        return $response->withStatus(409);
    }

    return $response->withStatus(201)->withHeader('Location', '/books/' . $book->getId());
})->addMiddleware(new SecurityMiddleware());


$app->put('/books/{bookId}', function (Request $request, Response $response, $args): Response {
    $book = Book::find(intval($args['bookId']));
    if (is_null($book)) {
        return $response->withStatus(404);
    }

    $data = $request->getParsedBody();

    if (!isset($data['name'])
        || !isset($data['author'])
        || !isset($data['publisher'])
        || !isset($data['isbn'])
        || !isset($data['pages'])) {
        return $response->withStatus(400);
    }

    $book
        ->setName($data['name'])
        ->setAuthor($data['author'])
        ->setPublisher($data['publisher'])
        ->setIsbn($data['isbn'])
        ->setPages(intval($data['pages']));

    if (!$book->save()) {
        return $response->withStatus(409);
    }

    return $response->withStatus(204)->withHeader('Location', '/books/' . $book->getId());
})->addMiddleware(new SecurityMiddleware());


$app->delete('/books/{bookId}', function (Request $request, Response $response, $args): Response {
    $book = Book::find(intval($args['bookId']));
    if (is_null($book)) {
        return $response->withStatus(404);
    }
    if (!$book->delete()) {
        return $response->withStatus(409);
    }

    return $response->withStatus(204);
})->addMiddleware(new SecurityMiddleware());

$app->run();
