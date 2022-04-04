package algorithm;

import heap.BinaryHeap;
import heap.Heap;
import heap.Vertex;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class Dijkstra {
    public static void main(String[] args) throws FileNotFoundException {
        List<Vertex> vertexs = new ArrayList<>();
        List<List<Vertex>> graphneigb = new ArrayList<>();
        List<Map<Vertex, Long>> graphdistance = new ArrayList<>();
        File dataset = new File("src/dataset/DCdata.dat");
        Scanner sc = new Scanner(dataset);
        int nodeNum = sc.nextInt();
        for (int i = 0; i < nodeNum; i++) {
            vertexs.add(new Vertex());
            graphneigb.add(new ArrayList<>());
            graphdistance.add(new HashMap<>());
        }
        int edgeNum = sc.nextInt();
        while (sc.hasNext()) {
            int source = sc.nextInt();
            int target = sc.nextInt();
            Vertex trg = vertexs.get(target);
            graphneigb.get(source).add(trg);
            long traveltime = sc.nextLong();
            graphdistance.get(source).put(trg, traveltime);
            long spatialDistanceInMeters = sc.nextLong();// ignore this data.
        }
        for (int i = 0; i < nodeNum; i++) {
            vertexs.get(i).setDirectDistance(graphdistance.get(i));
            vertexs.get(i).setNeighbors(graphneigb.get(i));
        }

        for (int i = 0; i < 1001; i++) {
            search(vertexs,vertexs.get(0),new BinaryHeap<Long, Vertex>());
        }


    }

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
                        neighbor.setDistanceFromSource(alt);
                        pq.decreaseKey(neighbor.getDistanceFromSource(), alt);
                    }
                }
            }
        }
    }
}
