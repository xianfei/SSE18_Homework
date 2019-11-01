import java.util.Random;

public class RandCharThread extends Thread{
    private int sleepTime=0;
    public RandCharThread(ThreadData threadData) {
        threadData.c=(char)(new Random().nextInt(26)+'a');
        threadData.sleepTime = new Random().nextInt(1000);
        this.sleepTime = threadData.sleepTime;
    }
    @Override
    public void run() {
        try {
            sleep(sleepTime);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
