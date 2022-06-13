#include "company.h"

Company::Company(int groupId,int scale):scale(scale),groupId(groupId),
    groupLevelTree(AvlRankTree(scale)),levelZeroScoreArr(new int[scale+1]()),
    GroupPlayerHash(DynamicHashTable()){}

Company::~Company()
{
	delete[] levelZeroScoreArr;
}

Company::Company(const Company& group):scale(group.scale),groupId(group.groupId),
    groupLevelTree(AvlRankTree(group.groupLevelTree)),levelZeroScoreArr(new int[group.scale]()),
    GroupPlayerHash(group.GroupPlayerHash)
{
	for (int i = 0; i < group.scale+1; i++)
	{
		this->levelZeroScoreArr[i] = group.levelZeroScoreArr[i];
	}
} 


int Company::getGroupId() const
{
	return this->groupId;
}

void Company::MergeGroups(Company* group) //merge group-->this (group is smaller)
{
    if (this->getTotalNumPeopleAtGroup() == 0 && group->getTotalNumPeopleAtGroup() == 0)
    {
        return;
    }
    if(this->GroupPlayerHash.getNumPlayersAtHash() == 0 
      && group->GroupPlayerHash.getNumPlayersAtHash() == 0) //nothing to merge
    {
        return;
    }
    //groupId is of "this" also after the merge
    for(int i=0;i<scale+1;i++)
    {
        this->levelZeroScoreArr[i]+=group->levelZeroScoreArr[i]; //merge arrays
        group->levelZeroScoreArr[i]=0; //empty the Arr of the group
    }
//    //create a new hash using the hash tables of the groups
//    if(this->GroupPlayerHash.getNumPlayersAtHash() ==0)
//    {
//        this->GroupPlayerHash.insertFromOtherHashTable(group->GroupPlayerHash);
//        group->GroupPlayerHash.cleanHashTable();
//        this->GroupPlayerHash.setPlayersGroupId(this->groupId);
//    }
//    else if(group->GroupPlayerHash.getNumPlayersAtHash()!=0 &&
//        this->GroupPlayerHash.getNumPlayersAtHash()!=0)
//    {
//        DynamicHashTable merged_hash(this->GroupPlayerHash,group->GroupPlayerHash);
//        merged_hash.setPlayersGroupId(this->groupId); //set the GroupId of all the players to this
//        group->GroupPlayerHash.cleanHashTable();
//        this->GroupPlayerHash.cleanHashTable();
//        this->GroupPlayerHash.insertFromOtherHashTable(merged_hash); //merged -> this
//        merged_hash.cleanHashTable();
//    }
    //merge hash
    this->GroupPlayerHash.mergeHash(group->GroupPlayerHash);
    this->GroupPlayerHash.setPlayersGroupId(this->groupId);
   // merge rankTrees
    AvlRankTree merged_tree(group->groupLevelTree,this->groupLevelTree);
    this->groupLevelTree.empty();
    group->groupLevelTree.empty();
    this->groupLevelTree.fillFromTree(merged_tree);
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

void Company::removePlayerFromHash(int player_id)
{
    this->GroupPlayerHash.remove(player_id);
}
void Company::addPlayerToHash(const shared_ptr<Employee>& new_player)
{
    this->GroupPlayerHash.insert(new_player);
}
int Company::getGroupSumOfHighestMPlayerLevel(int sum,int m)
{
    return this->groupLevelTree.getSumOfHighestMPlayerLevel(sum,m,groupLevelTree.getRoot());
}

void Company::printGroupTree()
{
  this->groupLevelTree.printTree();
}


