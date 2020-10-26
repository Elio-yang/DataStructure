#include <stdio.h>
#include <stdlib.h>

struct t_node{
    int key;
    struct t_node *l_child;
    struct t_node *r_child;
};

void pre_build(struct t_node *T);
void pre_in_build(struct t_node *T);
void in_post_build(struct t_node *T);

void pre_order(struct t_node *T);
void pre_order_iter(struct t_node *T);
void in_order(struct t_node *T);
void in_order_iter(struct t_node *T);
void post_order(struct t_node *T);
void post_order_iter(struct t_node *T);
void level_order(struct t_node *T);
void level_num(struct t_node*T);

struct t_node *find_node(struct t_node *T, int key);
struct t_node *find_parent(struct t_node *T, int key);
void find_allparent(struct t_node *T);

void delete_node(struct t_node *T, int key);
void delete_sub(struct t_node *T, int key);
void delete_tree(struct t_node *T);

int get_hight(struct t_node *T);
int get_hight_node(struct t_node *T, struct t_node *v);

int main()
{

}