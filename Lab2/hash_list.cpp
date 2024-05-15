#include "hash_list.h"
#include <iostream>

hash_list::hash_list() {
    size = 0;
    head = NULL;
    iter_ptr = NULL;
}

/**-----------------------------------------------------------------------------------
 * START Part 1
 *------------------------------------------------------------------------------------*/

void hash_list::insert(int key, float value) {
    
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

bool hash_list::insertBool(int key, float value) {
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

std::optional<float> hash_list::get_value(int key) const { 
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

bool hash_list::remove(int key) { 
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

size_t hash_list::get_size() const { 
    return size;
}

hash_list::~hash_list() {
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

void hash_list::printList() {
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

hash_list::hash_list(const hash_list &other) {
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

hash_list &hash_list::operator=(const hash_list &other) { 
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

void hash_list::reset_iter() {
    iter_ptr = head;
}


void hash_list::increment_iter() {
    if(iter_ptr != NULL) {
        iter_ptr = iter_ptr->next;
    }
}


std::optional<std::pair<const int *, float *>> hash_list::get_iter_value() { 
    if(iter_ptr != NULL) {
        return std::pair(&(iter_ptr->key), &(iter_ptr->value));
    }
    return std::nullopt; 
}

int hash_list::get_iter_key() {
    if(iter_ptr != NULL) {
        return iter_ptr->key;
    }
    return 0;
}
bool hash_list::iter_at_end() { 
    return (iter_ptr == NULL);
}
/**-----------------------------------------------------------------------------------
 * END Part 2
 *------------------------------------------------------------------------------------*/
