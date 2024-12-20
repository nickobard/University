package thedrake.game;

import thedrake.board.Board;
import thedrake.board.tiles.BoardPos;
import thedrake.tiles.Tile;
import thedrake.tiles.TilePos;
import thedrake.troops.Troop;
import thedrake.troops.tiles.PlayingSide;

public class GameState {
    private final Board board;
    private final PlayingSide sideOnTurn;
    private final Army blueArmy;
    private final Army orangeArmy;
    private final GameResult result;

    public GameState(
            Board board,
            Army blueArmy,
            Army orangeArmy) {
        this(board, blueArmy, orangeArmy, PlayingSide.BLUE, GameResult.IN_PLAY);
    }

    public GameState(
            Board board,
            Army blueArmy,
            Army orangeArmy,
            PlayingSide sideOnTurn,
            GameResult result) {
        this.board = board;
        this.sideOnTurn = sideOnTurn;
        this.blueArmy = blueArmy;
        this.orangeArmy = orangeArmy;
        this.result = result;
    }

    public Board board() {
        return board;
    }

    public PlayingSide sideOnTurn() {
        return sideOnTurn;
    }

    public GameResult result() {
        return result;
    }

    public Army army(PlayingSide side) {
        if (side == PlayingSide.BLUE) {
            return blueArmy;
        }

        return orangeArmy;
    }

    public Army armyOnTurn() {
        return army(sideOnTurn);
    }

    public Army armyNotOnTurn() {
        if (sideOnTurn == PlayingSide.BLUE)
            return orangeArmy;

        return blueArmy;
    }

    public Tile tileAt(TilePos pos) {
        if (blueArmy.boardTroops().at(pos).isPresent()) {
            return blueArmy.boardTroops().at(pos).get();
        } else if (orangeArmy.boardTroops().at(pos).isPresent()) {
            return orangeArmy.boardTroops().at(pos).get();
        } else {
            return board.at(pos);
        }
    }

    private boolean canStepFrom(TilePos origin) {
        if (origin == TilePos.OFF_BOARD) {
            return false;
        }
        if (result != GameResult.IN_PLAY) {
            return false;
        }
        if (armyOnTurn().boardTroops().at(origin).isEmpty()) {
            return false;
        } else return armyOnTurn().boardTroops().canMoveTroops();
    }

    private boolean canStepTo(TilePos target) {
        if (target == TilePos.OFF_BOARD) {
            return false;
        }
        Tile tileToStepTo = tileAt(target);
        return result == GameResult.IN_PLAY && tileToStepTo.canStepOn();
    }

    private boolean canCaptureOn(TilePos target) {
        if (target == TilePos.OFF_BOARD) {
            return false;
        }
        if (result != GameResult.IN_PLAY) {
            return false;
        } else return armyNotOnTurn().boardTroops().at(target).isPresent();
    }

    public boolean canStep(TilePos origin, TilePos target) {
        return canStepFrom(origin) && canStepTo(target);
    }

    public boolean canCapture(TilePos origin, TilePos target) {
        return canStepFrom(origin) && canCaptureOn(target);
    }

    public boolean canPlaceFromStack(TilePos target) {
        if (armyOnTurn().stack().isEmpty() || target == TilePos.OFF_BOARD || !canStepTo(target)) {
            return false;
        }
        if (sideOnTurn == PlayingSide.ORANGE) {
            if (army(PlayingSide.ORANGE).boardTroops().isLeaderPlaced()) {

                if (army(PlayingSide.ORANGE).boardTroops().isPlacingGuards()) {
                    return target.isNextTo(orangeArmy.boardTroops().leaderPosition());
                }

                for (var pos :
                        target.neighbours()) {
                    if (army(PlayingSide.ORANGE).boardTroops().at(pos).isPresent()) {
                        return true;
                    }
                }
                return false;
            } else return target.row() == board.dimension() && tileAt(target).canStepOn();
        } else {
            if (army(PlayingSide.BLUE).boardTroops().isLeaderPlaced()) {
                if (army(PlayingSide.BLUE).boardTroops().isPlacingGuards()) {
                    return target.isNextTo(blueArmy.boardTroops().leaderPosition());
                }
                for (var pos :
                        target.neighbours()) {
                    if (army(PlayingSide.BLUE).boardTroops().at(pos).isPresent()) {
                        return true;
                    }
                }
                return false;
            } else return target.row() == 1 && tileAt(target).canStepOn();
        }
    }

    public GameState stepOnly(BoardPos origin, BoardPos target) {
        if (canStep(origin, target))
            return createNewGameState(
                    armyNotOnTurn(),
                    armyOnTurn().troopStep(origin, target), GameResult.IN_PLAY);

        throw new IllegalArgumentException();
    }

    public GameState stepAndCapture(BoardPos origin, BoardPos target) {
        if (canCapture(origin, target)) {
            Troop captured = armyNotOnTurn().boardTroops().at(target).get().troop();
            GameResult newResult = GameResult.IN_PLAY;

            if (armyNotOnTurn().boardTroops().leaderPosition().equals(target))
                newResult = GameResult.VICTORY;

            return createNewGameState(
                    armyNotOnTurn().removeTroop(target),
                    armyOnTurn().troopStep(origin, target).capture(captured), newResult);
        }

        throw new IllegalArgumentException();
    }

    public GameState captureOnly(BoardPos origin, BoardPos target) {
        if (canCapture(origin, target)) {
            Troop captured = armyNotOnTurn().boardTroops().at(target).get().troop();
            GameResult newResult = GameResult.IN_PLAY;

            if (armyNotOnTurn().boardTroops().leaderPosition().equals(target))
                newResult = GameResult.VICTORY;

            return createNewGameState(
                    armyNotOnTurn().removeTroop(target),
                    armyOnTurn().troopFlip(origin).capture(captured), newResult);
        }

        throw new IllegalArgumentException();
    }

    public GameState placeFromStack(BoardPos target) {
        if (canPlaceFromStack(target)) {
            return createNewGameState(
                    armyNotOnTurn(),
                    armyOnTurn().placeFromStack(target),
                    GameResult.IN_PLAY);
        }

        throw new IllegalArgumentException();
    }

    public GameState resign() {
        return createNewGameState(
                armyNotOnTurn(),
                armyOnTurn(),
                GameResult.VICTORY);
    }

    public GameState draw() {
        return createNewGameState(
                armyOnTurn(),
                armyNotOnTurn(),
                GameResult.DRAW);
    }

    private GameState createNewGameState(Army armyOnTurn, Army armyNotOnTurn, GameResult result) {
        if (armyOnTurn.side() == PlayingSide.BLUE) {
            return new GameState(board, armyOnTurn, armyNotOnTurn, PlayingSide.BLUE, result);
        }

        return new GameState(board, armyNotOnTurn, armyOnTurn, PlayingSide.ORANGE, result);
    }
}
