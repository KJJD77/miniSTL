#ifndef MYHASHTABLE_H
#define MYHASHTABLE_H

#include <bits/stdc++.h>
template <typename Key, typename Value, typename Hash = std::hash<Key>>
class myHashTable
{

private:
    class HashNode
    {
    public:
        Key key;
        Value value;
        explicit HashNode(Key key) : key(key), value(){}
        
    }
};

#endif