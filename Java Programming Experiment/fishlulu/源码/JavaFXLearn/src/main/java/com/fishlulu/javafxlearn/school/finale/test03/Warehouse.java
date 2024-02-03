package com.fishlulu.javafxlearn.school.finale.test03;

import java.util.LinkedList;
import java.util.Queue;

public class Warehouse {
    private static final int MAX_PACKAGES = 5;
    private Queue<String> storage = new LinkedList<>();
    private static int numPackages;

    public synchronized void storePackage(String packageId) {
        try {
            while (storage.size() == MAX_PACKAGES) {
                System.out.println("仓库已满。等待空间。");
                wait();
            }

            storage.add(packageId);
            numPackages++;
            System.out.println("存储包裹: " + packageId+"仓库剩余空间: " + (MAX_PACKAGES - numPackages));

            notify();
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    public synchronized String retrievePackage() {
        try {
            while (storage.isEmpty()) {
                System.out.println("仓库为空。等待包裹。");
                wait();
            }

            String packageId = storage.poll();
            numPackages--;
            System.out.println("取出包裹: " + packageId+"仓库剩余空间: " + (MAX_PACKAGES - numPackages));

            notify();

            return packageId;
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            return null;
        }
    }

    public static int getMaxCapacity() {
        return MAX_PACKAGES;
    }

    public static int getNumPackages() {
        return numPackages;
    }
}
