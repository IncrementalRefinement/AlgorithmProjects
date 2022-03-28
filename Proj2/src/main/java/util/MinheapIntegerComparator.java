package util;

import java.util.Comparator;

public class MinheapIntegerComparator implements Comparator<Integer> {

    private static final MinheapIntegerComparator comparator = new MinheapIntegerComparator();

    private MinheapIntegerComparator() {}

    public static MinheapIntegerComparator getSingletonInstance() {
        return comparator;
    }

    @Override
    public int compare(Integer o1, Integer o2) {
        return Integer.compare(o1, o2);
    }
}
