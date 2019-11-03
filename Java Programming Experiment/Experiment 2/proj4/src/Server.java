import java.io.*;
import java.net.*;
import java.util.ArrayList;
import java.util.Arrays;

public class Server implements Constants {
    static GameData data=new GameData();
    public static void main(String[] argv){
        // 接受TCP
        new Thread(()->{
            while (true)
            try {
                ServerSocket serverSocket = new ServerSocket(TCP_PORT);
                Socket socket = serverSocket.accept();
                InetAddress inetAddress = socket.getInetAddress();
                System.out.println("\nA new game created. IP: " + inetAddress.getHostAddress());
                ObjectInputStream inputFromClient = new ObjectInputStream(socket.getInputStream());
               // ObjectOutputStream outputToClient = new ObjectOutputStream(socket.getOutputStream());
                for (int i = 0; i < N ; i++) {
                    String gotStr=inputFromClient.readObject().toString();
                    //System.out.println("tcp"+gotStr);
                    data.updateA(gotStr);
                }
            } catch (IOException | ClassNotFoundException ignored) {
            }
        }).start();
        // 接受UDP
        new Thread(()->{
            byte[] buf = new byte[64];
            while (true)
                try {
                    DatagramSocket socket = new DatagramSocket(UDP_PORT);
                    DatagramPacket receivePacket = new DatagramPacket(buf, buf.length);
                    for (int i = 0; i < N ; i++) {
                        Arrays.fill(buf, (byte) 0); // Initialize buffer for each iteration
                        socket.receive(receivePacket); // Receive from the client in a packet
                        //System.out.println("udp"+new String(buf).trim());
                        data.updateB(new String(buf).trim());
                    }
                } catch (IOException ignored) {
                }
        }).start();
    }
}

class GameData implements Constants{
    private ArrayList<String> dataA=new ArrayList<>();
    private ArrayList<String> dataB=new ArrayList<>();
    int round=0,aScore=0,bScore=0;
    void updateA(String str){
        dataA.add(str);
        if(dataA.size()>round&&dataB.size()>round) print(round++);
    }
    void updateB(String str){
        dataB.add(str);
        if(dataA.size()>round&&dataB.size()>round) print(round++);
    }
    void print(int round){
        if(round==0){
            System.out.println("\t\t\t\tThread A\t\t\t\tThread B");
            System.out.println("Round\tSleep\tRandom\tPoints\tSleep\tRandom\tPoints\t");
            System.out.println("\t\ttime\tselect\tobtain\ttime\tselect\tobtain\t");
        }
        String[] a=dataA.get(round).split("-");
        String[] b=dataB.get(round).split("-");

        if (a[1].equals(b[1])) {
            System.out.println((round+1)+"\t\t"+a[0]+"\t\t"+a[1]+"\t"+1+"\t\t"+b[0]+"\t\t"+b[1]+"\t"+1);
            aScore++;
            bScore++;
        } else if ((a[1].equals("Rock")&&b[1].equals("Paper"))||(a[1].equals("Paper")&&b[1].equals("Scissor"))
                ||(a[1].equals("Scissor")&&b[1].equals("Rock"))) {
            System.out.println((round+1)+"\t\t"+a[0]+"\t\t"+a[1]+"\t"+0+"\t\t"+b[0]+"\t\t"+b[1]+"\t"+2);
            bScore += 2;
        } else {
            System.out.println((round+1)+"\t\t"+a[0]+"\t\t"+a[1]+"\t"+2+"\t\t"+b[0]+"\t\t"+b[1]+"\t"+0);
            aScore += 2;
        }
        if(round==N-1){
            if(aScore>bScore)System.out.println("A is the winner");
            else if(aScore<bScore)System.out.println("B is the winner");
            else System.out.println("None is the winner");
            // reset and ready for a new game
            this.round=aScore=bScore=0;
            dataA.clear();
            dataB.clear();
        }
    }
}
