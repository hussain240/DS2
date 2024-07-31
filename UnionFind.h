//
// Created by hussa on 7/29/2024.
//

#ifndef DS2_UNIONFIND_H
#define DS2_UNIONFIND_H

#define STARTSIZE 1000
template<class T>
class NodeFind{
public:
    T value;
    int size;
    int key;
    NodeFind<T>* next;
    NodeFind<T>* father;
    NodeFind()=default;
    NodeFind(T value);
};
template<class T>
class hashTable{
    int fullSize;
    int size;
    NodeFind<T>* *arr;
    int hash(int key)const;
public:
    hashTable();
    void insert(int key,T vlaue);
    void resize();
    NodeFind<T>* operator[](int key);

};
template<class T>
class UnionFind{
    hashTable<T> values;
    hashTable<T> lists;

public:

};

///////NodeFind implementation
template<class T>
NodeFind<T>::NodeFind(T value, int key) {
    this->value=value;
    this->size=1;
    this->key=key;
    this->next= nullptr;
    this->father=this;
}




////////hashTable implementation
template<class T>
hashTable<T>::hashTable() {
    this->fullSize=STARTSIZE;
    this->size=0;
    this->arr= nullptr;
}
template<class T>
int hashTable<T>::hash(int key) const {
    return key % this->fullSize;
}
template<class T>
void hashTable<T>::insert(int key,T value) {
    if(this->arr== nullptr)
    {
        this->arr=new NodeFind<T>*[STARTSIZE];
        for(int i=0;i<STARTSIZE;i++)
        {
            this->arr[i]= nullptr;
        }
    }
    NodeFind<T>*toInsert=new NodeFind<T>(key,NodeFind<T>(value));
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
    this->fullSize*=2;
    NodeFind<T>* *newArr = new NodeFind<T>*[this->fullSize];
    for(int i=0;i<this->fullSize;i++)
    {
        newArr[i]= nullptr;
    }
    for(int i=0;i<this->fullSize/2;i++)
    {
        NodeFind<T>*transfer= this->arr[i];
        while(transfer.value!= nullptr)
        {
            if(newArr[hash(transfer.key)]== nullptr)
            {
                newArr[hash(transfer.key)]=toInsert;

            }
            else {
                transfer.next = newArr[hash(transfer.key)];
                newArr[hash(transfer.key)] = toInsert;
            }
            transfer= transfer->value.next;
        }
    }
    delete[] this->arr;
    this->arr=newArr;

}
template<class T>
NodeFind<T> *hashTable<T>::operator[](int key) {

        NodeFind<T>*transfer= this->arr[hash(key)];
        while(transfer!= nullptr)
        {
            if(transfer->key==key)
            {
                return transfer;
            }
            transfer= transfer->value.next;
        }
    return nullptr;

}
#endif //DS2_UNIONFIND_H
