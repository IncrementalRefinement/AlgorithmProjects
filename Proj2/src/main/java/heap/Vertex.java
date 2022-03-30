package heap;

import java.util.List;
import java.util.Map;

public class Vertex {

    private long distanceFromSource;
    private Vertex vertexBefore;
    private List<Vertex> neighbors;
    private Map<Vertex, Long> directDistance;

    public Vertex() {
        this.distanceFromSource = Long.MIN_VALUE;
        this.vertexBefore = null;
    }

    public void setDistanceFromSource(long distance) {
        this.distanceFromSource = distance;
    }

    public void setVertexBefore(Vertex vertex) {
        this.vertexBefore = vertex;
    }

    public void setNeighbors(List<Vertex> neighbors) {
        this.neighbors = neighbors;
    }

    public void setDirectDistance(Map<Vertex, Long> directDistance) {
        this.directDistance = directDistance;
    }

    public long getDistanceFromSource() {
        return distanceFromSource;
    }

    public Vertex getVertexBefore() {
        return vertexBefore;
    }

    public List<Vertex> getNeighbors() {
        return this.neighbors;
    }

    public long getDirectDistance(Vertex vertex) {
        return directDistance.get(vertex);
    }
}
