package com.fishlulu.javafxlearn.school.expr02;

import javafx.scene.canvas.GraphicsContext;
import javafx.scene.image.Image;

public class Car {
    private static final int MIN_SPEED = 1;
    private static final int MAX_SPEED = 100;
    private static final int SPEED_STEP = 1;

    private GraphicsContext gc;
    private Image carImage;
    private int speed = MIN_SPEED;
    private boolean isMoving = false;
    private double posX = 0;
    private double posY = 0;
    private double maxX = 0;
    private double maxY = 0;
    private Thread moveThread; // 线程对象

    public Car(Image carImage, GraphicsContext gc, double maxX, double maxY) {
        this.gc = gc;
        this.carImage = carImage;
        this.maxX = maxX;
        this.maxY = maxY;
        // 初始化线程
        moveThread = new Thread(this::move);
    }

    public int getSpeed() {
        return speed;
    }

    public boolean isMoving() {
        return isMoving;
    }

    public void setSpeed(int speed) {
        if (speed >= MIN_SPEED && speed <= MAX_SPEED) {
            this.speed = speed;
        }
    }

    public void start() {
        isMoving = true;
        if (moveThread.isAlive()) {
            // 如果线程仍在运行，则不重复启动
            return;
        }
        // 启动线程
        moveThread = new Thread(this::move);
        moveThread.start();
    }

    public void stop() {
        isMoving = false;
        // 中断线程
        if (moveThread.isAlive()) {
            moveThread.interrupt();
        }
    }

    private void move() {
        while (isMoving) {
            try {
                Thread.sleep(1000 / speed);
                // 擦除旧位置
                clearOldPosition();
                // 更新小车位置
                posX += SPEED_STEP;
                if (posX >= maxX) {
                    posX = posX - maxX;
                }
                // 绘制新位置
                draw();
            } catch (InterruptedException e) {
                // 检测线程中断，以便停止移动
                return;
            }
        }
    }

    public void draw() {
        gc.drawImage(carImage, posX, posY);
    }

    private void clearOldPosition() {
        gc.clearRect(posX, posY, carImage.getWidth(), carImage.getHeight());
    }
}
