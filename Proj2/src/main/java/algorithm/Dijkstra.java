package algorithm;

import heap.BinaryHeap;
import heap.FibonacciHeap;
import heap.Heap;
import heap.Vertex;

import java.io.*;
import java.util.*;

public class Dijkstra {
    static List<Vertex> vertexs;
    static List<List<Vertex>> graphneigb;
    static List<Map<Vertex, Long>> graphdistance;

    public static void main(String[] args) throws IOException {
        vertexs = new ArrayList<>();
        graphneigb = new ArrayList<>();
        graphdistance = new ArrayList<>();
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
            long traveltime = Math.round(sc.nextDouble() * 1000);
            graphdistance.get(source).put(trg, traveltime);
            double spatialDistanceInMeters = sc.nextDouble();// ignore this data.
        }
        for (int i = 0; i < nodeNum; i++) {
            vertexs.get(i).setDirectDistance(graphdistance.get(i));
            vertexs.get(i).setNeighbors(graphneigb.get(i));
        }

        BinaryHeapEvaluate();
        FibonacciHeapEvaluate();

    }

    public static void BinaryHeapEvaluate() throws IOException {
        BufferedWriter writer = new BufferedWriter(new FileWriter("src/Results/BinaryHeap.dat"));
        for (int i = 0; i < 1001; i++) {
            //At least 1000 pairs of query
            long startTime = System.currentTimeMillis();   //获取开始时间
            for (int j = 0; j < 1001; j+=150) {
                search(vertexs, vertexs.get(j), new BinaryHeap<Long, Vertex>());
            }
            long endTime = System.currentTimeMillis(); //获取结束时间
            writer.write((endTime - startTime) + " ");
            writer.newLine();
        }
        writer.close();
    }

    public static void FibonacciHeapEvaluate() throws IOException {
        BufferedWriter writer = new BufferedWriter(new FileWriter("src/Results/FibonacciHeap.dat"));
        for (int i = 0; i < 1001; i++) {
            //At least 1000 pairs of query
            long startTime = System.currentTimeMillis();   //获取开始时间
            for (int j = 0; j < 1001; j+=150) {
                search(vertexs, vertexs.get(j), new FibonacciHeap<Long, Vertex>());
            }
            long endTime = System.currentTimeMillis(); //获取结束时间
            writer.write((endTime - startTime) + " ");
            writer.newLine();
        }
        writer.close();
    }

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
}
