#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<math.h>
FILE *fpr1,*fpr2,*fpw1,*fpw2;//定义文件指针 
//b表项中0表示向上，1表示向左，2表示向左上
void LCS_LENGTH(char X[],char Y[],int b[][61],int c[][61],int m,int n){//算法核心部分 
	int i,j;
	c[0][0]=0;
	for(i=1;i<=m;i++) c[i][0]=0;//初始化c的特殊情况 
	for(j=1;j<=n;j++) c[0][j]=0;
	for(i=1;i<=m;i++){
		for(j=1;j<=n;j++){
			if(X[i-1]==Y[j-1]){//若两个数组最后一位相同，LCS长度加1，向左上移动 
				c[i][j]=c[i-1][j-1]+1;
				b[i][j]=2; 
			}
			else if(c[i-1][j]>=c[i][j-1]){//若不同，分为两种情况，取较大者为LCS长度 
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
void PRINT_LCS(int b[][61],char X[],int i,int j){//用于打印LCS内容 
	if(i==0||j==0) return;//递归出口 
	if(b[i][j]==2){//若向左上移动 
		PRINT_LCS(b,X,i-1,j-1);//递归 
		fprintf(fpw1,"%c",X[i-1]);//打印当前字母 
	}
	else if(b[i][j]==0) PRINT_LCS(b,X,i-1,j);//向上向左的递归情况 
	else PRINT_LCS(b,X,i,j-1); 
}
int main(){
	double run_time;
	_LARGE_INTEGER time_start;//开始时间 
	_LARGE_INTEGER time_over;//结束时间 
	double dqFreq;//计时器频率 
	LARGE_INTEGER f;
	QueryPerformanceFrequency(&f);
	dqFreq=(double)f.QuadPart;
	fpr1=fopen("../input/inputA.txt","r");//打开文件指针 
	fpr2=fopen("../input/inputB.txt","r");
	fpw1=fopen("../output/result.txt","a");
	fpw2=fopen("../output/time.txt","a");
	int b[91][61],c[91][61];
	int i,j,m,n;
	char X[91],Y[61];
	m=15;//A组 
	for(n=10;n<=60;n+=10){
		fscanf(fpr1,"%s",X);
		fscanf(fpr1,"%s",Y);
		QueryPerformanceCounter(&time_start);//记录算法开始时的时间 
		LCS_LENGTH(X,Y,b,c,m,n);
		QueryPerformanceCounter(&time_over);//记录算法结束时的时间 
		run_time=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;//计算算法所用时间 
		fprintf(fpw2,"A组规模为(%d,%d)的字符串组的LCS计算时间为：%fns\n",m,n,run_time);//将结果输出到time.txt 
		fprintf(fpw1,"A组规模为(%d,%d)的字符串组的LCS长度为：%d，其中一个解为：",m,n,c[m][n]);
		PRINT_LCS(b,X,m,n);
		fprintf(fpw1,"\n");
	}
	n=25;//B组 
	for(m=15;m<=90;m+=15){
		fscanf(fpr2,"%s",X);
		fscanf(fpr2,"%s",Y);
		QueryPerformanceCounter(&time_start);
		LCS_LENGTH(X,Y,b,c,m,n);
		QueryPerformanceCounter(&time_over);
		run_time=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;
		fprintf(fpw2,"B组规模为(%d,%d)的字符串组的LCS计算时间为：%fns\n",m,n,run_time);
		fprintf(fpw1,"B组规模为(%d,%d)的字符串组的LCS长度为：%d，其中一个解为：",m,n,c[m][n]);
		PRINT_LCS(b,X,m,n);
		fprintf(fpw1,"\n");
	}
	fclose(fpr1);//关闭文件指针 
	fclose(fpr2);
	fclose(fpw1);
	fclose(fpw2);
	return 0;
}
