public class Main {
    public static void main(String[] args) {
        Triangle triangle = new Triangle(1,1.5,1,"yellow",true);
        System.out.println("Area:"+triangle.getArea());
        System.out.println("Perimeter:"+triangle.getPerimeter());
        System.out.println("Color:"+triangle.getColor());
        System.out.println("isFiled:"+triangle.isFilled());
    }
}
