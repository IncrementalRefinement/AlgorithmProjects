package com.demo.app;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class NaiveWordCount {

    // TODO: get run time
    
    public static void main(String[] args) throws Exception {
        Date beginTime = new java.util.Date();

        File inputFile = new File("input.txt");
//        BufferedReader br = new BufferedReader(new FileReader(inputFile));
        Map<String, Long> wordCountMap = new HashMap<>();

//        String[] words = br.readLine().split("\\s+");
        Scanner fileReader = new Scanner(inputFile);


        while (fileReader.hasNext()) {
            String word = fileReader.next();
            Long count = wordCountMap.get(word);
            if (count == null) {
                wordCountMap.put(word, 1L);
            } else {
                wordCountMap.put(word, count + 1);
            }
        }


        StringBuilder sb = new StringBuilder();

        for (Map.Entry<String, Long> entry : wordCountMap.entrySet()) {
            sb.append(entry.getKey()).append(": ").append(entry.getValue()).append('\n');
        }

        File outputFile = new File("output.txt");

        try (FileOutputStream fos = new FileOutputStream(outputFile)) {
            fos.write(sb.toString().getBytes());
        }

        Date endTine = new java.util.Date();
        long deltaTime = endTine.getTime() - beginTime.getTime();
        System.out.println((double) deltaTime / 1000);
    }
}
