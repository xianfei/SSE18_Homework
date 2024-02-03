package com.fishlulu.javafxlearn.school.prac02;

import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.stage.Stage;
import javafx.scene.control.Button;
import javafx.scene.layout.Pane;

import java.io.IOException;
import javafx.util.Duration;

public class FlagShrink extends Application {
    private double xOffset = 0;
    private double yOffset = 0;
    private boolean isDragging = false;
    private double originalImageWidth;
    private double originalImageHeight;

    @Override
    public void start(Stage stage) throws IOException {
        // 创建一个布局
        BorderPane root = new BorderPane();

        // 创建一个 ImageView 来显示图像
        Image img = new Image("file:D:\\Pictures\\图标\\china.jfif");
        ImageView imgView = new ImageView(img);
        originalImageWidth = img.getWidth();
        originalImageHeight = img.getHeight();

        // 创建一个 Pane 并将 ImageView 放入其中
        Pane imagePane = new Pane(imgView);
        root.setCenter(imagePane);

        //timeline来闪烁图片
        Duration flashInterval = Duration.seconds(1.0);
        Timeline flashTimeline = new Timeline(
            new KeyFrame(flashInterval, event -> {
                if (imgView.getOpacity() == 1.0) {
                    imgView.setOpacity(0.0);
                } else {
                    imgView.setOpacity(1.0);
                }
            })
        );
        flashTimeline.setCycleCount(Timeline.INDEFINITE);

        flashTimeline.play();
        // 创建放大和缩小按钮
        Button btnEnlarge = new Button("Enlarge");
        Button btnShrink = new Button("Shrink");
        btnEnlarge.setStyle("-fx-font-size: 14px"); // 设置按钮字体大小
        btnShrink.setStyle("-fx-font-size: 14px");  // 设置按钮字体大小
        btnEnlarge.setMinWidth(100); // 设置按钮的最小宽度
        btnShrink.setMinWidth(100);  // 设置按钮的最小宽度
        // 设置按钮的布局位置到左上角
        btnEnlarge.setLayoutX(0);
        btnEnlarge.setLayoutY(0);
        btnShrink.setLayoutX(100);
        btnShrink.setLayoutY(0);

        // 使用匿名内部类处理按钮点击事件
        btnEnlarge.setOnAction(event -> {
            imgView.setScaleX(imgView.getScaleX() * 1.2);
            imgView.setScaleY(imgView.getScaleY() * 1.2);
        });

        btnShrink.setOnAction(event -> {
            imgView.setScaleX(imgView.getScaleX() / 1.2);
            imgView.setScaleY(imgView.getScaleY() / 1.2);
        });

        // 将按钮放入 HBox 中
        HBox buttonBox = new HBox(10);
        buttonBox.getChildren().addAll(btnEnlarge, btnShrink);
        buttonBox.setTranslateX(10);
        buttonBox.setTranslateY(10);

        // 将按钮添加到根布局的底部
        root.setBottom(buttonBox);

        // 添加鼠标拖动功能
        imgView.setOnMousePressed(event -> {
            xOffset = event.getSceneX() - imgView.getTranslateX();
            yOffset = event.getSceneY() - imgView.getTranslateY();
            isDragging = true;
        });

        imgView.setOnMouseDragged(event -> {
            if (isDragging) {
                imgView.setTranslateX(event.getSceneX() - xOffset);
                imgView.setTranslateY(event.getSceneY() - yOffset);
            }
        });

        imgView.setOnMouseReleased(event -> {
            isDragging = false;
        });

        // 创建场景
        Scene scene = new Scene(root, 640, 480);
        // 设置初始缩放比例，以便图像不覆盖整个窗口
        double initialScale = 0.5;
        imgView.setScaleX(initialScale);
        imgView.setScaleY(initialScale);

        // 添加大小变化监听器，使图像适应窗口大小并保持长宽比例
        stage.widthProperty().addListener((obs, oldVal, newVal) -> {
            double scale = newVal.doubleValue() / originalImageWidth;
            imgView.setFitWidth(newVal.doubleValue());
            imgView.setFitHeight(originalImageHeight * scale);
        });

        stage.heightProperty().addListener((obs, oldVal, newVal) -> {
            double scale = newVal.doubleValue() / originalImageHeight;
            imgView.setFitHeight(newVal.doubleValue());
            imgView.setFitWidth(originalImageWidth * scale);
        });

        // 设置舞台标题并显示
        stage.setTitle("Hello!");
        stage.setScene(scene);
        stage.show();
    }

//    public static void main(String[] args) {
//        launch();
//    }
}
