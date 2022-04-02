package algorithm;

import heap.Heap;
import heap.Vertex;

import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class Dijkstra {

    public static void search(List<Vertex> graph, Vertex source, Heap<Long, Vertex> pq) {

        for (Vertex vertex : graph) {
            vertex.setVertexBefore(null);
            vertex.setDistanceFromSource(Long.MAX_VALUE);
        }

        Set<Vertex> vertexInHeap = new HashSet<>();

        pq.push(0L, source);
        vertexInHeap.add(source);

        while (!vertexInHeap.isEmpty()) {
            Vertex theVertex = pq.pop();
            vertexInHeap.remove(theVertex);
            for (Vertex neighbor : theVertex.getNeighbors()) {
                if (neighbor.getVertexBefore() == null) {
                    // the vertex that is firstly visited will be add to the pq & the set
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
                        neighbor.setDistanceFromSource(alt);
                        pq.decreaseKey(neighbor.getDistanceFromSource(), alt);
                    }
                }
            }
        }
    }
}
