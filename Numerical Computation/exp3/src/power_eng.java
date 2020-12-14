import java.util.ArrayList;
import java.util.Arrays;
import java.util.Map;

public class power_eng {
    // eigenvalue
    private double[][] a = {{611, 196, -192, 407, -8, -52, -49, 29},
            {196, 899, 113, -192, -71, -43, -8, -44},
            {-192, 113, 899, 196, 61, 49, 8, 52},
            {407, -192, 196, 611, 8, 44, 59, -23},
            {-8, -71, 61, 8, 411, -599, 208, 208},
            {-52, -43, 49, 44, -599, 411, 208, 208},
            {-49, -8, 8, 59, 208, 208, 99, -911},
            {29, -44, 52, -23, 208, 208, -911, 99}};
    double[] p = {1, 1, 1, 1, 1, 1, 1, 1};            // initial eigenvector

    ArrayList<Double> eigenvector = new ArrayList<>();
    Double eigenvalue = 0.0;

    public power_eng(double[][] a) {
        this.a = a;
        p = new double[a[0].length];
        Arrays.fill(p, 1);
        calc();
    }

    public void calc() {
        double lambda = 0;
        double[] q;
        double last_lambda = -100;
        while (true) {
            eigenvector.clear();
            for (int i = 0; i < p.length; i++) eigenvector.add(p[i]);  // show the current vector
            eigenvalue = lambda;                             // and the eigenvalue (lambda)
            if (Math.abs(last_lambda - lambda) < 0.000001) break;
            last_lambda = lambda;
            q = p;
            p = AxP(a, q);
            lambda = norm(p);
            p = PxL(p, 1 / lambda);

        }
    }

    // Computes P = A x P (A - matrix, P - column vector)
    private static double[] AxP(double[][] a, double[] p) {
        double[] q = new double[p.length];
        double s;
        for (int i = 0; i < p.length; i++) {
            q[i] = 0;
            for (int j = 0; j < p.length; j++)
                q[i] = q[i] + a[i][j] * p[j];
        }
        return q;
    }

    // Computes P = P x L (P - vector, L - scalar)
    private static double[] PxL(double[] p, double lambda) {
        double[] q = new double[p.length];
        for (int i = 0; i < p.length; i++)
            q[i] = p[i] * lambda;
        return q;
    }

    // Computes P-Q (P and Q - vectors)
    private static double[] PminusQ(double[] p, double[] q) {
        double[] r = new double[p.length];
        for (int i = 0; i < p.length; i++)
            r[i] = p[i] - q[i];
        return r;
    }

    // Computes Euclidean norm of P
    private static double norm(double[] p) {
        double s = 0;
        for (int i = 0; i < p.length; i++)
            s = s + p[i] * p[i];
        return Math.sqrt(s);
    }
}
