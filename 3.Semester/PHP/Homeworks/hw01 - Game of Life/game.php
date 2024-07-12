<?php declare(strict_types=1);

const DEAD = '.';
const ALIVE = 'X';

/**
 * Reads input and outputs array of read lines.
 * @param string $string input from file.
 * @return array output array of strings
 */
function readInput(string $string): array
{
    return explode(PHP_EOL, $string);
}

/**
 * Transform matrix to string to be printed.
 * @param array $matrix array of strings to be printed.
 * @return string concatenated strings from matrix/strings array.
 */
function writeOutput(array $matrix): string
{
    return implode(PHP_EOL, $matrix);
}

/**
 * @param string $row current line of cells.
 * @param int $col current position of the cell.
 * @return int number of alive cells to the one position right and left and on current position.
 */
function countLiveCellsAroundOnLine(string $row, int $col): int
{
    $liveCells = 0;
    if ($row[$col] == ALIVE)
        $liveCells++;
    if ($col > 0 && $row[$col - 1] == ALIVE)
        $liveCells++;
    if ($col < (strlen($row) - 1) && $row[$col + 1] == ALIVE)
        $liveCells++;
    return $liveCells;
}

/**
 * @param array $matrix represents matrix of chars or array of strings.
 * @param int $row represents current row of cells.
 * @param int $col represents current cell on the row .
 * @return int number of cells alive with one position from current cell.
 */
function countLiveCellsAround(array &$matrix, int $row, int $col): int
{
    $liveCellsAround = 0;

    $liveCellsAround += countLiveCellsAroundOnLine($matrix[$row], $col);
    if ($row > 0)
        $liveCellsAround += countLiveCellsAroundOnLine($matrix[$row - 1], $col);
    if ($row < count($matrix) - 1)
        $liveCellsAround += countLiveCellsAroundOnLine($matrix[$row + 1], $col);

    return $matrix[$row][$col] == ALIVE ? $liveCellsAround - 1 : $liveCellsAround;
}

/**
 * @param int $liveCellsAround number of live cells around.
 * @return bool true if living cell should die.
 */
function cellShouldDie(int $liveCellsAround): bool
{
    if ($liveCellsAround < 2)
        return true;
    else if ($liveCellsAround > 3)
        return true;
    return false;
}

/**
 * @param int $liveCellsAround number of live cells around.
 * @return bool true if dead cell should be alive.
 */
function cellShouldLive(int $liveCellsAround): bool
{
    if ($liveCellsAround == 3)
        return true;
    return false;
}

/**
 * @param string $cell current cell to be evaluated.
 * @param int $liveCellsAround number of the live cells around this cell.
 * @return void
 */
function changeCell(string &$cell, int $liveCellsAround): void
{
    if ($cell == ALIVE && cellShouldDie($liveCellsAround))
        $cell = DEAD;
    else if ($cell == DEAD && cellShouldLive($liveCellsAround))
        $cell = ALIVE;
}

/**
 * @param array $matrix current state to be changed.
 * @return array represents new matrix of the next state of cells
 */
function gameStep(array $matrix): array
{
    $rows = count($matrix);
    $cols = strlen($matrix[0]);

    $result = $matrix;

    for ($i = 0; $i < $rows; $i++) {
        for ($j = 0; $j < $cols; $j++) {
            $liveCellsAround = countLiveCellsAround($matrix, $i, $j);
            $currentCell = $matrix[$i][$j];
            changeCell($currentCell, $liveCellsAround);
            $result[$i][$j] = $currentCell;
        }
    }
    return $result;
}
