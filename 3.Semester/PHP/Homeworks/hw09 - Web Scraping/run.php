<?php declare(strict_types=1);

use Goutte\Client;
use Symfony\Component\DomCrawler\Crawler;

require __DIR__ . '/vendor/autoload.php';

const DELAY = 10_000; // microseconds - 1 second totally

const NAME_MATCH_THRESHOLD = 0.5;
const DETAILS_MATCH_THRESHOLD = 0.5;


const ESHOPS = [
    'ALZA' => [
        'BASE_URL' => 'https://www.alza.cz',
        'SEARCH_SEPARATOR' => '%20',
        'SEARCH_URL' => 'https://www.alza.cz/search.htm?exps=',
        'ITEMS_LIST_SELECTOR' => 'div#boxes > div[class~=box]',
        'DETAILS_LINK_SELECTOR' => 'a',
        'ITEM_NAME_SELECTOR' => 'h1[itemprop=name]',
        'ITEM_PRICE_SELECTOR' => 'span.price-box__price',
        'ITEM_DETAILS_SELECTOR' => 'div#detailText span'

    ]
    ,
    'DATART' => [
        'BASE_URL' => 'https://www.datart.cz',
        'SEARCH_SEPARATOR' => '+',
        'SEARCH_URL' => 'https://www.datart.cz/vyhledavani?q=',
        'ITEMS_LIST_SELECTOR' => 'div.product-box-list div.product-box',
        'DETAILS_LINK_SELECTOR' => 'a.product-box-link-box',
        'ITEM_NAME_SELECTOR' => 'h1[class|=product-detail-title]',
        'ITEM_PRICE_SELECTOR' => 'div.price-wrap',
        'ITEM_DETAILS_SELECTOR' => 'p.perex'

    ]
];

function getPrice(string $price): float
{
    preg_match_all('/\d/', $price, $matches);
    return floatval(implode('', $matches[0]));
}


/**
 * @param Crawler $crawler
 * @param string $selector
 * @return string|null
 */
function text(Crawler $crawler, string $selector): ?string
{
    $new = $crawler->filter($selector);
    if (count($new)) {
        return trim($new->text());
    }

    return null;
}

/**
 * @param string $query - query string e.g. 'Beats Studio3'
 * @return array
 */
function scrape(string $query): array
{
    echo "Scraping..." . PHP_EOL;

    $results = [];
    $query_words = preg_split('/\s+/', trim($query));

    foreach (ESHOPS as $eshop) {

        echo '...from eshop ' . $eshop['BASE_URL'] . PHP_EOL;

        $query = implode($eshop['SEARCH_SEPARATOR'], $query_words);
        $query_url = $eshop['SEARCH_URL'] . $query;

        $client = new Client();
        $crawler = $client->request('GET', $query_url);

        usleep(DELAY);

        $crawler->filter($eshop['ITEMS_LIST_SELECTOR'])->each(function (Crawler $node) use (&$results, &$client, &$eshop) {
            $details_node = $node->filter($eshop['DETAILS_LINK_SELECTOR']);

            if (!$details_node->count()) {
                echo "No link to details page." . PHP_EOL;
                return;
            }

            $details_url_suffix = $details_node->attr('href');

            if (is_null($details_url_suffix) || !str_starts_with($details_url_suffix, "/")) {
                echo "Link to details is empty." . PHP_EOL;
                return;
            }

            $details_url = $eshop['BASE_URL'] . $details_url_suffix;
            $details_page = $client->request('GET', $details_url);

            usleep(DELAY);

            if (!$details_page->count()) {
                echo "Details page is empty or not found." . PHP_EOL;
                return;
            }
            $name = text($details_page, $eshop['ITEM_NAME_SELECTOR']);
            $price = text($details_page, $eshop['ITEM_PRICE_SELECTOR']);
            $details = text($details_page, $eshop['ITEM_DETAILS_SELECTOR']);

            echo "Adding item to results..." . PHP_EOL;

            $results[] = [
                'name' => $name,
                'price' => $price,
                'description' => $details,
                'link' => $details_url,
                'eshop' => $eshop['BASE_URL']
            ];
        });
    }
    return $results;
}

/**
 * @param string $query - query string e.g. 'Beats Studio 3'
 * @param array $results - input product collection
 * @return array
 */
function filter(string $query, array $results, bool $strict_filtering = false): array
{
    echo "Filtering..." . PHP_EOL . PHP_EOL;


    $query_words = preg_split('/\s+/', trim($query));
    $words_number = count($query_words);

    $filtered_results = [];

    foreach ($results as $result) {
        $name_matches_counter = 0;
        $details_matches_counter = 0;
        foreach ($query_words as $word) {
            if (str_contains($result['name'], $word)) {
                $name_matches_counter++;
            }
            if (str_contains($result['description'], $word)) {
                $details_matches_counter++;
            }
        }
        $name_match_rate = $name_matches_counter / $words_number;
        $details_match_rate = $details_matches_counter / $words_number;

        if ($strict_filtering) {
            $passed = $name_match_rate >= NAME_MATCH_THRESHOLD && $details_match_rate >= DETAILS_MATCH_THRESHOLD;
        } else {
            $passed = $name_match_rate >= NAME_MATCH_THRESHOLD || $details_match_rate >= DETAILS_MATCH_THRESHOLD;
        }

        if ($passed) {
            $filtered_results[] = $result;
        } else {

            echo "Item didn't passed filtering:" . PHP_EOL;

            print_r($result);

            echo "Query: " . implode(' ', $query_words) . PHP_EOL;
            echo "Name match rate: " . $name_match_rate . PHP_EOL;
            echo "Details match rate " . $details_match_rate . PHP_EOL;
            echo PHP_EOL;

        }

    }
    usort($filtered_results, fn($a, $b) => getPrice($a['price']) - getPrice($b['price']));
    return $filtered_results;
}

/**
 * @param array $results
 * @param bool $includeDescription
 * @return void
 * input array $results show contain following keys
 * - 'name'
 * - 'price'
 * - 'link' - link to product detail page
 * - 'eshop' - eshop identifier e.g. 'alza'
 * - 'description'
 */
function printResults(array $results, bool $includeDescription = false): void
{
    $width = [
        'name' => 0,
        'price' => 0,
        'link' => 0,
        'eshop' => 0,
        'description' => 0,
    ];
    foreach ($results as $result) {
        foreach ($result as $key => $value) {
            $width[$key] = max(mb_strlen($value), $width[$key]);
        }
    }
    echo '+' . str_repeat('-', 2 + $width['name']);
    echo '+' . str_repeat('-', 2 + $width['price']);
    echo '+' . str_repeat('-', 2 + $width['link']);
    echo '+' . str_repeat('-', 2 + $width['eshop']) . "+" . PHP_EOL;
    foreach ($results as $result) {

        echo '| ' . $result['name'] . str_repeat(' ', $width['name'] - mb_strlen($result['name'])) . ' ';
        echo '| ' . $result['price'] . str_repeat(' ', $width['price'] - mb_strlen($result['price'])) . ' ';
        echo '| ' . $result['link'] . str_repeat(' ', $width['link'] - mb_strlen($result['link'])) . ' ';
        echo '| ' . $result['eshop'] . str_repeat(' ', $width['eshop'] - mb_strlen($result['eshop'])) . ' ';
        echo "|" . PHP_EOL;
        echo '+' . str_repeat('-', 2 + $width['name']);
        echo '+' . str_repeat('-', 2 + $width['price']);
        echo '+' . str_repeat('-', 2 + $width['link']);
        echo '+' . str_repeat('-', 2 + $width['eshop']) . "+" . PHP_EOL;
        if ($includeDescription) {
            echo '| ' . $result['description'] . str_repeat(' ',
                    max(0, 7 + $width['name'] + $width['price'] + $width['link'] - mb_strlen($result['description'])));
            echo "|" . PHP_EOL;
            echo str_repeat('-', 10 + $width['name'] + $width['price'] + $width['link']) . PHP_EOL;
        }
    }
}

// MAIN
if (count($argv) !== 2) {
    echo "Usage: php run.php <query>" . PHP_EOL;
    exit(1);
}

$query = $argv[1];
$results = scrape($query);
$results = filter($query, $results);
printResults($results, true);
