package com.fishlulu.javafxlearn.school.finale.test03;

import java.util.UUID;

public class ArrivalTruck extends Thread {
    private Warehouse warehouse;
    private Runnable onUpdateDashboard;

    public ArrivalTruck(Warehouse warehouse) {
        this.warehouse = warehouse;
        super.setName("ArrivalTruck");
    }

    // 设置更新仓库情况的回调方法
    public void setOnUpdateDashboard(Runnable onUpdateDashboard) {
        this.onUpdateDashboard = onUpdateDashboard;
    }

    @Override
    public void run() {
        Thread.currentThread().setName("ArrivalTruckDashBoard");
        while (true) {
            String packageId = UUID.randomUUID().toString();
            warehouse.storePackage(packageId);

            // 通知 UI 更新
            if (onUpdateDashboard != null) {
                onUpdateDashboard.run();
            }

            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
    }
}
