 #include "company.h"
using std::shared_ptr;
 
template <typename Employee>
Company<Employee>::Company(int company_id): company_id(company_id), current_value(company_id),
    company_salary_tree(AvlRankTree()), company_employies_hash_table(DynamicHashTable()) {};

template <typename Employee>
int Company<Employee>::getCompanyId() const
{
	return this->company_id;
}

template <typename Employee>
void Company<Employee>::mergeCompanys(Company<Employee>* Company) //merge group-->this (group is smaller)
{
    if (this->getTotalNumPeopleAtCompany() == 0 && Company->getTotalNumPeopleAtCompany() == 0)
    {
        return;
    }
    if(this->company_employies_hash_table.getNumEmployeesAtHash() == 0
      && Company->company_employies_hash_table.getNumEmployeesAtHash() == 0) //nothing to merge
    {
        return;
    }
  
    //merge hash
    this->company_employies_hash_table.mergeHash(Company->company_employies_hash_table);
    this->company_employies_hash_table.setEmployeesCompanyId(this->company_id);
   // merge rankTrees
    AvlRankTree merged_tree(Company->company_salary_tree,this->company_salary_tree);
    this->company_salary_tree.empty();
    this->company_salary_tree.fillFromTree(merged_tree);
    merged_tree.empty();
}

template<typename Employee>
void Company<Employee>::decreseScoreAtLevelZeroScoreArr(int score)
{
    this->levelZeroScoreArr[score]--;
}

template<typename Employee>
void Company<Employee>::increaseScoreAtLevelZeroScoreArr(int score)
{
    this->levelZeroScoreArr[score]++;
}

//may throw bad alloc
template<typename Employee>
void Company<Employee>::removeScoreFromLevelAtRankTree(int salary, int id)
{
    this->company_salary_tree.remove(salary, id);
}

//may throw bad alloc
template<typename Employee>
void Company<Employee>::insertScoreFromLevelAtRankTree(int level,int score)
{
    this->company_salary_tree.insert(level,score);
}

template<typename Employee>
int Company<Employee>::getTotalNumPeopleAtCompany()
{
    return this->company_employies_hash_table.getNumEmployeesAtHash();
}

template<typename Employee>
int Company<Employee>::getNumPeopleAtLevelZeroWithScore(int score)
{
    return this->levelZeroScoreArr[score];
}

template<typename Employee>
int Company<Employee>::getTotalNumPeopleAtTree()
{
    return this->company_salary_tree.getTotalNumPeopleAtTree();
}

template<typename Employee>
double Company<Employee>::getPrecentOfPlayersWithScoreBetweenBounds(int score,int lowerLevel,int higherLevel,
                   int* error, int numPeopleAtZero, int numPeopleAtZeroWithScore)
{
    return this->company_salary_tree.getPrecentOfPlayersWithScoreBetweenBounds(score,lowerLevel,
                         higherLevel,error,numPeopleAtZero,numPeopleAtZeroWithScore);
}

template<typename Employee>
void Company<Employee>::removePlayerFromHash(int player_id)
{
    this->company_employies_hash_table.remove(player_id);
}

template<typename Employee>
void Company<Employee>::addEmployeeToHash(const shared_ptr<Employee>& new_player)
{
    this->GroupPlayerHash.insert(new_player);
}

template<typename Employee>
int Company<Employee>::getCompanySumOfHighestMPlayerLevel(int sum,int m)
{
    return this->groupLevelTree.getSumOfHighestMPlayerLevel(sum,m,groupLevelTree.getRoot());
}

template<typename Employee>
void Company<Employee>::printCompanyTree()
{
  this->CompanyLevelTree.printTree();
}


