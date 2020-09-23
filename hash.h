#ifndef _HASH_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*key 的类型*/
#define data_t char*
/*哈希表的最小大小*/
#define MIN_SIZE 29
/*散列表元素链表的节点*/
struct node{
    data_t data;
    struct node *next;
};

/*分离链接散列表*/
struct hash_table{
    int table_size;
    /*
     * 指针数组：
     * 第一次malloc：H->list=(struct node**)malloc(sizeof(struct node*)*H->table_size)
     * 第二次malloc：H->list[i]=（struct node*)malloc(sizeof(struct node))
     * */
    struct node* *list;
};

/*hash函数*/
extern unsigned int hash(const char *str,int table_size);
/*初始化哈希表*/
extern struct hash_table * init_hash(int table_size);
extern void destory_hash(struct hash_table *h);
extern struct node *contain(data_t key,struct hash_table *h);
/*解决冲突：分离链接法  插入*/
extern void put(data_t key,struct hash_table *h);
/*生成下一个素数*/
extern int next_prime(int n);
extern int is_prime(int n);
/**/
#endif