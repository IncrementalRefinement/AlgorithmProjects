package heap;

import java.util.Vector;

public class binomialHeap<K extends Comparable<K>, V> implements Heap<K, V> {
    private Vector<Node> trees;
    private int size;

    public binomialHeap(int size) {
        this.trees = new Vector<Node>(size);
        this.size = size;
    }

    private class Node {
        K key;
        int degree;
        Node parent;
        Node sibling;
        Node child;

        public Node(K key) {
            this.key = key;
            this.degree = 0;
            this.parent = null;
            this.sibling = null;
            this.child = null;
        }
    }

    private Node mergeTree(Node T1, Node T2) {
        if (T1.key.compareTo(T2.key) > 0) {
            return mergeTree(T2, T1);
        }
        T2.sibling = T1.child;
        T1.child = T2;
        return T1;
    }

    @Override
    public void push(K key, V value) {
        Node tmp = new Node(key);


    }

    @Override
    public V pop() {

    }

    @Override
    public void decreaseKey(K before, K after) {

    }
}
