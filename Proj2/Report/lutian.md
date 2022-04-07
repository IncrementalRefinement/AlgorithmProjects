# Proj2

## Architecture of the Project

We implement this project in Java and use [Maven](https://maven.apache.org/) for project management and building automation. As a result, the project is organized in a "Maven" way. The implementation of all the Heap is inside "/src/main/java/heap/" the Dijkstra and the performance test code is within the class "algorithm.Dijkstra". Also, we adopt the idea of Test Driven Development(TDD), and constructed a set of unit test in "src/test/java" before actual implementation procedure.

The test data and the test result is in //TODO. You can also run the main method in "algorithm.Dijkstra" and relaunch the test and generate the result if you like.

## Introduction of the Fibonacci Heap

// TODO

## Theoretical Comparison

// TODO

### Binary Heap

### Fibonacci Heap

## Theoretical Analysis of the Dijkstra Algorithm

Bounds of the running time of Dijkstra's algorithm on a graph with edges **E** and vertices **V** can be expressed as a function of the number of edges **|E|** and the number of vertices **|V|**. The complexity is mainly determined by the data structure that is used to represent the priority queue of the vertex.

For any data structure, the running time is[1]:

$\Theta(|E| * T_{\text{dk}} + |V| * T_{\text{pop}})$

The $T_{\text{dk}}$ and $T_{\text{em}}$ are the complexities of the decrease-key and pop operations of the implementation data structure beneath the priority queue.

// TODO: maybe

## Test

// pass

## Discussion & Conclusion

## References

1. Cormen, Thomas H.; Leiserson, Charles E.; Rivest, Ronald L.; Stein, Clifford (2001). "Section 24.3: Dijkstra's algorithm". Introduction to Algorithms (Second ed.). MIT Press and McGraw–Hill. pp. 595–601. ISBN 0-262-03293-7.
