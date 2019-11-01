public class CalcAndPrint implements Runnable {
    private ThreadData a, b;

    public CalcAndPrint(ThreadData a, ThreadData b) {
        this.a = a;
        this.b = b;
    }

    @Override
    public void run() {
        if (a.c > b.c) {
            System.out.println(Main.round+"\t\t"+a.sleepTime+"\t\t"
                    +a.c+"\t\t"+2+"\t\t"+b.sleepTime+"\t\t"+b.c+"\t\t"+0);
            Main.aScore += 2;
        } else if (a.c < b.c) {
            System.out.println(Main.round+"\t\t"+a.sleepTime+"\t\t"
                    +a.c+"\t\t"+0+"\t\t"+b.sleepTime+"\t\t"+b.c+"\t\t"+2);
            Main.bScore += 2;
        } else {
            System.out.println(Main.round+"\t\t"+a.sleepTime+"\t\t"
                    +a.c+"\t\t"+1+"\t\t"+b.sleepTime+"\t\t"+b.c+"\t\t"+1);
            Main.aScore++;
            Main.bScore++;
        }
        if(Main.round==Main.N){
            if(Main.aScore>Main.bScore)System.out.print("A is the winner");
            else if(Main.aScore<Main.bScore)System.out.print("B is the winner");
            else System.out.print("None is the winner");
        }
    }
}
