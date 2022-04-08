# Proj2

## Architecture of the Project

We implement this project in Java and use [Maven](https://maven.apache.org/) for project management and building automation. As a result, the project is organized in a "Maven" way. The implementation of all the Heap is inside "/src/main/java/heap/" the Dijkstra and the performance test code is within the class "algorithm.Dijkstra". Also, we adopt the idea of Test Driven Development(TDD), and constructed a set of unit test in "src/test/java" before actual implementation procedure.

The test data and the test result is in //TODO. You can also run the main method in "algorithm.Dijkstra" and relaunch the test and generate the result if you like.

## Introduction of the Fibonacci Heap

Fibonacci heap is a data structure for priority queue operations, consisting of a collection of heap-ordered trees. It has a better amortized running time than many other priority queue data structures including the binary heap and binomial heap. A Fibonacci heap is a collection of trees satisfying the heap property.

// TODO fib_heap_img1.png

In our implementation, the node of the tree is organized in a doubled linked list. Each node maintains the value, key and the degree of the current node. Also the node also store the pointer to its parent and leftmost child.

```java
private class Node {

    public boolean mark;
    public int degree;
    public K key;
    public V value;
    public Node before, after, parent, children;
}
```

The FibonacciHeap keep track of node with the minimum key. Also, in order to support the DECREASE-KEY operation in $\Theta(1)$ time complexity, the HashMap of keyToNodeMap is introduced to accelerate the look up operation.

```java
public class FibonacciHeap<K extends Comparable<K>, V> implements Heap<K, V> {
    // ......
    
    // ptr to the minNode is also the ptr to the rootNodeList
    private Node minNode;
    private int N;
    private Map<K, Node> keyToNodeMap;

    // .......
}
```

The push operation is rather simple and swift —— we simply insert the new node into the list of the root nodes and update the map. Which will take only constant time.

```java
@Override
public void push(K key, V value) {
    Node theNode = new Node(key, value);
    keyToNodeMap.put(key, theNode);
    insertIntoRootList(theNode);
    N++;
}
```

The pop operation first insert the children of the minNode into the root node list and then remove the minNode. After that the delayed work of consolidating the trees in the root list finally occurs. The consolidate operation aims to make the trees within the root list only have unique degree(the number of children). The consolidate operation makes sure that the root list wouldn't expand too long. Intuitively thinking, if the root list if so long that it is degenerates to a linked list with the pointer to its minimum node, the pop operation will have to iterate through the list to find the minimum node after the pop, which is undesirable.

```java
@Override
public V pop() {
    assert (minNode != null);

    Node ret = minNode;
    if (ret != null) {
        // 1. insert the child node into root node list
        Node theNode = minNode.children;
        while (theNode != null) {
            Node nextNode = theNode.after;
            removeFromDoubleLinkedList(theNode);
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

private void consolidate() {
    Map<Integer, Node> degreeToNode = new HashMap<>();
    Node currentNode = minNode;
    minNode = null;

    while (currentNode != null) {
        Node next = currentNode.after;
        removeFromDoubleLinkedList(currentNode);
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
```

The decreaseKey of the heap is not as complicated as the pop operation. We firstly look up the node in the map and then update its key. If the key is less the key of its parent, we cut the node from its parent and insert it into the root node list.

But wait, what about cascadeCut operation, why would we bother doing that? Why would we cut the parent from the grand parent node if the grand parent node has been marked()?. The answer is that the cascade operation makes sure that the tree would have too much kid and become too flat. Otherwise the flat tree will takes much time to insert all these child of the flat layer of the tree. However, the cascade will cause the root list longer than simple cut. I think it's kind of like a tradeoff between the length of the root node list and the flatness of the tree in root node list.

```java
@Override
public void decreaseKey(K before, K after) {
    assert(before.compareTo(after) > 0);
    assert (!keyToNodeMap.containsKey(after));

    // 1. update the map
    Node theNode = keyToNodeMap.get(before);
    theNode.key = after;
    keyToNodeMap.remove(before);
    keyToNodeMap.put(after, theNode);

    if (theNode.parent != null) {
        if (theNode.key.compareTo(theNode.parent.key) < 0) {
            Node parentNode = theNode.parent;
            cut(theNode, theNode.parent);
            cascadeCut(parentNode);
        }
    } else {
        // The node is within the root list
        removeFromDoubleLinkedList(theNode);
        insertIntoRootList(theNode);
    }
}

private void cut(Node theNode, Node parentNode) {
    parentNode.degree--;
    if (theNode == parentNode.children) {
        parentNode.children = theNode.after;
    } else {
        theNode.parent = null;
        theNode.before.after = theNode.after;
        if (theNode.after != null) {
            theNode.after.before = theNode.before;
        }
    }
    removeFromDoubleLinkedList(theNode);
    insertIntoRootList(theNode);
    theNode.mark = false;
}

private void cascadeCut(Node theNode) {
    Node parent = theNode.parent;
    if (parent != null) {
        if (!theNode.mark) {
            theNode.mark = true;
        } else {
            cut(theNode, parent);
            cascadeCut(parent);
        }
    }
}
```

## Theoretical Comparison

// PASS

### Binary Heap

### Fibonacci Heap

## Theoretical Analysis of the Dijkstra Algorithm

Bounds of the running time of Dijkstra's algorithm on a graph with edges **E** and vertices **V** can be expressed as a function of the number of edges **|E|** and the number of vertices **|V|**. The complexity is mainly determined by the data structure that is used to represent the priority queue of the vertex.

For any data structure, the running time is[1]:

$\Theta(|E| * T_{\text{dk}} + |V| * T_{\text{pop}})$

The $T_{\text{dk}}$ and $T_{\text{em}}$ are the complexities of the decrease-key and pop operations of the implementation data structure beneath the priority queue which is already presented in last section.

## Test

// pass

## Discussion & Conclusion

As the test shows, it seems like the fibonacci heap doesn't outperform the binary heap a lot, sometimes even worse than the binomial heap. But why? It is because of the way we implement the Dijkstra algorithm. In our implementation, we don't push all the vertex into the PQ at the beginning. Rather, we only push the node into the PQ as its been visited. As a result, the size of the heap is not that big and the improvement of advanced algorithm is not prominent. On the contrary, the complex operation of the doubled linked list will takes more time than some naive approach. But if the Dijkstra algorithm makes the heap with large scale at the beginning, the fibonacci heap will show its efficiency of amortized logN complexity DECREASE-KEY.

```java
public static void search(List<Vertex> graph, Vertex source, Heap<Long, Vertex> pq) {

    for (Vertex vertex : graph) {
            vertex.setVertexBefore(null);
            vertex.setDistanceFromSource(Long.MAX_VALUE);
    }

    Set<Vertex> vertexInHeap = new HashSet<>();

    source.setVertexBefore(null);
    source.setDistanceFromSource(0);
    pq.push(0L, source);
    vertexInHeap.add(source);

    while (!vertexInHeap.isEmpty()) {
        Vertex theVertex = pq.pop();
        vertexInHeap.remove(theVertex);
        for (Vertex neighbor : theVertex.getNeighbors()) {
            if (neighbor.getVertexBefore() == null) {
                // the vertex that is firstly visited will be added to the pq & the set
                neighbor.setVertexBefore(theVertex);
                neighbor.setDistanceFromSource(theVertex.getDistanceFromSource() + theVertex.getDirectDistance(neighbor));
                vertexInHeap.add(neighbor);
                pq.push(neighbor.getDistanceFromSource(), neighbor);
            } else {
                if (!vertexInHeap.contains(neighbor)) {
                    // if the vertex is already visited and not inside the pq, the shorted path to it has already been found
                    continue;
                }
                long alt = theVertex.getDistanceFromSource() + theVertex.getDirectDistance(neighbor);
                if (alt < neighbor.getDistanceFromSource()) {
                    pq.decreaseKey(neighbor.getDistanceFromSource(), alt);
                    neighbor.setDistanceFromSource(alt);
                }
            }
        }
    }
}
```

The result of the project enlighten us that the more advanced approach might not always be the best approach, we should design and pick up the most suitable approach in practice.

## References

1. Cormen, Thomas H.; Leiserson, Charles E.; Rivest, Ronald L.; Stein, Clifford (2001). "Section 24.3: Dijkstra's algorithm". Introduction to Algorithms (Second ed.). MIT Press and McGraw–Hill. pp. 595–601. ISBN 0-262-03293-7.
