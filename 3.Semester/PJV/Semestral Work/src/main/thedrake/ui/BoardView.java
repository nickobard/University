package thedrake.ui;

import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.layout.GridPane;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.stage.Modality;
import javafx.stage.Stage;
import thedrake.board.Board;
import thedrake.board.moves.Move;
import thedrake.board.tiles.BoardPos;
import thedrake.board.tiles.BoardTile;
import thedrake.game.Army;
import thedrake.game.GameResult;
import thedrake.game.GameState;
import thedrake.game.StandardDrakeSetup;
import thedrake.tiles.PositionFactory;
import thedrake.troops.Troop;
import thedrake.troops.tiles.PlayingSide;
import thedrake.troops.tiles.TroopFace;
import thedrake.troops.tiles.TroopTile;

import java.util.ArrayList;
import java.util.List;

public class BoardView extends GridPane implements TileViewContext {

    private Scene mainMenuScene;

    private GameState gameState;

    private StackTileView selected;

    private ValidMoves validMoves;

    private Label sideOnTurnName;

    private final int BOARD_OFFSET = 6;

    private final int MAX_TROOPS_COUNT = 7;

    ArrayList<BoardTileView> boardTileViews = new ArrayList<>();
    ArrayList<TileView> capturedTileViewsBlue = new ArrayList<>();
    ArrayList<TileView> capturedTileViewsOrange = new ArrayList<>();

    ArrayList<StackTileView> stackTileViewsBlue = new ArrayList<>();
    ArrayList<StackTileView> stackTileViewsOrange = new ArrayList<>();


    public BoardView(GameState gameState, Scene mainMenuScene) {
        this.mainMenuScene = mainMenuScene;
        this.gameState = gameState;
        this.validMoves = new ValidMoves(gameState);

        PositionFactory pf = gameState.board().positionFactory();

        for (int y = 0; y < pf.dimension(); y++) {
            for (int x = 0; x < pf.dimension(); x++) {
                BoardPos pos = pf.pos(x, pf.dimension() - y - 1);
                BoardTileView view = new BoardTileView(gameState.tileAt(pos), pos, this);
                add(view, x, BOARD_OFFSET + y);
                boardTileViews.add(view);
            }
        }

        initNonBoardTiles(pf.dimension());

        setBlueArmyStack();
        setOrangeArmyStack();
        setBlueArmyCaptured();
        setOrangeArmyCaptured();

        Label sideOnTurnText = new Label("Player on turn:");
        add(sideOnTurnText, 0, 0);

        sideOnTurnName = new Label();
        sideOnTurnName.setStyle("-fx-font-weight: bold");
        add(sideOnTurnName, 1, 0);

        updateSideOnTurnName();


        setHgap(5);
        setVgap(5);
        setPadding(new Insets(15));
        setAlignment(Pos.CENTER);
    }

    private void updateSideOnTurnName() {
        if (gameState.armyOnTurn().side().equals(PlayingSide.BLUE)) {
            sideOnTurnName.setText("BLUE");
            sideOnTurnName.setTextFill(Color.BLUE);
        } else {
            sideOnTurnName.setText("ORANGE");
            sideOnTurnName.setTextFill(Color.ORANGE);
        }

    }

    public void reloadGame() {
        selected = null;
        gameState = newSampleGameState();
        validMoves = new ValidMoves(gameState);
        updateTiles();
    }

    private void initNonBoardTiles(int dimension) {
        for (int x = 0; x < MAX_TROOPS_COUNT; x++) {
            TileView orangeCaptured = new TileView(BoardTile.EMPTY);
            add(orangeCaptured, x, 1);
            capturedTileViewsOrange.add(orangeCaptured);
            StackTileView orangeStack = new StackTileView(BoardTile.EMPTY, this);
            add(orangeStack, x, 3);
            stackTileViewsOrange.add(orangeStack);
            TileView blueCaptured = new TileView(BoardTile.EMPTY);
            add(blueCaptured, x, dimension + BOARD_OFFSET + 4);
            capturedTileViewsBlue.add(blueCaptured);
            StackTileView blueStack = new StackTileView(BoardTile.EMPTY, this);
            add(blueStack, x, dimension + BOARD_OFFSET + 2);
            stackTileViewsBlue.add(blueStack);
        }
    }

    private void setBlueArmyStack() {
        Army blueArmy = gameState.army(PlayingSide.BLUE);

        for (int x = 0; x < blueArmy.stack().size(); x++) {
            Troop troop = blueArmy.stack().get(x);
            TroopTile tile = new TroopTile(troop, PlayingSide.BLUE, TroopFace.AVERS);
            stackTileViewsBlue.get(x).setTile(tile);
        }

        for (int x = blueArmy.stack().size(); x < MAX_TROOPS_COUNT; x++) {
            stackTileViewsBlue.get(x).setTile(BoardTile.EMPTY);
        }
    }


    private void setOrangeArmyStack() {
        Army orangeArmy = gameState.army(PlayingSide.ORANGE);

        for (int x = 0; x < orangeArmy.stack().size(); x++) {
            Troop troop = orangeArmy.stack().get(x);
            TroopTile tile = new TroopTile(troop, PlayingSide.ORANGE, TroopFace.AVERS);
            stackTileViewsOrange.get(x).setTile(tile);
        }

        for (int x = orangeArmy.stack().size(); x < MAX_TROOPS_COUNT; x++) {
            stackTileViewsOrange.get(x).setTile(BoardTile.EMPTY);
        }
    }

    private void setBlueArmyCaptured() {
        Army blueArmy = gameState.army(PlayingSide.BLUE);

        for (int x = 0; x < blueArmy.captured().size(); x++) {
            Troop troop = blueArmy.captured().get(x);
            TroopTile tile = new TroopTile(troop, PlayingSide.ORANGE, TroopFace.AVERS);
            capturedTileViewsBlue.get(x).setTile(tile);
        }

        for (int x = blueArmy.captured().size(); x < MAX_TROOPS_COUNT; x++) {
            capturedTileViewsBlue.get(x).setTile(BoardTile.EMPTY);
        }
    }

    private void setOrangeArmyCaptured() {
        Army orangeArmy = gameState.army(PlayingSide.ORANGE);

        for (int x = 0; x < orangeArmy.captured().size(); x++) {
            Troop troop = orangeArmy.captured().get(x);
            TroopTile tile = new TroopTile(troop, PlayingSide.BLUE, TroopFace.AVERS);
            capturedTileViewsOrange.get(x).setTile(tile);
        }

        for (int x = orangeArmy.captured().size(); x < MAX_TROOPS_COUNT; x++) {
            capturedTileViewsOrange.get(x).setTile(BoardTile.EMPTY);
        }
    }

    private void updateTiles() {

        for (BoardTileView view : boardTileViews) {
            view.setTile(gameState.tileAt(view.position()));
        }
        setBlueArmyStack();
        setOrangeArmyStack();
        setBlueArmyCaptured();
        setOrangeArmyCaptured();

        updateSideOnTurnName();

        if (gameState.result() != GameResult.IN_PLAY || armyOnTurnCannotMove())
            endGame();
    }

    private boolean armyOnTurnCannotMove() {
        return validMoves.allMoves().isEmpty();

    }

    public Stage getStage() {
        return (Stage) getScene().getWindow();
    }

    public void closeBoardStage() {
        getStage().close();
    }

    public Scene getMainMenusScene() {
        return mainMenuScene;
    }

    private void endGame() {
        Stage dialog = new Stage();
        dialog.setScene(new Scene(new DialogView(getWinnerText(), this)));
        dialog.setTitle("Game Over!");
        dialog.initOwner(getStage());
        dialog.initModality(Modality.APPLICATION_MODAL);
        dialog.setOnCloseRequest((event -> {
            Stage stage = getStage();
            stage.setScene(mainMenuScene);
            stage.show();
        }));
        dialog.showAndWait();
    }

    String getWinnerText() {
        if (gameState.armyNotOnTurn().side() == PlayingSide.BLUE)
            return "Blue player wins!";
        return "Orange player wins!";
    }

    @Override
    public void tileViewSelected(StackTileView boardTileView) {
        if (selected != null && selected != boardTileView) {
            selected.unselect();
        }
        selected = boardTileView;

        clearMoves();
        if (boardTileView.isOnStack())
            showMoves(validMoves.movesFromStack());
        else
            showMoves(validMoves.boardMoves(((BoardTileView) boardTileView).position()));

    }

    @Override
    public void executeMove(Move move) {
        selected.unselect();
        selected = null;
        clearMoves();
        gameState = move.execute(gameState);
        validMoves = new ValidMoves(gameState);
        updateTiles();
    }

    @Override
    public boolean canBePlacedFromStack(TroopTile tile) {
        if (!isOnTurnSide(tile))
            return false;
        return isFirstInArmyStack(tile) && isFirstInViewsStack(tile);
    }

    @Override
    public boolean isOnTurnSide(TroopTile tile) {
        return gameState.sideOnTurn() == tile.side();
    }


    private boolean isFirstInArmyStack(TroopTile tile) {
        var armyStack = gameState.armyOnTurn().stack();
        if (armyStack.isEmpty())
            return false;
        return armyStack.get(0).equals(tile.troop());
    }

    private boolean isFirstInViewsStack(TroopTile tile) {
        var viewsStack = getViewStack(tile.side());
        if (viewsStack.isEmpty())
            return false;
        return viewsStack.get(0).getTile().equals(tile);
    }

    private ArrayList<StackTileView> getViewStack(PlayingSide side) {
        if (side == PlayingSide.BLUE)
            return stackTileViewsBlue;
        return stackTileViewsOrange;
    }

    private void showMoves(List<Move> moves) {
        for (Move move : moves) {
            tileViewAt(move.target()).setMove(move);
        }
    }

    private void clearMoves() {
        for (BoardTileView view : boardTileViews) {
            view.clearMove();
        }
    }

    private BoardTileView tileViewAt(BoardPos target) {
        int index = (gameState.board().dimension() - 1 - target.j()) * 4 + target.i();
        return (BoardTileView) getChildren().get(index);
    }

    public static GameState newSampleGameState() {
        Board board = new Board(4);
        PositionFactory pf = board.positionFactory();
        board = board.withTiles(new Board.TileAt(pf.pos(1, 1), BoardTile.MOUNTAIN));
        return new StandardDrakeSetup().startState(board);
    }
}
