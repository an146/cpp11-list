#include <chrono>
#include <iostream>
#include <iomanip>
#include <list>
#include "list.hpp"
#include "test.hpp"

using namespace std;
using namespace ourstd::test;

void
test_ints()
{
    ourstd::list<int> ls;
    ourstd::list<int>::iterator it;

    ls.push_back(0);
    ls.push_back(1);
    ls.push_back(2);
    ls.push_front(3);
    ls.push_back(4);
    assert_contents(ls, {3, 0, 1, 2, 4});

    it = next(ls.begin(), 2);
    ls.insert(it, 123);
    assert_contents(ls, {3, 0, 123, 1, 2, 4});
    it = ls.erase(it);
    assert_contents(ls, {3, 0, 123, 2, 4});
    ls.insert(it, 124);
    assert_contents(ls, {3, 0, 123, 124, 2, 4});

    ls.reverse();
    assert_contents(ls, {4, 2, 124, 123, 0, 3});

    //some const_iterator testing
    const ourstd::list<int> &cls = ls;
    assert_contents(cls, {4, 2, 124, 123, 0, 3});
    assert_contents(ls, cls);
    assert_contents(cls, ls);
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
    ourstd::list<A> ls;
    ls.push_back(A(42));
    ls.reverse();
    ls.erase(ls.begin());
    assert(ls.begin() == ls.end());
}

class benchmark
{
    std::chrono::time_point<std::chrono::system_clock> start, last;
public:
    explicit benchmark(string bench_desc) : start(std::chrono::system_clock::now()), last(start)
    {
        using namespace std;
        cout << "=== Benchmarking: " << bench_desc << endl;
    }
    ~benchmark()
    {
        last = start;
        mark("Total elapsed");
    }
    void mark(string desc)
    {
        using namespace std;
        using namespace std::chrono;
        auto mrk = system_clock::now();
        int elapsed = duration_cast<milliseconds>(mrk-last).count();
        last = mrk;
        cout << fixed << setprecision(3);
        cout << desc << ": " << elapsed/1000.0f << "s" << endl;
    }
};

template <class L>
void
test_speed(string L_desc)
{
    const int Lists = 20;
    const int Elements = 1000000;

    benchmark bench(L_desc);
    L *ls = new L[Lists];
    for (int i = 0; i < Lists; i++) {
        L *l = &ls[i];
        for (int j = 0; j < Elements; j++) {
            l->push_back(j);
        }
    }
    bench.mark("create&push");
    delete[] ls;
    bench.mark("destroy");
}

int
main()
{
    test_ints();
    test_nonpod();
    test_speed<std::list<int> >("std::list<int>");
    test_speed<ourstd::list<int> >("ourstd::list<int>");
}
