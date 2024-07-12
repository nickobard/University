package thedrake.ui;

import javafx.scene.layout.*;
import javafx.scene.paint.Color;
import thedrake.tiles.Tile;
import thedrake.troops.tiles.TroopTile;

public class StackTileView extends TileView {
    protected final TileViewContext context;

    private final static Border selectionBorder = new Border(
            new BorderStroke(
                    Color.BLACK, BorderStrokeStyle.SOLID, CornerRadii.EMPTY, new BorderWidths(3)
            ));

    public StackTileView(Tile tile, TileViewContext context) {
        super(tile);
        this.context = context;

        setOnMouseClicked(e -> onClick());
    }

    protected void onClick() {
        if (tile.hasTroop() && context.canBePlacedFromStack((TroopTile) tile))
            select();
    }

    protected boolean isOnStack() {
        return true;
    }

    protected void select() {
        setBorder(selectionBorder);
        context.tileViewSelected(this);
    }

    public void unselect() {
        setBorder(null);
    }

}
