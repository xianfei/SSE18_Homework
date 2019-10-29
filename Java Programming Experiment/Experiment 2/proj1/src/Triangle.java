public class Triangle extends GeometricObject{
    private double side1=0,side2=0,side3=0;
    public Triangle() {
    }
    public Triangle(double side1, double side2, double side3) {
        this.side1 = side1;
        this.side2 = side2;
        this.side3 = side3;
    }
    public Triangle(double side1, double side2, double side3, String color,boolean isFilled) {
        super(isFilled,color);
        this.side1 = side1;
        this.side2 = side2;
        this.side3 = side3;
    }
    // accessor methods
    public double getSide1() {
        return side1;
    }
    public void setSide1(double side1) {
        this.side1 = side1;
    }
    public double getSide2() {
        return side2;
    }
    public void setSide2(double side2) {
        this.side2 = side2;
    }
    public double getSide3() {
        return side3;
    }
    public void setSide3(double side3) {
        this.side3 = side3;
    }
    @Override
    public double getPerimeter() {
        return side1+side2+side3;
    }
    @Override
    public double getArea() {
        return Math.sqrt((getPerimeter()/2)*(getPerimeter()/2-side1)
                *(getPerimeter()/2-side2)*(getPerimeter()/2-side3));
    }
    @Override
    public String toString() {
        return "Triangle: side1 = " + side1 + " side2 = " + side2
                +  " side3 = " + side3 + super.toString();
    }
}
