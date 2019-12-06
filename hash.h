//
// Created by Alan on 12/2/2019.
//

#ifndef CHEATERS_HASH_H
#define CHEATERS_HASH_H

#endif //CHEATERS_HASH_H

#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

//HashTable class
class HashTable {
    vector<int> arr[150001];
    int capacity;
    int size;
public:
    HashTable();
    unsigned int hash(string key);
    void insertNode(string key, int value);
    void deleteNode(string key);
    vector<int> find(string key);
};

