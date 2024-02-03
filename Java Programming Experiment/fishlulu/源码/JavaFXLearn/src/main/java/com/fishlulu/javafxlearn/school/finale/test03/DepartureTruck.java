package com.fishlulu.javafxlearn.school.finale.test03;

public class DepartureTruck extends Thread {
    private Warehouse warehouse;
    private Runnable onUpdateDashboard;

    public DepartureTruck(Warehouse warehouse) {
        this.warehouse = warehouse;
        super.setName("DepartureTruck");
    }

    // 设置更新仓库情况的回调方法
    public void setOnUpdateDashboard(Runnable onUpdateDashboard) {
        this.onUpdateDashboard = onUpdateDashboard;
    }

    @Override
    public void run() {
        Thread.currentThread().setName("DepartureTruckDashBoard");
        while (true) {
            warehouse.retrievePackage();
            // 通知 UI 更新
            if (onUpdateDashboard != null) {
                onUpdateDashboard.run();
            }
            try {
                Thread.sleep(1500);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
    }
}
