import java.util.Arrays;

public class Main {
    private static final double e = 0.00001;

    static double[][] A =
            {{611, 196, -192, 407, -8, -52, -49, 29},
                    {196, 899, 113, -192, -71, -43, -8, -44},
                    {-192, 113, 899, 196, 61, 49, 8, 52},
                    {407, -192, 196, 611, 8, 44, 59, -23},
                    {-8, -71, 61, 8, 411, -599, 208, 208},
                    {-52, -43, 49, 44, -599, 411, 208, 208},
                    {-49, -8, 8, 59, 208, 208, 99, -911},
                    {29, -44, 52, -23, 208, 208, -911, 99}};

    static double[][] B = new double[10][10];
    static double[][] C = new double[12][12];
    static double[][] D = new double[20][20];
    static double[][] E = new double[50][50];

    public static void main(String[] args) {
        // 初始化矩阵B
        for (int i = 0; i < 10; i++) {
            for (int j = i; j < 10; j++) {
                B[i][j] = B[j][i] = 1.0 / (i + j + 1);
            }
        }
        // 初始化矩阵C
        for (int i = 0; i < 12; i++) {
            for (int j = 0; j < 12; j++) {
                C[i][j] = Math.min((12 - i), (12 - j));
            }
        }
        // 初始化矩阵D
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                D[i][j] = Math.sqrt(2.0 / 21.0) * Math.sin((i * j * 3.14) / 21.0);
            }
        }
        // 初始化矩阵
        for (int i = 0; i < 50; i++) {
            E[i][i] = E[i][49] = 1;
            for (int j = i + 1; j < 49; j++) {
                E[i][j] = 0;
                E[j][i] = -1;
            }
        }
        double[][][] matrices={A,B,C,D,E};

        // power_eng求解
        System.out.println("幂法:");
        System.out.println("矩阵\t最大特征值\t特征向量\t运行时间\t");
        for (int i = 0; i < 5; i++) {
            long startTime=System.nanoTime();
            power_eng powerEng = new power_eng(matrices[i]);
            long endTime=System.nanoTime();
            System.out.print((char)('A'+i));
            System.out.print("\t"+powerEng.eigenvalue);
            System.out.print("\t"+Arrays.toString(powerEng.eigenvector.toArray()));
            System.out.println("\t" + (endTime-startTime)/1000000.0 + "ms");
        }

        // jacobi_eng求解
        System.out.println("\n\nJacobi方法:");
        System.out.println("矩阵\t最大特征值\t运行时间\t");
        for (int i = 0; i < 4; i++) {
            long startTime=System.nanoTime();
            jacobi_eng algorithm = new jacobi_eng(e, matrices[i]);
            long endTime=System.nanoTime();
            System.out.print((char)('A'+i));
            System.out.print("\t"+algorithm.getMaxEigenvalue());
            System.out.println("\t" + (endTime-startTime)/1000000.0 + "ms");
        }
    }
}
