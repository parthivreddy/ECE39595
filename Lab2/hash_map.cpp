#include "hash_map.h"

hash_map::hash_map(size_t capacity) {
    _size = 0;
    _capacity = capacity;
    _head = new hash_list[capacity];
}

hash_map::hash_map(const hash_map &other) {
    if(other._head == NULL) {
        _capacity = 0;
        _size = 0;
        _head = NULL;
        return;
    }
    _capacity = other._capacity;
    _size = other._size;
    _head = new hash_list[other._capacity];
    for(int i = 0; i < other._capacity; i++) {
        _head[i] = other._head[i];
    }
}

hash_map &hash_map::operator=(const hash_map &other) {
    if(this == &other) return *this;
    hash_map temp = other;
    std::swap(this->_size, temp._size);
    std::swap(this->_head, temp._head);
    std::swap(this->_capacity, temp._capacity);
    return *this;
}

void hash_map::insert(int key, float value) {
    int bin = key % _capacity;
    if(_head[bin].insertBool(key, value)) {
        _size++;
    }
}

std::optional<float> hash_map::get_value(int key) const {
    int bin = key % _capacity;
    return _head[bin].get_value(key);
}

bool hash_map::remove(int key) {
    int bin = key % _capacity;
    if(_head[bin].remove(key)) {
        _size--;
        return true;
    }
    return false;

}

size_t hash_map::get_size() const {
    return _size;
}

size_t hash_map::get_capacity() const {
    return _capacity;
}

void hash_map::get_all_keys(int * keys) {
    int indexCounter = 0;
    for(int i = 0; i < _capacity; i++) {
        _head[i].reset_iter();
        while(!_head[i].iter_at_end()) {
            keys[indexCounter] = _head[i].get_iter_key();
            _head[i].increment_iter();
            indexCounter++;
        }
    }
}

void hash_map::get_bucket_sizes(size_t * buckets) {
    for(int i = 0; i < _capacity; i++) {
        buckets[i] = _head[i].get_size();
    }
}

hash_map::~hash_map() {
    for(int i = 0; i < _capacity; i++) {
        _head[i].~hash_list();
    }
    delete[] _head;
}