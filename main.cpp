#include <iostream>
#include <cstdlib>
#include <ctime>
#include "AVL.h"
#include "BSTROOT.h"
#include "BSTLEAF.h"
#include "BSTRAND.h"
using namespace std;
using namespace cop3530;


bool comes_before(const int & a, const int & b){
    return ( a < b);
}

bool equals(const int & a, const int & b){
    return ( a == b);
}


int main(void) {

    srand(time(nullptr));

    AVL<int,int,comes_before,equals> map;

    map.insert(1, 21);

    map.insert(2, 22);

    AVL<int,int,comes_before,equals> map_1 = map;

    cout << "Key 2 contains: " << map.lookup(2) << endl;

    map.insert(3, 23);

    AVL<int,int,comes_before,equals> const const_map = map;

    map.print_tree();

    cout << "Key 3 contains: " << map.lookup(3) << endl;

    cout << "Original TreeMap contains key 3?: " << map.contains(3) << endl;

    cout << "Copied TreeMap contains key 3?: " << map_1.contains(3) << endl;

    map_1 = map;

    cout << "Re-assigned TreeMap contains key 3?: " << map_1.contains(3) << endl;

    AVL<int,int,comes_before,equals> map_2 = std::move(map_1);

    cout << "map_2 contains key 3?: " << map_2.contains(3) << endl;

    map_1.insert(4, 5);

    map_2 = std::move(map_1);

    cout << "map_2 contains key 4?: " << map_2.contains(4) << endl;

    cout << "map_1 contains key 4?: " << map_1.contains(4) << endl;

    map.remove(2);

    cout << "Key 1 contains: " << map.lookup(1) << endl;

    cout << "Is empty? " << map.is_empty() << endl;

    cout << "Is full? " << map.is_full() << endl;

    cout << "Size of map: " << map.size() << endl;

    cout << "Height: " << map.height() << endl;

    cout << "BF: " << map.balance() << endl;

    map.clear();

    cout << "Is empty now? " << map.is_empty() << endl;

    map.insert(11, 10);

    cout << "Size now: " << map.size() << endl;

    return 0;
}