import java.util.Random;

public class Main {
    public static void main(String[] args) {
	// write your code here
        Random random = new Random();
        for (int i = 0; i < 100; i++) {
            System.out.print((char)(random.nextInt(26)+'a'));
        }

    }
}
