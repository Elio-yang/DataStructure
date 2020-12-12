#include <string>
#include<cassert>
using namespace std;

typedef unsigned int  size_t;
template < class T>
class vector {
public:
        typedef T * iterator;

        vector();
        vector(int size, T const& a);
        vector(const vector<T> & a);
        ~vector();
        size_t size() const;
        size_t capacity() const;
        size_t max_capacity() const;
        void push_back(const T& val);
        void pop_back();
        T& operator[](int index);
        vector<T>& operator=(const vector<T>& a);
        bool empty() const;
        iterator begin() const;
        iterator end() const;
private:
        size_t  _size;
        size_t  _capacity;
        T*      _buf;
        const size_t _max_capacity = 65536;
};
template<class T>
vector<T>::vector()
{
        _size = 0;
        _buf = new T[1];
        _capacity = 1;
}

template<class T>
vector<T>::vector(int s, const T& a)
{
        if (s > _max_capacity) {
                s = _max_capacity;
        }
        _size = s;
        _capacity = 1;
        while (_capacity < _size) {
                _capacity *= 2;
        }
        _buf = new T[_capacity];
        for (size_t i = 0; i < _size; i++) {
                _buf[i] = a;
        }
}
template<class T>
vector<T>::vector(const vector<T> & a)
{
        _size = a._size;
        _capacity = a._capacity;
        _buf = new T[_capacity];
        for (size_t i = 0; i < _size; i++) {
                _buf[i] = a._buf[i];
        }
}
template<class T>
vector<T>::~vector()
{
        delete[] _buf;
}

template<class T>
size_t vector<T>::size() const
{
        return _size;
}

template<class T>
size_t vector<T>::capacity() const
{
        return _capacity;
}
template<class T>
size_t vector<T>::max_capacity() const
{
        return _max_capacity;
}
template<class T>
T& vector<T>::operator[](int index)
{
        assert(index >= 0 && index < _size);
        return _buf[index];
}

template<class T>
void vector<T>::push_back(const T& val)
{
        if (_size < _capacity) {
                _buf[_size] = val;
                _size++;
                return ;
        } else if (_size == _max_capacity) {
                return ;
        }
        _capacity *= 2;
        if (_capacity >= _max_capacity) {
                _capacity = _max_capacity;
        }
        T * tmp = new T[_capacity];
        for (size_t i = 0; i < _size; i++) {
                tmp[i] = _buf[i];
        }
        tmp[_size] = val;
        _size++;
        delete[] _buf;
        _buf = tmp;
}

template<class T>
void vector<T>::pop_back()
{
        assert(_size > 0);
        _size--;
}
template<class T>
bool vector<T>::empty() const
{
        if (_size == 0) {
                return true;
        }
        return false;
}
// 迭代器的实现
template<class T>
typename vector<T>::iterator vector<T>::begin() const
{
        return _buf;
}
template<class T>
typename vector<T>::iterator vector<T>::end() const
{
        return _buf + _size;
}
template<class T>
vector<T>& vector<T>::operator=(const vector<T> & a)
{
        if (this == &a) {
                return *this ;
        }
        delete[] _buf;
        _size = a._size;
        _capacity = a._capacity;
        _buf = new T[_capacity];
        for (size_t i = 0; i < _size; i++) {
                _buf[i] = a._buf[i];
        }
        return *this;
}

int main()
{
        int c = 20;
        vector<string> a;
        vector<string> b;
        for (int i = 0 ; i < 3; i++) {
                a.push_back("hello");
        }
        b = a;
        for (vector<string>::iterator it = b.begin(); it != b.end(); it++) {
                cout << *it << " " << endl;
        }
        return 0;
}