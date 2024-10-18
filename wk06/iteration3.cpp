/**
 * iteration3.cc
 *
 * Print beginning half of a list
 */

/**
 * DO NOT ADD ANY INCLUDES!!
 */

#include "iteration3.hh"
using namespace std;


void printHalf(const list<int>& lst)
{
    int count=0;
    int halfsize = lst.size() / 2;
        for (auto it = lst.begin(); it != lst.end() && count < halfsize; ++it) {
            cout << *it;
            if (next(it) != lst.end() && count < halfsize - 1) {
                cout << " ";
       }
        count++;
    }
    cout << endl;
}
