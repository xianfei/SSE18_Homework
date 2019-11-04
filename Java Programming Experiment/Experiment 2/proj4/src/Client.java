import java.io.*;
import java.net.*;
import java.util.Arrays;
import java.util.Random;

public class Client {
    public static void main(String argv[]) {
        // TCP
        new ThreadA("localhost").start();
        // UDP
        new ThreadB("localhost").start();
    }
}

class ThreadA extends Thread implements Constants{
    private ObjectOutputStream toServer = null;
    private String host;

    public ThreadA(String host) {
        this.host = host;
    }

    @Override
    public void run() {
        try {
            Socket socket = new Socket(host, TCP_PORT);
            //fromServer = new ObjectInputStream(socket.getInputStream());
            toServer = new ObjectOutputStream(socket.getOutputStream());
            for (int i = 0; i< N; i++) {
                int sleepTime = new Random().nextInt(1000);
                int randHand = new Random().nextInt(3);
                sleep(sleepTime);
                switch (randHand) {
                    case 0:
                        toServer.writeObject(sleepTime + "-" + "Rock");
                        break;
                    case 1:
                        toServer.writeObject(sleepTime + "-" + "Paper");
                        break;
                    case 2:
                        toServer.writeObject(sleepTime + "-" +  "Scissor");
                        break;
                }
                // System.out.println(sleepTime);
            }
            socket.close();
        } catch (IOException|InterruptedException e) {
            e.printStackTrace();
        }
    }
}

class ThreadB extends Thread implements Constants{
    private DatagramSocket socket;
    private byte[] buf = new byte[256]; // The byte array for sending and receiving datagram packets
    private InetAddress address; // Server InetAddress
    private DatagramPacket sendPacket; // The packet sent to the server
    private String host;

    public ThreadB(String host) {
        this.host = host;
    }
    @Override
    public void run() {
        try {
            Arrays.fill(buf, (byte) 0); // Initialize buffer for each iteration
            socket = new DatagramSocket();
            address = InetAddress.getByName(host);
            sendPacket = new DatagramPacket(buf, buf.length, address, UDP_PORT);
            for (int i = 0; i < N; i++) {
                int sleepTime = new Random().nextInt(1000);
                int randHand = new Random().nextInt(3);
                sleep(sleepTime);
                switch (randHand) {
                    case 0:
                        sendPacket.setData((sleepTime + "-" + "Rock").getBytes());
                        break;
                    case 1:
                        sendPacket.setData((sleepTime + "-" + "Paper").getBytes());
                        break;
                    case 2:
                        sendPacket.setData((sleepTime + "-" + "Scissor").getBytes());
                        break;
                }
                socket.send(sendPacket);
                // System.out.println(sleepTime);
            }
            socket.close();
        } catch (IOException | InterruptedException ex) {
            ex.printStackTrace();
        }
    }
}