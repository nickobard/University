# Task

The task of the course is to implement The Drake Game for 2 players, using Java FX.

### Source Code Structure:

```text
.
├── README.md
└── src
    ├── main
    │   ├── module-info.java
    │   └── thedrake
    │       ├── board
    │       │   ├── Board.java
    │       │   ├── BoardTroops.java
    │       │   ├── moves
    │       │   │   ├── BoardMove.java
    │       │   │   ├── CaptureOnly.java
    │       │   │   ├── Move.java
    │       │   │   ├── PlaceFromStack.java
    │       │   │   ├── StepAndCapture.java
    │       │   │   └── StepOnly.java
    │       │   └── tiles
    │       │       ├── BoardPos.java
    │       │       └── BoardTile.java
    │       ├── client
    │       │   ├── App.java
    │       │   ├── controllers
    │       │   │   └── MenuController.java
    │       │   ├── menu.fxml
    │       │   └── styles
    │       │       ├── fonts
    │       │       │   └── BeyondWonderland.ttf
    │       │       ├── images
    │       │       │   └── background.jpg
    │       │       └── menu.css
    │       ├── game
    │       │   ├── Army.java
    │       │   ├── GameResult.java
    │       │   ├── GameState.java
    │       │   └── StandardDrakeSetup.java
    │       ├── tiles
    │       │   ├── PositionFactory.java
    │       │   ├── Tile.java
    │       │   └── TilePos.java
    │       ├── troops
    │       │   ├── actions
    │       │   │   ├── ShiftAction.java
    │       │   │   ├── SlideAction.java
    │       │   │   ├── StrikeAction.java
    │       │   │   └── TroopAction.java
    │       │   ├── Offset2D.java
    │       │   ├── tiles
    │       │   │   ├── PlayingSide.java
    │       │   │   ├── TroopFace.java
    │       │   │   └── TroopTile.java
    │       │   └── Troop.java
    │       └── ui
    │           ├── BoardTileView.java
    │           ├── BoardView.java
    │           ├── DialogView.java
    │           ├── MenuController.java
    │           ├── menu.fxml
    │           ├── StackTileView.java
    │           ├── TheDrakeApp.java
    │           ├── TileBackgrounds.java
    │           ├── TileViewContext.java
    │           ├── TileView.java
    │           ├── TroopImageSet.java
    │           └── ValidMoves.java
    └── test
        ├── main
        │   └── MainSuite.java
        ├── suite01
        │   ├── Offset2DTest.java
        │   ├── TestSuite.java
        │   └── TroopTest.java
        ├── suite02
        │   ├── BoardTest.java
        │   ├── TestSuite.java
        │   └── TroopTileTest.java
        ├── suite03
        │   ├── BoardTroopsTest.java
        │   └── TestSuite.java
        └── suite04
            ├── ActionsTest.java
            ├── GameStateTest.java
            └── TestSuite.java


```