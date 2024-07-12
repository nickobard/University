package thedrake.troops;

import java.util.Objects;

public class Offset2D {

    public final int x, y;

    public Offset2D(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public boolean equalsTo(int x, int y) {
        return this.x == x && this.y == y;
    }

    public Offset2D yFlipped() {
        return new Offset2D(x, -y);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Offset2D offset2D = (Offset2D) o;
        return x == offset2D.x && y == offset2D.y;
    }

    @Override
    public int hashCode() {
        return Objects.hash(x, y);
    }
}
