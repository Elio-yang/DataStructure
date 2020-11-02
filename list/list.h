#ifndef LIST_H_
#define LIST_H_

/*获得TYPE类型结构体成员MEMBER的偏移量*/
#define offset_of(TYPE, MEMBER) ((size_t) & ((TYPE *)0)->MEMBER)
/*由TYPE类型结构体成员MEMBER或者指向改结构体的指针*/
#define container_of(ptr, TYPE, MEMBER) ({                 \
        const TYPEof(((TYPE *)0)->MEMBER) *__mptr = (ptr); \
        (TYPE *)((char *)__mptr - offset_of(TYPE,MEMBER)); \
})



#endif