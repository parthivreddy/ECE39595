// #include "hash_map.h"
#include <algorithm>

template <typename K, typename V>
hash_map<K, V>::hash_map(size_t capacity, float upper_load_factor, float lower_load_factor) {
    _size = 0;
    _capacity = capacity;
    _head = new hash_list<K,V>[capacity];
    _upper_load_factor = upper_load_factor;
    _lower_load_factor = lower_load_factor;
}

template <typename K, typename V>
hash_map<K, V>::hash_map(const hash_map &other) {
    if(other._head == NULL) {
        _capacity = 0;
        _size = 0;
        _head = NULL;
        return;
    }
    _capacity = other._capacity;
    _size = other._size;
    _upper_load_factor = other._upper_load_factor;
    _lower_load_factor = other._lower_load_factor;
    _head = new hash_list<K,V>[other._capacity];
    for(size_t i = 0; i < other._capacity; i++) {
        _head[i] = other._head[i];
    }
}

template <typename K, typename V>
hash_map<K,V> &hash_map<K,V>::operator=(const hash_map &other) {
    if(this == &other) return *this;
    hash_map<K,V>temp = other;
    std::swap(this->_size, temp._size);
    std::swap(this->_head, temp._head);
    std::swap(this->_capacity, temp._capacity);
    std::swap(this->_upper_load_factor, temp._upper_load_factor);
    std::swap(this->_lower_load_factor, temp._lower_load_factor);
    return *this;
}

template <typename K, typename V>
void hash_map<K,V>::insert(K key, V value) {
    //std::cout << "inserting key: " << key << "and value: " << value << "\n";
    size_t bin = _hash(key) % _capacity;
    if(_head[bin].insertBool(key, value)) {
        _size++;
    }
    if(rehashBool()) {
        rehash();
    }
}

template <typename K, typename V>
bool hash_map<K,V>::rehashBool() {
    if(_size > _upper_load_factor * _capacity) {
        if(_capacity < _capacities[2]) {
            return true;
        }
    }
    else if(_size < _lower_load_factor * _capacity) {
        if(_capacity > _capacities[0]) {
            return true;
        }
    }

    return false;
}

template <typename K, typename V>
void hash_map<K,V>::rehash() {
    //int caplen = sizeof(_capacities) / sizeof(_capacities[0]);
    hash_list<K,V> * oldHead = _head; //oldHead will contain previous hashing
    size_t newCap;
    int capInd = 0;
    while(_capacities[capInd] <= _capacity) {
        capInd++; //finds first ind where capacity < newcap
    }

    if(_size > _upper_load_factor * _capacity) {
        //increase capacity
        newCap = _capacities[capInd];
    }
    else {
        if(_capacity == _capacities[capInd - 1]) {
            newCap = _capacities[capInd - 2];
        }
        else {
            newCap = _capacities[capInd - 1];
        }
    }
    _head = new hash_list<K,V>[newCap]; //new array for new num of buckets
    
    _size = 0;
    for(size_t i = 0; i < _capacity; i++) {
        oldHead[i].reset_iter();
        while(!oldHead[i].iter_at_end()) {
            std::optional<std::pair<const K *, V *>> tup = oldHead[i].get_iter_value();
            if(tup.has_value()) {
                K key = *(tup.value().first);
                V value = *(tup.value().second);
                size_t ind = _hash(key) % newCap;
                if(_head[ind].insertBool(key, value)) {
                    _size++;
                }
            }
            oldHead[i].increment_iter();
        }
    }
    _capacity = newCap;
    delete [] oldHead;
}


template <typename K, typename V>
std::optional<K> hash_map<K,V>::get_value(K key) const {
    size_t bin = _hash(key) % _capacity;
    return _head[bin].get_value(key);
}

template <typename K, typename V>
bool hash_map<K,V>::remove(K key) {
    //std::cout << "removing key: " << key << "\n";
    size_t bin = _hash(key) % _capacity;
    if(_head[bin].remove(key)) {
        _size--;
        if(rehashBool()) {
            rehash();
        }
        return true;
    }
    return false;

}

template <typename K, typename V>
size_t hash_map<K, V>::get_size() const {
    return _size;
}

template <typename K, typename V>
size_t hash_map<K,V>::get_capacity() const {
    return _capacity;
}

template <typename K, typename V>
void hash_map<K, V>::get_all_keys(K * keys) {
    int indexCounter = 0;
    for(size_t i = 0; i < _capacity; i++) {
        _head[i].reset_iter();
        while(!_head[i].iter_at_end()) {
            keys[indexCounter] = _head[i].get_iter_key();
            _head[i].increment_iter();
            indexCounter++;
        }
    }
}

template<typename K, typename V>
void hash_map<K, V>::get_all_sorted_keys(K * keys) {
    get_all_keys(keys);
    std::sort(keys, keys + _size);
}

template <typename K, typename V>
void hash_map<K, V>::get_bucket_sizes(size_t * buckets) {
    for(size_t i = 0; i < _capacity; i++) {
        buckets[i] = _head[i].get_size();
    }
}

template <typename K, typename V>
hash_map<K, V>::~hash_map() {
    for(size_t i = 0; i < _capacity; i++) {
        _head[i].~hash_list();
    }
    delete[] _head;
}