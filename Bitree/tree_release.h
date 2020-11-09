#include <typeinfo>

/* 节点中，可以存放基本类型或构造类型
 * 出于效率的考虑，对于后一情况通常只保存对象的指针
 * 因此，在主体结构析构之前，需要首先释放这些成员对象所占的空间
 * 此处，借助C++中偏特化技术区分上述两种情况，并做对应处理
 * */

template<typename T> class Cleaner{
        static void clean(T x){
#ifdef _DEBUG
                static int n=0;
                if(strlen(typeid(T).name())){
                        printf("\t<%s>[%d]=",typeid(T).name(),++n);
                        //print(x) 还没实现
                        printf("purged\n");
                }
#endif
        }
};
/*偏特化*/
template<typename T>class Cleaner<T*>{
        static void clean(T* x){
                if(x){
                        delete x;
                }
#ifdef _DEBUG
                static int n=0;
                if(strlen(typeid(T).name())){
                        printf("\t<%s>[%d]=",typeid(T).name(),++n);
                        //print(x) 还没实现
                        printf("purged\n");
                }
#endif
        }
};

template<typename T>void release(T x){
        Cleaner<T>::clean(x);
}
