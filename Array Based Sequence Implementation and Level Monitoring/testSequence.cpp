#include"Sequence.h"
#include<cassert>
#include<iostream>
#include<string>
#include<cstddef>
#include<cstdlib>

int main()
{
    Sequence s, g;
    unsigned long x = 0;
    assert(s.empty() == true);
    assert(s.insert(0) == 0);
    assert(s.insert(1) == 1);
    assert(s.insert(1) == 1);
    assert(s.insert(1) == 1);
    assert(s.insert(2) == 4);
    assert(s.remove(1) == 3);

    assert(g.insert(0) == 0);
    assert(g.insert(1) == 1);
    assert(g.insert(1) == 1);
    assert(g.insert(1) == 1);
    assert(g.insert(2) == 4);
    s.swap(g);



    for (int i = 0; i < g.size(); i++)
    {
        g.get(i, x);
        std::cout << x << std::endl;
    }

    std::cout << "Passed all tests" << std::endl;

	return(0);
}