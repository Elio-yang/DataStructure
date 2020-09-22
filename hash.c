#include "hash.h"

extern unsigned int hash(const char *str,int table_size)
{
    unsigned int hash_val=0;
    while(*str!='\0'){
        hash_val=(hash_val<<5)+ *str++;
    }
    return hash_val%table_size;
}
extern struct hash_table * init_hash_table(int table_size)
{
    
}
extern void destory_hash_table(struct hash_table *h);
extern struct node *find(data_t key,struct hash_table *h);
extern void insert(data_t key,struct hash_table *h);

