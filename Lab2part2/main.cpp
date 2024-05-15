#include <iostream>

#include "hash_map.h"
// #include "hash_list.h"


int main() {
    //std::cout << "hello\n";
    hash_map<int, float> map1 = hash_map<int, float>(5, 1, 0.5);
    for(int i = 0; i < 10; i++) {
        map1.insert(i,i);
    }
    std::cout << "hello\n";
}