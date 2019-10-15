package com.company;

public class Main {
    public static void main(String[] args) {
        System.out.print("Taxable\tSingle\tMarried\tMarried\tHead of\t\n");
        System.out.print("Income\t       \tJoint  \tSepa...\ta House\t\n");
        for(int i=50000;i<=60000;i+=50){
            System.out.printf("%d\t%d\t%d\t%d\t%d\t\n",i,(int)calcSingle(i),
                    (int)calcMarriedJointly(i),(int)calcMarriedSeparately(i),(int)calcHeadHousehold(i));
        }
    }
    static double calcSingle(double income){
        if(income<7300)return income*0.1;
        if(income<29700)return 730+(income-7300)*0.15;
        if(income<71950)return 4090+(income-29700)*0.25;
        if(income<150150)return 14652.5+(income-71950)*0.28;
        if(income<326450)return 36548.5+(income-150150)*0.33;
        return 94727.5+(income-326450)*0.35;
    }
    static double calcMarriedJointly(double income){
        if(income<14600)return income*0.1;
        if(income<59400)return 1460+(income-14600)*0.15;
        if(income<119950)return 8180+(income-59400)*0.25;
        if(income<182800)return 23317.5+(income-119950)*0.28;
        if(income<326450)return 40915.5+(income-182800)*0.33;
        return 88320.0+(income-326450)*0.35;
    }
    static double calcMarriedSeparately(double income){
        if(income<7300)return income*0.1;
        if(income<29700)return 730+(income-7300)*0.15;
        if(income<59975)return 4090+(income-29700)*0.25;
        if(income<91400)return 11658.75+(income-59975)*0.28;
        if(income<163225)return 20457.75+(income-91400)*0.33;
        return 44160+(income-163225)*0.35;
    }
    static double calcHeadHousehold(double income){
        if(income<10450)return income*0.1;
        if(income<39800)return 1045+(income-10450)*0.15;
        if(income<102800)return 5447.5+(income-39800)*0.25;
        if(income<166450)return 21197.5+(income-102800)*0.28;
        if(income<326450)return 39019.5+(income-166450)*0.33;
        return 91819.5+(income-326450)*0.35;
    }
}
