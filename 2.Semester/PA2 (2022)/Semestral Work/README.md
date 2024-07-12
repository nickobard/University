
# Assignment

## Implement the classic game Pac-Man against the computer (you can also implement other variants).

### The game must meet the following functionalities:

* Adherence to basic rules, collecting bonuses, coins (dots), cherries, teleporters, etc.
* Implementation of several types of ghost AI. The game must be able to display different ghosts with different AIs simultaneously. To improve clarity, ghosts with different AIs can be displayed using different colors or symbols.
* Ability to load maps from a file (maze + positions of bonuses and ghosts).
* Configurable game difficulty from a file (ghost speed, duration of individual game modes, probability of adding a new bonus to the map, etc.)
* Scalable ghost difficulty (various ghost strategies based on difficulty and behavior)

### Where to use polymorphism? (recommended)

* Player types: player, ghost (various types of artificial intelligence)
* Game mode: classic (ghosts move according to their strategies), frantic (ghosts chase the player), invulnerable (ghosts are slower, can be killed)
* Game tile: ground, wall, dot, bonus (changes mode), cherry (more points), teleport
* User interface: console, ncurses, SDL, OpenGL (various variants), etc.

### Additional information

[Pac-Man - Wikipedia](https://en.wikipedia.org/wiki/Pac-Man)

[Ghost behavior in Pac-Man Part 1](http://programujte.com/clanek/2011010500-chovani-duchu-ve-hre-pac-man-cast-1/)

[Ghost behavior in Pac-Man Part 2](http://programujte.com/clanek/2011010900-chovani-duchu-ve-hre-pac-man-cast-2/)

### Note

This task is graded by an automatic system and then by the instructor. First, submit and debug the task using the automatic system, then submit one of your chosen solutions for evaluation by the instructor. Submission for instructor evaluation is done by clicking the "Submit to Instructor" button on the selected solution. The instructor will evaluate only one of your solutions and will not begin evaluating until you submit the task. Until the task is evaluated by both the automatic system and the instructor, no points are awarded (only partial ratings in percentages are displayed).

# Results

Created using SDL graphic library.

![](assets/pacman_game.jpg)

## How to run:

```shell
# build
make all
# run
make run
# create documentation
make doc
```

## How to play:

- Push arrows to change direction of the pacman.
- User portals to slow down the ghost and to teleport.
- Pick up all the scores to win.
- Game is over when you loose all the lives.