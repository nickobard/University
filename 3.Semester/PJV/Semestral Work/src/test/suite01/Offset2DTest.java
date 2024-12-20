package suite01;

import org.junit.Test;
import thedrake.troops.Offset2D;

import java.lang.reflect.Modifier;

import static org.junit.Assert.*;

public class Offset2DTest {

    @Test
    public void classStructure() {
        // Třída drží souřadnice jako dva public immutable
        // atributy x a y typu int.
        try {
            assertTrue(Modifier.isFinal(
                    Offset2D.class.getField("x").getModifiers()));
            assertTrue(Modifier.isFinal(
                    Offset2D.class.getField("y").getModifiers()));

            assertSame(Offset2D.class.getField("x").getType(), int.class);
            assertSame(Offset2D.class.getField("y").getType(), int.class);
        } catch (NoSuchFieldException e) {
            fail();
        }
    }

    @Test
    public void behaviour() {
        // Konstruktor, který bere dva parametry typu int.
        Offset2D offset2D = new Offset2D(10, -5);

        assertSame(10, offset2D.x);
        assertSame(-5, offset2D.y);

        // Metoda equals pro porovnávání s jinými souřadnicemi
        assertTrue(offset2D.equalsTo(10, -5));
        assertFalse(offset2D.equalsTo(9, -5));
        assertFalse(offset2D.equalsTo(10, -4));
        assertFalse(offset2D.equalsTo(0, 1));

        // Metoda yFlipped vytváří nový Offset2D se obrácenou y souřadnicí.
        assertTrue(offset2D.yFlipped().equalsTo(10, 5));
        assertTrue(offset2D.yFlipped().yFlipped().equalsTo(10, -5));
        assertNotSame(offset2D.yFlipped(), offset2D);
    }
}
