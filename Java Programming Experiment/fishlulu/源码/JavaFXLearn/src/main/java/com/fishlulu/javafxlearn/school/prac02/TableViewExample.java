package com.fishlulu.javafxlearn.school.prac02;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;
import javafx.stage.Stage;
import javafx.scene.control.Button;

public class TableViewExample extends Application {

    @Override
    public void start(Stage primaryStage) {
        primaryStage.setTitle("表格示例");

        GridPane gridPane = new GridPane();

        // 第一行：56个民族图标
        //a1-a56.png
        for (int i = 1; i <= 56; i++) {
            Image image = new Image("/icons/a" + i + ".png");
            ImageView imageView = new ImageView(image);
            gridPane.add(imageView, i - 1, 0);
        }

        // 第二行：第一列 - 唐诗《咏鹅》全诗内容
        Text poemText = new Text("鹅鹅鹅...");
        gridPane.add(poemText, 0, 1);

        // 第二行：第二列 - 2行4列的卦象符号
        //b1-b8.png
        GridPane guaGridPane = new GridPane();
        for (int i = 1; i <= 8; i++) {
            Image guaImage = new Image("/icons/b" + i + ".png");
            ImageView guaImageView = new ImageView(guaImage);
            guaGridPane.add(guaImageView, (i - 1) % 4, (i - 1) / 4);
        }
        gridPane.add(guaGridPane, 1, 1);

        // 第二行：第三列 - 阴阳图
        Image yinYangImage = new Image("/icons/c1.png");
        ImageView yinYangImageView = new ImageView(yinYangImage);
        gridPane.add(yinYangImageView, 2, 1);

        // 第三行：左右排放的两个按钮
        Button leftButton = new Button("左按钮");
        Button rightButton = new Button("右按钮");
        HBox buttonBox = new HBox(leftButton, rightButton);
        gridPane.add(buttonBox, 0, 2);

        Scene scene = new Scene(gridPane, 800, 400);
        primaryStage.setScene(scene);
        primaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
