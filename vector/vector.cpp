#include <iostream>
#define DEFAULT_CAPACITY 3
using Rank=int;

template<typename T>
class Vector{
protected:
    /*规模，容量，数据区*/
    Rank __size;
    int  __capacity;
    T   *__elem;

    /*复制区域A[lo,hi)*/
    void copy_from(T const *A,Rank lo,Rank hi);
    /*扩容*/
    void expand();
    /*压缩*/
    void shrink();
    /*选取最大元素*/
    Rank max(Rank lo,Rank hi);
    /*扫描交换*/
    bool bubble(Rank lo,Rank hi);
    /*冒泡排序*/
    void bubble_sort(Rank lo,Rank hi);
    /*选择排序*/
    void selection_sort(Rank lo,Rank hi);
    /*归并算法*/
    void merge(Rank lo,Rank mi,Rank hi);
    /*归并排序*/
    void merge_sort(Rank lo,Rank hi);
    /*轴点构造算法*/
    Rank partition(Rank lo,Rank hi);
    /*快速排序*/
    void quick_sort(Rank lo,Rank hi);
    /*堆排序*/
    void heap_sort(Rank lo,Rank hi);
public:
/*===========================================================================*/
    /*
     *构造函数
     */
    Vector(int c=DEFAULT_CAPACITY,int s=0,T v=0)
    {
        __elem=new T[__capacity=c];
        for(__size=0;__size<s;__elem[__size++]=v);
    }
    Vector(T const *A,Rank n)
    {
        copy_from(A,0,n);
    }
    Vector(T const *A,Rank lo,Rank hi)
    {
        copy_from(A,lo,hi);
    }
    Vector(Vector<T> const &V)
    {
        copy_from(V.__elem,0,V.__size);
    }
    Vector(Vector<T> const &V,Rank lo,Rank hi)
    {
        copy_from(V.__elem,lo,hi);

    }
/*===========================================================================*/
    /*析构函数*/
    ~Vector()
    {
        delete [] __elem;
    }
/*===========================================================================*/
    /*只读访问接口*/
    Rank size() const
    {
        return __size;
    }
    bool empty()
    {
        return !__size;
    }
    int disorder() const;
    Rank find(T const &e) const
    {
        return find(e,0,__size);
    }
    Rank find(T const &e,Rank lo,Rank hi) const;
    Rank search(T const &e) const
    {
        return (0>=__size)?(-1):search(e,0,__size);
    }
    Rank search(T const &e,Rank lo,Rank hi) const;
    bool equal(Vector<T> V) const;
/*===========================================================================*/
    /*可写访问接口*/
    T& operator [](Rank r) const;
    Vector<T>& operator=(Vector<T> const&);
    bool operator==(Vector<T> V) const;
    T remove(Rank r);
    int remove(Rank lo, Rank hi);
    Rank insert(Rank r,T const &e);
    Rank insert(T const &e)
    {
        return insert(__size,e);
    }
    void sort(Rank lo,Rank hi);
    void sort()
    {
        sort(0,__size);
    }
    void unsort(Rank lo,Rank hi)
    void unsort()
    {
        sort(0,__size);
    }
    int uniquify();
    int d_duplicate();
/*===========================================================================*/
    /*遍历*/
    void traverse(void (*)(T&));
    template <typename VST> void traverse(VST &);
};

template<typename T>
void Vector<T>::copy_from(T const* A,Rank lo,Rank hi)
{
    __elem=new T[__capacity=(hi-lo)*2];
    __size=0;
    while(lo<hi){
        __elem[size++]=A[lo++];
    }
}
/*重载赋值(=)运算符*/
template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const& V)
{
    if(__elem){
        delete [] __elem;
    }
    copy_from(V.__elem,0,V.size);
    return *this;
}
/*数组扩容*/
template<typename T>
void Vector<T>::expand()
{
    if(__size<__capacity){
        return;
    }
    /*不低于最低容量*/
    __capacity=std::max(__capacity,DEFAULT_CAPACITY);
    T* old=__elem;
    /*扩容至两倍*/
    __elem=new T[__capacity<<1];
    for(int i=0;i<__size;i++){
        __elem[i]=old[i];
    }
    delete [] old;
}

template<typename T>
void Vector<T>::shrink()
{
    /*不至于缩小至DEFAULT一下*/
    if(__size<DEFAULT_CAPACITY<<1){
        return;
    }
    /*factor=__size/__cap > 1/2
       when shrink factor > 1/4
       以25%的装载因子为界限
    */
    if(__size<<2>__capacity){ 
        return;
    }
    T *old=__elem;
    /*缩小至一半*/
    __elem=new T[__capacity>>=1];
    for(int i=0;i<__size;i++){
        __elem[i]=old[i];
    }
    delete [] old;
}
/*重载取下标运算符([])*/
template<typename T>
T& Vector<T>::operator[](Rank r) const
{
    return __elem[r];
}
/*洗牌算法(等概率)，向量整体置乱算法*/
template<typename T>
void Vector<T>::unsort(Rank lo,Rank hi)
{
    /*新的向量v[0,hi-lo)*/
    T *v=__elem+lo;
    for(Rank i=hi-lo;i>0;i--){
        std::swap(v[i-1],v[rand()%i]);
    }
}
/*判断是否相等*/
template<typename T>
bool Vector<T>::equal(Vector<T> V) const
{
    if(__size!=V.size()){
        return false;
    }
    for(int i=0;i<__size;i++){
        if(__elem[i]!=V.__elem[i]){
            return false;
        }
    }
    return true;
}
/*重载判断是否相等运算符(==)*/
template<typename T>
bool Vector<T>::operator==(Vector<T> V) const
{
    if(__size!=V.size()){
        return false;
    }
    for(int i=0;i<__size;i++){
        if(__elem[i]!=V.__elem[i]){
            return false;
        }
    }
    return true;
}
/*无序查找*/
template<typename T>
Rank Vector<T>::find(T const &e,Rank lo,Rank hi) const
{
    while((lo<hi--)&&(e!=__elem[i]));
    return (hi<lo)?(-1):hi;
}
template<typename T>
Rank Vector<T>::insert(Rank r,T const& e)
{
    /*第一步，是否需要扩容*/
    expand();
    for(int i=__size;i>r;i--){
        __elem[i]=__elem[i-1];
    }
    __elem[r]=e;
    __size++;
    return r;
}
template<typename T>
Rank Vector<T>::remove(Rank lo,Rank hi)
{
    if(lo==hi) return 0;
    while(hi<__size){
        __elem[lo++]=__elem[hi++];
    }
    /*[lo,...)丢弃，故__size=lo*/
    __size=lo;
    shrink();
    /*返回被删除的元素个数*/
    return hi-lo;
}
/*单个的删除会调用区间长为1的删除*/
template<typename T>
T Vector<T>::remove(Rank r)
{
    T tmp=__elem[r];
    remove(r,r+1);
    return tmp;
}
/*无序数组删除重复元素*/
template<typename T>
int Vector<T>::d_duplicate()
{
    int pre_size=__size;
    Rank i=1;
    while(i<__size){
        (find(__elem[i],0,i)<0)?(r++):remove(r);
    }
    return pre_size-__size;
}


