public class Square extends GeometricObject implements Colorable {
    // Design a class named Square that extends GeometricObject and implements Colorable.
    // Implement howToColor to display a message on how to color the square.
    public Square(boolean isFilled, String color) {
        super(isFilled, color);
    }
    public Square() {
    }
    @Override
    public void howToColor() {
        if(super.isFilled())System.out.println("Draw a square and colored with "+super.getColor());
        else System.out.println("Draw square without filled");
    }
}
