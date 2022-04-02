package heap;

import java.util.HashMap;
import java.util.Map;

public class BinomialHeap<K extends Comparable<K>, V> implements Heap<K, V> {
    private Node head;
    private int size;
    private Map<K, Node> keyToNodeMap;

    public BinomialHeap() {
        this.head = null;
        keyToNodeMap = new HashMap<>();
    }

    public BinomialHeap(Node h) {
        this.head = h;
        keyToNodeMap = new HashMap<>();
    }

    private class Node {
        K key;
        V value;
        int degree;
        Node parent;
        Node sibling;
        Node child;

        public Node(K key, V value) {
            this.key = key;
            this.value = value;
            this.degree = 0;
            this.parent = null;
            this.sibling = null;
            this.child = null;
        }
    }

    private void linkBinomialTrees(Node x, Node y) {
        // x is  y's parent
        y.parent = x;
        y.sibling = x.child;
        x.child = y;
        // increase the degree of x
        x.degree += 1;
    }

    private void merge(BinomialHeap h2) {
        Node curr1 = head;
        Node curr2 = h2.head;
        Node curr3;
        if (curr1.degree <= curr2.degree) {
            curr3 = curr1;
            curr1 = curr1.sibling;
        } else {
            curr3 = curr2;
            curr2 = curr2.sibling;
        }

        Node temp = curr3;

        // merge two heaps without taking care of trees with same degree
        // the roots of the tree must be in acscending order of degree
        while (curr1 != null && curr2 != null) {
            if (curr1.degree <= curr2.degree) {
                curr3.sibling = curr1;
                curr1 = curr1.sibling;
            } else {
                curr3.sibling = curr2;
                curr2 = curr2.sibling;
            }
            curr3 = curr3.sibling;
        }

        // copy all the remaining trees of heap1
        while (curr1 != null) {
            curr3.sibling = curr1;
            curr1 = curr1.sibling;
            curr3 = curr3.sibling;
        }
        // copy all the remaining trees of heap2
        while (curr2 != null) {
            curr3.sibling = curr2;
            curr2 = curr2.sibling;
            curr3 = curr3.sibling;
        }

        // scan the list and repeatedly merge binomial trees with same degree
        curr3 = temp;
        Node prev = curr3;
        Node next = curr3.sibling;

        while (next != null) {
            // if two adjacent tree roots have different degree or 3 consecutive roots have same degree
            // move to the next tree. We only merge the last two roots in 3 consecutive roots;
            if ((curr3.degree != next.degree) || (next.sibling != null && curr3.degree == next.sibling.degree)) {
                prev = curr3;
                curr3 = next;
            } else {
                // otherwise repeatdly merge binomial trees with same degree
                if (curr3.key.compareTo(next.key) <= 0) {
                    curr3.sibling = next.sibling;
                    linkBinomialTrees(curr3, next);// curr3 as parent
                } else {
                    if (prev == curr3) {
                        temp = next;// head merged
                    } else {
                        prev.sibling = next;
                    }
                    linkBinomialTrees(next, curr3);// next as parent
                    curr3 = next;
                }
            }
            next = curr3.sibling;
        }
        head = temp;
    }

    private Node reverlist(Node head) {
        Node prev = new Node(null, null);
        prev.sibling = head;
        Node cur = head;
        while (cur != null) {
            Node next = cur.sibling;
            cur.sibling = prev;
            prev = cur;
            cur = next;
        }
        Node newHead = prev;
        head.sibling = null;
        return newHead;
    }

    @Override
    public void push(K key, V value) {
        Node tmp = new Node(key, value);
        keyToNodeMap.put(key, tmp);
        if (this.head == null) {
            this.head = tmp;
            return;
        }
        BinomialHeap h = new BinomialHeap();
        h.head = tmp;
        merge(h);
    }

    @Override
    public V pop() {
        // traverse all the roots and find compare
        if (this.head == null) {
            return null;
        }
        Node curr = head;
        Node prevMin = null;// find the root with minimum key
        Node minPtr = head;
        Node prevPtr = null;
        K minkey = head.key;
        // remove the smallest node from the heap
        while (curr != null) {
            if (curr.key.compareTo(minkey) <= 0) {
                minkey = curr.key;
                prevMin = prevPtr;
                minPtr = curr;
            }
            prevPtr = curr;
            curr = curr.sibling;
        }

        // remove the node pointed by minPtr
        if (prevMin != null) {
            prevMin.sibling = minPtr.sibling;
        } else {
            head = minPtr.sibling;
        }
        keyToNodeMap.remove(minPtr.key);
        if (minPtr.child == null) {
            return minPtr.value;
        }
        // process child of min root

        // remove parent reference from all its child
        Node childPtr = minPtr.child;
        while (childPtr != null) {
            childPtr.parent = null;
            childPtr = childPtr.sibling;
        }

        // reverse the order in root's children
        Node childP = minPtr.child;
        BinomialHeap h = new BinomialHeap(reverlist(childP));
        merge(h);
        return minPtr.value;
    }

    @Override
    public void decreaseKey(K before, K after) {
        assert (before.compareTo(after) > 0);

        // 1. update the map
        Node theNode = keyToNodeMap.get(before);
        theNode.key = after;

        while (theNode.parent != null) {
            if (theNode.key.compareTo(theNode.parent.key) < 0) {
                K tmp = theNode.key;
                V tmpv = theNode.value;
                theNode.key = theNode.parent.key;
                theNode.value = theNode.parent.value;
                theNode.parent.key = tmp;
                theNode.parent.value = tmpv;
            } else {
                break;
            }
            theNode = theNode.parent;
        }
    }
}
