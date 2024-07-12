package thedrake.ui;

import javafx.scene.layout.Pane;
import thedrake.tiles.Tile;

public class TileView extends Pane {

    protected final static TileBackgrounds backgrounds = new TileBackgrounds();

    protected Tile tile;

    public TileView(Tile tile) {
        this.tile = tile;
        setPrefSize(100, 100);
        update();
    }

    protected void update() {
        setBackground(backgrounds.get(this.tile));
    }

    public void setTile(Tile tile) {
        this.tile = tile;
        update();
    }

    public Tile getTile() {
        return tile;
    }
}
