package com.demo.app;

import javafx.util.Pair;

import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class WordCountSorter {

    public static List<Map.Entry<String, Integer>> sort(Set<Map.Entry<String, Integer>> entrySet) {
        List<Map.Entry<String, Integer>> ret = new LinkedList<>(entrySet);
        ret.sort(
            (Map.Entry<String, Integer> entry1, Map.Entry<String, Integer> entry2) -> {
                if (entry1.getValue().compareTo(entry2.getValue()) == 0) {
                    return entry1.getKey().compareTo(entry2.getKey());
                } else {
                    return entry1.getValue().compareTo(entry2.getValue());
                }
            }
        );
        return ret;
    }
}
