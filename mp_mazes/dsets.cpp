/* Your code here! */
#include "dsets.h"
using namespace std;

void DisjointSets::addelements(int num) {
    for (int i = 0; i < num; i++) {
        _elements.push_back(-1);
    }
}

int DisjointSets::find(int elem) {
    if (_elements[elem] < 0) {
        return elem;
    } else {
        _elements[elem] = find(_elements[elem]);
        return _elements[elem];
    }
}

void DisjointSets::setunion(int a, int b) {
    if(find(a) == find(b)){
        return;
    }

    int newSize = _elements[find(a)] + _elements[find(b)];
    if(find(a) < find(b)){
        _elements[find(a)] = newSize;
        _elements[find(b)] = find(a);
    } else{
        _elements[find(b)] = newSize;
        _elements[find(a)] = find(b);
    }
}

int DisjointSets::size(int elem) {
    int s = -1 * _elements[find(elem)];
    return s;
}
