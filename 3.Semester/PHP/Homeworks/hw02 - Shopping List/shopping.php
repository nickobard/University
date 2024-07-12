<?php declare(strict_types=1);

/**
 * Regular expression patterns for searching numbers,
 * can be combined to search float numbers.
 */
const integerPart = '(\d+(\.\d{3})*)';
const floatingPart = '(,\d+)?';

/**
 * Patterns for searching prices among shopping items.
 */
const patterns = [
    '/CZK\s*(' . integerPart . floatingPart . ')/',
    '/(' . integerPart . floatingPart . ')\s*(CZK|Kč)/',
    '/(' . integerPart . '),-/'
];

/**
 * Use patterns to search a price number in the shopping item string.
 * @param string $item is a shopping item.
 * @return array|string[] a pair of values - string unformatted string number and updated item without price.
 */
function getNumberString(string $item): array
{
    foreach (patterns as $pattern) {
        if (preg_match($pattern, $item, $matches))
            return [$matches[1], trim(str_replace($matches[0], "", $item))];
    }
    return ["0", ""];
}

/**
 * Parse string number, formatting it to appropriate conversion format.
 * @param string $stringNumber is number in string type.
 * @return float|int value of the number.
 */
function parseToNumberType(string $stringNumber): float|int
{

    $parsedToNumberFormat = str_replace('.', '', $stringNumber);
    $parsedToNumberFormat = str_replace(',', '.', $parsedToNumberFormat);
    return (float)$parsedToNumberFormat;
}

/**
 * Gets price value from number in string type.
 * @param string $item is number is string type.
 * @return float value of the number.
 */
function getPrice(string $item): float
{
    return parseToNumberType($item);
}

/**
 * Paser shopping list to map with prices as formatted strings and values as shopping items.
 * @param array $list of unparsed shopping items.
 * @return array parsed shopping items.
 */
function parseShoppingList(array &$list): array
{

    $items = [];
    foreach ($list as $item) {
        list($numberString, $updatedItem) = getNumberString($item);
        $price = getPrice($numberString);
        $items[strval($price)] = $updatedItem;
    }
    return $items;
}

/**
 * Sorts list of shopping items by price.
 * @param string[] $list unsorted shopping items list.
 * @return string[] sorted shopping items list.
 */
function sortList(array $list): array
{
    $items = parseShoppingList($list);
    $prices = [];
    $sorted = [];
    foreach (array_keys($items) as $item) {
        $prices[] = floatval($item);
    }

    sort($prices);

    foreach ($prices as $price) {
        $stringPrice = strval($price);
        $sorted[$stringPrice] = $items[$stringPrice];
    }

    return $sorted;
}

/**
 * Calculates sum of all prices in shopping items list.
 * @param string[] $list shopping items list.
 */
function sumList(array $list): float
{
    $sum = 0;
    foreach (array_keys($list) as $price) {
        $sum += floatval($price);
    }
    return $sum;
}

if (count($argv) !== 2) {
    echo "Usage: php shopping.php <input>" . PHP_EOL;
    exit(1);
}
$input = trim(file_get_contents(end($argv)));
$list = explode(PHP_EOL, $input);
$list = sortList($list);
print_r($list);
print_r(sumList($list) . PHP_EOL);
