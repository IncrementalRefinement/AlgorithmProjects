package com.demo.app.diy.mapreduce;

import javafx.util.Pair;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;
import java.util.concurrent.LinkedBlockingQueue;

public class Mapper implements Runnable {

    private final LinkedBlockingQueue<Pair<String, Integer>> outputQueue;
    private final List<File> fileList;

    public Mapper() {
        this.outputQueue = new LinkedBlockingQueue<>();
        this.fileList = new LinkedList<>();
    }

    @Override
    public void run() {
        List<Scanner> scannerList = new LinkedList<>();
        for (File file : fileList) {
            try {
                Scanner scanner = new Scanner(file);
                scannerList.add(scanner);
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
        }

        for (Scanner scanner : scannerList){
            while (scanner.hasNext()) {
                String word = scanner.next();
                outputQueue.offer(new Pair<>(word, 1));
            }
            scanner.close();
        }
    }

    public LinkedBlockingQueue<Pair<String, Integer>> getOutputQueue() {
        return outputQueue;
    }

    public void addFile(File newFile) {
        fileList.add(newFile);
    }
}
