#include "hash.h"

/*
 * 哈希函数：H(Key)=Sum_i(Key[keysize-1-i])*32^i;
 */
extern unsigned int hash(const char *str,int table_size)
{
    unsigned int hash_val=0;
    while(*str!='\0'){
        hash_val=(hash_val<<5)+ *str++;
    }
    return hash_val%table_size;
}
extern struct hash_map * init_hash(int table_size)
{
    struct hash_map * H;
    if(table_size<MIN_SIZE){
        printf("table size too small(<29)\n");
        exit(EXIT_FAILURE);
    }
    H=(struct hash_map *)malloc(sizeof(struct hash_map));
    if(H==NULL){
        SPACE_ERR();
        exit(EXIT_FAILURE);
    }
    H->table_size=next_prime(table_size);
    H->list=
        (struct node**)malloc(sizeof(struct node*)*H->table_size);
    if(H->list==NULL){
        SPACE_ERR();
        exit(EXIT_FAILURE);
    }
    for(int i=0;i<H->table_size;i++){
        H->list[i]=(struct node*)malloc(sizeof(struct node));
        if(H->list[i]==NULL){
            printf("Out of space!\n");
            exit(EXIT_FAILURE);
        }else{
            H->list[i]->next=NULL;
        }
    }
    return H;
}
extern void destory_hashmap(struct hash_map *H)
{
    for(int i=0;i<H->table_size;i++){
        free(H->list[i]);
    }
    free(H);
}
extern struct node *contain(data_t key,struct hash_map *H)
{
    struct node *pos;
    struct node *head;
    head=H->list[hash(key,H->table_size)];
    pos=head->next;
    while(pos!=NULL&&strcmp(key,pos->data)!=0){
        pos=pos->next;
    }
    return pos;
}
extern void put(data_t key,struct hash_map *H)
{
    struct node *pos;
    struct node *new_node;
    struct node *head;

    pos=contain(key,H);
    /*不在散列表中*/
    if(pos==NULL){
        new_node=(struct node *)malloc(sizeof(struct node));
        if(new_node==NULL){
            SPACE_ERR();
            exit(EXIT_FAILURE);
        }else{
            head=H->list[hash(key,H->table_size)];
            new_node->data=key;
            new_node->next=head->next;
            head->next=new_node;
        }
    }
}
extern int next_prime(int n)
{
    int prime=0;
    for(int i=n;;i++){
        if(is_prime(i)){
            prime=i;
            break;
        }
    }
    return prime;
}
extern int is_prime(int n)
{
    for(int i=2;i*i<=n;i++){
        if(n%i==0){
            return 0;
        }
    }
    return 1;
}

extern struct hashmap_square * init_square_hash(int table_size)
{
    struct hashmap_square *H;
    if(table_size<MIN_SIZE){
        printf("table size too small(<29)\n");
        exit(EXIT_FAILURE);
    }
    H=(struct hashmap_square*)malloc(sizeof(struct hashmap_square));
     if(H==NULL){
        SPACE_ERR();
        exit(EXIT_FAILURE);
    }
    H->table_size=next_prime(table_size);
    H->cells=(struct hash_cell*)malloc(sizeof(struct hash_cell)*H->table_size);
    if(H->cells==NULL){
        SPACE_ERR();
        exit(EXIT_FAILURE);
    }
    for(int i=0;i<H->table_size;i++){
        H->cells[i].State=Empty;
    }
    return H;
}
extern void destory_square_hashmap(struct hashmap_square *H)
{
    for(int i=0;i<H->table_size;i++){
        free(H->cells);
    }
    free(H);
}

extern int contain_square(data_t key,struct hashmap_square *H)
{
    int pos;
    int cnt_collison=0;
    pos=hash(key,H->table_size);
    while(H->cells[pos].State!=Empty&&strcmp(H->cells[pos].data,key)!=0){
        pos+=pos + 2 * ++cnt_collison-1;
        if(pos>=H->table_size){
            pos= pos- H->table_size;
        }
    }
    if(H->cells[pos].State=Empty){
        return 0;

    }
}

extern void put_square(data_t key,struct hashmap_square *H)
{
    int pos;
    int cnt_collison=0;
    

} 