#include "unionFind.h"

unionFind::unionFind(int groupsNum,int scale):scale(scale),groupsNum(groupsNum),
    parentArr(new int[groupsNum +1]()),groupSizeArr(new int[groupsNum + 1]()),
    grArray(new Group*[groupsNum +1])
{
    for (int i = 1; i < groupsNum+1; ++i) {
        parentArr[i] = -1;
        groupSizeArr[i] = 1;
        grArray[i] = new Group(i,scale);
    }
}

unionFind::~unionFind() {
    delete[] parentArr;
    delete[] groupSizeArr;
    for(int i=1;i<groupsNum+1;i++)
    {
        delete grArray[i];
    }
    delete[] grArray;
}

//void unionFind::Makeset(int x) {
//    this->parents[x] = -1;
//    this->size_[x] = 1;
//}

int unionFind::Find(int x) {   //assume x valid
    int parent = this->parentArr[x];
    int old_p = x;
    while (parent > -1) {
        old_p = parent;
        parent = this->parentArr[parent];
    }
    parent = old_p;  //shrink paths
    int temp = x;
    int new_temp;
    while (temp != parent) {
        new_temp = parentArr[temp];
        parentArr[temp] = parent;
        temp = new_temp;
    }
    return parent;
}

void unionFind::Union(int p_curr, int q_curr) {
    int p = this->Find(p_curr);
    int q = this->Find(q_curr);
    if (p == q) return;
    if (groupSizeArr[p] > groupSizeArr[q]) {
        groupSizeArr[p] += groupSizeArr[q];
        groupSizeArr[q] = 0;
        parentArr[q] = p;
        grArray[p]->MergeGroups(grArray[q]);
    }
    else if (groupSizeArr[p] <= groupSizeArr[q]) {
        groupSizeArr[q] += groupSizeArr[p];
        groupSizeArr[p] = 0;
        parentArr[p] = q;
        grArray[q]->MergeGroups(grArray[p]);
    }
    //else {
    //    if (p > q) {
    //        groupSizeArr[p] += groupSizeArr[q];
    //        groupSizeArr[q] = 0;
    //        parentArr[q] = p;
    //        MgrArray[q]->MergeGroups(grArray[p]);

    //        //            merged_dc_to_delete[q] = dc_array[q];
    //        //            dc_array[q] = dc_array[p];
    //    }
    //    else {
    //        groupSizeArr[q] += size_[p];
    //        groupSizeArr[p] = 0;
    //        parentArr[p] = q;
    //        MgrArray[q]->MergeGroups(grArray[p]);

    //        //            merged_dc_to_delete[p] = dc_array[p];
    //        //            dc_array[p] = dc_array[q];
    //    }
 /*   }*/
}

Group* unionFind::getGroup(int groupId)
{
    int realGroup=this->Find(groupId);
    return grArray[realGroup];
}
