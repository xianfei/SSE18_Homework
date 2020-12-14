import java.util.Arrays;

public class jacobi_eng {

    private double e;
    private double[][] A;
    private double[][] I;

    public jacobi_eng(double e, double[][] A) {
        this.e = e;
        this.A = A;
        generateI(A);
    }

    public double[][] getEigenvalue() {
        double[][] M = A;
        double[][] eigenVectors = MatrixUtils.deepCopy(I);
        MatrixElement max = getMaxTopRight(M);

        while (max.val > e) {
            double phi = getPhi(M, max.i, max.j);

            double sin = Math.sin(phi);
            double cos = Math.cos(phi);

            double[][] H = generateH(sin, cos, max.i, max.j);

            M = MatrixUtils.multiply(MatrixUtils.multiply(MatrixUtils.transpose(H), M), H);

            max = getMaxTopRight(M);
            eigenVectors = MatrixUtils.multiply(eigenVectors, H);
        }

        return M;
    }

    public double getMaxEigenvalue(){
        double[][] result=getEigenvalue();
        double max = -100;
        for (double[] doubles : result) {
            for (double v : doubles) {
                if(v>max)max=v;
            }
        }
        return max;
    }

    private double[][] generateH(double sin, double cos, int i, int j) {
        double[][] res = MatrixUtils.deepCopy(I);

        res[i][i] = cos;
        res[i][j] = -sin;
        res[j][i] = sin;
        res[j][j] = cos;

        return res;
    }

    private double getPhi(double[][] m, int i, int j) {
        double atanArgs = (double) 2 * m[i][j] / (m[i][i] - m[j][j]);
        return Math.atan(atanArgs) / 2;
    }

    private MatrixElement getMaxTopRight(double[][] m) {
        MatrixElement max = new MatrixElement(m[0][1], 0, 1);

        for (int i = 0; i < m.length; i++) {
            for (int j = i + 1; j < m.length; j++) {
                if (Math.abs(max.val) < Math.abs(m[i][j])) {
                    max = new MatrixElement(Math.abs(m[i][j]), i, j);
                }
            }
        }

        return max;
    }

    private void generateI(double[][] matrix) {
        I = new double[matrix.length][matrix.length];
        for (int i = 0; i < matrix.length; i++) {
            I[i][i] = 1;
        }
    }


}

class MatrixUtils {

    public static void print(double[][] matrix) {
        for (double[] row : matrix) {
            for (double i : row) {
                System.out.printf("%4f ",i);
            }
            System.out.println();
        }

        System.out.println();
    }

    public static double[][] transpose(double[][] m) {
        double[][] temp = new double[m[0].length][m.length];
        for (int i = 0; i < m.length; i++)
            for (int j = 0; j < m[0].length; j++)
                temp[j][i] = m[i][j];
        return temp;
    }

    public static double[][] subtract(double[][] a, double[][] b) {
        int rows = a.length;
        int columns = a[0].length;
        double[][] result = new double[rows][columns];
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                result[i][j] = a[i][j] - b[i][j];
            }
        }
        return result;
    }

    public static double[][] multiply(double[][] A, double[][] B) {
        int aRows = A.length;
        int aColumns = A[0].length;
        int bColumns = B[0].length;

        double[][] C = new double[aRows][bColumns];

        for (int i = 0; i < aRows; i++) {
            for (int j = 0; j < bColumns; j++) {
                for (int k = 0; k < aColumns; k++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }

        return C;
    }


    public static double[][] multiplyToNum(double[][] A, double number) {
        for (int i = 0; i < A.length; i++) {
            for (int j = 0; j < A[0].length; j++) {
                A[i][j] *= number;
            }
        }

        return A;
    }



    public static double[][] deepCopy(double[][] original) {
        final double[][] result = new double[original.length][];

        for (int i = 0; i < original.length; i++) {
            result[i] = Arrays.copyOf(original[i], original[i].length);
        }

        return result;
    }

    public static double[][] getColumn(double[][] matrix, int i) {
        double [][] column = new double[matrix[0].length][1];

        int c = 0;

        while (c < matrix.length) {
            column[c][0] = matrix[c][i];
            c++;
        }

        return column;
    }
}

class MatrixElement {

    double val;
    int i;
    int j;

    public MatrixElement(double val, int i, int j) {
        this.val = val;
        this.i = i;
        this.j = j;
    }

}
