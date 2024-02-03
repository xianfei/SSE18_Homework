//package com.fishlulu.javafxlearn.school.expr02;
//import javafx.application.Application;
//import javafx.scene.Scene;
//import javafx.scene.canvas.Canvas;
//import javafx.scene.canvas.GraphicsContext;
//import javafx.scene.control.Button;
//import javafx.scene.control.TextField;
//import javafx.scene.image.Image;
//import javafx.scene.layout.VBox;
//import javafx.stage.Stage;
//
//public class CarInterface extends Application {
//
//
//    @Override
//    public void start(Stage primaryStage) {
//        // Constants
//        final int MIN_SPEED = 1;
//        final int MAX_SPEED = 100;
//
//
//
//        // Create JavaFX elements
//        Canvas canvas = new Canvas(400, 200);
//        GraphicsContext gc = canvas.getGraphicsContext2D();
//
//        // Create a Car instance
//        // Load car image
//        Image carImage = new Image("file:D:\\Pictures\\图标\\car.png");
//        Car car = new Car(carImage, gc, (int)canvas.getWidth() - (int) carImage.getWidth(), (int)canvas.getHeight() - (int) carImage.getHeight());
//        TextField speedInput = new TextField();
//        Button startButton = new Button("Start");
//        Button stopButton = new Button("Stop");
//
//        // Event handlers
//        startButton.setOnAction(e -> {
//            int speed = Integer.parseInt(speedInput.getText());
//            //如果没有获取到输入speed,或者speed不在范围内,则设置为默认值
//            if (speed < MIN_SPEED || speed > MAX_SPEED) {
//                speed = MIN_SPEED;
//                //更改输出框内容为当前速度
//                speedInput.setText(String.valueOf(speed));
//            }
//            car.setSpeed(speed);
//            car.start();
//        });
//
//        stopButton.setOnAction(e -> car.stop());
//
//        // Create layout
//        VBox layout = new VBox();
//        layout.getChildren().addAll(canvas, speedInput, startButton, stopButton);
//
//        // Create a scene
//        Scene scene = new Scene(layout);
//        primaryStage.setScene(scene);
//        // Draw the car
//        car.draw();
//        primaryStage.setTitle("Car Simulation");
//        primaryStage.show();
//    }
//    public static void main(String[] args) {
//        launch();
//    }
//
//}
//
package com.fishlulu.javafxlearn.school.expr02;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

public class CarInterface extends Application {

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {
        final int MIN_SPEED = 1;
        final int MAX_SPEED = 100;

        Canvas canvas = new Canvas(400, 200);
        GraphicsContext gc = canvas.getGraphicsContext2D();
        //传入图片,并缩小到25%大小
        Image carImage = new Image("file:D:\\Pictures\\图标\\car.png", canvas.getWidth() / 4, canvas.getHeight() / 4, true, true);

        Car car = new Car(carImage, gc, canvas.getWidth() - carImage.getWidth(), canvas.getHeight() - carImage.getHeight());
        TextField speedInput = new TextField();
        Button startButton = new Button("Start");
        Button stopButton = new Button("Stop");

        startButton.setOnAction(e -> {
            int speed;
            try {
                speed = Integer.parseInt(speedInput.getText());
                if (speed < MIN_SPEED || speed > MAX_SPEED) {
                    speed = MIN_SPEED;
                    speedInput.setText(String.valueOf(speed));
                }
            } catch (NumberFormatException ex) {
                speed = MIN_SPEED;
                speedInput.setText(String.valueOf(speed));
            }
            car.setSpeed(speed);
            car.start();
        });

        stopButton.setOnAction(e -> car.stop());

        VBox layout = new VBox();
        layout.getChildren().addAll(canvas, speedInput, startButton, stopButton);
        Scene scene = new Scene(layout);
        primaryStage.setScene(scene);
        car.draw();
        primaryStage.setTitle("Car Simulation");
        primaryStage.show();
    }
}
