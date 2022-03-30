package heap;

import java.util.Comparator;

public interface Heap <K extends Comparable<K>, V> {

    public void push(K key, V value);

    public V pop();

    public void decreaseKey(K before, K after);
}
