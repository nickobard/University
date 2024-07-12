package thedrake.board;

import thedrake.board.tiles.BoardPos;
import thedrake.board.tiles.BoardTile;
import thedrake.tiles.PositionFactory;
import thedrake.tiles.TilePos;

import java.util.Arrays;

public class Board {

    private final int dimension;
    private final BoardTile[][] tiles;

    // Konstruktor. Vytvoří čtvercovou hrací desku zadaného rozměru, kde v
    // šechny dlaždice jsou prázdné, tedy BoardTile.EMPTY
    public Board(int dimension) {
        tiles = new BoardTile[dimension][dimension];
        for (var rowTiles : tiles) {
            Arrays.fill(rowTiles, BoardTile.EMPTY);
        }
        this.dimension = dimension;
    }

    public Board(int dimension, BoardTile[][] tiles) {
        this.tiles = tiles;
        this.dimension = dimension;
    }

    // Rozměr hrací desky
    public int dimension() {
        return dimension;
    }

    // Vrací dlaždici na zvolené pozici.
    public BoardTile at(TilePos pos) {
        return tiles[pos.i()][pos.j()];
    }

    // Vytváří novou hrací desku s novými dlaždicemi. Všechny ostatní dlaždice zůstávají stejné
    public Board withTiles(TileAt... ats) {
        var tiles = new BoardTile[dimension][dimension];

        for (int i = 0; i < dimension; i++)
            tiles[i] = this.tiles[i].clone();

        for (var at : ats) {
            tiles[at.pos.i()][at.pos.j()] = at.tile;
        }
        return new Board(dimension, tiles);
    }

    // Vytvoří instanci PositionFactory pro výrobu pozic na tomto hracím plánu
    public PositionFactory positionFactory() {
        return new PositionFactory(dimension);
    }

    public static class TileAt {
        public final BoardPos pos;
        public final BoardTile tile;

        public TileAt(BoardPos pos, BoardTile tile) {
            this.pos = pos;
            this.tile = tile;
        }
    }
}

