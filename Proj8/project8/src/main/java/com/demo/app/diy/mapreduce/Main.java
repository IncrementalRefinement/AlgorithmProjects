package com.demo.app.diy.mapreduce;

public class Main {

    public static void main(String[] args) {
        for (int i = 0; i < 4; i++) {
            TestRunnable t = new TestRunnable();
            t.run();
        }
    }
}
