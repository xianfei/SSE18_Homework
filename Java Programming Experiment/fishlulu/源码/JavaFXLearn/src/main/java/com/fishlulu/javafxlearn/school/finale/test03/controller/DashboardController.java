package com.fishlulu.javafxlearn.school.finale.test03.controller;

import com.fishlulu.javafxlearn.school.finale.test03.Warehouse;
import javafx.application.Platform;
import javafx.scene.control.Label;

public class DashboardController {
    private Label capacityLabel;
    private Label packagesLabel;

    public void setLabels(Label capacityLabel, Label packagesLabel) {
        this.capacityLabel = capacityLabel;
        this.packagesLabel = packagesLabel;
    }

    public Runnable updateDashboard() {
        return () -> Platform.runLater(()->{
                System.out.println("updateDashboard");
                if (capacityLabel != null && packagesLabel != null) {
                    capacityLabel.setText("仓库容量: " + Warehouse.getMaxCapacity());
                    packagesLabel.setText("包裹数量: " + Warehouse.getNumPackages());
                    System.out.println("更新标签成功");
                }
            }

        );

    }
}
