#include "BiNode.h"


template<typename T>
class BiTree {
protected:
        int _size;
        pNode(T)_root;

        virtual int updateH(pNode(T)x);

        void update_above(pNode(T)x);/*更新树的高度*/

public:
        BiTree() : _size(0), _root(NULL)
        {}

        ~BiTree()
        { if (_size > 0) remove(_root); }

        int size() const
        { return _size; };

        int get_height(pNode(T)x);

        pNode(T)insert_root(pNode(T)x, T const &e);

        pNode(T)insert_lc(pNode(T)x, T const &e);

        pNode(T)insert_rc(pNode(T)x, T const &e);

        pNode(T)attach_lc(pNode(T)x, BiTree<T> *&t);

        pNode(T)attach_rc(pNode(T)x, BiTree<T> *&t);

        /*操作器*/
        template<typename VST>
        void trav_pre(VST &visit)
        {
                if (_root) { _root->travPre(visit); }
        }

        template<typename VST>
        void trav_in(VST &visit)
        {
                if (_root) { _root->travIn(visit); }
        }

        template<typename VST>
        void trav_post(VST &visit)
        {
                if (_root) { _root->travPost(visit); }

        }

        template<typename VST>
        void trav_level(VST &visit)
        {
                if (_root) { _root->travLevel(visit); }
        }

        int remove(pNode(T)x);

        BiTree<T>*
};

template<typename T>
int BiTree<T>::get_height(pNode(T)x)
{
        int h_l;
        int h_r;
        int max_h;
        if (x) {
                h_l = get_height(x->lc);
                h_r = get_height(x->rc);
                max_h = max(h_l, h_r);
                return max_h + 1;
        } else {
                return -1;
        }
}

template<typename T>
int BiTree<T>::updateH(BiNode<T> *x)
{
        return x->height = 1 + max(stature(x->lc), stature(x->rc));
}

template<typename T>
void BiTree<T>::update_above(BiNode<T> *x)
{
        while (x) {
                updateH(x);
                x = x->parent;
        }
}

template<typename T>
pNode(T)BiTree<T>::insert_root(BiNode<T> *x, const T &e)
{
        _size = 1;
        return _root = new BiNode<T>(e);
}

template<typename T>
pNode(T)BiTree<T>::insert_lc(BiNode<T> *x, const T &e)
{
        ++_size;
        x->insertLC(e);
        update_above(x);
        return x->lc;
}

template<typename T>
pNode(T)BiTree<T>::insert_rc(BiNode<T> *x, const T &e)
{
        ++_size;
        x->insertRC(e);
        update_above(x);
        return x->rc;
}

template<typename T>
BiNode<T> *BiTree<T>::attach_lc(BiNode<T> *x, BiTree<T> *&t)
{
        x->lc = t->_root;
        if (x->lc) { x->lc->parent = x; }
        _size += t->_size;
        update_above(x);
        t->_root = nullptr;
        t->_size = 0;
        release(t);
        t = nullptr;
        return x;
}

template<typename T>
BiNode<T> *BiTree<T>::attach_rc(BiNode<T> *x, BiTree<T> *&t)
{
        x->rc = t->_root;
        if (x->rc) { x->rc->parent = x; }
        _size += t->_size;
        update_above(x);
        t->_root = nullptr;
        t->_size = 0;
        release(t);
        t = nullptr;
        return x;
}

template<typename T>
int BiTree<T>::remove(pNode(T)x)
{
        from_parent(*x) = nullptr;
        update_above(x->parent);
        int n = remove_at(x);
        _size -= n;
        return n;
}

template<typename T>
static int remove_at(pNode(T)x)
{
        if (!x) { return 0; }
        int n = 1 + remove_at(x->lc) + remove_at(x->rc);
        release(x->data);/*考虑非基本类型*/
        release(x);
        return n;
}

