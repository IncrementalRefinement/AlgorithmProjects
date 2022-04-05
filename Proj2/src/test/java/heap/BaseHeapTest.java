package heap;

import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.assertEquals;

public abstract class BaseHeapTest {

    Heap<Integer, String> theHeap;

    @Before
    public void init() {
        throw new RuntimeException();
    }

    @Test
    public void sanityTest() {
        int count = 10;

        for (int i = 0; i < count; i++) {
            theHeap.push(i, String.valueOf(i));
        }

        for (int i = 2; i < count; i++) {
            theHeap.decreaseKey(i, i - 1);
        }

        for (int i = 0; i < count; i++) {
            theHeap.pop();
        }
    }

    @Test
    public void pushPopTest() {
        int count = 100;

        for (int i = 0; i < count; i++) {
            theHeap.push(i, String.valueOf(i));
        }

        for (int i = 0; i < count; i++) {
            assertEquals(String.valueOf(i), theHeap.pop());
        }
    }

    @Test
    public void decreaseKeyTest() {
        int count = 100;

        for (int i = 2; i < count; i++) {
            theHeap.push(i, String.valueOf(i));
        }

        for (int i = 2; i < count; i++) {
            theHeap.decreaseKey(i, i - 1);
        }

        for (int i = 2; i < count; i++) {
            assertEquals( String.valueOf(i), theHeap.pop());
        }
    }
}
