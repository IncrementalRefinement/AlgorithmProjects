package heap;

public class binomialHeap<K extends Comparable<K>, V> implements Heap<K, V> {
    private class Node{
        int key,degree;
        Node parent;
        Node sibling;
        Node child;

        public Node(int key) {
            this.key = key;
            this.degree = 0;
            this.parent = null;
            this.sibling = null;
            this.child = null;
        }
    }



    @Override
    public void push(K key, V value) {

    }

    @Override
    public V pop() {
        return null;
    }

    @Override
    public void decreaseKey(K before, K after) {

    }
}
