# Task 1: Game of Life

The Game of Life is a cellular automaton that simulates the development of a community of living organisms. It operates on a matrix of cells, where the evolution is determined solely by the initial configuration, evolving according to specified rules without any additional input. For more information, see Wikipedia - [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)).

## Assignment

Your task is to implement three functions defined in the `game.php` script.

The first function `readInput` takes a string as input, representing the initial configuration:

- `X` represents a live cell
- `.` represents a dead cell

Each line is separated by `\n`. You can assume all lines are of equal length. The goal of this function is to convert the string into your chosen representation of a matrix of cells, which will be used in computing the next steps of the game (e.g., a 2D array).

The inverse function to `readInput` is `writeOutput`, which converts a matrix of cells back into a string.

The last function is `gameStep`, which takes a matrix of cells as input and returns the matrix of cells in the next step according to the rules:

1. Any live cell with fewer than two live neighbors dies (underpopulation).
2. Any live cell with two or three live neighbors survives to the next generation.
3. Any live cell with more than three live neighbors dies (overpopulation).
4. Any dead cell with exactly three live neighbors becomes a live cell (reproduction).

Consider all 8 surrounding cells as neighbors, including diagonals.

Keep the functions with their original annotations; you can create additional helper functions as needed.

## Project Structure

- `input` - folder containing example initial generations you can use
- `animate.php` - script that prints each subsequent generation to the terminal every second
- `game.php` - script where you need to implement the functions mentioned above
- `next.php` - script that prints the next generation of an input generation

## Execution

To test and evaluate, you can use examples from the `input` folder and the scripts `next.php` and `animate.php`, which already implement file reading and result printing and use functions from `game.php`.

To evaluate the next step:

```shell
$ php next.php input/block.txt
```


To run a simulation with a given initial generation:

```shell
$ php animate.php input/blinker.txt
```

You do not need to modify `animate.php` and `next.php`. You can add additional initial generation examples, e.g., from the [Life Lexicon](http://conwaylife.com/ref/lexicon/lex.htm).
