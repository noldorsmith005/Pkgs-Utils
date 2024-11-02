#include <iostream>
#include <string>

using namespace std;

template <class T>


struct List {
    private:
        int curr_index; 
        int size;
        T *backing;


    public:
        List() {
            curr_index = 0;
            size = 10;
            backing = new T[size];
        }

        ~List() {
            delete[] backing;
            backing = nullptr;
        }


        int len() {
            return curr_index;
        }

        void print() {
            cout << "\n[";
            for (int i = 0; i < curr_index; i++) {
                cout << backing[i];
                if ((i + 1) < curr_index) {
                    cout << ", ";
                }
            }
            cout << "]\n";
        }

        void append(T item) {
            if ((curr_index + 1) < size) {
                backing[curr_index] = item;
            }
            else {
                size = (size * 2);
                T old_array[curr_index];
                for (int i = 0; i < curr_index; i++) {
                    old_array[i] = backing[i];
                }
                backing = new T[size];
                for (int c = 0; c < curr_index; c++) {
                    backing[c] = old_array[c];
                }
                backing[curr_index] = item;
            }
            curr_index += 1;
        }

        void remove(int idx) {
            if (idx < curr_index) {
                for (int i = idx; i < curr_index; i++) {
                    backing[i] = backing[(i + 1)];
                }
                curr_index -= 1;
            }
            else {
                throw invalid_argument("Index out of bounds. ");
            }
        }

        int find(T item) {
            for (int i = 0; i < curr_index; i++) {
                if (backing[i] == item) {
                    return i;
                }
            }
            return -1;
        }

        T get(int idx) {
            if (idx < curr_index) {
                return backing[idx];
            }
            else {
                throw invalid_argument("Index out of bounds. ");
            }
        }
};