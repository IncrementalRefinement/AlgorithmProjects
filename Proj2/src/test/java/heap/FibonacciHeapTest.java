package heap;

import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class FibonacciHeapTest extends BaseHeapTest {

    @Override
    public void init() {
        theHeap = new FibonacciHeap<>();
    }

    @Test
    public void specialTest1() {
        theHeap.push(4, "4");
        theHeap.push(3, "3");
        theHeap.push(1, "1");
        theHeap.push(5, "5");
        theHeap.push(2, "2");

        FibonacciHeap fibonacciHeap = (FibonacciHeap) theHeap;
        fibonacciHeap.checkRep();
        assertEquals(fibonacciHeap.getTop(), "1");
        theHeap.pop();
        fibonacciHeap.checkRep();
        assertEquals(fibonacciHeap.getTop(), "2");
        theHeap.pop();
        fibonacciHeap.checkRep();
        assertEquals(fibonacciHeap.getTop(), "3");
        theHeap.push(1, "1");
        fibonacciHeap.checkRep();
        assertEquals(fibonacciHeap.getTop(), "1");
        theHeap.decreaseKey(5, -9);
        assertEquals(fibonacciHeap.getTop(), "5");
        fibonacciHeap.checkRep();
    }

    @Test
    public void specialTest2() {
        theHeap.push(4, "4");
        theHeap.push(3, "3");
        theHeap.push(1, "1");
        theHeap.push(5, "5");
        theHeap.push(2, "2");

        FibonacciHeap fibonacciHeap = (FibonacciHeap) theHeap;
        assertEquals(fibonacciHeap.getTop(), "1");
        theHeap.pop();
        assertEquals(fibonacciHeap.getTop(), "2");
    }
}
