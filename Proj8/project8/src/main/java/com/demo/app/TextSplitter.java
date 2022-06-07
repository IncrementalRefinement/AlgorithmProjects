package com.demo.app;

import java.io.File;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;

public class TextSplitter {

    private static final String INPUT_FILE = "input.txt";
    public static final int SPLIT_NUMBER = 8;

    public static void main(String[] args) throws IOException {
        FileOutputStream[] fileOutputStreams = new FileOutputStream[SPLIT_NUMBER];

        for (int i = 0; i < SPLIT_NUMBER; i++) {
            fileOutputStreams[i] = new FileOutputStream("input_" + i +".txt");
        }


        long index = 0;

        File inputFile = new File(INPUT_FILE);
        Scanner scanner = new Scanner(inputFile);

        while (scanner.hasNext()) {
            String word = scanner.next();
            fileOutputStreams[(int) (index % SPLIT_NUMBER)].write((word + " ").getBytes());
            index++;
        }
    }
}
