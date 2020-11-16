#pragma once

#include "ListNode.h"

template<typename T>class List{
private:
        int _size;
        p_list_node(T) header;
        p_list_node(T) trailer;//哨兵节点
protected:
        void init();//创建时初始化
        int clear();//清空
        void cp_nodes(p_list_node(T) p,int n);//复制自位置p起的n项
        void merge(p_list_node(T)&,int,List<T>&,p_list_node(T),int);//归并
        void merge_sort(p_list_node(T) &p,int n);
        void selection_sort(p_list_node(T) &p,int n);
        void insertion_sort(p_list_node(T) &p,int n);
        //从p开始的连续n个位置排序
public:
        List(){init();}
        List(List<T> const &L);//整体复制
        List(List<T> const &L,Rank r,int n);//复制列表L中自r起的n项
        List(p_list_node(T) p,int n);//复制自p起的n项
        ~List();//析构函数，释放包括哨兵节点在内的所有节点
//只读
        Rank size() const {return _size;}
        bool empty() const{return _size<=0;}
        T& operator[](Rank r) const;//重载按下标访问
        p_list_node(T) first() const { return header->succ;}
        p_list_node(T) last() const {return trailer->pred;}
        bool valid(p_list_node(T) p)
        {
                return p&&(trailer!=p)&&(header!=p);
        }
        p_list_node(T) find(T const &e){ return find(e,_size,trailer);}
        p_list_node(T) find(T const &e,int n,p_list_node(T) p)const ;
        p_list_node(T) search(T const &e) const ;
        p_list_node(T) search(T const &e,int n,p_list_node(T) p)const;

        p_list_node(T) max(p_list_node(T) ,int n);
        p_list_node(T) max(){return max(header->succ,_size);}

        p_list_node(T) insert_as_first(T const &e);//作为头节点插入
        p_list_node(T) insert_as_last(T const &e);//作为尾节点插入
        p_list_node(T) insert_after(p_list_node(T) p,T const &e);//p之后插入
        p_list_node(T) insert_before(p_list_node(T) p,T const &e);//p之前插入

        T remove(p_list_node(T) p);//移除节点p

        void merge(List<T> &L){merge(header->succ,_size,L,L.header->succ,L._size);}
        void sort(p_list_node(T) p,int n);
        void sort(){sort(first(),_size);}
        int dedup();//无序去重
        int uniq();//有序去重
        void reverse();//翻转列表

        void traverse(void (*)(T&));//函数指针遍历

        template<typename VST>
        void traverse(VST& );//函数对象遍历
};



