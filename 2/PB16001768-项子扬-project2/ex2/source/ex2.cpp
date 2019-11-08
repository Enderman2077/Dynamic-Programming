#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<math.h>
FILE *fpr1,*fpr2,*fpw1,*fpw2;//�����ļ�ָ�� 
//b������0��ʾ���ϣ�1��ʾ����2��ʾ������
void LCS_LENGTH(char X[],char Y[],int b[][61],int c[][61],int m,int n){//�㷨���Ĳ��� 
	int i,j;
	c[0][0]=0;
	for(i=1;i<=m;i++) c[i][0]=0;//��ʼ��c��������� 
	for(j=1;j<=n;j++) c[0][j]=0;
	for(i=1;i<=m;i++){
		for(j=1;j<=n;j++){
			if(X[i-1]==Y[j-1]){//�������������һλ��ͬ��LCS���ȼ�1���������ƶ� 
				c[i][j]=c[i-1][j-1]+1;
				b[i][j]=2; 
			}
			else if(c[i-1][j]>=c[i][j-1]){//����ͬ����Ϊ���������ȡ�ϴ���ΪLCS���� 
				c[i][j]=c[i-1][j];
				b[i][j]=0;
			}
			else{
				c[i][j]=c[i][j-1];
				b[i][j]=1;
			}
		}
	}
}
void PRINT_LCS(int b[][61],char X[],int i,int j){//���ڴ�ӡLCS���� 
	if(i==0||j==0) return;//�ݹ���� 
	if(b[i][j]==2){//���������ƶ� 
		PRINT_LCS(b,X,i-1,j-1);//�ݹ� 
		fprintf(fpw1,"%c",X[i-1]);//��ӡ��ǰ��ĸ 
	}
	else if(b[i][j]==0) PRINT_LCS(b,X,i-1,j);//��������ĵݹ���� 
	else PRINT_LCS(b,X,i,j-1); 
}
int main(){
	double run_time;
	_LARGE_INTEGER time_start;//��ʼʱ�� 
	_LARGE_INTEGER time_over;//����ʱ�� 
	double dqFreq;//��ʱ��Ƶ�� 
	LARGE_INTEGER f;
	QueryPerformanceFrequency(&f);
	dqFreq=(double)f.QuadPart;
	fpr1=fopen("../input/inputA.txt","r");//���ļ�ָ�� 
	fpr2=fopen("../input/inputB.txt","r");
	fpw1=fopen("../output/result.txt","a");
	fpw2=fopen("../output/time.txt","a");
	int b[91][61],c[91][61];
	int i,j,m,n;
	char X[91],Y[61];
	m=15;//A�� 
	for(n=10;n<=60;n+=10){
		fscanf(fpr1,"%s",X);
		fscanf(fpr1,"%s",Y);
		QueryPerformanceCounter(&time_start);//��¼�㷨��ʼʱ��ʱ�� 
		LCS_LENGTH(X,Y,b,c,m,n);
		QueryPerformanceCounter(&time_over);//��¼�㷨����ʱ��ʱ�� 
		run_time=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;//�����㷨����ʱ�� 
		fprintf(fpw2,"A���ģΪ(%d,%d)���ַ������LCS����ʱ��Ϊ��%fns\n",m,n,run_time);//����������time.txt 
		fprintf(fpw1,"A���ģΪ(%d,%d)���ַ������LCS����Ϊ��%d������һ����Ϊ��",m,n,c[m][n]);
		PRINT_LCS(b,X,m,n);
		fprintf(fpw1,"\n");
	}
	n=25;//B�� 
	for(m=15;m<=90;m+=15){
		fscanf(fpr2,"%s",X);
		fscanf(fpr2,"%s",Y);
		QueryPerformanceCounter(&time_start);
		LCS_LENGTH(X,Y,b,c,m,n);
		QueryPerformanceCounter(&time_over);
		run_time=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;
		fprintf(fpw2,"B���ģΪ(%d,%d)���ַ������LCS����ʱ��Ϊ��%fns\n",m,n,run_time);
		fprintf(fpw1,"B���ģΪ(%d,%d)���ַ������LCS����Ϊ��%d������һ����Ϊ��",m,n,c[m][n]);
		PRINT_LCS(b,X,m,n);
		fprintf(fpw1,"\n");
	}
	fclose(fpr1);//�ر��ļ�ָ�� 
	fclose(fpr2);
	fclose(fpw1);
	fclose(fpw2);
	return 0;
}
