#ifndef UNIONFIND_H_
#define UNIONFIND_H_

//#include <stdio.h>
//#include <stdlib.h>
#include "company.h"

class unionFind {
    int scale;
    int groupsNum;
    int* parentArr;
    int* groupSizeArr;
    Company** grArray;
public:
    unionFind(int groupsNum,int scale); //will make k groups
    ~unionFind();
   
    //void Makeset(int x);//return singletone x
    
    void Union(int p, int q); //return a new union group, p&q deleted.
    
    int Find(int x); //return the group that x belong to

    //call this function after using find to get the real id of the group
    Company* getGroup(int groupId);
    
};
typedef unionFind* UnionFind;


#endif //UNIONFIND_H_