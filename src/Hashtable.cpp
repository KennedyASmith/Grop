/**
 * Hashtable.cpp
 *
 *      Implementation of Hashtable, using chaining.
 *      Interface mostly follows std::unordered_map
 *
 * Kennedy Smith
 *
 */
#include "Hashtable.h"
#include <iostream>
#include <vector>
#include <functional>
#include "Entry.h"

template <class Value>
Hashtable<Value>::Hashtable() : Hashtable(initial_capacity) {}

template <class Value>
Hashtable<Value>::Hashtable(size_t initial_capacity)
{
    this->current_size = 0;
    this->capacity = initial_capacity;
    this->data = new std::vector<KeyValue>[initial_capacity];
}

template <class Value>
Value *Hashtable<Value>::insert(const Key &key, const Value &to_insert) {
    size_t index = index_of(key); // Compute the hash index
    KeyValue *keyVal = nullptr;
    std::vector<KeyValue>& vec = this->data[index]; 
    // Get a reference to the vector at the specified index
    for (auto& kv : vec) {
        if (kv.key == key) {
            // Found an existing entry with the same key
            keyVal = &kv;
        }
    }

    if (keyVal != nullptr) { // The key already exists, update the value
        keyVal->val = to_insert;
    } else { // The key doesn't exist, insert a new entry at the head of the chain
        this->data[index].push_back(KeyValue(key, to_insert));
        this->current_size++; // Increment the size of the table
        if (load_factor() > max_load_factor) { // Check if we need to expand the table
            expand();
        }
    }
 
    return &(keyVal->val);
}

template <class Value>
void Hashtable<Value>::expand()
{
    size_t old_capacity = this->capacity;
    this->capacity *= 2;
    std::vector<KeyValue> *old_data = this->data;
    this->data = new std::vector<KeyValue>[this->capacity];
    out << "Old Cap " << old_capacity << " New Cap " << this->capacity << endl;
    // Rehash the old elements into the new table
    for (size_t i = 0; i < old_capacity; i++) {
        for (const KeyValue& keyVal : old_data[i]) {
            size_t index = index_of(keyVal.key);
            this->data[index].push_back(keyVal);
        }
    }
    delete[] old_data;
}

template <class Value>
Value &Hashtable<Value>::at(const Key &key)
{
    Value *to_return = find(key);
    if (to_return == nullptr)
    {
        throw std::runtime_error("Key not in table");
    }
    return *to_return;
}

template <class Value>
const Value &Hashtable<Value>::at(const Key &key) const
{
    const Value *to_return = find(key);
    if (to_return == nullptr)
    {
        throw std::runtime_error("Key not in table");
    }
    return *to_return;
}

template <class Value>
Value *Hashtable<Value>::find(const Key &key)
{
    size_t index = index_of(key);

    std::vector<KeyValue> &bucket = this->data[index];

    for (auto &keyVal : bucket)
    {
        if (keyVal.key == key)
        {
            return &keyVal.val;
        }
    }

    return nullptr;
}

template <class Value>
const Value *Hashtable<Value>::find(const Key &key) const
{
    size_t index = index_of(key);
    const std::vector<KeyValue> &bucket = this->data[index];
    for (auto &keyVal : bucket)
    {
        if (keyVal.key == key)
        {
            return &keyVal.val;
        }
    }
    return nullptr;
}

template <class Value>
Value &Hashtable<Value>::operator[](const Key &key)
{
    Value *found = find(key);
    if (found != nullptr)
    {
        return *found;
    }
    Value new_val{};
    Value &inserted = *insert(key, new_val);
    return inserted;
}

template <class Value>
size_t Hashtable<Value>::index_of(const Key &key) const
{
    return std::hash<Key>{}(key) % this->capacity;
}

template <class Value>
size_t Hashtable<Value>::size() const
{
    return this->current_size;
}

template <class Value>
double Hashtable<Value>::load_factor() const
{
    return (double)size() / (double)this->capacity;
}

// Explicit template specialization for "string"s
template class Hashtable<std::string>;

// Explicit template specialization for "Entry"s
#include "Entry.h"
template class Hashtable<std::vector<Entry>>;
