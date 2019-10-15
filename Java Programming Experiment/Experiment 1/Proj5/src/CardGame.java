import java.util.ArrayList;

public class CardGame {
    public static String get24Points(int[] nums) {
        ArrayList<Double> numArrayList = new ArrayList<>(); // 用于存放数字
        ArrayList<String> stringArrayList = new ArrayList<>(); // 用于存放数字的字符串形式
        for (int num:nums) { // 将数组转换为ArrayList
            numArrayList.add((double)num);
            stringArrayList.add(Integer.toString(num));
        }
        String result = recursion(numArrayList, stringArrayList);
        if (result == null) return "Can't found!";
        return result;
    }

    // 递归，数组中取出两个数计算后结果放回数组
    private static String recursion(ArrayList<Double> numArrayList, ArrayList<String> stringArrayList) {
        String result = null;
        int n = numArrayList.size();
        if (n == 1) {
            if (Math.abs(numArrayList.get(0) - 24.0) <= 0.000001) result = stringArrayList.get(0); // 若数组只有一个数，且为24，则将算式字符串返回
            return result;
        }

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                ArrayList<Double> newNumArrayList = new ArrayList<Double>();// 用于递归的新数组
                ArrayList<String> newStringArrayList = new ArrayList<String>();// 用于存放算式的新数组
                // 任意取出两个数的不同组合情况
                for (int r = 0; r < n; r++) {
                    if (r != i && r != j) {
                        newNumArrayList.add(numArrayList.get(r));
                        newStringArrayList.add(stringArrayList.get(r));
                    }
                }
                newNumArrayList.add(numArrayList.get(i) + numArrayList.get(j));// 加入取出的两数计算结果 a+b
                newStringArrayList.add("(" + stringArrayList.get(i) + "+" + stringArrayList.get(j) + ")");// 记录两数计算的算式
                result = recursion(newNumArrayList, newStringArrayList);//递归
                if (result != null) return result;    //若已有结果，则返回

                newNumArrayList.remove(newNumArrayList.size() - 1);// 移除上次添加的两数计算结果
                newStringArrayList.remove(newStringArrayList.size() - 1);
                newNumArrayList.add(numArrayList.get(i) - numArrayList.get(j));//a-b
                newStringArrayList.add("(" + stringArrayList.get(i) + "-" + stringArrayList.get(j) + ")");
                result = recursion(newNumArrayList, newStringArrayList);
                if (result != null) return result;    //若已有结果，则返回

                newNumArrayList.remove(newNumArrayList.size() - 1);
                newStringArrayList.remove(newStringArrayList.size() - 1);
                newNumArrayList.add(numArrayList.get(i) * numArrayList.get(j));//a*b
                newStringArrayList.add(stringArrayList.get(i) + "*" + stringArrayList.get(j));
                result = recursion(newNumArrayList, newStringArrayList);
                if (result != null) return result;    //若已有结果，则返回

                newNumArrayList.remove(newNumArrayList.size() - 1);
                newStringArrayList.remove(newStringArrayList.size() - 1);
                newNumArrayList.add(numArrayList.get(i) / numArrayList.get(j));//a/b
                newStringArrayList.add(stringArrayList.get(i) + "/" + stringArrayList.get(j));
                result = recursion(newNumArrayList, newStringArrayList);
                if (result != null) return result;    //若已有结果，则返回

                newNumArrayList.remove(newNumArrayList.size() - 1);
                newStringArrayList.remove(newStringArrayList.size() - 1);
                newNumArrayList.add(numArrayList.get(j) - numArrayList.get(i));//b-a
                newStringArrayList.add("(" + stringArrayList.get(j) + "-" + stringArrayList.get(i) + ")");
                result =recursion(newNumArrayList, newStringArrayList);
                if (result != null) return result;    //若已有结果，则返回

                newNumArrayList.remove(newNumArrayList.size() - 1);
                newStringArrayList.remove(newStringArrayList.size() - 1);
                newNumArrayList.add(numArrayList.get(j) / numArrayList.get(i));//b/a
                newStringArrayList.add(stringArrayList.get(j) + "/" + stringArrayList.get(i));
                result = recursion(newNumArrayList, newStringArrayList);
                if (result != null) return result;    //若已有结果，则返回
            }
        }
        return null;
    }
}