#include "./list.hh"

using namespace std;



int main() {
    List<int> list;
    for (int i = 0; i < 1000000; i++) {
        int random = rand()%10;
        list.append(random);
    }
    list.print();
    // list.append("hello world");
    // list.append("a");
    // list.append("e");
    // list.append("i");
    // list.append("o");
    // list.append("u");


    /*
        Time to insert and print 1,000,000 items at size(0)=10:
            -0.16s user
    */
}
