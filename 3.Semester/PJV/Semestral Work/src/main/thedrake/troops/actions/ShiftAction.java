package thedrake.troops.actions;

import thedrake.board.moves.Move;
import thedrake.board.moves.StepAndCapture;
import thedrake.board.moves.StepOnly;
import thedrake.board.tiles.BoardPos;
import thedrake.game.GameState;
import thedrake.tiles.TilePos;
import thedrake.troops.Offset2D;
import thedrake.troops.tiles.PlayingSide;

import java.util.ArrayList;
import java.util.List;

public class ShiftAction extends TroopAction {

    public ShiftAction(Offset2D offset) {
        super(offset);
    }

    public ShiftAction(int offsetX, int offsetY) {
        super(offsetX, offsetY);
    }

    @Override
    public List<Move> movesFrom(BoardPos origin, PlayingSide side, GameState state) {
        List<Move> result = new ArrayList<>();
        TilePos target = origin.stepByPlayingSide(offset(), side);

        if (state.canStep(origin, target)) {
            result.add(new StepOnly(origin, (BoardPos) target));
        } else if (state.canCapture(origin, target)) {
            result.add(new StepAndCapture(origin, (BoardPos) target));
        }

        return result;
    }
}
