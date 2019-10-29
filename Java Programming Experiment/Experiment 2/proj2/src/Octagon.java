public class Octagon extends GeometricObject implements Comparable,Cloneable {
    private int side=0;
    public Octagon(int side) {
        this.side = side;
    }
    public Octagon() {
    }
    @Override
    public Object clone() throws CloneNotSupportedException {
        return super.clone();
    }
    @Override
    public int compareTo(Object o) {
        return side-((Octagon)o).getSide();
    }
    public int getSide() {
        return side;
    }
    public void setSide(int side) {
        this.side = side;
    }
    @Override
    public double getPerimeter(){
        return 8*side;
    }
    @Override
    public double getArea() {
        return (2+4/Math.sqrt(2))*side*side;
    }
}
