//
// Created by hussa on 7/29/2024.
//

#ifndef DS2_UNIONFIND_H
#define DS2_UNIONFIND_H
#include <memory>
#include "pair.h"
#define STARTSIZE 1000
template<class T>
class NodeFind{
public:
    T value;
    int key;
    int size;
    std::shared_ptr<NodeFind<T>>next;
    std::shared_ptr<NodeFind<T>>father;
    NodeFind()=default;
    NodeFind(T value,int key);
};
template<class T>
class hashTable{
    int fullSize;
    int size;
    pair<T> *arr;
    int hash(int key)const;
public:
    hashTable();
    void insert(int key,T vlaue);
    void resize();

};
template<class T>
class UnionFind{
    hashTable<T>hashed;

public:

};

///////NodeFind implementation
template<class T>
NodeFind<T>::NodeFind(T value, int key) {
    this->value=value;
    this->key=key;
    this->size=0;
    this->next= nullptr;
    this->father=this;
}




////////hashTable implementation
template<class T>
hashTable<T>::hashTable() {
    this->fullSize=STARTSIZE;
    this->size=0;
    this->arr=new pair<T>*[STARTSIZE];
}
template<class T>
int hashTable<T>::hash(int key) const {
    return key % this->fullSize;
}
template<class T>
void hashTable<T>::insert(int key,T value) {
    pair<T>toInsert=pair<T>(key,value);
    if(this->arr[hash(key)]== nullptr)
    {
        this->arr[hash(key)]=toInsert;
        return;
    }
    toInsert.next=this->arr[hash(key)];
    this->arr[hash(key)]=toInsert;
}
template<class T>
void hashTable<T>::resize() {
    hashTable<T>newHash;

}
#endif //DS2_UNIONFIND_H
