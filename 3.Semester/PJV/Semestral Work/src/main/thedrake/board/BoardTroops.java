package thedrake.board;

import thedrake.board.tiles.BoardPos;
import thedrake.troops.tiles.PlayingSide;
import thedrake.tiles.TilePos;
import thedrake.troops.tiles.TroopTile;
import thedrake.troops.Troop;
import thedrake.troops.tiles.TroopFace;

import java.util.*;

public class BoardTroops {
    private final PlayingSide playingSide;
    private final Map<BoardPos, TroopTile> troopMap;
    private final TilePos leaderPosition;
    private final int guards;

    public BoardTroops(PlayingSide playingSide) {
        this.playingSide = playingSide;
        troopMap = Collections.emptyMap();
        leaderPosition = BoardPos.OFF_BOARD;
        guards = 0;
    }

    public BoardTroops(
            PlayingSide playingSide,
            Map<BoardPos, TroopTile> troopMap,
            TilePos leaderPosition,
            int guards) {
        this.playingSide = playingSide;
        this.troopMap = troopMap;
        this.leaderPosition = leaderPosition;
        this.guards = guards;
    }

    public Optional<TroopTile> at(TilePos pos) {
        return Optional.ofNullable(troopMap.get(pos));
    }

    public PlayingSide playingSide() {
        return playingSide;
    }

    public TilePos leaderPosition() {
        return leaderPosition;
    }

    public int guards() {
        return guards;
    }

    public boolean isLeaderPlaced() {
        return leaderPosition != TilePos.OFF_BOARD;
    }

    public boolean isPlacingGuards() {
        return isLeaderPlaced() && guards < 2;
    }

    public boolean canMoveTroops() {
        return isLeaderPlaced() && !isPlacingGuards();
    }

    public Set<BoardPos> troopPositions() {
        return troopMap.keySet();
    }

    public BoardTroops placeTroop(Troop troop, BoardPos target) {
        if (troopMap.containsKey(target)) {
            throw new IllegalArgumentException();
        }

        var newTroopTile = new TroopTile(troop, playingSide, TroopFace.AVERS);
        var newTroops = new HashMap<>(troopMap);
        newTroops.put(target, newTroopTile);

        int newGuards = guards;
        var newLeaderPosition = leaderPosition;


        if (isPlacingGuards()) {
            newGuards++;
        } else if (!isLeaderPlaced()) {
            newLeaderPosition = target;
        }

        return new BoardTroops(playingSide, newTroops, newLeaderPosition, newGuards);
    }

    public BoardTroops troopStep(BoardPos origin, BoardPos target) {
        if (!isLeaderPlaced() || isPlacingGuards()) {
            throw new IllegalStateException();
        }
        if (troopMap.containsKey(target) || !troopMap.containsKey(origin)) {
            throw new IllegalArgumentException();
        }

        var movedTroopTile = troopMap.get(origin).flipped();
        var newTroops = new HashMap<>(troopMap);
        var newLeaderPosition = leaderPosition;
        newTroops.remove(origin);
        newTroops.put(target, movedTroopTile);

        if (origin.equals(leaderPosition)) {
            newLeaderPosition = target;
        }

        return new BoardTroops(playingSide, newTroops, newLeaderPosition, guards);
    }

    public BoardTroops troopFlip(BoardPos origin) {
        if (!isLeaderPlaced()) {
            throw new IllegalStateException(
                    "Cannot move troops before the leader is placed.");
        }

        if (isPlacingGuards()) {
            throw new IllegalStateException(
                    "Cannot move troops before guards are placed.");
        }

        if (!at(origin).isPresent())
            throw new IllegalArgumentException();

        Map<BoardPos, TroopTile> newTroops = new HashMap<>(troopMap);
        TroopTile tile = newTroops.remove(origin);
        newTroops.put(origin, tile.flipped());

        return new BoardTroops(playingSide, newTroops, leaderPosition, guards);
    }

    public BoardTroops removeTroop(BoardPos target) {
        if (!isLeaderPlaced() || isPlacingGuards()) {
            throw new IllegalStateException();
        }

        if (!troopMap.containsKey(target)) {
            throw new IllegalArgumentException();
        }

        var newTroops = new HashMap<>(troopMap);
        newTroops.remove(target);
        var newLeaderPosition = leaderPosition;
        if (target.equals(leaderPosition)) {
            newLeaderPosition = BoardPos.OFF_BOARD;
        }

        return new BoardTroops(playingSide, newTroops, newLeaderPosition, guards);
    }
}
