import java.lang.Comparable;

public class Point implements Comparable<Point> {

    private int x;
    private int y;
    private int z;

    public Point(int x, int y, int z) {
        this.x = x;
        this.y = y;
        this.z = z;
    }

    public static Point parsePoint(String point) {
        String[] data = point.split(",");
        return new Point(
                Integer.parseInt(data[0]),
                Integer.parseInt(data[1]),
                Integer.parseInt(data[2])
        );
    }

    @Override
    public int compareTo(Point other) {
        if (z != other.z)
            return z - other.z;

        if (y != other.y)
            return y - other.y;

        return x - other.x;
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    public void setZ(int z) {
        this.z = z;
    }

    public int translateZ(int dz) {
        z += dz;
        return z;
    }

    public int getZ() {
        return z;
    }

    public void show() {
        System.out.println("(" + x + "," + y + "," + z + ")");
    }
}
