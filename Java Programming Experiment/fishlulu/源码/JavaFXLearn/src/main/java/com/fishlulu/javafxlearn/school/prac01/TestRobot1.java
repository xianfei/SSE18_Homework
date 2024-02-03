package com.fishlulu.javafxlearn.school.prac01;

import java.util.ArrayList;
import org.junit.Test;


/*
 * Write a class Robot, which has a name and may move(steps) , turnLeft(), 
 * turnRight() and getPosition(). getPosition() returns an object which holds 
 * the coordinates. It also needs a directional status (which are south, 
 * north, east or west). Write a sub class SmartRobot, which has a 
 * two-dimensional array to record each step.
 */
public class TestRobot1 {

    public static void main(String[] args) {
        Robot robot = new Robot("eva-00");
        SmartRobot smartRobot = new SmartRobot("eva-01");
        System.out.println(robot);
        smartRobot.move(12);
        smartRobot.turnLeft();
        smartRobot.move(11);
        smartRobot.turnRight();
        smartRobot.move(10);
        System.out.println(smartRobot);

        ArrayList<Robot> robotList =  new ArrayList<Robot>();
        robotList.add(robot);
        robotList.add(smartRobot);
        for (Robot r : robotList) {
            System.out.println(r);
        }


    }


}

class Robot {
    String name;
    Position position = new Position(0, 0);
    public Robot(String name)
    {
        this.name = name;
    }

    // Directional status, using enum type
    public enum Direction {
        NORTH, SOUTH, EAST, WEST
    };
    Direction dir=Direction.EAST;

    public int move(int steps){
        // 我们不考虑撞墙的问题
        switch (dir) {
            case NORTH:
                position.y += steps;
                break;
            case SOUTH:
                position.y -= steps;
                break;
            case EAST:
                position.x += steps;
                break;
            case WEST:
                position.x -= steps;
                break;
            default:
                break;
        }
        return steps;
    }
    public void turnLeft(){
        switch (dir) {
            case NORTH:
                dir = Direction.WEST;
                break;
            case SOUTH:
                dir = Direction.EAST;
                break;
            case EAST:
                dir = Direction.NORTH;
                break;
            case WEST:
                dir = Direction.SOUTH;
                break;
            default:
                break;
        }
    };
    public void turnRight(){
        switch (dir) {
            case NORTH:
                dir = Direction.EAST;
                break;
            case SOUTH:
                dir = Direction.WEST;
                break;
            case EAST:
                dir = Direction.SOUTH;
                break;
            case WEST:
                dir = Direction.NORTH;
                break;
            default:
                break;
        }
    }
    public Position getPosition() {
        return position;
    }

    public Direction getDir() {
        return dir;
    }

    public void setPosition(Position position) {
        this.position = position;
    }

    public String getName() {
        return name;
    }
    //override toString() in Robot to output its coordinates
    @Override
    public String toString() {
        return "Robot [name=" + name + ", position=" + position.x+","+position.y  + ", dir=" + dir + "]";
    }
}

class Position { // 直接使用公有属性，省略 getter/setter
    public Position(int x, int y) {
        this.x = x;
        this.y = y;
    }
    public int x;
    public int y;
}

class SmartRobot extends Robot
    {
        //finish the superclass's ctor(s) and the subclass's ctors. One of the subclass's ctor need to call another ctor to set the initial direction.
        int[][] map = new int[30][30];
        public SmartRobot(String name) {
            super(name);
        }
        @Override
        public int move(int steps) {
            // TODO Auto-generated method stub
            int movedSteps = super.move(steps);
            map[position.x][position.y] = 1;
            return movedSteps;
        }
        @Override
        public String toString() {
//            //output its path
//            String path = "";
//            for (int i = 0; i < map.length; i++) {
//                for (int j = 0; j < map.length; j++) {
//                    if(map[i][j] == 0)
//                    {
//                        path += " ";
//                    }
//                    else{
//                        path += "*";
//                    }
//                }
//                path += "\n";
//            }
            return "SmartRobot [name=" + name + ", position=" + position.x+","+position.y + ", dir=" + dir + "]\n";

        }
    }