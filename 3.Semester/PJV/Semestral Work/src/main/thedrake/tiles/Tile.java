package thedrake.tiles;

import thedrake.game.GameState;
import thedrake.board.moves.Move;
import thedrake.board.tiles.BoardPos;

import java.util.List;

public interface Tile {

    // Vrací True, pokud je tato dlaždice volná a lze na ni vstoupit.
    public boolean canStepOn();

    // Vrací True, pokud tato dlaždice obsahuje jednotku
    public boolean hasTroop();

    public List<Move> movesFrom(BoardPos pos, GameState state);
}
