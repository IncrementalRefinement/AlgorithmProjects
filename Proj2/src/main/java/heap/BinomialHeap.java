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
        if (head == null) {
            head = h2.head;
            return;
        }
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

        Node temphead = curr3;

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

        // scan the list and repeatedly combine binomial trees with same degree
        Node cur = temphead;
        Node prev = temphead;
        Node next = cur.sibling;

        while (next != null) {
            // if two adjacent tree roots have different degree or 3 consecutive roots have same degree
            // move to the next tree. We only merge the last two roots in 3 consecutive roots;
            if ((cur.degree != next.degree) || (next.sibling != null && cur.degree == next.sibling.degree)) {
                prev = cur;
                cur = next;
            } else {
                // otherwise repeatdly merge binomial trees with same degree
                if (cur.key.compareTo(next.key) <= 0) {
                    cur.sibling = next.sibling;
                    linkBinomialTrees(cur, next);// curr3 as parent
                } else {
                    if (temphead == cur) {
                        temphead = next;// head merged
                    } else {
                        prev.sibling = next;
                    }
                    linkBinomialTrees(next, cur);// next as parent
                    cur = next;
                }
            }
            next = cur.sibling;
        }
        head = temphead;
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

        // find the smallest root from the heap
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

        Node theNode = keyToNodeMap.get(before);
        theNode.key = after;
        //swap the key, value, and pointer with its parent until the node.Key > node.parent.Key.
        while (theNode.parent != null) {
            if (theNode.key.compareTo(theNode.parent.key) < 0) {
                K tmp = theNode.key;
                V tmpv = theNode.value;
                keyToNodeMap.remove(theNode.key);
                keyToNodeMap.remove(theNode.parent.key);
                theNode.key = theNode.parent.key;
                theNode.value = theNode.parent.value;
                theNode.parent.key = tmp;
                theNode.parent.value = tmpv;
                keyToNodeMap.put(theNode.key,theNode);
                keyToNodeMap.put(theNode.parent.key,theNode.parent);
            } else {
                break;
            }
            theNode = theNode.parent;
        }
    }

}
