#include <cassert>
#include <iostream>
#include <vector>
#include "list.hpp"

using namespace std;
using ourstl::list;

template <class InputIterator1, class InputIterator2>
void
assert_range(InputIterator1 b1, InputIterator1 e1, InputIterator2 b2, InputIterator2 e2)
{
    int pos = 0;
    for (; b1 != e1 && b2 != e2; ++b1, ++b2, ++pos) {
        if (*b1 != *b2) {
            cerr << "Ranges differ at pos=" << pos << endl;
            assert(!"ranges differ");
        }
    }
    if (b1 != e1) {
        cerr << "Second range ends at pos=" << pos << endl;
        assert(!"range sizes differ");
    }
    if (b2 != e2) {
        cerr << "First range ends at pos=" << pos << endl;
        assert(!"range sizes differ");
    }
    /* ok, ranges are equal */
}

template <class InputIterator, class Cont>
void assert_range(InputIterator b, InputIterator e, const Cont &c)
{ return assert_range(b, e, c.begin(), c.end()); }

template <class InputIterator, class T>
void assert_range(InputIterator b, InputIterator e, std::initializer_list<T> il)
{ return assert_range(b, e, il.begin(), il.end()); }

template <class Cont1, class Cont2>
void assert_cont(const Cont1 &c1, const Cont2 &c2)
{ return assert_range(c1.begin(), c1.end(), c2.begin(), c2.end()); }

template <class Cont, class T>
void assert_cont(const Cont &c, std::initializer_list<T> il)
{ return assert_range(c.begin(), c.end(), il.begin(), il.end()); }

void
test_ints()
{
    list<int> ls;
    list<int>::iterator it;

    ls.push_back(0);
    ls.push_back(1);
    ls.push_back(2);
    ls.push_front(3);
    ls.push_back(4);
    assert_cont(ls, {3, 0, 1, 2, 4});

    it = ls.begin(); ++it; ++it;
    ls.insert(it, 123);
    assert_cont(ls, {3, 0, 123, 1, 2, 4});
    it = ls.erase(it);
    assert_cont(ls, {3, 0, 123, 2, 4});
    ls.insert(it, 124);
    assert_cont(ls, {3, 0, 123, 124, 2, 4});

    ls.reverse();
    assert_cont(ls, {4, 2, 124, 123, 0, 3});

    //some const_iterator testing
    const list<int> &cls = ls;
    assert_cont(cls, {4, 2, 124, 123, 0, 3});
    assert_cont(ls, cls);
    assert_cont(cls, ls);
    assert(ls.begin() == cls.begin());
    assert(cls.end() == ls.end());
    assert(ls.begin() != cls.end());
    assert(ls.end() != cls.begin());
}

struct A
{
    int _x;
    A(int x) : _x(x) { }
};

void
test_nonpod()
{
    list<A> ls;
    ls.push_back(A(42));
    ls.reverse();
    ls.erase(ls.begin());
    assert(ls.begin() == ls.end());
}

int
main()
{
    test_ints();
    test_nonpod();
    cerr << "OK" << endl;
}
