import java.util.HashMap;
import java.util.Map;

public class Main {
    public static void main(String[] args) {
        System.out.println(getLCM(120,150));
        System.out.println(getLCM(7,14));
        System.out.println(getLCM(7,8));
        System.out.println(getLCM(1,2));
        System.out.println(getLCM(345,455));

    }
    static int[][] getPrimeFactors(int num){
        HashMap hashMap=new HashMap();
        int ret[][];
        for(int i=2;i<=num;i++){
            if(num%i==0)hashMap.put(i,new int[2]);
            while(num%i==0){
                ((int[])hashMap.get(i))[0]++;
                num/=i;
            }
        }
        int i=0;
        ret= new int[hashMap.size()][2];
        for (Object o :hashMap.entrySet()) {
            ret[i][0]=(int)((Map.Entry)o).getKey();
            ret[i][1]=((int[])(((Map.Entry)o).getValue()))[2];
            i++;
        }
        return ret;
    }
    static int getLCM(int num1,int num2){
        HashMap hashMap=new HashMap();
        for(int i=2;i<=num1;i++){
            if(num1%i==0)hashMap.put(i,new int[2]);
            while(num1%i==0){
                ((int[])hashMap.get(i))[0]++;
                num1/=i;
            }
        }
        for(int i=2;i<=num2;i++){
            if(num2%i==0&&!hashMap.containsKey(i))hashMap.put(i,new int[2]);
            while(num2%i==0){
                ((int[])hashMap.get(i))[1]++;
                num2/=i;
            }
        }
        int i=1;
        for (Object o :hashMap.entrySet()) {
            i*= Math.pow((int)((Map.Entry)o).getKey() ,Math.max(((int[])(((Map.Entry)o).getValue()))[0]
                    ,((int[])(((Map.Entry)o).getValue()))[1]));
        }
        return i;
    }
}
