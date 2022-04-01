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
            this.before = null;
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
            keyToNodeMap.remove(ret.key);
            N--;

            // 3. consolidate
            consolidate();
        }
        return ret.value;
    }

    @Override
    public void decreaseKey(K before, K after) {
        assert(before.compareTo(after) > 0);

        // 1. update the map
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

    private void insertBefore(Node position, Node insertedNode) {
        insertedNode.before = position.before;
        if (position.before != null) {
            position.before.after = insertedNode;
        }
        position.before = insertedNode;
        insertedNode.after = position;
    }

    private void insertAfter(Node position, Node insertedNode) {
        insertedNode.after = position.after;
        if (position.after != null) {
            position.after.before = insertedNode;
        }
        position.after = insertedNode;
        insertedNode.before = position;
    }

    // detach a node from all its relationship with others
    private void detachNode(Node theNode) {
        if (theNode.before != null) {
            theNode.before.after = theNode.after;
        }

        if (theNode.after != null) {
            theNode.after.before = theNode.before;
        }

        theNode.before = null;
        theNode.after = null;
        theNode.parent = null;
        theNode.children = null;
    }

    private void consolidate() {
        Map<Integer, Node> degreeToNode = new HashMap<>();
        Node currentNode = minNode;
        minNode = null;

        while (currentNode != null) {
            Node next = currentNode.after;
            int degree = currentNode.degree;
            while (degreeToNode.get(degree) != null) {
                Node other = degreeToNode.get(degree);
                currentNode = mergeTwoNode(currentNode, other);
                degreeToNode.remove(degree);
                degree = currentNode.degree;
            }
            degreeToNode.put(degree, currentNode);
            currentNode = next;
        }

        for (Node node : degreeToNode.values()) {
            insertIntoRootList(node);
        }
    }

    private Node mergeTwoNode(Node node1, Node node2) {
        if (node1.key.compareTo(node2.key) < 0) {
            node1.degree++;
            node2.mark = false;
            if (node1.children != null) {
                insertAfter(node1.children, node2);
            } else {
                node1.children = node2;
                node2.before = null;
                node2.after = null;
            }
            node2.parent = node1;
            return node1;
        } else {
            node2.degree++;
            node1.mark = false;
            if (node2.children != null) {
                insertAfter(node2.children, node1);
            } else {
                node2.children = node1;
                node1.before = null;
                node1.after = null;
            }
            node1.parent = node2;
            return node2;
        }
    }

    private void cut(Node theNode, Node parentNode) {
        parentNode.degree--;
        if (theNode == parentNode.children) {
            parentNode.children = theNode.after;
        }
        insertIntoRootList(theNode);
        theNode.mark = false;
    }

    private void cascadeCut(Node theNode) {
        Node parent = theNode.parent;
        if (parent != null) {
            if (!parent.mark) {
                parent.mark = true;
            } else {
                cut(theNode, parent);
                cascadeCut(parent);
            }
        }
    }

    private void insertIntoRootList(Node theNode) {
        theNode.before = null;
        theNode.after = null;
        theNode.parent = null;
        if (minNode == null) {
            minNode = theNode;
        } else if (theNode.key.compareTo(minNode.key) < 0) {
            insertBefore(minNode, theNode);
            minNode = theNode;
        } else {
            insertAfter(minNode, theNode);
        }
    }
}
