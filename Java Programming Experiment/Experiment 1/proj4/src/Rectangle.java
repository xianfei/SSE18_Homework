public class Rectangle {
    private double width;
    private double height;
    private static String color;

    public Rectangle() {
        this(150, 100);
    }

    public Rectangle(double width, double height) {
        this.width = width;
        this.height = height;
    }

    public double getWidth() {
        return width;
    }

    public void setWidth(double width) {
        this.width = width;
    }

    public double getHeight() {
        return height;
    }

    public void setHeight(double height) {
        this.height = height;
    }

    public static String getColor() {
        return color;
    }

    public static void setColor(String color) {
        Rectangle.color = color;
    }

    public double getArea() {
        return width * height;
    }

    public double getPerimeter(){
        return 2 * (width + height);
    }

    @Override
    public String toString() {
        return "Rectangle{" +
                "width=" + width +
                ", height=" + height +
                ", color=" + color +
                '}';
    }
}
