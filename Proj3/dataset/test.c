#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<math.h>

struct tip{
	int f1,f2;
};

struct fruitprice{
	int f1,price;
};
 
int main(void)
{
	int i,M,b,s=0,j,max;
    FILE *fp;//�����ļ�ָ��
    scanf("%d%d",&i,&M); //����i,M
    int num1[i],num2[i];
    struct tip tips[i];
    struct fruitprice price[M];
	if((fp=fopen(".\\Data\\100sparse.txt","w"))==NULL)
	{
	printf("can not open the file\n");
	exit(0);
	}
	printf("open the file successful\n");
    fprintf(fp,"%d %d\n",i,M); 
    srand(time(NULL)); //��ʼ��ʱ������
    for(j=0;j<i+1;j++)
    {
    	while(1){
		b=rand()%M+1; //���� 
		num1[j]=b;
		while(1){
			b=rand()%M+1;
			if(b!=num1[j]){
				break;
			}
		}
		num2[j]=b;
		if(num2[j]<num1[j]){
			int c=num2[j];
			num2[j]=num1[j];
			num1[j]=c;
		}
		tips[j].f1=num1[j];
		tips[j].f2=num2[j];
		int flag=0;
		for(int k=0;k<j;k++){
			if(tips[k].f1==tips[j].f1&&tips[k].f2==tips[j].f2){
				flag=1;
				break;
			}
		}
		if(flag==0){
			break;
		}
		}
    }
	for(j=0;j<i+1;j++){
		for(int k=0;k<i-j;k++){
			if(tips[k].f1>tips[k+1].f1){
				int temp1=tips[k].f1;
				int temp2=tips[k].f2;
				tips[k].f1=tips[k+1].f1;
				tips[k].f2=tips[k+1].f2;
				tips[k+1].f1=temp1;
				tips[k+1].f2=temp2;
			}
		}
	}
	for(j=1;j<i+1;j++){
    	fprintf(fp,"%04d %04d",tips[j].f1,tips[j].f2); //�������д���ļ�
    	fprintf(fp,"\n");  //����
	}
    for(j=M;j>0;j--){
    	b=rand()%1000+1;
    	fprintf(fp,"%04d %d",j,b);
    	fprintf(fp,"\n");
	}
	fclose(fp); //�ر��ļ�
    return 0;
	} 


