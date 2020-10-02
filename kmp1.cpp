#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

int* build_next(char *P);
int kmp(char *T,char *P);
int main()
{

    while (1)
    {
        char str[100];
        scanf("%s",str);
        int *next=build_next(str);
        int m=strlen(str);
        for(int i=0;i<m;i++)
        {
            cout<<next[i]<<" ";
        }
    }
    system("pause");
    return 0;
}
int* build_next(char *P)
{
    size_t m=strlen(P),j=0;
    int *N=new int[m];
    int t=N[0]=-1;
    while(j<m-1){
        if(0>t||P[j]==P[t]){
            j++;
            t++;
            N[j]=t;
        }else{
            t=N[t];
        }
    }
    return N;
}
int kmp(char *T,char *P)
{
    int *next=build_next(P);
    int m=(int)strlen(P),j=0;
    int n=(int)strlen(T),i=0;
    while(j<m&&i<n){
        if(0>j||P[j]==T[i]){
            i++;
            j++;
        }else{
            j=next[j];
        }
    }
    for(int k=0;k<m;k++){
        cout<<next[k]<<" ";
    }
    cout<<endl;
    delete[] next;
    return i-j;
}
