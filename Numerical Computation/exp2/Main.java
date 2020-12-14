import java.util.*;

public class Main
{
    static double c1[]=new double[3]; // 男生  女生  全体
    static double c2[]= new double[3]; // 男生  女生  全体
    public static void main(String[] args)
    {
        // man height
        double[] man_h = { 1.69, 1.65, 1.72, 1.71, 1.75, 1.75, 1.66, 1.7, 1.78, 1.78, 1.75, 1.8, 1.78, 1.65, 1.85, 1.72, 1.78, 1.65, 1.77, 1.81, 1.83, 1.73, 1.73, 1.8, 1.7, 1.67, 1.70, 1.78, 2.0, 1.8, 1.63, 1.83, 1.79, 1.67, 1.70, 1.8, 1.7, 1.75, 1.85, 1.62, 1.85, 1.73, 1.79, 1.73, 1.75, 1.76, 1.73, 1.78, 1.72, 1.82, 1.74, 1.75, 1.76, 1.78, 1.83, 1.70, 1.65, 1.81, 1.75, 1.68, 1.73, 1.83, 1.76, 1.8, 1.75, 1.8, 1.8, 1.78, 1.74, 1.76, 1.7, 1.73, 1.78, 1.70, 1.85, 1.79, 1.75, 1.72, 1.7, 1.71, 1.72, 1.69, 1.69, 1.79, 1.8, 1.63, 1.7, 1.71, 1.88, 1.82, 1.8, 1.73, 1.75, 1.83, 1.7, 1.85, 1.78, 1.79, 1.72, 1.68, 1.75, 1.78 };
        // man weight
        double[] man_w = { 62.5, 61, 77, 60, 65, 65, 56, 60, 48, 58, 73, 103, 65, 59, 67, 62, 67, 54, 100, 79, 74, 65, 56, 70, 50, 60, 70, 93, 87, 65, 62, 75, 75, 70, 55, 88, 75, 69, 86, 61, 74, 55.8, 65, 63, 70, 62, 60, 63, 60, 100, 72, 56, 72.35, 70, 72, 54, 65, 83, 80, 72.3, 69, 106, 85, 65, 86, 72, 95, 36, 98, 57, 60, 75, 70, 57, 85, 65, 67, 80, 73, 67, 76, 52, 63.5, 65, 72, 53, 63, 58, 80, 65, 78, 65, 89, 70, 65, 95, 55, 62, 50, 57, 61, 65};
        double[] woman_h={1.61, 1.63, 1.63, 1.58, 1.67, 1.62, 1.54, 1.54, 1.8, 1.61, 1.66, 1.75, 1.63, 1.63, 1.68, 1.58, 1.68, 1.60, 1.59, 1.54, 1.60, 1.65, 1.68};
        double[] woman_w={52.8, 51.2, 47, 50, 47, 50, 38, 53, 68, 53, 49, 56, 48.5, 46, 57.5, 45, 56, 42, 52, 53, 57, 60, 53};
        double[] all_h = {1.61, 1.63, 1.63, 1.58, 1.67, 1.62, 1.54, 1.54, 1.8, 1.61, 1.66, 1.75, 1.63, 1.63, 1.68, 1.58, 1.68, 1.60, 1.59, 1.54, 1.60, 1.65, 1.68, 1.69, 1.65, 1.72, 1.71, 1.75, 1.75, 1.66, 1.7, 1.78, 1.78, 1.75, 1.8, 1.78, 1.65, 1.85, 1.72, 1.78, 1.65, 1.77, 1.81, 1.83, 1.73, 1.73, 1.8, 1.7, 1.67, 1.70, 1.78, 2.0, 1.8, 1.63, 1.83, 1.79, 1.67, 1.70, 1.8, 1.7, 1.75, 1.85, 1.62, 1.85, 1.73, 1.79, 1.73, 1.75, 1.76, 1.73, 1.78, 1.72, 1.82, 1.74, 1.75, 1.76, 1.78, 1.83, 1.70, 1.65, 1.81, 1.75, 1.68, 1.73, 1.83, 1.76, 1.8, 1.75, 1.8, 1.8, 1.78, 1.74, 1.76, 1.7, 1.73, 1.78, 1.70, 1.85, 1.79, 1.75, 1.72, 1.7, 1.71, 1.72, 1.69, 1.69, 1.79, 1.8, 1.63, 1.7, 1.71, 1.88, 1.82, 1.8, 1.73, 1.75, 1.83, 1.7, 1.85, 1.78, 1.79, 1.72, 1.68, 1.75, 1.78 };
        double[] all_w = {52.8, 51.2, 47, 50, 47, 50, 38, 53, 68, 53, 49, 56, 48.5, 46, 57.5, 45, 56, 42, 52, 53, 57, 60, 53, 62.5, 61, 77, 60, 65, 65, 56, 60, 48, 58, 73, 103, 65, 59, 67, 62, 67, 54, 100, 79, 74, 65, 56, 70, 50, 60, 70, 93, 87, 65, 62, 75, 75, 70, 55, 88, 75, 69, 86, 61, 74, 55.8, 65, 63, 70, 62, 60, 63, 60, 100, 72, 56, 72.35, 70, 72, 54, 65, 83, 80, 72.3, 69, 106, 85, 65, 86, 72, 95, 36, 98, 57, 60, 75, 70, 57, 85, 65, 67, 80, 73, 67, 76, 52, 63.5, 65, 72, 53, 63, 58, 80, 65, 78, 65, 89, 70, 65, 95, 55, 62, 50, 57, 61, 65};
        { // 使用W=cH^2
            System.out.println("使用W=cH^2:");
            Info info = new Info();
            calc(man_h, man_w,0,info,"W=cH^2");
            estimate(man_h, man_w,0,info,"W=cH^2");
            calc(woman_h, woman_w,1,info,"W=cH^2");
            estimate(woman_h, woman_w,1,info,"W=cH^2");
            calc(all_h, all_w,2,info,"W=cH^2");
            estimate(all_h, all_w,2,info,"W=cH^2");
            System.out.println(info);
        }
        System.out.println();
        { // 使用W=cH^3
            System.out.println("使用W=cH^3:");
            Info info = new Info();
            calc(man_h, man_w,0,info,"W=cH^3");
            estimate(man_h, man_w,0,info,"W=cH^3");
            calc(woman_h, woman_w,1,info,"W=cH^3");
            estimate(woman_h, woman_w,1,info,"W=cH^3");
            calc(all_h, all_w,2,info,"W=cH^3");
            estimate(all_h, all_w,2,info,"W=cH^3");
            System.out.println(info);
        }
        System.out.println();
        { // 使用W=c1H^c2
            System.out.println("使用W=c1H^c2：");
            estimateC1HC2(man_h, man_w,"男生",0);
            estimateC1HC2(woman_h,woman_w,"女生",1);
            estimateC1HC2(all_h,all_w,"全体",2);
        }
        System.out.println();
        { // 使用W=cH^c2
            System.out.println("使用W=cH^c2:");
            Info info = new Info();
            calc(man_h, man_w,0,info,"W=cH^c2");
            estimate(man_h, man_w,0,info,"W=cH^c2");
            calc(woman_h, woman_w,1,info,"W=cH^c2");
            estimate(woman_h, woman_w,1,info,"W=cH^c2");
            calc(all_h, all_w,2,info,"W=cH^c2");
            estimate(all_h, all_w,2,info,"W=cH^c2");
            System.out.println(info);
        }
        System.out.println();
        { // 使用W=c1H^c
            System.out.println("使用W=c1H^c:");
            Info info = new Info();
            calc(man_h, man_w,0,info,"W=c1H^c");
            estimate(man_h, man_w,0,info,"W=c1H^c");
            calc(woman_h, woman_w,1,info,"W=c1H^c");
            estimate(woman_h, woman_w,1,info,"W=c1H^c");
            calc(all_h, all_w,2,info,"W=c1H^c");
            estimate(all_h, all_w,2,info,"W=c1H^c");
            System.out.println(info);
        }
    }

    public static void calc(double[] x, double[] y,int p,Info info,String way){
        double c[] = new double[x.length];
        if(way.equals("W=cH^2"))
            for (int i = 0; i < x.length; i++)
                c[i] = y[i] / (x[i]*x[i]);
        if(way.equals("W=cH^3"))
            for (int i = 0; i < x.length; i++)
                c[i] = y[i] / (x[i]*x[i]*x[i]);
        if(way.equals("W=cH^c2"))
            for (int i = 0; i < x.length; i++)
                c[i] = y[i] / (Math.pow(x[i],c2[p]));

        //     W=c1H^c
        // 除以c1     W/c1 = H^c
        // 取ln   ln(W)-ln(c1) = c*ln(H)
        // 除以ln(H)    c=(ln(W)-ln(c1))/ln(H)
        if(way.equals("W=c1H^c"))
            for (int i = 0; i < x.length; i++)
                c[i] = (Math.log(y[i])-Math.log(c1[p])) / (Math.log(x[i]));
        info.info[0][p]=sum(c)/c.length;
        info.info[1][p]=getVariance(c);
        info.info[2][p]=median(c);
    }

    public static void estimate(double[] x, double[] y,int p,Info info,String way)
    {
        double[] x_=new double[x.length];
        if(way.equals("W=cH^2"))
            for (int i = 0; i < x.length; i++)
                x_[i]=x[i]*x[i];
        if(way.equals("W=cH^3"))
            for (int i = 0; i < x.length; i++)
                x_[i]=x[i]*x[i]*x[i];
        if(way.equals("W=cH^c2"))
            for (int i = 0; i < x.length; i++)
                x_[i]=(Math.pow(x[i],c2[p]));
        if(way.equals("W=c1H^c")) {
            //     W=c1H^c
            // 除以c1     W/c1 = H^c
            // 取ln   ln(W)-ln(c1) = c*ln(H)
            double[] y_=new double[x.length];
            for (int i = 0; i < x.length; i++){
                x_[i] = Math.log(x[i]);
                y_[i]=Math.log(y[i])-Math.log(c1[p]);
            }
            info.info[3][p] = getA(x_, y_);
            return;
        }
        info.info[3][p] = getA(x_, y);
    }

    public static void estimateC1HC2(double[] x, double[] y , String desc ,int pos)
    {
        //           W=c1H^c2
        // 除以c1     W/c1 = H^c2
        // 取ln   ln(W)-ln(c1) = c2*ln(H)
        // 移项    ln(W)=c2*ln(H)+ln(c1)
        // 换元
        double[] x_=new double[x.length];
        double[] y_=new double[x.length];
        for (int i = 0; i < x.length; i++){
            x_[i]=Math.log(x[i]);
            y_[i]=Math.log(y[i]);
        }
        c2[pos] = getA(x_, y_);
        c1[pos] = Math.exp(getB(x_,y_));
        System.out.println(desc+" c1:"+c1[pos]+"  c2:"+c2[pos]);
    }

    /*
    返回x的系数a 公式：a = ( n sum( xy ) - sum( x ) sum( y ) ) / ( n sum( x^2 ) - sum(x) ^ 2 )
     */
    public static double getA(double[] x, double[] y)
    {
        int n = x.length;
        return (double) ((n * pSum(x, y) - sum(x) * sum(y)) / (n * sqSum(x) - Math
                .pow(sum(x), 2)));
    }

    /*
     返回常量系数系数b 公式：b = sum( y ) / n - a sum( x ) / n
     */
    public static double getB(double[] x, double[] y)
    {
        int n = x.length;
        double a = getA(x, y);
        return sum(y) / n - a * sum(x) / n;
    }

    /*
     求和
     */
    private static double sum(double[] ds)
    {
        double s = 0;
        for (double d : ds)
        {
            s = s + d;
        }
        return s;
    }

    /*
     求平方和
     */
    private static double sqSum(double[] ds)
    {
        double s = 0;
        for (double d : ds)
        {
            s = s + Math.pow(d, 2);
        }
        return s;
    }

    /*
     返回对应项相乘后的和
     */
    private static double pSum(double[] x, double[] y)
    {
        double s = 0;
        for (int i = 0; i < x.length; i++)
        {
            s = s + x[i] * y[i];
        }
        return s;
    }

    /**
     * 方差s^2=[(x1-x)^2 +...(xn-x)^2]/n
     * @param x
     * @return
     */
    public static double getVariance(double[] x) {
        int m = x.length;
        double sum = 0;
        for (int i = 0; i < m; i++) {// 求和
            sum += x[i];
        }
        double dAve = sum / m;// 求平均值
        double dVar = 0;
        for (int i = 0; i < m; i++) {// 求方差
            dVar += (x[i] - dAve) * (x[i] - dAve);
        }
        return dVar / m;
    }


    /**
     * 中位数(double)
     * @param nums: A list of integers.
     * @return: An integer denotes the middle number of the array.
     */
    public static double median(double []nums){
        if(nums.length==0)
            return 0;
        int start=0;
        int end=nums.length-1;
        int index=partition(nums, start, end);
        if(nums.length%2==0){
            while(index!=nums.length/2-1){
                if(index>nums.length/2-1){
                    index=partition(nums, start, index-1);
                }else{
                    index=partition(nums, index+1, end);
                }
            }
        }else{
            while(index!=nums.length/2){
                if(index>nums.length/2){
                    index=partition(nums, start, index-1);
                }else{
                    index=partition(nums, index+1, end);
                }
            }
        }
        return nums[index];
    }

    private static int partition(double nums[], int start, int end){
        int left=start;
        int right=end;
        double pivot=nums[left];
        while(left<right){
            while(left<right&&nums[right]>=pivot){
                right--;
            }
            if(left<right){
                nums[left]=nums[right];
                left++;
            }
            while(left<right&&nums[left]<=pivot){
                left++;
            }
            if(left<right){
                nums[right]=nums[left];
                right--;
            }
        }
        nums[left]=pivot;
        return left;
    }
}

class Info{
    double info[][] = new double[4][3];

    @Override
    public String toString() {
        return "\t\t男生\t女生\t全体\n平均值\t"+info[0][0]+'\t'+info[0][1]+'\t'+info[0][2]+
                "\n方差\t"+info[1][0]+'\t'+info[1][1]+'\t'+info[1][2]+
                "\n中间值\t"+info[2][0]+'\t'+info[2][1]+'\t'+info[2][2]+
                "\n估计值\t"+info[3][0]+'\t'+info[3][1]+'\t'+info[3][2];
    }
}