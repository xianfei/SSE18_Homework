public class Main{

    public static void main(String[] args) {
        Rectangle r1 = new Rectangle(4, 40);
        Rectangle r2 = new Rectangle(3.5, 39.5);
        Rectangle.setColor("Red");
        System.out.println("r1:" + r1 + ",area=" + r1.getArea() + ",perimeter=" + r1.getPerimeter());
        System.out.println("r2:" + r2 + ",area=" + r2.getArea() + ",perimeter=" + r2.getPerimeter());
        Time t1 = new Time();
        Time t2 = new Time(555550000);
        System.out.println("t1:" + t1);
        System.out.println("t2:" + t2);
    }
}
