#ifndef UNIONFIND_H
#define UNIONFIND_H


#include "company.h"

class unionFind {
    int groupsNum;
    int* parentArr;
    int* groupSizeArr;
    Company** grArray;
public:
    unionFind(int groupsNum); //will make k groups
    ~unionFind();
   
    //void Makeset(int x);//return singletone x
    
    void Union(int p, int q); //return a new union group, p&q deleted.
    
    int Find(int x); //return the group that x belong to

    //call this function after using find to get the real id of the group
    Company* getCompany(int companyId);
    
};
typedef unionFind* UnionFind;


#endif //UNIONFIND_H