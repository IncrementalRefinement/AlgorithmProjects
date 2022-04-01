package heap;

import java.util.HashMap;
import java.util.Map;

public class FibonacciHeap<K extends Comparable<K>, V> implements Heap<K, V>{

    private class Node {

        public boolean mark;
        public int degree;
        public K key;
        public V value;
        public Node before, after, parent, children;

        public Node(K theKey, V theValue) {
            this.mark = false;
            this.degree = 0;
            this.key = theKey;
            this.value = theValue;
            this.after = null;
            this.parent = null;
            this.children = null;
        }
    }


    // ptr to the mainNode is also the ptr to the rootNodeList
    private Node minNode;
    private int N;
    private Map<K, Node> keyToNodeMap;

    public FibonacciHeap() {
        minNode = null;
        N = 0;
        keyToNodeMap = new HashMap<>();
    }

    @Override
    public void push(K key, V value) {
        Node theNode = new Node(key, value);
        keyToNodeMap.put(key, theNode);
        insertIntoRootList(theNode);
        N++;
    }

    @Override
    public V pop() {
        assert (minNode != null);

        Node ret = minNode;
        if (ret != null) {
            // 1. insert the child nod
            Node theNode = minNode.children;
            while (theNode != null) {
                Node nextNode = theNode.after;
                insertAfter(minNode, theNode);
                theNode.parent = null;
                theNode = nextNode;
            }

            // 2. remove the current minNoe
            minNode = ret.after;
            detachNode(ret);
            N--;

            // 3. consolidate
            consolidate();
        }
        return ret.value;
    }

    @Override
    public void decreaseKey(K before, K after) {
        // 1. update the map
        assert(before.compareTo(after) > 0);

        Node theNode = keyToNodeMap.get(before);
        theNode.key = after;
        keyToNodeMap.remove(before);
        keyToNodeMap.put(after, theNode);

        if (theNode.parent != null) {
            if (theNode.key.compareTo(theNode.parent.key) < 0) {
                cut(theNode, theNode.parent);
                cascadeCut(theNode.parent);
            }
        }
    }

    private void insertBefore(Node position, Node insertedNode) {}

    private void insertAfter(Node position, Node insertedNode) {}

    private void detachNode(Node theNode) {}

    private void consolidate() {}

    private void cut(Node theNode, Node parentNode) {}

    private void cascadeCut(Node theNode) {}

    private void insertIntoRootList(Node theNode) {}
}
