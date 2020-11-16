#pragma once

#include "ListNode_implementation.h"
typedef int Rank;//按秩访问
#define p_list_node(T) ListNode<T>*

template<typename T>class ListNode{
        T data;
        p_list_node(T) pred;//前驱节点
        p_list_node(T) succ;//后继节点
public:
        ListNode()= default;
        explicit ListNode(T e,p_list_node(T) p=NULL,p_list_node(T) s=NULL)
        :data(e),pred(p),succ(s){}

        p_list_node(T) insert_as_pred(T const &e);
        p_list_node(T) insert_as_succ(T const &e);
};

template<typename T>p_list_node(T) ListNode<T>::insert_as_pred(const T &e)
{
        p_list_node(T) x=new ListNode(e,pred,this);
        pred->succ=x;
        this->pred=x;
        return x;
}
template<typename T>p_list_node(T) ListNode<T>::insert_as_succ(const T &e)
{
        p_list_node(T) x=new ListNode(e,this,succ);
        succ->pred=x;
        this->succ=x;
        return x;
}

