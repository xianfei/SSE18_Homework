public class Main {
    public static void main(String[] args) throws CloneNotSupportedException {
        // Write a test program that creates an array of five GeometricObject.
        // For each object in the array, invoke its howToColor method if it is colorable.
        GeometricObject[] gArrray={new GeometricObject(),new Square(true,"blue"),
                new GeometricObject(),new Square(false,"yellow"),new Square()};
        for (int i = 0; i <5 ; i++) if(gArrray[i] instanceof Colorable)((Square)gArrray[i]).howToColor();

        // Write a test program that creates an Octagon object with side value 5
        // and displays its area and perimeter. Create a new object
        // using the clone method and compare the two objects using the compareTo method.
        Octagon oct=new Octagon(5);
        System.out.printf("Area:%.2f Perimeter:%.2f\n",oct.getArea(),oct.getPerimeter());
        Octagon oct_=new Octagon();
        oct_= (Octagon) oct.clone();
        System.out.println("using compareTo:"+oct.compareTo(oct_));
    }
}
