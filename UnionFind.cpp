//
// Created by hussa on 8/7/2024.
//
#include "UnionFind.h"
NodeHash<std::shared_ptr < fleet>> *UnionFind::findHash(int key) const {
    return this->values.find(key);
}
void UnionFind::makeSet(int key,std::shared_ptr<fleet> value) {
    this->values.insert(key,value);
}

int UnionFind::findRank(int key) {
   NodeHash<std::shared_ptr<fleet>>* findFather= this->values.find(key);
    if(findFather== nullptr)
    {
        return 0;
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
    int toReturn=counRank;
    toReturn+=findFather->rank;
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
    return toReturn;

}
NodeHash<std::shared_ptr<fleet>> *UnionFind::find(int key) {
    //////////need to correct the father in the find path and return the set key
   NodeHash<std::shared_ptr<fleet>>* findFather= this->values.find(key);
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
    
    return findFather;

}

int UnionFind::Union(int key1, int key2){
    NodeHash<std::shared_ptr<fleet>>* fleet1=this->find(key1);
    NodeHash<std::shared_ptr<fleet>>* fleet2=this->find(key2);
    if(fleet1==nullptr || fleet2==nullptr || fleet1==fleet2)
    {
        return -1;
    }
    int num1=fleet1->value->getNumOfPirate();
    int num2=fleet2->value->getNumOfPirate();
    if(num1>=num2)
    {
        fleet2->fatherId=fleet1->fatherId;
    }
    else
    {
        fleet1->fatherId=fleet2->fatherId;
    }
    if(fleet1->size>=fleet2->size)
    {
        fleet1->size+=fleet2->size;
        fleet2->father=fleet1;
        fleet1->value->addNumOfPirate(num2);
        if(num1>=num2)
        {
            fleet2->rank+=num1;
            fleet2->rank-=fleet1->rank;
        }
        else{

            fleet1->rank+=num2;
            fleet2->rank-=fleet1->rank;
        }
        
    }
    else{
        fleet2->size+=fleet1->size;
        fleet1->father=fleet2;
        fleet2->value->addNumOfPirate(num1);
        if(num2>num1)
        {
            fleet1->rank+=num2;
            fleet1->rank-=fleet2->rank;
        }
        else{
            fleet2->rank+=num1;
            fleet1->rank-=fleet2->rank;
        }

    }
    return 0;
}
/*int UnionFind::Union(int key1, int key2)
{
    NodeHash<std::shared_ptr<fleet>>* fleet1=this->values.find(key1);
    NodeHash<std::shared_ptr<fleet>>* fleet2=this->values.find(key2);
    if(fleet1==nullptr || fleet2==nullptr || fleet1==fleet2)
    {
        return -1;
    }
    int num1=fleet1->value->getNumOfPirate();
    int num2=fleet2->value->getNumOfPirate();
    if(num1>=num2)
    {
        fleet1->size+=fleet2->size;
        fleet2->father=fleet1;
        fleet1->value->addNumOfPirate(num2);
        fleet2->rank+=num1;
    }
    else{
            fleet2->size+=fleet1->size;
            fleet1->father=fleet2;
             fleet2->value->addNumOfPirate(num1);
            fleet1->rank+=num2;
    }
    return 0;
}*/