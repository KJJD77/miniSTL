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
        explicit HashNode(const Key &key) : key(key), value() {}

        HashNode(const Key &key, const Value &value) : key(key), value(value) {}

        bool operator==(const HashNode &other)const
        {
            return other.key == key;
        }

        bool operator!=(const HashNode &other)const
        {
            return other.key != key;
        }

        bool operator<(const HashNode &other)const
        {
            return key < other.key;
        }

        bool operator>(const HashNode &other)const
        {
            return key > other.key;
        }

        bool operator==(const Key &key_)const
        {
            return key == key_;
        }

        void print() const
        {
            std::cout << key << " " << value << "\n";
        }
    };

    using Bucket = std::list<HashNode>;
    std::vector<Bucket> buckets;
    Hash hashFunc;
    size_t tableSize;
    size_t numElements;

    double maxLoadFactor = 0.75;

    size_t hash(const Key &key)
    {
        return hashFunc(key);
    }

    void rehash(size_t newSize)
    {
        std::vector<Bucket> newBuckets(newSize);
        for (auto &bucket : buckets)
        {
            for (auto &hashNode : bucket)
            {
                size_t newIndex = hashFunc(hashNode.key) % newSize;
                newBuckets[newIndex].push_back(hashNode);
            }
        }
        buckets = std::move(newBuckets);
        tableSize = newSize;
    }

public:
    myHashTable(size_t size = 10, const Hash &hashFunc = Hash()) : buckets(size), hashFunc(hashFunc), numElements(0), tableSize(size) {}

    void insert(const Key &key, const Value &value)
    {
        if ((numElements + 1) > tableSize * maxLoadFactor)
        {
            if (tableSize == 0)
                tableSize = 1;
            rehash(2 * tableSize);
        }
        size_t index = hash(key) % tableSize;
        std::list<HashNode> &bucket = buckets[index];
        auto it = find(bucket.begin(), bucket.end(), key);
        if (it == bucket.end())
        {
            bucket.push_back(HashNode(key, value));
            numElements++;
        }
    }

    void insertKey(const Key &key)
    {
        insert(key, Value{});
    }

    void erase(const Key &key)
    {
        size_t index = hash(key) % tableSize;
        std::list<HashNode> &bucket = buckets[index];
        auto it = find(bucket.begin(), bucket.end(), key);
        if (it != bucket.end())
        {
            bucket.erase(it);
            numElements--;
        }
    }

    Value *find(const Key &key)
    {
        size_t index = hash(key) % tableSize;
        std::list<HashNode> &bucket = buckets[index];
        auto it = find(bucket.begin(), bucket.end(), key);
        if (it != bucket.end())
            return &it->value;
        return nullptr;
    }

    size_t size()
    {
        return numElements;
    }

    void clear()
    {
        this->numElements = 0;
        this->buckets.clear();
        this->tableSize = 0;
    }

    void print()
    {
        for (size_t i = 0; i < buckets.size(); ++i)
        {
            for (const HashNode &element : buckets[i])
            {
                element.print();
            }
        }
        std::cout << std::endl;
    }
};

#endif