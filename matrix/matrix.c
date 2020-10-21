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
#define SHOW_S(p_s,col_a)        	do{								\
						for(int i=0;i<Q;i++){					\
							printf("{\n");					\
							printf("\trow=%d\n",p_s[i].row);		\
							printf("\tcol=%d\n",p_s[i].col);		\
							printf("\tval=%d\n",p_s[i].val);		\
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
							for(int j=i;j<=col_s;j++){			\
								int index=i*(i-1)/2+(j-1);		\
								*(p_m+index)=*(*(p_s+i-1)+j-1);		\
							}						\
						}							\
					}while(0)
#define MAP_SPARSE_MATRIX(p_s,p_m,col_s,cnt)	do{\
							int tmp;					\
							for(int i=0;i<col_s;i++){			\
								for(int j=0;j<col_s;j++){		\
									if((*(*p_s+i)+j)!=0){		\
										++tmp;			\
									}				\
								}					\
							}						\
							cnt=tmp;					\
							p_m=(struct sparse_matrix*)			\
							malloc(sizeof(struct sparse_matrix)*tmp);   	\
							int l=0;					\
							for(int i=0;i<col_s;i++){			\
								for(int j=0;j<col_s;j++){		\
									if((*(*p_s+i)+j)!=0){		\
										p_m[l].row=i;		\
										p_m[l].col=j;		\
										p_m[l].val=		\
										*((*p_s+i)+j);		\
									}				\
								}					\
							}						\
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
	int tri_M[N][N];
	INIT(tri_M,5,5);
	int all=N*(N+1)/2;
	int map_tri_M[all];
	MAP_TRIANGLE_MATRIX(tri_M,map_tri_M,N);
	SHOW(tri_M,N,N);
	SHOW_O(map_tri_M,all);
	/*compress symmetric matrix*/
	int sym_M[N][N];
	INIT(sym_M,5,5);
	int map_sym_M[all];
	MAP_SYMMETRIC_MATRIX(sym_M,map_sym_M,N);
	SHOW(sym_M,N,N);
	SHOW_O(map_sym_M,N);
	/*compress sparse matrix*/
	int sparse_matrix[Q][Q];
	INIT(sparse_matrix,Q,Q);
	struct sparse_matrix *map_sparse;
	int cnt=0;
	MAP_SPARSE_MATRIX(sparse_matrix,map_sparse,Q,cnt);
	SHOW(sparse_matrix,Q,Q);
	SHOW_S(map_sparse,cnt);
	
	


	


	return 0;
}
