package thedrake.troops;

import thedrake.troops.actions.TroopAction;
import thedrake.troops.tiles.TroopFace;

import java.util.Collections;
import java.util.List;

public class Troop {

    private final String name;
    private final Offset2D aversPivot;
    private final Offset2D reversPivot;

    private final List<TroopAction> aversActions;

    private final List<TroopAction> reversActions;

    public Troop(String name, Offset2D aversPivot, Offset2D reversPivot, List<TroopAction> aversActions, List<TroopAction> reversActions) {
        this.name = name;
        this.aversPivot = aversPivot;
        this.reversPivot = reversPivot;
        this.aversActions = aversActions;
        this.reversActions = reversActions;
    }

    public Troop(String name, Offset2D aversPivot, Offset2D reversPivot) {
        this.name = name;
        this.aversPivot = aversPivot;
        this.reversPivot = reversPivot;
        this.aversActions = Collections.emptyList();
        this.reversActions = Collections.emptyList();
    }

    public Troop(String name, Offset2D pivot, List<TroopAction> aversActions, List<TroopAction> reversActions) {
        this.name = name;
        this.aversPivot = pivot;
        this.reversPivot = pivot;
        this.aversActions = aversActions;
        this.reversActions = reversActions;
    }

    public Troop(String name, Offset2D pivot) {
        this.name = name;
        this.aversPivot = pivot;
        this.reversPivot = pivot;
        this.aversActions = Collections.emptyList();
        this.reversActions = Collections.emptyList();
    }

    public Troop(String name, List<TroopAction> aversActions, List<TroopAction> reversActions) {
        this.name = name;
        this.aversPivot = new Offset2D(1, 1);
        this.reversPivot = new Offset2D(1, 1);
        this.aversActions = aversActions;
        this.reversActions = reversActions;
    }

    public Troop(String name) {
        this.name = name;
        this.aversPivot = new Offset2D(1, 1);
        this.reversPivot = new Offset2D(1, 1);
        this.aversActions = Collections.emptyList();
        this.reversActions = Collections.emptyList();
    }

    public List<TroopAction> getAversActions() {
        return aversActions;
    }

    public List<TroopAction> getReversActions() {
        return reversActions;
    }

    public String name() {
        return name;
    }

    public Offset2D pivot(TroopFace face) {
        return (face == TroopFace.AVERS) ? aversPivot : reversPivot;
    }
}
