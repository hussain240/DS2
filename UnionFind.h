//
// Created by hussa on 7/29/2024.
//

#ifndef DS2_UNIONFIND_H
#define DS2_UNIONFIND_H
#include <memory>
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
class UnionFind{
    int fullSize;
    int size;
    T* arr;
public:

};
template<class T>
NodeFind<T>::NodeFind(T value, int key) {
    this->value=value;
    this->key=key;
    this->size=0;
    this->next= nullptr;
    this->father=this;
}
#endif //DS2_UNIONFIND_H
