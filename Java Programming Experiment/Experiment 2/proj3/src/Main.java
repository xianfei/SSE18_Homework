public class Main {
    static final int N = 3;
    static int aScore=0,bScore=0,round=1;
    public static void main(String[] args) {
        System.out.println("\t\t\t\tThread A\t\t\t\tThread B");
        System.out.println("Round\tSleep\tRandom\tPoints\tSleep\tRandom\tPoints\t");
        System.out.println("\t\ttime\tchar\tobtain\ttime\tchar\tobtain\t");

        for (int i = 0; i < N; i++) {
            ThreadData dataA = new ThreadData(),dataB = new ThreadData();
            RandCharThread threadA = new RandCharThread(dataA);
            RandCharThread threadB = new RandCharThread(dataB);
            Thread threadC= new Thread(new CalcAndPrint(dataA,dataB));
            try {
                threadA.start();
                threadB.start();
                threadA.join();
                threadB.join();
                threadC.start();
                threadC.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            round++;
        }
    }
}

