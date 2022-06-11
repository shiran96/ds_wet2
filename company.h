#ifndef COMPANY_H
#define COMPANY_H

#include "dynamic_hash_table.h"
#include "employee.h"
#include "rank_tree.h"

#include "memory"
using std::shared_ptr;

template <typename Employee>
class Company{
private:

    int company_id;
    int current_value;  
    int num_of_zero_emploies;
    int sum_of_zero_bump_grade;
    AvlRankTree company_salary_tree;
    DynamicHashTable company_employies_hash_table;

public:
    explicit Company(int company_id);
    ~Company() = default ;
    Company(const Company& Company) = default;
    void mergeCompanys(Company<Employee>* Company);
    Company& operator=(const Company& Company)=delete;
    int getCompanyId() const;
    void decreseScoreAtLevelZeroScoreArr(int score);
    void increaseScoreAtLevelZeroScoreArr(int score);
    void removeScoreFromLevelAtRankTree(int level,int score);
    void insertScoreFromLevelAtRankTree(int level,int score);
    int getTotalNumPeopleAtCompany();
    int getTotalNumPeopleAtTree();
    void removePlayerFromHash(int player_id);
    void addEmployeeToHash(const shared_ptr<Employee>& new_employee);
    int getNumPeopleAtLevelZeroWithScore(int score);
    double getPrecentOfPlayersWithScoreBetweenBounds(int score,int lowerLevel,int higherLevel,
                          int* error, int numPeopleAtZero, int numPeopleAtZeroWithScore);
    int getCompanySumOfHighestMPlayerLevel(int sum,int m);
    void printCompanyTree() ; //for debug
};

#endif /*Company_H*/