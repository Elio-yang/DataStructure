#ifndef _HASH_H_
#define _HASH_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SPACE_ERR() printf("out of space! in function %s line:%d \n",__func__,__LINE__)
/*key 的类型*/
#define data_t char*
/*哈希表的最小大小*/
#define MIN_SIZE 29
/*散列表元素链表的节点*/
/*===========================================================================*/
struct node{
    data_t data;
    struct node *next;
};

/*分离链接散列表*/
struct hash_map{
    int table_size;
    /*
     * 指针数组：
     * 第一次malloc：H->list=(struct node**)malloc(sizeof(struct node*)*H->table_size)
     * 第二次malloc：H->list[i]=（struct node*)malloc(sizeof(struct node))
     * */
    struct node* *list;
};

/*初始化哈希表*/
extern struct hash_map * init_hash(int table_size);
extern void destory_hashmap(struct hash_map *H);
extern struct node *contain(data_t key,struct hash_map *H);
/*解决冲突：分离链接法  插入*/
extern void put(data_t key,struct hash_map *H);
/*===========================================================================*/
/*描述该节点状态*/
enum state{Legitimate,Empty,Deleted};

/*哈希表的元素*/
struct hash_cell{
    data_t data;
    enum state State;
};

/*平方探测散列表*/
struct hashmap_square{
    int table_size;
    /*这是一个数组*/
    struct hash_cell * cells;
};

extern struct hashmap_square *init_square_hash(int table_size);
extern void destory_square_hashmap(struct hashmap_square *H);
extern int contain_square(data_t key,struct hashmap_square *H);
extern void put_square(data_t key,struct hashmap_square *H);
/*===========================================================================*/
/*hash函数*/
extern unsigned int hash(const char *str,int table_size);
/*===========================================================================*/

/*生成下一个素数*/
extern int next_prime(int n);
extern int is_prime(int n);
/**/
#endif