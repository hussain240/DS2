//
// Created by hussa on 8/7/2024.
//
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

void UnionFind::Union(int key1, int key2) {
    NodeHash<std::shared_ptr<fleet>> *list1 = this->values.find(key1);
    NodeHash<std::shared_ptr<fleet>> *list2 = this->values.find(key2);
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
