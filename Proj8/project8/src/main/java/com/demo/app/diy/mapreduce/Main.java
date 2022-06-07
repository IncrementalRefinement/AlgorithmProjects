package com.demo.app.diy.mapreduce;

import com.demo.app.TextSplitter;

import java.io.File;
import java.util.*;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Main {

    private static final int MAPPER_NUM = 4;
    private static final int REDUCER_NUM = 4;

    public static void main(String[] args) throws InterruptedException {
        Date beginTime = new java.util.Date();

        List<Mapper> mappers = new ArrayList<>(MAPPER_NUM);
        List<Reducer> reducers = new ArrayList<>(REDUCER_NUM);
        ExecutorService executorService = Executors.newCachedThreadPool();

        for (int i = 0; i < MAPPER_NUM; i++) {
            mappers.add(new Mapper());
        }

        for (int i = 0; i <REDUCER_NUM; i++) {
            reducers.add(new Reducer());
        }

        for (int i = 0; i < TextSplitter.SPLIT_NUMBER; i++) {
            File file = new File("input_" + i + ".txt");
            mappers.get(i % MAPPER_NUM).addFile(file);
        }

        for (int i = 0; i < MAPPER_NUM; i++) {
            reducers.get(i % REDUCER_NUM).addInputQueue(mappers.get(i).getOutputQueue());
        }

        List<Thread> mapperThreads = new LinkedList<>();
        for (Mapper mapper : mappers) {
            Thread mapperThread = new Thread(mapper);
            // executorService.submit(mapperThread);
            mapperThreads.add(mapperThread);
            mapperThread.start();
        }

        List<Thread> reducerThreads = new LinkedList<>();
        for (Reducer reducer : reducers) {
            Thread reducerThread = new Thread(reducer);
            // executorService.submit(reducerThread);
            reducerThreads.add(reducerThread);
            reducerThread.start();
        }

        for (Thread thread : mapperThreads) {
            thread.join();
        }

        for (Thread thread : reducerThreads) {
            thread.stop();
        }

        List<Map<String, Integer>> mapList = new LinkedList<>();
        for (Reducer reducer : reducers) {
            mapList.add(reducer.getOutputMap());
        }
        Map<String, Integer> combineResult = combine(mapList);
        for (Map.Entry<String, Integer> entry : combineResult.entrySet()) {
            System.out.println(entry.getKey() + " : " + entry.getValue());
        }

        Date endTine = new java.util.Date();
        long deltaTime = endTine.getTime() - beginTime.getTime();
        System.out.println((double) deltaTime / 1000);
    }

    private static Map<String, Integer> combine(List<Map<String, Integer>> mapList) {
        Map<String, Integer> result = new HashMap<>();
        for (Map<String, Integer> map : mapList) {
            for (Map.Entry<String, Integer> entry : map.entrySet()) {
                result.merge(entry.getKey(), entry.getValue(), Integer::sum);
            }
        }
        return result;
    }
}
