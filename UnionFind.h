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
    NodeHash<T>* operator[](int key)const;
    void print()
    {
        for(int i=0;i<this->fullSize;i++)
        {
            NodeHash<T>*current = this->arr[i];
            while(current!= nullptr)
            {
                std::cout<< current->fatherId<<std::endl;
                current=current->next;
            }
        }
    }
};


class UnionFind{
    hashTable<std::shared_ptr<fleet>> values;
    //hashTable<T> lists;

public:
    UnionFind()=default;
    ~UnionFind()=default;
    void makeSet(int key,std::shared_ptr<fleet> value);
    NodeHash<std::shared_ptr<fleet>>* find(int key)const;
    void Union(int key1,int key2);
    NodeHash<std::shared_ptr<fleet>>* operator[](int key)const;
    void print()
    {
        this->values.print();
    }

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
    this->arr= nullptr;
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
NodeHash<T>* hashTable<T>::operator[](int key) const{

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

NodeHash<std::shared_ptr < fleet>> *

UnionFind::operator[](int key) const {
    return this->values[key];
}
void UnionFind::makeSet(int key,std::shared_ptr<fleet> value) {
    this->values.insert(key,value);
}

NodeHash<std::shared_ptr<fleet>> *UnionFind::find(int key) const {
    //////////need to correct the father in the find path and return the set key
    NodeHash<std::shared_ptr<fleet>>* findFather= this->values[key];
    if(findFather== nullptr)
    {
        return nullptr;
    }
    NodeHash<std::shared_ptr<fleet>>* start2=findFather;
    NodeHash<std::shared_ptr<fleet>>* tmp=findFather;
    int counRank=0;
    while (findFather->father!=findFather)
    {
        counRank+=findFather->rank;
        findFather=findFather->father;
    }
    int fatherId=findFather->fatherId;
    while(start2->father!=start2)
    {
        tmp=start2->father;
        int currentRank=start2->rank;
        start2->rank=counRank;
        counRank-=currentRank;
        start2->father=findFather;
        start2->fatherId=fatherId;
        start2=tmp;
    }
    return this->values[fatherId];
}

void UnionFind::Union(int key1, int key2) {
    NodeHash<std::shared_ptr<fleet>> *list1 = this->values[key1];
    NodeHash<std::shared_ptr<fleet>> *list2 = this->values[key2];
    if (list1 == nullptr || list2 == nullptr || list1 == list2) {
        return;
    }
    int num1=list1->value->getNumOfPirate();
    int num2=list2->value->getNumOfPirate();
    if (list1->size < list2->size) {
        list2->size = list2->size + list1->size;
        list1->father = list2;
        if(num1<=num2)
        {
            list1->fatherId=list2->key;
            list1->rank+=num2-list2->rank;
            if(num1==num2)
            {
                list2->fatherId=list1->key;
                list1->fatherId=list1->key;
            }
        }
        else{
            list2->fatherId=list1->key;
            list1->rank+=num2;
            list2->rank-=list1->rank;
        }
        list2->value->addNumOfPirate(num1);
    }
    else
    {
        list1->size = list2->size + list1->size;
        list2->father = list1;
        if(num1>=num2)
        {
            list2->fatherId=list1->key;
            list2->rank+=num1-list1->rank;
        }
        else{
            list1->fatherId=list2->key;
            list2->rank+=num1;
            list1->rank-=list2->rank;
        }
        list1->value->addNumOfPirate(num2);
    }
}


#endif //DS2_UNIONFIND_H
