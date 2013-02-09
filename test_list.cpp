#include <iostream>
//#include <list>
#include "list.hpp"
#include "test.hpp"

using namespace std;
using namespace ourstl::test;
using ourstl::list;

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
