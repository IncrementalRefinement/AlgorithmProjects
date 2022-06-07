package com.demo.app.diy.mapreduce;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Main {

    public static void main(String[] args) {
        ExecutorService executorService = Executors.newCachedThreadPool();
        System.out.println("Main begins");
        TestRunnable t1 = new TestRunnable();
        TestRunnable t2 = new TestRunnable();
        TestRunnable t3 = new TestRunnable();
        TestRunnable t4 = new TestRunnable();
        executorService.execute(t1);
        executorService.execute(t2);
        executorService.execute(t3);
        executorService.execute(t4);
        System.out.println();
        System.out.println("Main ends");
    }
}
