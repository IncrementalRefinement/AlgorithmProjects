package com.demo.app.diy.mapreduce;

import javafx.util.Pair;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.LinkedBlockingQueue;

public class Reducer implements Runnable {

    private List<LinkedBlockingQueue<Pair<String, Integer>>> inputQueues;
    private Map<String, Integer> outputMap;

    public Reducer() {
        this.inputQueues = new LinkedList<>();
        this.outputMap = new HashMap<>();
    }

    @Override
    public void run() {
        while (true) {
            for (LinkedBlockingQueue<Pair<String, Integer>> queue : inputQueues) {
                if (!queue.isEmpty()) {
                    Pair<String, Integer> thePair = queue.poll();
                    outputMap.merge(thePair.getKey(), 1, Integer::sum);
                }
            }
        }
    }

    public Map<String, Integer> getOutputMap() {
        return outputMap;
    }

    public void addInputQueue(LinkedBlockingQueue<Pair<String, Integer>> theQueue) {
        inputQueues.add(theQueue);
    }
}
