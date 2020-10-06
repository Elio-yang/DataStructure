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
/*===========================================================================*/
    /*可写访问接口*/
    T& operator [](Rank r) const;
    Vector<T>& operator=(Vector<T> const&);
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
    int deduplicate();
    int uniquify();
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

template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const& V)
{
    if(__elem){
        delete [] __elem;
    }
    copy_from(V.__elem,0,V.size);
    return *this;
}

template<typename T>
void Vector<T>::expand()
{
    if(__size<__capacity){
        return;
    }
    __capacity=std::max(__capacity,DEFAULT_CAPACITY);
    T* old=__elem;
    __elem=new T[__capacity<<1];
    for(int i=0;i<__size;i++){
        __elem[i]=old[i];
    }
    delete [] old;
}

template<typename T>
void Vector<T>::shrink()
{
    if(__size<DEFAULT_CAPACITY<<1){
        return;
    }
    if(__size<<2>__capacity){
        return;
    }
    T *old=__elem;
    __elem=new T[__capacity>>=1];
    for(int i=0;i<__size;i++){
        __elem[i]=old[i];
    }
    delete [] old;
}

template<typename T>
T& Vector<T>::operator[](Rank r) const
{
    return __elem[r];
}
