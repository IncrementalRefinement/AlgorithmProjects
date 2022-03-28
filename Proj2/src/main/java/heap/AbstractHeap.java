package heap;

import java.util.Collection;
import java.util.Comparator;

public abstract class AbstractHeap<E> implements Heap<E> {

    private final Comparator<E> comparator;

    private AbstractHeap() {
        this.comparator = null;
    }

    public AbstractHeap(Comparator<E> comparator) {
        this.comparator = comparator;
    }

    public AbstractHeap(Collection<E> collection, Comparator<E> comparator) {
        this.comparator = comparator;
        constructHeapFromEmpty(collection);
    }

    public void merge(AbstractHeap<E> otherHeap) {

    }

    private void constructHeapFromEmpty(Collection<E> collection) {}
}
