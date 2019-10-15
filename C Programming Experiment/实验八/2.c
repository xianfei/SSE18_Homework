#include<stdio.h>
main()
{
	int strcmp(char*p1,char*p2);
	char a[100],b[100];
	gets(a);
	gets(b);
	strcmp(a,b);
}
int strcmp(char*p1,char*p2)
{
	int a,b;
	for(a=0;a<100;a++)
	{
		if(p1[a]!=p2[a]){
			b=p1[a]-p2[a];
			break;
		}
		else b=0;
	}
	printf("%d",b);
	return 0;
}