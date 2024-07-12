package thedrake.board.moves;

import thedrake.game.GameState;
import thedrake.board.tiles.BoardPos;

public class CaptureOnly extends BoardMove {

    public CaptureOnly(BoardPos origin, BoardPos target) {
        super(origin, target);
    }

    @Override
    public GameState execute(GameState originState) {
        return originState.captureOnly(origin(), target());
    }

}
