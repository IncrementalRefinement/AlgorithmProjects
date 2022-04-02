package heap;

import java.util.Stack;

public class binomialHeap<K extends Comparable<K>, V> implements Heap<K, V> {
    private Node head;
    private int size;

    public binomialHeap(int size) {
        this.head = null;
        this.size = size;
    }

    public binomialHeap(Node h, int size) {
        this.head = h;
        this.size = size;
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

    private void merge(binomialHeap h2) {
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
        // the roots of the tree must be in accending order of degree from
        // left to right
        while (curr1 != curr3 && curr2 != curr3) {
            if (curr1.degree <= curr2.degree) {
                curr3.sibling = curr1;
                curr1 = curr1.sibling;
            } else {
                curr3.sibling = curr2;
                curr2 = curr2.sibling;
            }

            curr3 = curr3.sibling;
        }

        if (curr1 != curr3) {
            // copy all the remaining trees of heap1
            while (curr1 != curr3) {
                curr3.sibling = curr1;
                curr1 = curr1.sibling;
                curr3 = curr3.sibling;
            }
        }

        if (curr2 != curr3) {
            // copy all the remaining trees of heap2
            while (curr2 != curr3) {
                curr3.sibling = curr2;
                curr2 = curr2.sibling;
                curr3 = curr3.sibling;
            }
        }


        // scan the merged list and repeatidly merge binomial trees with same degree
        curr3 = temp;
        Node prev = curr3;
        Node next = curr3.sibling;

        while (next != curr3) {
            // if two adjacent tree roots have different degree or 3 consecutive roots have same degree
            // move to the next tree
            if ((curr3.degree != next.degree) || (next.sibling != curr3 && curr3.degree == next.sibling.degree)) {
                prev = curr3;
                curr3 = next;
            } else {
                // otherwise repeatdly merge binomial trees with same degree
                if (curr3.key.compareTo(next.key) <= 0) {
                    curr3.sibling = next.sibling;
                    linkBinomialTrees(curr3, next);
                } else {
                    if (prev == curr3) {
                        temp = next;
                    } else {
                        prev.sibling = next;
                    }



                    linkBinomialTrees(next, curr3);
                    curr3 = next;
                }
            }

            next = curr3.sibling;
        }

        head = temp;
    }

    @Override
    public void push(K key, V value) {
        Node tmp = new Node(key, value);
        binomialHeap h = new binomialHeap(tmp, 1);
        merge(h);
    }

    @Override
    public V pop() {        // traverse all the roots and find compare
        if (head == null) {
            return null;
        }
        // deletes the smallest node from the heap
        Node curr = head;
        Node prevMin = null;
        // find the root with minimum key
        Node minPtr = head;
        Node prevPtr = null;
        K minkey = head.key;


        while (curr != null) {
            if (curr.key.compareTo(minkey) <= 0) {
                minkey = curr.key;
                prevMin = prevPtr;
                minPtr = curr;
            }
            prevPtr = curr;
            curr = curr.sibling;
        }

        // delete the node pointed by minPtr
        if (prevMin != null) {
            prevMin.sibling = minPtr.sibling;
        } else {
            head = minPtr.sibling;
        }

        // remove parent reference from all its child
        Node childPtr = minPtr.child;
        while (childPtr != null) {
            childPtr.parent = null;
            childPtr = childPtr.sibling;
        }

        // reverse the order
        Stack<Node> s = new Stack<Node>();
        childPtr = minPtr.child;
        while (childPtr != null) {
            s.push(childPtr);
            childPtr = childPtr.sibling;

            curr = s.peek();
            Node temp = curr;
            s.pop();

            while (!s.empty()) {
                curr.sibling = s.peek();
                s.pop();
                curr = curr.sibling;
            }

            curr.sibling = null;

            binomialHeap h = new binomialHeap(1);
            h.head = temp;

            // merge
            merge(h);

            // return the min root
            return minPtr.value;

        }

        @Override
        public void decreaseKey (K before, K after){

        }
    }
