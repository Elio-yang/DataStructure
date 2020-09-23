#include "hash.h"
#include "hash.c"

extern struct hash_table *init_hash(int table_size);
extern void put(data_t key, struct hash_table *h);
int main()
{
	struct hash_table *H;
	H = init_hash(400);
	put("hello", H);
	if(contain("hello",H)!=NULL){
		printf("exist \"hello\" \n");
	}
	put("test",H);
	if(contain("test",H)!=NULL){
		printf("exist \"test\" \n");
	}
	return 0;
}
