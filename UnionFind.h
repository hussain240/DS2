//
// Created by hussa on 7/29/2024.
//

#ifndef DS2_UNIONFIND_H
#define DS2_UNIONFIND_H
#define STARTSIZE 1000
#include "Fleet.h"
#include <memory>
template<class T>
class NodeHash{
public:
    T value;
    int key;
    int size;
    int fatherId;
    int rank;
    NodeHash<T>* next;
    NodeHash<T>* father;
    NodeHash()=default;
    NodeHash(int key,T value);
};




template<class T>
class hashTable{
    int fullSize;
    int size;
    NodeHash<T>* *arr;
    int hash(int key)const;
public:
    hashTable();
    ~hashTable();
    void insert(int key,T value);
    void resize();
    NodeHash<T>* find(int key)const;

};


class UnionFind{
    hashTable<std::shared_ptr<fleet>> values;
    //hashTable<T> lists;
void swap(int &a, int &b);
public:
    UnionFind()=default;
    ~UnionFind()=default;
    void makeSet(int key,std::shared_ptr<fleet> value);
    NodeHash<std::shared_ptr<fleet>>* find(int key);
    int findRank(int key);
    int Union(int key1,int key2);
    NodeHash<std::shared_ptr<fleet>>* findHash(int key)const;
};

///////NodeHash implementation
template<class T>
NodeHash<T>::NodeHash(int key,T value) {
    this->value=value;
    this->key=key;
    this->size=1;
    this->fatherId=key;
    this->rank=0;
    this->father= this;
    this->next= nullptr;
}



////////hashTable implementation
template<class T>
hashTable<T>::hashTable() {
    this->fullSize=STARTSIZE;
    this->size=0;
    this->arr=new NodeHash<T>*[STARTSIZE];
        for(int i=0;i<STARTSIZE;i++)
        {
            this->arr[i]= nullptr;
        }
}
template<class T>
hashTable<T>::~hashTable() {
    for (int i = 0; i < fullSize; i++) {
        NodeHash<T>* current = this->arr[i];
        while (current != nullptr) {
            NodeHash<T>* toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }
    delete[] this->arr;
}
template<class T>
int hashTable<T>::hash(int key) const {
    return key % this->fullSize;
}
template<class T>
void hashTable<T>::insert(int key,T value) {
    ////////need to do resize when full
    this->size++;
    if(this->size== this->fullSize)
    {
        this->resize();
    }
    if(this->arr== nullptr)
    {
        this->arr=new NodeHash<T>*[STARTSIZE];
        for(int i=0;i<STARTSIZE;i++)
        {
            this->arr[i]= nullptr;
        }
    }
    NodeHash<T> *toInsert=new NodeHash<T>(key,value);
    if(this->arr[hash(key)]== nullptr)
    {
        this->arr[hash(key)]=toInsert;
        return;
    }
    toInsert->next=this->arr[hash(key)];
    this->arr[hash(key)]=toInsert;
}
template<class T>
void hashTable<T>::resize() {
    int oldSize = this->fullSize;
    this->fullSize *= 2;
    NodeHash<T>** newArr = new NodeHash<T>*[this->fullSize];
    for (int i = 0; i < this->fullSize; i++) {
        newArr[i] = nullptr;
    }
    for (int i = 0; i < oldSize; i++) {
        NodeHash<T>* transfer = this->arr[i];
        while (transfer != nullptr) {
            NodeHash<T>* next = transfer->next;
            int newIndex = hash(transfer->key);
            transfer->next = newArr[newIndex];
            newArr[newIndex] = transfer;
            transfer = next;
        }
    }
    delete[] this->arr;
    this->arr = newArr;

}
template<class T>
NodeHash<T>* hashTable<T>::find(int key) const{

    NodeHash<T>*transfer= this->arr[hash(key)];
    while(transfer!= nullptr)
    {
        if(transfer->key==key)
        {
            return transfer;
        }
        transfer= transfer->next;
    }
    return nullptr;

}




////////////////UnionFind implementation



#endif //DS2_UNIONFIND_H
