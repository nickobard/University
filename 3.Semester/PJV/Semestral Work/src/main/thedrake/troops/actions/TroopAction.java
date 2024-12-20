package thedrake.troops.actions;

import thedrake.board.moves.Move;
import thedrake.board.tiles.BoardPos;
import thedrake.game.GameState;
import thedrake.troops.Offset2D;
import thedrake.troops.tiles.PlayingSide;

import java.util.List;

public abstract class TroopAction {
    private final Offset2D offset;

    public TroopAction(int offsetX, int offsetY) {
        this(new Offset2D(offsetX, offsetY));
    }

    public TroopAction(Offset2D offset) {
        this.offset = offset;
    }

    public Offset2D offset() {
        return offset;
    }

    public abstract List<Move> movesFrom(BoardPos origin, PlayingSide side, GameState state);
}
