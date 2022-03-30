package heap;

import java.util.HashMap;
import java.util.Map;
import java.util.Vector;

public class BinaryHeap<K extends Comparable<K>, V> implements Heap<K, V>{

    // TODO: only support no duplicate key case

    private Vector<Node> nodeVector;
    private Map<K, Integer> keyToIndexMap;

    private class Node {

        K key;
        V value;

        public Node(K theKey, V theValue) {
            key = theKey;
            value = theValue;
        }

        public K getKey() {
            return key;
        }

        public void setKey(K key) {
            this.key = key;
        }

        public V getValue() {
            return value;
        }

        public void setValue(V value) {
            this.value = value;
        }
    }

    public BinaryHeap() {
        nodeVector = new Vector<>();
        keyToIndexMap = new HashMap<>();
    }

    @Override
    public void push(K key, V value) {
        assert (!keyToIndexMap.containsKey(key));

        Node newNode = new Node(key, value);
        // 1. add the node to the end
        nodeVector.add(newNode);
        keyToIndexMap.put(key, nodeVector.size() - 1);
        // 2. swim the node up
        swim(nodeVector.size() - 1);
    }

    @Override
    public V pop() {
        assert (nodeVector.size() > 0);

        Node nodeToPop = nodeVector.get(0);
        exchange(0, nodeVector.size() - 1);
        nodeVector.remove(nodeVector.size() - 1);
        keyToIndexMap.remove(nodeToPop.getKey());
        sink(0);

        return nodeToPop.getValue();
    }

    @Override
    public void decreaseKey(K before, K after) {
        assert (before.compareTo(after) > 0);
        assert (!keyToIndexMap.containsKey(after));

        int index = keyToIndexMap.get(before);
        Node theNode = nodeVector.get(index);
        theNode.setKey(after);
        keyToIndexMap.remove(before);
        keyToIndexMap.put(after, index);
        swim(index);
    }

    private void swim(int index) {
        int currentIndex = index;
        int parentIndex = (currentIndex - 1) / 2;
        while (parentIndex >= 0 && parentIndex != currentIndex) {
            Node currentNode = nodeVector.get(currentIndex);
            Node parentNode = nodeVector.get(parentIndex);
            if (parentNode.getKey().compareTo(currentNode.getKey()) > 0) {
                exchange(currentIndex, parentIndex);
            } else {
                break;
            }
            currentIndex = parentIndex;
            parentIndex = (currentIndex - 1) / 2;
        }
    }

    private void sink(int index) {
        int N = nodeVector.size();
        int currentIndex = index;
        int leftChildIndex = 2 * currentIndex + 1;
        int rightChildIndex = 2 * currentIndex + 2;
        while (currentIndex < N && (leftChildIndex < N || rightChildIndex < N)) {
            Node currentNode = nodeVector.get(currentIndex);
            Node leftChildNode = nodeVector.get(leftChildIndex);
            if (rightChildIndex < N) {
                Node rightChildNode = nodeVector.get(rightChildIndex);
                if (rightChildNode.getKey().compareTo(leftChildNode.getKey()) < 0) {
                    if (currentNode.getKey().compareTo(rightChildNode.getKey()) > 0) {
                        exchange(currentIndex, rightChildIndex);
                        currentIndex = rightChildIndex;
                    } else {
                        break;
                    }
                } else {
                    if (currentNode.getKey().compareTo(leftChildNode.getKey()) > 0) {
                        exchange(currentIndex, leftChildIndex);
                        currentIndex = leftChildIndex;
                    } else {
                        break;
                    }
                }
            } else {
                if (currentNode.getKey().compareTo(leftChildNode.getKey()) > 0) {
                    exchange(currentIndex, leftChildIndex);
                    currentIndex = leftChildIndex;
                } else {
                    break;
                }
            }
            leftChildIndex = currentIndex * 2 + 1;
            rightChildIndex = currentIndex * 2 + 2;
        }
    }

    private void exchange(int index1, int index2) {
        Node node1 = nodeVector.get(index1);
        Node node2 = nodeVector.get(index2);
        nodeVector.set(index1, node2);
        nodeVector.set(index2, node1);
        keyToIndexMap.put(node1.getKey(), index2);
        keyToIndexMap.put(node2.getKey(), index1);
    }
}
