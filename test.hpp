#include <cassert>
#include <iostream>
#include <utility>

namespace ourstl {
namespace test {

template <class InputIterator1, class InputIterator2>
void
assert_range(InputIterator1 b1, InputIterator1 e1, InputIterator2 b2, InputIterator2 e2)
{
    using namespace std;

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
void assert_contents(const Cont1 &c1, const Cont2 &c2)
{ return assert_range(c1.begin(), c1.end(), c2.begin(), c2.end()); }

template <class Cont, class T>
void assert_contents(const Cont &c, std::initializer_list<T> il)
{ return assert_range(c.begin(), c.end(), il.begin(), il.end()); }

}
}
