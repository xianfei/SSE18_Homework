import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.scene.layout.Pane;
import javafx.scene.shape.Polygon;
import javafx.scene.shape.Rectangle;
import javafx.scene.shape.Circle;
import javafx.scene.paint.Color;
import javafx.util.Duration;

public class Car extends Pane {
    private double x = 0;
    private double y = 40;
    private Timeline animation;

    Car() {
        drawCar();
        animation = new Timeline(new KeyFrame(Duration.millis(100), e -> moveCar())); // 每50ms移动车辆
        animation.setCycleCount(Timeline.INDEFINITE); // 动画无限循环
    }

    // 绘制车辆
    private void drawCar() {
        getChildren().clear();
        Rectangle rectangle = new Rectangle(x, y - 20, 50, 10);
        rectangle.setFill(Color.SPRINGGREEN);
        Polygon polygon = new Polygon(x + 10, y - 20, x + 20, y - 30, x + 30,
                y - 30, x + 40, y - 20);
        polygon.setFill(Color.RED);
        Circle circle1 = new Circle(x + 15, y - 5, 5);
        Circle circle2 = new Circle(x + 35, y - 5, 5);
        this.getChildren().addAll(rectangle, circle1, circle2, polygon);
    }

    void pause() {
        animation.pause();
    }

    void play() {
        animation.play();
    }

    void setSpeed(double speed) {
        animation.setRate(speed);
    }

    private void moveCar() {
        if (x <= getWidth()) {
            x += 1;
    }
        else
            x = 0;
        drawCar();
    }
}