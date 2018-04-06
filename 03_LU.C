#include <stdio.h>
#define N 4

int main(){
	float a[N][N] = {{2.,1.,0,7.},{3.,4.,1.,2.},{4.,2.,1.,3.},{1.,1.,2.,1.}};
	float b[N] = {32.,22.,23.,13.};
	float l[N][N] = {{0},{0},{0},{0}};
	float u[N][N] = {{0},{0},{0},{0}};
	float x[N] = {0};
	float y[N] = {0};
	int sum;

	for(int i=1;i<=N;i++) l[i-1][i-1] = 1.0;
	for(int j=1;j<=N;j++){
		for(int i=1;i<=j;i++){
			sum = 0.0;
			for(int k=1;k<=i-1;k++) sum += l[i-1][k-1] * u[k-1][j-1];
			u[i-1][j-1] = a[i-1][j-1] - sum;
		}
		for(int i=j+1;i<=N;i++){
			sum = 0.0;
			for(int k=1;k<=j-1;k++) sum += l[i-1][k-1] * u[k-1][j-1];
			l[i-1][j-1] = a[i-1][j-1] - sum;
			if(u[j-1][j-1]!=0) l[i-1][j-1] = l[i-1][j-1] / u[j-1][j-1];
			else l[i-1][j-1] = 0.0;
		}
	}
	
	y[0] = b[0] / l[0][0];
	for(int i=2;i<=N;i++){
		sum = 0.0;
		for(int j=1;j<=i-1;j++) sum += l[i-1][j-1] * y[j-1];
		y[i-1] = b[i-1] - sum;
		if(l[i-1][i-1]!=0) y[i-1] = y[i-1]/l[i-1][i-1];
		else y[i-1] = 0.0;
	}
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			printf("[%4.2f]",l[i][j]);
		}
		printf(" |[%4.2f]| = [%4.2f]\n",y[i],b[i]);
	}
	printf("\n\n");

	x[N-1] = y[N-1] / u[N-1][N-1];
	for(int i=N-1;i>=1;i--){
		sum = 0.0;
		for(int j=i+1;j<=N;j++) sum += u[i-1][j-1] * x[j-1];
		x[i-1] = y[i-1] - sum;
		if(u[i-1][i-1]!=0) x[i-1] = x[i-1]/u[i-1][i-1];
		else x[i-1] = 0.0;
	}

	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			printf("[%4.2f]",u[i][j]);
		}
		printf(" |[%4.2f]| = [%4.2f]\n",x[i],y[i]);
	}
	return 0;
}
