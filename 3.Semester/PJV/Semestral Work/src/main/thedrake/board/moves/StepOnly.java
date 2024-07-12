package thedrake.board.moves;

import thedrake.board.tiles.BoardPos;
import thedrake.game.GameState;

public class StepOnly extends BoardMove {

    public StepOnly(BoardPos origin, BoardPos target) {
        super(origin, target);
    }

    @Override
    public GameState execute(GameState originState) {
        return originState.stepOnly(origin(), target());
    }

}
