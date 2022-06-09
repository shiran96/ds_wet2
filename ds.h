#ifndef DS_MANAGER_H
#define DS_MANAGER_H

#include "rank_tree.h"
#include "employee.h"
#include "dynamic_hash_table.h"
#include "exception"
#include "library2.h"
#include "unionFind.h"
#include <memory>
using std::Employee;

class DS
{
    public:
    int num_of_companies;
    int num_of_zero_emploies;
    int sum_of_zero_bump_grade;
    DynamicHashTable AllEmploiesHashTable;
    unionFind unionFindCompanies;
    rank_tree rankTree; //rank tree of levels including scores (level>0)

    DS(int k):num_of_companies(k), num_of_zero_emploies(0), sum_of_zero_bump_grade(0),
        AllEmploiesHashTable(DynamicHashTable()), unionFindCompanies(unionFind(k)),
        rankTree(AvlRankTree()){}

    ~DS() = default;

    
    StatusType DSacquireCompany(int GroupID1, int GroupID2);
    StatusType DSaddEmployee(int PlayerID, int GroupID, int score);
    StatusType DSremoveEmployee(int PlayerID);
    StatusType DSemployeeSalaryIncrease(int PlayerID, int LevelIncrease);
    StatusType DSpromoteEmployee(int PlayerID, int NewScore);
    StatusType DSavregeGradeInBounds(int GroupID, int score,
                            int lowerLevel, int higherLevel,double * players);
    StatusType DSsumOfGradeTopEmployee(int GroupID, int m, double * level);
    StatusType DScompanyValue(int company_id, void* standing);
    StatusType DSbumpGradeInBounds(int lower_salary, int higher_salary, int bump_grade);

};


#endif /*DS_MANAGER_H*/