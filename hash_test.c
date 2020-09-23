#include "hash.h"
int main()
{
    struct hash_table * H;
    H=init_hash(1000);
    put("hello",H);
    return 0;
}