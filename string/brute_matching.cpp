#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

int bs1(char *T,char *P);
int bs2(char *T,char *P);
int main()
{

    char dst[15]="hhhghvfgfhjb23";
    char pat[15]="vfgfh";
    cout<<bs1(dst,pat)<<endl;
    system("pause");
    return 0;
}
int bs1(char *T,char *P)
{
    size_t n=strlen(T),i=0;
    size_t m=strlen(P),j=0;
    while(j<m&&i<n){
        if(T[i]==P[j]){
            i++;
            j++;
        }else{
            i-=j-1;
            j=0;
        }
    }
    return i-j;
}
int bs2(char *T,char *P)
{
    size_t n=strlen(T),i;
    size_t m=strlen(P),j;
    for(i=0;i<n-m+1;i++){
        for(j=0;j<m;j++){
            if(T[i+j]!=P[j]){
                break;
            }
            if(j>=m){
                break;
            }
        }
    }
    return i;
}
