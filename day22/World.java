import java.util.HashSet;
import java.util.Set;
import java.util.TreeSet;

public class World {

    private TreeSet<Brick> bricks;
    private int startX = 0;
    private int startY = 0;
    private int endX = 0;
    private int endY = 0;

    public World() {
        bricks = new TreeSet<>();
    }

    private int findZ(int[][] zMap, Brick brick) {
        int z = 0;
        int sx = brick.getStart().getX() - startX;
        int sy = brick.getStart().getY() - startY;
        int ex = brick.getEnd().getX() - startX;
        int ey = brick.getEnd().getY() - startY;

        for (int i = sx; i <= ex; i++) {
            for (int j = sy; j <= ey; j++) {
                if (z < zMap[i][j])
                    z = zMap[i][j];
            }
        }

        return z;
    }

    private void makeBrickFallTo(
            int z,
            Brick brick,
            int[][] zMap,
            Brick[][] bMap
    ) {
        int sx = brick.getStart().getX() - startX;
        int sy = brick.getStart().getY() - startY;
        int ex = brick.getEnd().getX() - startX;
        int ey = brick.getEnd().getY() - startY;

        for (int i = sx; i <= ex; i++) {
            for (int j = sy; j <= ey; j++) {
                if (z == zMap[i][j])
                    brick.setSupportedBy(bMap[i][j]);
                brick.setZ(z + 1);
                zMap[i][j] = z + brick.getHeight();
                bMap[i][j] = brick;
            }
        }
    }

    public boolean add(Brick brick) {
        if (startX > brick.getStart().getX())
            startX = brick.getStart().getX();
        if (startY > brick.getStart().getY())
            startY = brick.getStart().getY();
        if (endX < brick.getEnd().getX())
            endX = brick.getEnd().getX();
        if (endY < brick.getEnd().getY())
            endY = brick.getEnd().getY();

        return bricks.add(brick);
    }

    public void fall() {
        int width = endX - startX + 1;
        int height = endY - startY + 1;
        int[][] zMap = new int[width][height];
        Brick[][] bMap = new Brick[width][height];

        for (Brick brick : bricks) {
            int z = findZ(zMap, brick);
            makeBrickFallTo(z, brick, zMap, bMap);
        }
    }

    public Set<Brick> findDesintegrableBrick() {
        HashSet<Brick> desintegrable = new HashSet<>(bricks);
        for (Brick brick : bricks) {
            Set<Brick> supportedBy = brick.getSupportedBy();
            if (supportedBy.size() == 1) {
                for (Brick supporter : supportedBy)
                    desintegrable.remove(supporter);
            }
        }

        return desintegrable;
    }

    private long desintegrate(Brick brick, Set<Brick> falling) {
        long res = 0;
        for (Brick supported : brick.getSupported()) {
            boolean willFall = true;
            for (Brick supporter : supported.getSupportedBy()) {
                if (!falling.contains(supporter)) {
                    willFall = false;
                    break;
                }
            }

            if (willFall) {
                falling.add(supported);
                res += 1 + desintegrate(supported, falling);
            }
        }

        return res;
    }

    public long desintegrateAll() {
        long res = 0;
        for (Brick brick : bricks) {
            HashSet<Brick> falling = new HashSet<>();
            falling.add(brick);

            res += desintegrate(brick, falling);
        }

        return res;
    }

    public void show() {
        System.out.println("stX:" + startX);
        System.out.println("stY:" + startY);
        System.out.println("enX:" + endX);
        System.out.println("enY:" + endY);
        for (Brick brick : bricks)
            brick.show();
    }
}
