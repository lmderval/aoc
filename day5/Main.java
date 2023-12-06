import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

public class Main {

    private static int readMap(List<String> lines, int beg,
                               List<Long[]> map) {
        int i;
        for (i = beg; i < lines.size(); i++) {
            if (lines.get(i).length() == 0) {
                break;
            }

            String[] rawPlans = lines.get(i).split(" ");
            Long[] plans = new Long[3];
            for (int j = 0; j < 3; j++) {
                plans[j] = Long.parseLong(rawPlans[j]);
            }

            map.add(plans);
        }

        return i + 2;
    }

    private static long[] parseSeeds(String s) {
        String[] rawSeeds = s.substring(7).split(" ");
        long[] seeds = new long[rawSeeds.length];
        for (int i = 0; i < seeds.length; i++) {
            seeds[i] = Long.parseLong(rawSeeds[i]);
        }

        return seeds;
    }

    private static void applyMap(long[] arr, List<Long[]> map) {
        long[] applied = new long[arr.length];
        System.arraycopy(arr, 0, applied, 0, arr.length);
        for (int i = 0; i < arr.length; i++) {
            for (Long[] plan : map) {
                long dest = plan[0];
                long src = plan[1];
                long length = plan[2];
                if (src <= arr[i] && arr[i] < src + length) {
                    applied[i] += dest - src;
                }
            }
        }

        System.arraycopy(applied, 0, arr, 0, arr.length);
    }

    private static long minOf(long[] arr) {
        long min = arr[0];
        for (long val : arr) {
            if (val < min) {
                min = val;
            }
        }

        return min;
    }

    private static long readAlmanac(List<String> lines) {
        long[] seeds = parseSeeds(lines.get(0));

        int i = 3;
        List<Long[]> toSoil = new ArrayList<>();
        i = readMap(lines, i, toSoil);

        List<Long[]> toFertilizer = new ArrayList<>();
        i = readMap(lines, i, toFertilizer);

        List<Long[]> toWater = new ArrayList<>();
        i = readMap(lines, i, toWater);

        List<Long[]> toLight = new ArrayList<>();
        i = readMap(lines, i, toLight);

        List<Long[]> toTemp = new ArrayList<>();
        i = readMap(lines, i, toTemp);

        List<Long[]> toHumidity = new ArrayList<>();
        i = readMap(lines, i, toHumidity);

        List<Long[]> toLocation = new ArrayList<>();
        i = readMap(lines, i, toLocation);

        applyMap(seeds, toSoil);
        applyMap(seeds, toFertilizer);
        applyMap(seeds, toWater);
        applyMap(seeds, toLight);
        applyMap(seeds, toTemp);
        applyMap(seeds, toHumidity);
        applyMap(seeds, toLocation);

        return minOf(seeds);
    }

    private static long readAlmanacRange(List<String> lines) {
        long[] seedsFactory = parseSeeds(lines.get(0));
        long start = seedsFactory[0];
        long end = start + seedsFactory[1];
        for (int i = 2; i < seedsFactory.length; i += 2) {
            if (seedsFactory[i] < start) {
                start = seedsFactory[i];
            }
            if (seedsFactory[i] + seedsFactory[i + 1] > end) {
                end = seedsFactory[i] + seedsFactory[i + 1];
            }
        }

        int i = 3;
        List<Long[]> toSoil = new ArrayList<>();
        i = readMap(lines, i, toSoil);

        List<Long[]> toFertilizer = new ArrayList<>();
        i = readMap(lines, i, toFertilizer);

        List<Long[]> toWater = new ArrayList<>();
        i = readMap(lines, i, toWater);

        List<Long[]> toLight = new ArrayList<>();
        i = readMap(lines, i, toLight);

        List<Long[]> toTemp = new ArrayList<>();
        i = readMap(lines, i, toTemp);

        List<Long[]> toHumidity = new ArrayList<>();
        i = readMap(lines, i, toHumidity);

        List<Long[]> toLocation = new ArrayList<>();
        i = readMap(lines, i, toLocation);

        long numSeeds = end - start;
        long n = numSeeds / 32;
        long min = 0;
        for (long segment = 0; segment < numSeeds; segment += n) {
            int size =
                (int) ((numSeeds - segment > n) ? n : numSeeds - segment);
            long[] seeds = new long[size];
            for (int j = 0; j < size; j++) {
                seeds[j] = start + segment + j;
            }

            applyMap(seeds, toSoil);
            applyMap(seeds, toFertilizer);
            applyMap(seeds, toWater);
            applyMap(seeds, toLight);
            applyMap(seeds, toTemp);
            applyMap(seeds, toHumidity);
            applyMap(seeds, toLocation);

            long currMin = minOf(seeds);
            if (min == 0 || min > currMin) {
                min = currMin;
            }
        }

        return min;
    }

    public static void main(String[] args) {
        if (args.length < 1) {
            System.exit(1);
        }

        Path path = Paths.get(args[0]);
        try {
            List<String> lines = Files.readAllLines(path);

            long min = readAlmanac(lines);
            System.out.println("min: " + min);

            long minRange = readAlmanacRange(lines);
            System.out.println("minRange: " + minRange);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
