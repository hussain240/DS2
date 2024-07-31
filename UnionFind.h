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
    virtual void insert(int key,T vlaue);
    void resize();
    NodeHash<T>* operator[](int key);

};


template<class T>
class UnionFind{
    hashTable<T> values;
    hashTable<T> lists;

public:
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

/////////////pair implementation
template<class T>
pair<T>::pair(NodeHash<T>*father, T value) {
    this->father=father;
    this->value=value;
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
    toInsert.next=this->arr[hash(key)];
    this->arr[hash(key)]=toInsert;
}
template<class T>
void hashTable<T>::resize() {
    this->fullSize*=2;
    NodeHash<T>* *newArr = new NodeHash<T>*[this->fullSize];
    for(int i=0;i<this->fullSize;i++)
    {
        newArr[i]= nullptr;
    }
    for(int i=0;i<this->fullSize/2;i++)
    {
        NodeHash<T>*transfer= this->arr[i];
        while(transfer!= nullptr)
        {
            if(newArr[hash(transfer.key)]== nullptr)
            {
                newArr[hash(transfer.key)]=transfer;

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
NodeHash<T> *hashTable<T>::operator[](int key) {

    NodeHash<T>*transfer= this->arr[hash(key)];
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




////////////////UnionFind implementation
template<class T>
void UnionFind<T>::makeSet(int key,T value) {
    this->values.insert(key,value);
    this->lists.insert(key,value);
}
template<class T>
NodeHash<T> *UnionFind<T>::find(int key) const {
    //////////need to correct the father in the find path and return the set key


}
template<class T>
void UnionFind<T>::Union(int key1, int key2) {
    if(key1>key2)
    {

    }
}
#endif //DS2_UNIONFIND_H
