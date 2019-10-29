public class GeometricObject {
    private boolean isFilled=false;
    private String color="black";
    public GeometricObject() {
    }
    public GeometricObject(boolean isFilled, String color) {
        this.isFilled = isFilled;
        this.color = color;
    }
    public boolean isFilled() {
        return isFilled;
    }
    public void setFilled(boolean filled) {
        isFilled = filled;
    }
    public String getColor() {
        return color;
    }
    public void setColor(String color) {
        this.color = color;
    }
    public double getPerimeter(){
        return -1;
    }
    public double getArea(){
        return -1;
    }
    @Override
    public String toString() {
        return  " isFilled=" + isFilled + " color=" + color;
    }
}
