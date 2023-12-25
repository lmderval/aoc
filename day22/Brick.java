import java.lang.Comparable;
import java.lang.Math;
import java.util.HashSet;
import java.util.Set;

public class Brick implements Comparable<Brick> {

    private Point start;
    private Point end;
    private HashSet<Brick> supportedBy;
    private HashSet<Brick> supported;

    public Brick(Point start, Point end) {
        this.start = new Point(
                Math.min(start.getX(), end.getX()),
                Math.min(start.getY(), end.getY()),
                Math.min(start.getZ(), end.getZ())
        );
        this.end = new Point(
                Math.max(start.getX(), end.getX()),
                Math.max(start.getY(), end.getY()),
                Math.max(start.getZ(), end.getZ())
        );

        supportedBy = new HashSet<>();
        supported = new HashSet<>();
    }

    public static Brick parseBrick(String brick) {
        String[] data = brick.split("~");
        return new Brick(
                Point.parsePoint(data[0]),
                Point.parsePoint(data[1])
        );
    }

    @Override
    public int compareTo(Brick other) {
        return start.compareTo(other.start);
    }

    public void setZ(int z) {
        int dz = z - start.getZ();
        start.setZ(z);
        end.translateZ(dz);
    }

    public int getHeight() {
        return end.getZ() - start.getZ() + 1;
    }

    public Point getStart() {
        return start;
    }

    public Point getEnd() {
        return end;
    }

    public void setSupportedBy(Brick brick) {
        if (brick == null)
            return;

        supportedBy.add(brick);
        brick.supported.add(this);
    }

    public Set<Brick> getSupportedBy() {
        return supportedBy;
    }

    public Set<Brick> getSupported() {
        return supported;
    }

    public void show() {
        System.out.println("[(" + start.getX() + "," + start.getY() + ","
                + start.getZ() + ") - (" + end.getX() + "," + end.getY() + ","
                + end.getZ() + ")]");
    }
}
