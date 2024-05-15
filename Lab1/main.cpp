#include <iostream>

#include "hash_list.h"

int trace_1();
int trace_2();
int trace_3();
int trace_4();
int trace_5();

void insertTest() {
    hash_list list;
    list.insert(1,1);
    if (list.get_value(1) != 1)
    {
        std::cout << "GET failed for key=1\n";
    }
    list.insert(1,11);
    if (list.get_value(1) != 11)
    {
        std::cout << "GET failed for key=1\n";
    }
}

void removeTest() {
    hash_list list;
    if(list.remove(1)) {
        std::cout << "Remove Succeeded when Not supposed to\n";
        exit(1);
    }
    list.insert(1,1);
    list.insert(2,2);
    list.insert(3,3);
    list.remove(1);
    if(list.get_value(1).has_value()) {
        std::cout << "Remove failed\n";
    }
}

void copyTest() {
  hash_list list;
//   list.insert(1,1);
//   list.insert(2,2);
//   list.insert(3,3);
  hash_list list2(list);
//   size_t size= list2.get_size();
//   if(size != 3) {
//     std::cout << "Not correct size\n";
//   }
//   for(int i = 0; i < (int)size; i++) {
//     if(list2.get_value(i+1) != list.get_value(i+1)) {
//       std::cout << "values are wrong\n";
//     }
//   }

}

void assignment() {
    hash_list list;
    list.insert(1,10);
    hash_list list2;
    list2 = list;
}

void deepShallowTest() {
  hash_list list;
  list.insert(1,1);
  hash_list list2(list);
  list.insert(1,11);
  if(list2.get_value(1) != 1) {
    std::cout << "Not supposed to change\n";
  }
}

#ifdef PART2 // Only test iterators in part 2
void iterator_example(hash_list &list)
{
    /** We have to reset the iterator before we use it */
    list.reset_iter();

    /** We want to iterate over all nodes, so keep iterating until we're at the end */
    while (!list.iter_at_end())
    {
        /** Get pointers to key/value pairs */
        std::optional<std::pair<const int *, float *>> node_values = list.get_iter_value();

        /** Increment the VALUE. Note that the key remains unchanged */
        (*node_values.value().second)++;

        std::cout << "Key: " << *node_values.value().first
                  << " and value: " << *node_values.value().second << std::endl;

        /** Go to the next element */
        list.increment_iter();
    }
}
#endif

int main(int argc, char *argv[])
{

#ifdef PART1
    hash_list list;
    // trace_1();
    // trace_2();
    // trace_3();
    // trace_4();
    // trace_5();
    // std::cout << "testing\n";
    // if (list.get_size() != 0)
    // {
    //     std::cout << "Invalid size" << std::endl;
    //     exit(1);
    // }

    // // list.insert(3, 3);
    // // list.insert(4, 4);
    // // list.insert(5, 5);
    // // list.insert(6, 6);
    // // list.insert(7,7);
    // // list.insert(7,11);
    // // list.remove(7);
    // // list.remove(3);
    // // std::cout << "bool:" << list.remove(3) << "\n";

    // if (list.get_size() != 4)
    // {
    //     std::cout << "Invalid size" << std::endl;
    //     exit(1);
    // }

    // if (!list.get_value(3).has_value())
    // {
    //     std::cout << "expected 3 to be in list but it wasn't" << std::endl;
    //     exit(1);
    // }

    // if (!list.remove(3))
    // {
    //     std::cout << "Failed to remove 3 from list" << std::endl;
    //     exit(1);
    // }

    // if (list.get_value(3).has_value())
    // {
    //     std::cout << "Unexpected 3 in list" << std::endl;
    //     exit(1);
    // }
    //std::cout << "DONE\n";
    //std::cout.flush();

#endif

#ifdef PART2
    //iterator_example(list);
    //unittest_main();
    copyTest();
    assignment();
    
#endif

}
