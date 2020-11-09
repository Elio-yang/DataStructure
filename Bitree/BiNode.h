#pragma once
#include "Implementation.h"


#define pNode(T) BiNode<T>*
#define stature(p) ((p)?(p)->height:-1)

template<typename T>
class BiNode{
        T val;
        int height;
        pNode(T) lc;
        pNode(T) rc;
        pNode(T) parent;
/*构造函数*/
        BiNode(): parent(NULL), lc(NULL), rc(NULL), height(0){}
        explicit BiNode(T e,pNode(T) p,pNode(T) lc=NULL,pNode(T) rc=NULL,int h=0):
                val(e), height(h), lc(NULL), rc(NULL), parent(p){ }
/*接口操作*/
        int size();
        pNode(T) insertLC(T const &e);
        pNode(T) insertRC(T const &e);
        pNode(T) succ();/*当前节点的后缀*/
        template <typename VST> void travLevel ( VST& );
        template <typename VST> void travPre ( VST& );
        template <typename VST> void travIn ( VST& );
        template <typename VST> void travPost ( VST& );
        bool operator== (BiNode const &bn) {return this->val==bn.val;}
        bool operator< (BiNode const &bn) {return this->val<bn.val;}
        bool operator> (BiNode const &bn) {return this->val>bn.val;}
        bool operator>=(BiNode const &bn) {return this->val>=bn.val;}
        bool operator<=(BiNode const &bn) {return this->val<=bn.val;}
};


template<typename T>int BiNode<T>::size()
{
        int s=1;
        if(lc)s+=lc->size();
        if(rc)s+=rc->size();
        return s;
}

template<typename T>
pNode(T) BiNode<T>::insertLC(const T &e)
{
        return lc=new BiNode<T>(e, this);
}

template<typename T>
pNode(T) BiNode<T>::insertRC(const T &e)
{
        return rc=new BiNode<T>(e,this);
}

template<typename T>pNode(T) BiNode<T>::succ()
{

}

template<typename T>
template<typename VST>
void BiNode<T>::travPre(VST &visit)
{
        trav_pre_i(this,visit);
}
template<typename T,typename VST>
void trav_pre_i(pNode(T) x,VST& visit)
{
        if(!x) return;
        visit(x->val);
        trav_pre_i(x->lc,visit);
        trav_pre_i(x->rc,visit);
}



