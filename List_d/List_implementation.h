#pragma once

#include "List.h"

template<typename T>void List<T>::init()
{
        header = new ListNode<T>;
        trailer=new ListNode<T>;
        header->succ=trailer;
        header->pred=NULL;
        trailer->pred=header;
        trailer->succ=NULL;
        _size=0;
}

template<typename T>T List<T>::remove(ListNode<T> *p)
{
        T val=p->data;
        p->pred->succ=p->succ;
        p->succ->pred=p->pred;
        delete p;
        --_size;
        return val;
}

template<typename T>int List<T>::clear()
{
        int old_size=_size;
        while (_size>0)remove(header->succ);
        return old_size;
}

