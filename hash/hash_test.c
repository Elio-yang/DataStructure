#include "hash.h"
#include "hash.c"

int main()
{
    struct hash_map * H;
    H=init_hash(1000);
    put("hello",H);
    if(contain("hello",H)!=NULL){
        printf("exist \"hello\" \n");
    }
    system("pause");
    return 0;
}