#include <iostream>
#include <string>

using namespace std;


template <typename K, typename V>

struct Map {
    private:
        // Key Value Pair Structure //
        template <typename T = K, typename D = V>

        struct KVP {
            K key;
            V value;

            KVP(const K &key, const V &value) {
                this->key = key;
                this->value = value;
            }
        };


        // Chain Structure For Collision Handling //
        template <typename T = K, typename D = V> 

        struct Chain {
            private:
                int curr_index; 
                int size;
                KVP<K, V> **backing;


            public:
                Chain() {
                    curr_index = 0;
                    size = 10;
                    backing = new KVP<K, V>*[size];
                    for (int i = 0; i < size; i++) {
                        backing[i] = nullptr;
                    }
                }

                int len() {
                    return curr_index;
                }

                void append(KVP<K, V> item) {
                    if ((curr_index + 1) < size) {
                        KVP<K, V> *new_item = new KVP<K, V>(item.key, item.value);
                        backing[curr_index] = new_item;
                    }
                    else {
                        size = (size * 2);
                        KVP<K, V> *old_array[curr_index];
                        for (int i = 0; i < curr_index; i++) {
                            old_array[i] = backing[i];
                        }
                        backing = new KVP<K, V>*[size];
                        for (int c = 0; c < curr_index; c++) {
                            backing[c] = old_array[c];
                        }
                        KVP<K, V> *new_item = new KVP<K, V>(item.key, item.value);
                        backing[curr_index] = new_item;
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

                int find(K item) {
                    for (int i = 0; i < curr_index; i++) {
                        KVP<K, V> kvp = *backing[i];
                        if (kvp.key == item) {
                            return i;
                        }
                    }
                    return -1;
                }

                KVP<K, V> get(int idx) {
                    if (idx < curr_index) {
                        return *backing[idx];
                    }
                    else {
                        throw invalid_argument("Index out of bounds. ");
                    }
                }
        };


    // Main //
        int size;
        int filled;
        double max_density;
        Chain<K, V> **backing;

        int hash(string key) {
            int hash_val = 0;
            for(int i = 0; i < (int)key.length(); i++) {
                int curr_char = key.at(i);
                hash_val = (hash_val * 19 + curr_char) % size;
            }
            return hash_val;
        }

        int hash(int key) {
            int hash_val = 0;
            hash_val = key % size;
            return hash_val;
        }

        void rehash() {
            int len = size;
            size = (size * 2);
            filled = 0;
            Chain<K, V> **old_map = backing;
            backing = new Chain<K, V>*[size];
            for (int i = 0; i < len; i++) {
                if (old_map[i] != nullptr) {
                    Chain<K, V> chain = *old_map[i];
                    for (int c = 0; c < chain.len(); c++) {
                        KVP<K, V> item = chain.get(c);
                        insert(item.key, item.value);
                    }
                }
            }
        }

    public:
        Map() {
            size = 50;
            filled = 0;
            max_density = 0.5;
            backing = new Chain<K, V>*[size];
            for (int i = 0; i < size; i++) {
                backing[i] = nullptr;
            }
        }

        ~Map() {
            for (int i = 0; i < size; i++) {
                if (backing[i] != nullptr) {
                    delete backing[i];
                }
            }
            delete[] backing;
            backing = nullptr;
        }

        void print() {
            cout << "{\n";
            for (int i = 0; i < size; i++) {
                if (backing[i] != nullptr) {
                    Chain<K, V> chain = *backing[i];
                    for (int c = 0; c < chain.len(); c++) {
                        KVP<K, V> item = chain.get(c);
                        cout << "   {" << item.key << ", " << item.value << "}" << "\n";
                    }
                }
            }
            cout << "}\n\n";
            // Density output for debugging:
            // cout << "Density: " << filled << "/" << size;
        }

        void insert(const K key, const V value) {
            double density = (double)filled / (double)size;
            if (density > max_density) {
                rehash();
            }
            int index = hash(key);
            KVP<K, V> new_pair(key, value);
            Chain<K, V> *new_chain = new Chain<K, V>;
            if (backing[index] == nullptr) {
                (*new_chain).append(new_pair);
                backing[index] = new_chain;
            }
            else {
                Chain<K, V> old_chain = *backing[index];
                int idx = old_chain.find(key);
                if (idx != -1) {
                    old_chain.remove(idx);
                }
                for (int i = 0; i < old_chain.len(); i++) {
                    KVP<K, V> item = old_chain.get(i);
                    (*new_chain).append(item);
                }
                (*new_chain).append(new_pair);
                backing[index] = new_chain;
            }
            filled += 1;
        }

        void remove(K key) {
            for (int i = 0; i < size; i++) {
                if (backing[i] != nullptr) {
                    Chain<K, V> chain = *backing[i];
                    int idx = chain.find(key);
                    if (idx != -1) {
                        chain.remove(idx);
                    }
                    *backing[i] = chain;
                }
            }
            filled -= 1;
        }

        V get(K key) {
            for (int i = 0; i < size; i++) {
                if (backing[i] != nullptr) {
                    Chain<K, V> chain = *backing[i];
                    for (int c = 0; c < chain.len(); c++) {
                        KVP<K, V> item = chain.get(c);
                        if (item.key == key) {
                            return item.value;
                        }
                    }
                }
            }
            throw invalid_argument("Key not found. ");
        }
};