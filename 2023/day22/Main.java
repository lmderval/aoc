import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.Set;

public class Main {

    private static int readBricks(List<String> lines) {
        World world = new World();

        for (String line : lines) {
            Brick brick = Brick.parseBrick(line);
            world.add(brick);
        }

        world.show();
        System.out.println();

        world.fall();

        world.show();
        System.out.println();

        Set<Brick> desintegrable = world.findDesintegrableBrick();
        System.out.println("Can be desintegrated:");
        for (Brick brick : desintegrable)
            brick.show();

        long fallingBlocks = world.desintegrateAll();
        System.out.println(fallingBlocks + " blocks will fall.");

        return desintegrable.size();
    }

    public static void main(String[] args) {
        if (args.length < 1) {
            System.exit(1);
        }

        Path path = Paths.get(args[0]);
        try {
            List<String> lines = Files.readAllLines(path);

            int res = readBricks(lines);
            System.out.println("res: " + res);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
