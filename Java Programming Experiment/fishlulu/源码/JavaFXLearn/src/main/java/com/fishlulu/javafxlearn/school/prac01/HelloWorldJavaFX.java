package com.fishlulu.javafxlearn.school.prac01;

import javafx.application.Application;
import javafx.beans.binding.Bindings;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.StackPane;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.stage.Stage;

public class HelloWorldJavaFX extends Application {

    @Override
    public void start(Stage primaryStage) {
        Button button = new Button("Hello, JavaFX!");
        StackPane root = new StackPane(button);
        Scene scene = new Scene(root, 300, 200);
        primaryStage.setTitle("Hello JavaFX");
        primaryStage.setScene(scene);
        primaryStage.show();

        button.layoutXProperty().bind(Bindings.createDoubleBinding(
            () -> (scene.getWidth() - button.getWidth()) / 2,
            scene.widthProperty(), button.widthProperty()
        ));
        button.layoutYProperty().bind(Bindings.createDoubleBinding(
            () -> (scene.getHeight() - button.getHeight()) / 2,
            scene.heightProperty(), button.heightProperty()
        ));
        button.setTextFill(Color.BLUE);
        button.setFont(Font.font("Arial", 18));
    }

    public static void main(String[] args) {
        launch(args);
    }
}
