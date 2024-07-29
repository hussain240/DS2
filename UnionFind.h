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
    std::shared_ptr<NodeFather<T>>father;
};
template<class T>
class NodeFather{
public:
    T value;
    int key;
    int size;
};
template<class T>
class UnionFind{
    int fullSize;
    int size;
    T* arr;
public:

};
#endif //DS2_UNIONFIND_H
