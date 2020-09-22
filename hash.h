#ifndef _HASH_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*key 的类型*/
#define data_t int

/*散列表元素链表的节点*/
struct node{
    data_t data;
    struct node *next;
};

/*分离链接散列表*/
struct hash_table{
    int table_size;
    struct node *list;
};

/*hash函数*/
extern unsigned int hash(const char *str,int table_size);
/*初始化哈希表*/
extern struct hash_table * init_hash_table(int table_size);
extern void destory_hash_table(struct hash_table *h);
extern struct node *find(data_t key,struct hash_table *h);
/*解决冲突：分离链接法  插入*/
extern void insert(data_t key,struct hash_table *h);

#endif