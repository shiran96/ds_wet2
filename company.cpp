 #include "company.h"

Company::Company(int company_id): company_id(company_id), current_value(company_id),
    company_salary_tree(AvlRankTree()), company_employies_hash_table(DynamicHashTable()) {};

int Company::getCompanyId() const
{
	return this->company_id;
}

void Company::mergeCompanys(Company* Company) //merge group-->this (group is smaller)
{
    if (this->getTotalNumPeopleAtCompany() == 0 && Company->getTotalNumPeopleAtCompany() == 0)
    {
        return;
    }
    if(this->company_employies_hash_table.getNumPlayersAtHash() == 0
      && Company->company_employies_hash_table.getNumPlayersAtHash() == 0) //nothing to merge
    {
        return;
    }
  
    //merge hash
    this->company_employies_hash_table.mergeHash(Company->company_employies_hash_table);
    this->company_employies_hash_table.setPlayersGroupId(this->company_id);
   // merge rankTrees
    AvlRankTree merged_tree(Company->company_salary_tree,this->company_salary_tree);
    this->company_salary_tree.empty();
    this->company_salary_tree.fillFromTree(merged_tree);
    merged_tree.empty();
}

void Company::decreseScoreAtLevelZeroScoreArr(int score)
{
    this->levelZeroScoreArr[score]--;
}
void Company::increaseScoreAtLevelZeroScoreArr(int score)
{
    this->levelZeroScoreArr[score]++;
}

//may throw bad alloc
void Company::removeScoreFromLevelAtRankTree(int level,int score)
{
    this->groupLevelTree.remove(level,score);
}

//may throw bad alloc
void Company::insertScoreFromLevelAtRankTree(int level,int score)
{
    this->groupLevelTree.insert(level,score);
}

int Company::getTotalNumPeopleAtGroup()
{
    return this->GroupPlayerHash.getNumPlayersAtHash();
}
int Company::getNumPeopleAtLevelZeroWithScore(int score)
{
    return this->levelZeroScoreArr[score];
}

int Company::getTotalNumPeopleAtTree()
{
    return this->groupLevelTree.getTotalNumPeopleAtTree();
}

double Company::getPrecentOfPlayersWithScoreBetweenBounds(int score,int lowerLevel,int higherLevel,
                   int* error, int numPeopleAtZero, int numPeopleAtZeroWithScore)
{
    return this->groupLevelTree.getPrecentOfPlayersWithScoreBetweenBounds(score,lowerLevel,
                         higherLevel,error,numPeopleAtZero,numPeopleAtZeroWithScore);
}

void Company::removeEmployeerFromHash(int employee_id)
{
    this->company_employies_hash_table.remove(employee_id);
}
void Company::addEmployeeToHash(const shared_ptr<Employee>& new_player)
{
    this->company_employies_hash_table.insert(new_player);
}
int Company::getCompanySumOfHighestMPlayerLevel(int sum,int m)
{
    return this->company_salary_tree.getSumOfHighestMPlayerLevel(sum,m, company_salary_tree.getRoot());
}

void Company::printCompanyTree()
{
  this->company_salary_tree.printTree();
}


