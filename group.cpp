#include "group.h"

Group::Group(int groupId,int scale):scale(scale),groupId(groupId),
    groupLevelTree(AvlRankTree(scale)),levelZeroScoreArr(new int[scale+1]()),
    GroupPlayerHash(DynamicHashTable())

{};

Group::~Group()
{
	delete[] levelZeroScoreArr;
}

Group::Group(const Group& group):scale(group.scale),groupId(group.groupId),
    groupLevelTree(AvlRankTree(group.groupLevelTree)),levelZeroScoreArr(new int[group.scale]()),
    GroupPlayerHash(group.GroupPlayerHash)
{
	for (int i = 0; i < group.scale+1; i++)
	{
		this->levelZeroScoreArr[i] = group.levelZeroScoreArr[i];
	}
} 


int Group::getGroupId() const
{
	return this->groupId;
}

void Group::MergeGroups(Group* group) //merge group-->this (group is smaller)
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

void Group::decreseScoreAtLevelZeroScoreArr(int score)
{
    this->levelZeroScoreArr[score]--;
}
void Group::increaseScoreAtLevelZeroScoreArr(int score)
{
    this->levelZeroScoreArr[score]++;
}

//may throw bad alloc
void Group::removeScoreFromLevelAtRankTree(int level,int score)
{
    this->groupLevelTree.remove(level,score);
}

//may throw bad alloc
void Group::insertScoreFromLevelAtRankTree(int level,int score)
{
    this->groupLevelTree.insert(level,score);
}

int Group::getTotalNumPeopleAtGroup()
{
    return this->GroupPlayerHash.getNumPlayersAtHash();
}
int Group::getNumPeopleAtLevelZeroWithScore(int score)
{
    return this->levelZeroScoreArr[score];
}

int Group::getTotalNumPeopleAtTree()
{
    return this->groupLevelTree.getTotalNumPeopleAtTree();
}

double Group::getPrecentOfPlayersWithScoreBetweenBounds(int score,int lowerLevel,int higherLevel,
                   int* error, int numPeopleAtZero, int numPeopleAtZeroWithScore)
{
    return this->groupLevelTree.getPrecentOfPlayersWithScoreBetweenBounds(score,lowerLevel,
                         higherLevel,error,numPeopleAtZero,numPeopleAtZeroWithScore);
}

void Group::removePlayerFromHash(int player_id)
{
    this->GroupPlayerHash.remove(player_id);
}
void Group::addPlayerToHash(const shared_ptr<Player>& new_player)
{
    this->GroupPlayerHash.insert(new_player);
}
int Group::getGroupSumOfHighestMPlayerLevel(int sum,int m)
{
    return this->groupLevelTree.getSumOfHighestMPlayerLevel(sum,m,groupLevelTree.getRoot());
}

void Group::printGroupTree()
{
  this->groupLevelTree.printTree();
}


