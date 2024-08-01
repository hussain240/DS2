//
// Created by hussa on 7/29/2024.
//

#ifndef DS2_UNIONFIND_H
#define DS2_UNIONFIND_H
#define STARTSIZE 1000
template<class T>
class NodeHash{
public:
    T value;
    int key;
    int size;
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
    virtual void insert(int key,T vlaue);
    void resize();
    NodeHash<T>* operator[](int key)const;
    void makeNull(NodeHash<T>* toRemove);

};


template<class T>
class UnionFind{
    hashTable<T> values;
    hashTable<T> lists;

public:
    UnionFind()=default;
    ~UnionFind()=default;
    void makeSet(int key,T value);
    NodeHash<T>* find(int key)const;
    void Union(int key1,int key2);

};

///////NodeHash implementation
template<class T>
NodeHash<T>::NodeHash(int key,T value) {
    this->value=value;
    this->key=key;
    this->size=1;
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
        NodeHash<T>* current = arr[i];
        while (current != nullptr) {
            NodeHash<T>* toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }
    delete[] arr;
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
    NodeHash<T>*toInsert=new NodeHash<T>(key,value);
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
NodeHash<T> *hashTable<T>::operator[](int key) const{

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
template<class T>
void hashTable<T>::makeNull(NodeHash<T> *toRemove) {
    NodeHash<T>* firstInList=this->arr[toRemove->key];
    if(firstInList== nullptr)
    {
        return;
    }
    if(firstInList==toRemove)
    {
        this->arr[toRemove->key]=firstInList->next;
    }
    while(firstInList!=toRemove && firstInList!= nullptr)
    {
        if(firstInList->next==toRemove)
        {
            firstInList->next=toRemove->next;
        }
        firstInList=firstInList->next;
    }
    this->size--;
}




////////////////UnionFind implementation
template<class T>
void UnionFind<T>::makeSet(int key,T value) {
    this->values.insert(key,value);
    this->lists.insert(key,value);
}
template<class T>
NodeHash<T> *UnionFind<T>::find(int key) const {
    //////////need to correct the father in the find path and return the set key
    NodeHash<T>* findFather= this->values[key];
    if(findFather== nullptr)
    {
        return nullptr;
    }
    NodeHash<T>* start2=findFather;
    NodeHash<T>* tmp=findFather;
    while (findFather->father!=findFather)
    {
        findFather=findFather->father;
    }
    while(start2->father!=start2)
    {
        tmp=start2->father;
        start2->father=findFather;
        start2=tmp;
    }
    return findFather;
}
template<class T>
void UnionFind<T>::Union(int key1, int key2) {
    NodeHash<T>* list1=this->lists[key1];
    NodeHash<T>* list2=this->lists[key2];
    if(list1== nullptr||list2== nullptr)
    {
        return;
    }
    if(list1->size>list2->size)
    {
        list1->size+=list2->size;
        list2->father=list1;
        this->lists.makeNull(list2);
    }
    else{
        list2->size+=list1->size;
        list1->father=list2;
        this->lists.makeNull(list1);
    }
}
#endif //DS2_UNIONFIND_H
