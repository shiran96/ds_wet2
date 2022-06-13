#ifndef GROUP_H
#define GROUP_H

#include "dynamic_hash_table.h"
#include "rank_tree.h"

class Company
{
private:
    int scale; //need to save for copy constructor
    int groupId;
    AvlRankTree groupLevelTree;
    int* levelZeroScoreArr;
    DynamicHashTable GroupPlayerHash;

public:
    Company(int groupId,int scale);
    ~Company();
    Company(const Company& group);
    void MergeGroups(Company* group);
    Company& operator=(const Company& group)=delete;
    int getGroupId() const;
    void decreseScoreAtLevelZeroScoreArr(int score);
    void increaseScoreAtLevelZeroScoreArr(int score);
    void removeScoreFromLevelAtRankTree(int level,int score);
    void insertScoreFromLevelAtRankTree(int level,int score);
    int getTotalNumPeopleAtGroup();
    int getTotalNumPeopleAtTree();
    void removePlayerFromHash(int player_id);
    void addPlayerToHash(const shared_ptr<Employee>& new_player);
    int getNumPeopleAtLevelZeroWithScore(int score);
    double getPrecentOfPlayersWithScoreBetweenBounds(int score,int lowerLevel,int higherLevel,
                          int* error, int numPeopleAtZero, int numPeopleAtZeroWithScore);
    int getGroupSumOfHighestMPlayerLevel(int sum,int m);
    void printGroupTree() ; //for debug
};

#endif /*GROUP_H*/