#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 3
#define P 4
#define N 3
#define Q 5

struct sparse_matrix{
	int row;
	int col;
	int val;
};

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
						*(*(p_c+i)+j)+=			\
						*(*(p_a+i)+k) * *(*(p_b+k)+j);	\
							}                       \
						}                               \
					}                                       \
				}while(0)
#define SHOW(p_a,row_a,col_a)   	do{                                                             \
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
#define SHOW_S(p_s,col_s)        	do{								\
						for(int i=0;i<col_s;i++){				\
							printf("{ ");					\
							printf("row=%d",p_s[i].row);		\
							printf("\tcol=%d",p_s[i].col);		\
							printf("\tval=%d",p_s[i].val);		\
							printf(" }\n");					\
						}							\
					}while(0)					
#define MAKE_EMPTY(p_a,row_a,col_a)     do{								\
                                                memset(*(p_a),0,row_a*col_a*sizeof(typeof(*(*p_a))));	\
                                        }while(0)
#define COMPRESS_DIAGONAL(p_a,p_c,row_a)do{								\
						for(int i=0;i<row_a;i++){				\
							*(p_c+i)=*(*(p_a+i)+i);				\
						}                                			\
					}while(0)
#define MAP_TRIANGLE_MATRIX(p_t,p_m,col_t) 	do{							\
						for(int i=1;i<=col_t;i++){				\
							for(int j=1;j<=i;j++){				\
								int index=i*(i-1)/2 + (j-1);		\
								*(p_m+index)=*(*(p_t+i-1)+j-1);		\
							}						\
						}							\
					}while(0)
#define MAP_SYMMETRIC_MATRIX(p_s,p_m,col_s)	do{							\
						for(int i=1;i<=col_s;i++){				\
							for(int j=1;j<=i;j++){				\
								int index=i*(i-1)/2+(j-1);		\
								*(p_m+index)=*(*(p_s+i-1)+j-1);		\
							}						\
						}							\
					}while(0)
struct sparse_matrix* map_sparse_matrix(int(*p_s)[Q],int col_s,int*tmp)
{
	int cnt=0;
	for(int i=0;i<col_s;i++){
		for(int j=0;j<col_s;j++){
			if(*(*(p_s+i)+j)!=0){
				++cnt;
			}
		}
	}
	*tmp=cnt;
	struct sparse_matrix* p_m;
	p_m=(struct sparse_matrix*)malloc(sizeof(struct sparse_matrix)*cnt);
	int t=0;
	for(int i=0;i<col_s;i++){
		for(int j=0;j<col_s;j++){
			if(*(*(p_s+i)+j)!=0){
				p_m[t].row=i+1;
				p_m[t].col=j+1;
				p_m[t].val=*(*(p_s+i)+j);
				t++;
			}
		}
	}
	return p_m;
}
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
	int tri_M[Q][Q];
	INIT(tri_M,Q,Q);
	int all=Q*(Q+1)/2;
	int map_tri_M[all];
	MAP_TRIANGLE_MATRIX(tri_M,map_tri_M,Q);
	SHOW(tri_M,Q,Q);
	SHOW_O(map_tri_M,all);
	/*compress symmetric matrix*/
	int sym_M[Q][Q];
	INIT(sym_M,Q,Q);
	int map_sym_M[all];
	MAP_SYMMETRIC_MATRIX(sym_M,map_sym_M,Q);
	SHOW(sym_M,Q,Q);
	SHOW_O(map_sym_M,all);
	/*compress sparse matrix*/
	int sparse_matrix[Q][Q];
	INIT(sparse_matrix,Q,Q);
	int cnt=0;
	struct sparse_matrix *map_sparse=map_sparse_matrix(sparse_matrix,Q,&cnt);
	SHOW(sparse_matrix,Q,Q);
	SHOW_S(map_sparse,cnt);

	system("pause");
	return 0;
}
