// #include "hash_list.h"
#include <iostream>

template <typename T1, typename T2>
hash_list<T1, T2>::hash_list() {
    size = 0;
    head = NULL;
    iter_ptr = NULL;
}

/**-----------------------------------------------------------------------------------
 * START Part 1
 *------------------------------------------------------------------------------------*/

template <typename T1, typename T2>
void hash_list<T1, T2>::insert(T1 key, T2 value) {
    
    //std::cout << "Inserting key, value: " << key << ", " << value << "\n";
    if(head == NULL) {
        head = new node;
        head->key = key;
        head->value = value;
        head->next = NULL;
        size++;
        //printList();
        return;
    }
    node * currNode = head;

    while(currNode->next != NULL) {
        if(currNode->key == key) {
            currNode->value = value;
            //printList();
            return;
        }
        else {
            currNode = currNode->next;
        }
    }
    if(currNode->next == NULL) {
        if(currNode->key == key) {
            currNode->value = value;
        }
        else {
            node * newNode = new node;
            newNode->key = key;
            newNode->value = value;
            currNode->next = newNode;
            newNode->next = NULL;
            size = size + 1;
        }
    }
    //printList();

}

template <typename T1, typename T2>
bool hash_list<T1, T2>::insertBool(T1 key, T2 value) {
    if(head == NULL) {
        head = new node;
        head->key = key;
        head->value = value;
        head->next = NULL;
        size++;
        //printList();
        return true;
    }
    node * currNode = head;

    while(currNode->next != NULL) {
        if(currNode->key == key) {
            currNode->value = value;
            //printList();
            return false;
        }
        else {
            currNode = currNode->next;
        }
    }
    if(currNode->next == NULL) {
        if(currNode->key == key) {
            currNode->value = value;
            return false;
        }
        else {
            node * newNode = new node;
            newNode->key = key;
            newNode->value = value;
            currNode->next = newNode;
            newNode->next = NULL;
            size = size + 1;
            return true;
        }
    }
    //printList();
    return false;

}

template <typename T1, typename T2>
std::optional<T1> hash_list<T1, T2>::get_value(T2 key) const { 
    // if(key > (int) size) {
    //     return std::nullopt; 
    // }
    node * currNode = head;
    while(currNode != NULL) {
        if(currNode->key == key) {
            return currNode->value;
        }
        currNode = currNode->next;
    }
    return std::nullopt;
}

template <typename T1, typename T2>
bool hash_list<T1, T2>::remove(T1 key) { 
    //std::cout << "Remove: " << key << "\n";
    //printList();
    if(head == NULL) {
        //printList();
        return false;
    }
    if(head->key == key) {
        node * rem = head;
        head = head->next;
        delete rem;
        size--;
        //printList();
        return true;
    }
    node * currNode = head;
    node * prev = NULL;
    while(currNode != NULL) {
        if(currNode->key == key) {
            if(currNode == head) {
                head = head->next;
                delete currNode;
                size--;
                //printList();
                return true;
            }
            else {
                prev->next = currNode->next;
                delete currNode;
                size--;
                //printList();
                return true;
            }
        }
        else {
            prev = currNode;
            currNode = currNode->next;
        }
    }
    // std::cout << "Not in list\n";
    // printList();
    return false;

}


template <typename T1, typename T2>
size_t hash_list<T1, T2>::get_size() const { 
    return size;
}
template <typename T1, typename T2>
hash_list<T1, T2>::~hash_list() {
    node * curr = head;
    if(curr == NULL) {
        return;
    }
    node * next;
    while(curr != NULL) {
        next = curr->next;
        delete curr;
        curr = next;
    }
    head = NULL;
}

template <typename T1, typename T2>
void hash_list<T1, T2>::printList() {
    node * curr = head;
    std::cout << "\n----------\nPrinting\n";
    int i = 0;
    while(curr != NULL) {
        std::cout << "Node Num: " << i << "key, val: " << curr->key << ", " <<  curr->value << "\n";
        i++;
        curr = curr->next;
    }
    std::cout << "-----------\n";
    return;
}

/**-----------------------------------------------------------------------------------
 * END Part 1
 *------------------------------------------------------------------------------------*/


/**-----------------------------------------------------------------------------------
 * START Part 2
 *------------------------------------------------------------------------------------*/

template <typename T1, typename T2>
hash_list<T1, T2>::hash_list(const hash_list &other) {
    if(other.head != NULL) {
        head = new node;
        node * oldcurr = other.head;
        head->key = oldcurr->key;
        head->value = oldcurr->value;
        head->next = NULL;
        node * curr = head;
        size = other.size;
        iter_ptr = other.iter_ptr;
        while(oldcurr->next != NULL) {
            curr->next = new node;
            curr = curr->next;
            oldcurr = oldcurr->next;
            curr->key = oldcurr->key;
            curr->value = oldcurr->value;
        }
        curr->next = NULL;
    }
    else {
        size = 0;
        head = NULL;
        iter_ptr = NULL;
    }
}

template <typename T1, typename T2>
hash_list<T1,T2> &hash_list<T1, T2>::operator=(const hash_list &other) { 
    // this->size = other.size; 
    // this->iter_ptr = other.iter_ptr;
    if(this == &other) return *this;
    // node * curr = this->head;
    // node * temp = curr;
    // while(curr != NULL) {
    //     curr = curr->next;
    //     delete temp;
    //     temp = curr;
    // }
    hash_list temp = other;
    std::swap(this->size, temp.size);
    std::swap(this->head, temp.head);
    std::swap(this->iter_ptr, temp.iter_ptr);
    return *this;
}

template <typename T1, typename T2>
void hash_list<T1, T2>::reset_iter() {
    iter_ptr = head;
}


template <typename T1, typename T2>
void hash_list<T1, T2>::increment_iter() {
    if(iter_ptr != NULL) {
        iter_ptr = iter_ptr->next;
    }
}

template <typename T1, typename T2>
std::optional<std::pair<const T1 *, T2 *>> hash_list<T1, T2>::get_iter_value() { 
    if(iter_ptr != NULL) {
        return std::pair(&(iter_ptr->key), &(iter_ptr->value));
    }
    return std::nullopt; 
}

template <typename T1, typename T2>
T1 hash_list<T1, T2>::get_iter_key() {
    if(iter_ptr != NULL) {
        return iter_ptr->key;
    }
    return 0;
}

template <typename T1, typename T2>
bool hash_list<T1, T2>::iter_at_end() { 
    return (iter_ptr == NULL);
}
/**-----------------------------------------------------------------------------------
 * END Part 2
 *------------------------------------------------------------------------------------*/
