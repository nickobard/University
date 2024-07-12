package thedrake.troops.tiles;

import thedrake.game.GameState;
import thedrake.board.moves.Move;
import thedrake.board.tiles.BoardPos;
import thedrake.tiles.Tile;
import thedrake.troops.Troop;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;

public class TroopTile implements Tile {

    private final Troop troop;
    private final PlayingSide side;
    private final TroopFace face;

    // Konstruktor
    public TroopTile(Troop troop, PlayingSide side, TroopFace face) {
        this.troop = troop;
        this.side = side;
        this.face = face;
    }

    // Vrací barvu, za kterou hraje jednotka na této dlaždici
    public PlayingSide side() {
        return side;
    }

    // Vrací stranu, na kterou je jednotka otočena
    public TroopFace face() {
        return face;
    }

    // Jednotka, která stojí na této dlaždici
    public Troop troop() {
        return troop;
    }

    // Vrací False, protože na dlaždici s jednotkou se nedá vstoupit
    @Override
    public boolean canStepOn() {
        return !hasTroop();
    }

    // Vrací True
    @Override
    public boolean hasTroop() {
        return troop != null;
    }

    @Override
    public List<Move> movesFrom(BoardPos pos, GameState state) {

        HashSet<Move> uniqueMoves = new HashSet<>();
        if (face == TroopFace.AVERS) {
            var actions = troop.getAversActions();
            actions.forEach(action -> uniqueMoves.addAll(action.movesFrom(pos, side, state)));
        } else {
            var actions = troop.getReversActions();
            actions.forEach(action -> uniqueMoves.addAll(action.movesFrom(pos, side, state)));
        }
        return new ArrayList<>(uniqueMoves);
    }

    // Vytvoří novou dlaždici, s jednotkou otočenou na opačnou stranu
// (z rubu na líc nebo z líce na rub)
    public TroopTile flipped() {
        return new TroopTile(troop, side, (face == TroopFace.AVERS) ? TroopFace.REVERS : TroopFace.AVERS);
    }

}
