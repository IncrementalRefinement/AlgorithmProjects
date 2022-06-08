package com.demo.app;

import java.io.FileOutputStream;
import java.io.IOException;
import java.util.concurrent.ThreadLocalRandom;

public class TextGenerator {

    private static final String THE_TEXT = "But in a larger sense we can not dedicate we can not consecrate" +
            " we can not hallow this ground The brave men living and dead who struggled here have consecrated it" +
            " far above our poor power to add or detract The world will little note nor long remember what we say here" +
            " but it can never forget what they did here It is for us the living rather to be dedicated here to the unfinished" +
            " work which they who fought here have thus far so nobly advanced It is rather for us to be here dedicated to the great" +
            " task remaining before us that from these honored dead we take increased devotion to that cause for which they gave the" +
            " last full measure of devotion that we here highly resolve that these dead shall not have died in vain that this nation under God" +
            " shall have a new birth of freedom and that government of the people by the people for the people shall not perish from the earth";

    private static final String[] WORD_POOL = THE_TEXT.toLowerCase().split("\\s+");

    private static final long DEFAULT_TEXT_LENGTH = 50000000;

    private static final String TXT_FILE_NAME = "input.txt";

    public static void main(String[] args) throws IOException {
        StringBuilder sb = new StringBuilder();
        int randomIndex;
        int maxRange = WORD_POOL.length;

        for (long i = 0; i < DEFAULT_TEXT_LENGTH; i++) {
            randomIndex = ThreadLocalRandom.current().nextInt(0, maxRange);
            sb.append(WORD_POOL[randomIndex]);
            sb.append(' ');
        }

        try (FileOutputStream fos = new FileOutputStream(TXT_FILE_NAME)) {
            fos.write(sb.toString().getBytes());
        }
    }
}
