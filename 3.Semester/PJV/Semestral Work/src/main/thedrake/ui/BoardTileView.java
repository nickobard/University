package thedrake.ui;

import javafx.scene.image.ImageView;
import thedrake.board.moves.Move;
import thedrake.board.tiles.BoardPos;
import thedrake.tiles.Tile;
import thedrake.troops.tiles.TroopTile;

public class BoardTileView extends StackTileView {

    private Move move;



    private final ImageView moveImage;

    private final BoardPos position;

    public BoardTileView(Tile tile, BoardPos position, TileViewContext context) {
        super(tile, context);
        this.position = position;

        moveImage = new ImageView(getClass().getResource("/assets/images/move.png").toString());
        moveImage.setVisible(false);
        getChildren().add(moveImage);
    }



    public BoardPos position() {
        return position;
    }

    @Override
    protected void onClick() {
        if (move != null) {
            context.executeMove(move);
        } else if (tile.hasTroop() && context.isOnTurnSide((TroopTile) tile)) {
            select();
        }
    }

    @Override
    protected boolean isOnStack() {
        return false;
    }


    public void setMove(Move move) {
        this.move = move;
        moveImage.setVisible(true);
    }

    public void clearMove() {
        this.move = null;
        moveImage.setVisible(false);
    }
}
