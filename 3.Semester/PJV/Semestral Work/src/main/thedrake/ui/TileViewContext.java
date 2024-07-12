package thedrake.ui;

import thedrake.board.moves.Move;
import thedrake.troops.tiles.TroopTile;

public interface TileViewContext {

    void tileViewSelected(StackTileView boardTileView);

    void executeMove(Move move);

    boolean isOnTurnSide(TroopTile tile);

    boolean canBePlacedFromStack(TroopTile tile);
}
