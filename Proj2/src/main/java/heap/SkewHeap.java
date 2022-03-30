package heap;

public class SkewHeap<K extends Comparable<K>, V> implements Heap<K, V> {

    private class Node {
        private final K key;
        private final V vectx;
        private Node left;
        private Node right;

        public Node(K k, V vt) {
            this.key = k;
            this.vectx = vt;
            this.left = null;
            this.right = null;
        }
    }

    private Node root;

    private Node merge(Node heap1, Node heap2) {
        if (heap1 == null)
            return heap2;
        if (heap2 == null)
            return heap1;
        if ( heap1.key.compareTo(heap2.key) > 0 ) {
            Node tmp = heap1.left;
            heap1.left = merge(heap1.right, heap2);
            heap1.right = tmp;
            return heap1;
        } else {
            Node tmp = heap2.left;
            heap2.left = merge(heap2.right, heap1);
            heap2.right = tmp;
            return heap2;
        }
    }


    @Override
    public void push(K key, V value) {
        merge(root, new Node(key, value));
    }

    @Override
    public V pop() {
        V res = root.vectx;
        root = merge(root.left, root.right);
        return res;
    }

    @Override
    public void decreaseKey(K before, K after) {
        return;
    }

}
