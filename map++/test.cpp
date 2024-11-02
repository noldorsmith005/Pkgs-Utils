#include <iostream>
#include <string>
#include "./map.hh"
#include "../list++/list.hh"

using namespace std;



int main() {
    Map<int, int> map;

    // map.insert("test1", 0);
    // map.insert("test2", 3);
    // map.insert("test3", 5);
    // map.insert("test4", 7);
    // map.insert("test5", 9);
    // map.insert("testrehash", 11);
    // map.print();
    // int value = map.get("test2");
    // cout << "\n" << "value of 'test2': " << value << "\n";
    // map.remove("test2");
    // map.print();

    // map.insert(1, 2);
    // map.insert(3, 5);
    // map.insert(11, 1);
    // map.print();
    // map.insert(11, 11);
    // map.print();
    
    for (int i = 0; i < 1000000; i++) {
        int key = i;
        int value = rand()%100;
        map.insert(key, value);
    }
    map.print();

    /*
        Time to insert and print 1,000,000 items at size(0)=50 and max_density=0.5:
            ~0.81s user
    */
}
