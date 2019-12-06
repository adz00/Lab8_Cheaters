#include "hash.h"

HashTable::HashTable() {
    size = 0;
    capacity = 150001;
    for (int i=0; i<150001; i++) {
        vector<int> x;
        arr[i] = x;
    }
}

unsigned int HashTable::hash(string key) {
    unsigned int index = 0;
    int p = 31;

    for (int i=0; i<key.length(); i++) {
        if ((key[i]>0x40 && key[i]<0x5B) || (key[i]>0x60 && key[i]<0x7B) || (key[i]>0x2F && key[i]<0x3A))
        index = (index*p) + key[i];
    }

    return index%capacity;
}

void HashTable::insertNode(string key, int value) {
    int hashIndex = hash(key);
    arr[hashIndex].push_back(value);
    size++;
}

void HashTable::deleteNode(string key) {
    return;
}

vector<int> HashTable::find(string key) {
    int hashIndex = hash(key);
    return arr[hashIndex];
}



