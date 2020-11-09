//
// Created by ELIO on 2020/11/9.
//

/*Node 自身的状态,x不是指针*/
#define is_root(x)      ((!(x).parent))
#define is_lc(x)        (!is_root(x) && (&(x)==(x).parent->lc))
#define is_rc(x)        (!is_root(x) && (&(x)==(x).parent->rc))
#define has_parent(x)   (!is_root(x))
#define has_lc(x)       ((x).lc)
#define has_rc(x)       ((x).rc)
#define has_c(x)        (has_lc(x)||has_rc(x))
#define has_both_c(x)   (has_lc(x)&&has_rc(x))
#define is_leaf(x)      (!has_both_c(x))
/*与Node的关系,指针或者引用*/
#define brother(p) \
        (is_lc(*(p))?(p)->parent->rc:(p)->parent->lc)
#define uncle(p) \
        (is_lc(*((p)->parent))?((p)->parent->parent->rc):((p)->parent->parent->lc))
#define from_parent(p) \
        (is_root(p)?_root:(is_lc(p)?(p).parent->lc:(p).parent->rc))
