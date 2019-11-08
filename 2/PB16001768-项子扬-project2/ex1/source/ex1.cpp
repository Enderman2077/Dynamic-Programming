#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<math.h>
#define INFI 100000000 
FILE *fpr,*fpw1,*fpw2;//�ļ�ָ�� 
void MATRIX_CHAIN_ORDER(int p[],int n,int m[][31],int s[][31]){//���ڼ��㻮�ֵ���㷨 
	int i,j,k,l,q;
	for(i=1;i<=n;i++) m[i][i]=0;
	for(l=2;l<=n;l++){
		for(i=1;i<=n-l+1;i++){
			j=i+l-1;
			m[i][j]=INFI;
			for(k=i;k<=j-1;k++){
				q=m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
				if(q<m[i][j]){
					m[i][j]=q;
					s[i][j]=k;
				}
			}
		}
	}
}
void PRINT_OPTIMAL_PARENS(int s[][31],int i,int j){//�����Ż��Ľ��������ļ��� 
	if(i==j) fprintf(fpw1,"A%d",i);
	else{
		fprintf(fpw1,"(");
		PRINT_OPTIMAL_PARENS(s,i,s[i][j]);
		PRINT_OPTIMAL_PARENS(s,s[i][j]+1,j);
		fprintf(fpw1,")");
	}
}
int main(){
	double run_time;
	_LARGE_INTEGER time_start;//��ʼʱ�� 
	_LARGE_INTEGER time_over;//����ʱ�� 
	double dqFreq;//��ʱ��Ƶ�� 
	LARGE_INTEGER f;
	QueryPerformanceFrequency(&f);
	dqFreq=(double)f.QuadPart;
	int n,i,j;
	int p[31];
	int m[31][31],s[31][31];
	for(i=0;i<31;i++)
	for(j=0;j<31;j++){//��ʼ����������� 
		m[i][j]=0;
		s[i][j]=0;
	}
	fpr=fopen("../input/input.txt","r");//���ļ�ָ�� 
	fpw1=fopen("../output/result.txt","a");
	fpw2=fopen("../output/time.txt","a"); 
	for(i=0;i<31;i++) fscanf(fpr,"%d",&p[i]);
	n=5;
	while(n<=30){//��4����ͬ�������ģ�����㷨 
		QueryPerformanceCounter(&time_start);//��¼�㷨��ʼʱ��ʱ�� 
		MATRIX_CHAIN_ORDER(p,n,m,s);//�����㷨 
		QueryPerformanceCounter(&time_over);//��¼�㷨����ʱ��ʱ�� 
		PRINT_OPTIMAL_PARENS(s,1,n);//��������result.txt
		fprintf(fpw1,"\n");
		run_time=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;//�����㷨����ʱ�� 
		fprintf(fpw2,"n=%d runtime:%fns\n",n,run_time);//����������time.txt 
		for(i=0;i<31;i++)//��������������³�ʼ�� 
		for(j=0;j<31;j++){
			m[i][j]=0;
			s[i][j]=0;
		}
		if(n==5) n=10;//���������ģ 
		else if(n==10) n=20;
		else if(n==20) n=30;
		else break;
	}
	fclose(fpr);//�ر��ļ�ָ�� 
	fclose(fpw1);
	fclose(fpw2); 
	return 0;
}
