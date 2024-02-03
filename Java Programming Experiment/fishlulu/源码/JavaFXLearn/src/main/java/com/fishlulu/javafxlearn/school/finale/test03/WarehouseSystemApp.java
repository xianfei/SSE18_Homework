package com.fishlulu.javafxlearn.school.finale.test03;

import com.fishlulu.javafxlearn.school.finale.test03.controller.DashboardController;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
import javafx.scene.control.Label;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

public class WarehouseSystemApp extends Application {

    public static void main(String[] args) {
        launch(args);
    }
    @Override
    public void start(Stage primaryStage) throws Exception {

        Canvas canvas = new Canvas(400, 200);
        // 创建 UI 元素
        Label capacityLabel = new Label("仓库容量: ");
        Label packagesLabel = new Label("包裹数量: ");
        VBox root = new VBox(capacityLabel, packagesLabel);

        // 创建 Warehouse 对象
        Warehouse warehouse = new Warehouse();

        // 创建 DashboardController 对象
        DashboardController controller = new DashboardController();
        controller.setLabels(capacityLabel, packagesLabel);

        // 创建 ArrivalTruck 和 DepartureTruck 对象
        ArrivalTruck arrivalTruck = new ArrivalTruck(warehouse);
        DepartureTruck departureTruck = new DepartureTruck(warehouse);
        // 设置更新 UI 的回调方法
        arrivalTruck.setOnUpdateDashboard(controller.updateDashboard());
        departureTruck.setOnUpdateDashboard(controller.updateDashboard());

        // 启动卡车线程
        arrivalTruck.start();
        departureTruck.start();

        // 创建场景并设置主舞台
        Scene scene = new Scene(root, 300, 200);
        primaryStage.setTitle("仓库系统");
        primaryStage.setScene(scene);
        primaryStage.show();
    }


}
