package com.demo.app;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.util.HashMap;
import java.util.Map;

public class NaiveWordCount {

    // TODO: get run time
    
    public static void main(String[] args) throws Exception {
        File inputFile = new File(args[0]);
        BufferedReader br = new BufferedReader(new FileReader(inputFile));
        Map<String, Long> wordCountMap = new HashMap<>();

        String[] words = br.readLine().split("\\s+");

        for (String word : words) {
            Long count = wordCountMap.get(word);
            if (count == null) {
                wordCountMap.put(word, 0L);
            } else {
                wordCountMap.put(word, count + 1);
            }
        }


        StringBuilder sb = new StringBuilder();

        for (Map.Entry<String, Long> entry : wordCountMap.entrySet()) {
            sb.append(entry.getKey()).append(": ").append(entry.getValue()).append('\n');
        }

        File outputFile = new File(args[1]);

        try (FileOutputStream fos = new FileOutputStream(outputFile)) {
            fos.write(sb.toString().getBytes());
        }
    }
}
