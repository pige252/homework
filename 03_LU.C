#include <stdio.h>
#include <math.h>
#define n 100
#define TINY 1.0e-20

int main(){
	int N,i,j,k;
	printf("dimension of matrix :");
	scanf("%d",&N);
	float a[n][n],a_prime[n][n],l[n][n],u[n][n],p[n][n];
	float b[n],b_prime[n],b_test[n],x[n],y[n];
	float swap;
	//a' = p * a, a' * x = b',	a' = l * u,	u * x = y,	l * y = b'

	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("input A[%d][%d] :", i+1,j+1);
			scanf("%f",&a[i][j]);
		}
	}//	input matrix A
	
	for(i=0;i<N;i++){
		printf("input B[%d] :", i+1);
		scanf("%f",&b[i]);
	}// input columm B

	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			u[i][j] = 0.0;
			l[i][j] = 0.0;
			a_prime[i][j] = 0.0;
			if(i==j) p[i][j] = 1.0;
			else p[i][j] = 0.0;
		}
	}//initialize u,l,a_prime,p

	for(i=0;i<N;i++){
		int max_j = i;
		for(j=0;j<N;j++){
			if(fabs(a[j][i])>fabs(a[max_j][i])) max_j = j;
		}
		if(max_j!=i){
			for(k=0;k<N;k++){
				swap = p[i][k];
				p[i][k] = p[max_j][k];
				p[max_j][k] = swap;
			}
		}
	}//pivotize
	
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			for(k=0;k<N;k++){
				a_prime[i][j] += p[i][k] * a[k][j];
			}
		}
	}//a_prime = p * a

	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			b_prime[i] += p[i][j] * b[j];
		}
	}//b_prime = p * b

	for(j=1;j<=N;j++){
		for(i=1;i<=j;i++){
			u[i-1][j-1] = a_prime[i-1][j-1];
			for(k=1;k<=i-1;k++) u[i-1][j-1] -= l[i-1][k-1] * u[k-1][j-1];
		}	// u_ij = a_ij - sum(l_ik * u_kj)
		for(i=j+1;i<=N;i++){
			l[i-1][j-1] = a_prime[i-1][j-1];
			for(k=1;k<=j-1;k++) l[i-1][j-1] -= l[i-1][k-1] * u[k-1][j-1];
			if(u[j-1][j-1]==0.0) u[j-1][j-1] = TINY;
			l[i-1][j-1] /= u[j-1][j-1];
		}	// l_ij = { a_ij - sum(l_ik * u_kj) } / u_jj
	}
	for(i=1;i<=N;i++) l[i-1][i-1] = 1.0; // l_ii = 1
	
	y[0] = b[0] / l[0][0];	//	y_1 = b_1 / l_11
	for(i=2;i<=N;i++){
		y[i-1] = b[i-1];
		for(j=1;j<=i-1;j++) y[i-1] -= l[i-1][j-1] * y[j-1];
		y[i-1] /= l[i-1][i-1];
	} //	y_i = { b_i - sum(l_ij * y_j) } / l_ii

	x[N-1] = y[N-1] / u[N-1][N-1]; //	x_n = y_n / u_nn
	for(i=N-1;i>=1;i--){
		x[i-1] = y[i-1];
		for(j=i+1;j<=N;j++) x[i-1] -= u[i-1][j-1] * x[j-1];
		if(u[i-1][i-1]==0.0) u[i-1][i-1] = TINY;
		x[i-1] /= u[i-1][i-1];
	} //	x_i = { y_i - sum(u_ij * x_j) } / u_ii

// 결과출력
	printf("\na_prime[%d][%d] = p[%d][%d] * a[%d][%d]\n\n", N,N,N,N,N,N);
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("[%4.1f]",a_prime[i][j]);
		}
		printf(" = ");
		for(j=0;j<N;j++){
			printf("[%1.f]",p[i][j]);
		}
		printf("||");
		for(j=0;j<N;j++){
			printf("[%4.1f]",a[i][j]);
		}
		printf("\n");
	}
	printf("\na_prime[%d][%d] * x[%d] = b_prime[%d]\n\n", N,N,N,N);
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("[%4.1f]",a_prime[i][j]);
		}
		printf(" |[%4.1f]| = [%4.1f]\n",x[i],b[i]);
	}

	printf("\nU[][]\n");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("[%4.1f]",u[i][j]);
		}
		printf("\n");
	}

	printf("\nL[][]\n");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("[%4.1f]",l[i][j]);
		}
		printf("\n");
	}

	for(i=0;i<N;i++){
		b_test[i] = 0.0;
		for(j=0;j<N;j++){
			b_test[i] += a_prime[i][j] * x[j];
		}
	}
	printf("\ncheck a_prime[%d][%d] * x[%d] = b[%d]\n\n", N,N,N,N);
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("[%4.1f]",a_prime[i][j]);
		}
		printf(" |[%4.1f]| = [%4.1f]\n",x[i],b_test[i]);
	}

	return 0;
}
