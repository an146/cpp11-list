#include <cassert>
#include <iostream>
#include <vector>
#include "list.hpp"

using namespace std;
using ourstl::list;

template <class InputIterator1, class InputIterator2>
void
assert_equal_ranges(InputIterator1 b1, InputIterator1 e1, InputIterator2 b2, InputIterator2 e2)
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

template <class InputIterator, class T>
void
assert_range(InputIterator b, InputIterator e, std::initializer_list<T> expect)
{
    assert_equal_ranges(b, e, expect.begin(), expect.end());
}

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
    assert_range(ls.begin(), ls.end(), {3, 0, 1, 2, 4});

    it = ls.begin(); ++it; ++it;
    ls.insert(it, 123);
    assert_range(ls.begin(), ls.end(), {3, 0, 123, 1, 2, 4});
    it = ls.erase(it);
    assert_range(ls.begin(), ls.end(), {3, 0, 123, 2, 4});
    ls.insert(it, 124);
    assert_range(ls.begin(), ls.end(), {3, 0, 123, 124, 2, 4});

    ls.reverse();
    assert_range(ls.begin(), ls.end(), {4, 2, 124, 123, 0, 3});
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
