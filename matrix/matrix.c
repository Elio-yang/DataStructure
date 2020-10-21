#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 3
#define P 4
#define N 3

#define INIT(p,row,col) 	do{                                             \
					for(int i=0;i<row;i++){                 \
						for(int j=0;j<col;j++){         \
							scanf("%d",*(p+i)+j);   \
						}                               \
					}                                       \
                        	}while(0)
#define MULT(p_a,p_b,p_c,row_a,\
col_a,row_b,col_b) 		do{                                           	\
					for(int i=0;i<row_a;i++){               \
						for(int j=0;j<col_b;j++){       \
							for(int k=0;k<col_a;k++){\
								*(*(p_c+i)+j)+=*(*(p_a+i)+k) * *(*(p_b+k)+j);\
							}                       \
						}                               \
					}                                       \
				}while(0)
#define SHOW(p_a,row_a,col_a)   	do{                                                             \
						printf("matrix "#p_a":\n");				\
						if(row_a==1){						\
							for(int i=0;i<col_a;i++){			\
								printf("%d ",*(p_a+i));			\
							}						\
							printf("\n");					\
							break;						\
						}                             				\
						for(int i=0;i<row_a;i++){                               \
							for(int j=0;j<col_a;j++){                       \
								printf("%d ",*(*(p_a+i)+j));            \
							}                                               \
							printf("\n");                                   \
						}                                                       \
                                	}while(0)
#define SHOW_O(p_a,col_a)			do{\
						printf("matrix "#p_a":\n");				\
						for(int i=0;i<col_a;i++){				\
							printf("%d ",*(p_a+i));				\
						}							\
						printf("\n");						\
						break;							\
					}while(0)					
#define MAKE_EMPTY(p_a,row_a,col_a)     do{								\
                                                memset(*(p_a),0,row_a*col_a*sizeof(typeof(*(*p_a))));	\
                                        }while(0)
#define COMPRESS_DIAGONAL(p_a,p_c,row_a)do{								\
						for(int i=0;i<row_a;i++){				\
							*(p_c+i)=*(*(p_a+i)+i);				\
						}                                			\
					}while(0)

int main()
{
	int A[M][P];
	INIT(A, M, P);
	int B[P][N];
	INIT(B, P, N);
	/* do mult */
	int C[M][N] = { 0 };
	MULT(A, B, C, M, P, P, N);
	/* show */
	SHOW(A, M, P);
	SHOW(B, P, N);
	SHOW(C, M, N);
	/*compress dignal matrix*/
	int D[N][N]={0};
	INIT(D,N,N);
	int E[N]={0};
	COMPRESS_DIAGONAL(D,E,N);
	SHOW(D,N,N);
	SHOW_O(E,N);
	/*compress triangle matrix*/
	

	


	return 0;
}
