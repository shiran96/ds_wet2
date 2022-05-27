#ifndef GROUP_H
#define GROUP_H

#include "dynamic_hash_table.h"
#include "rank_tree.h"

class Group
{
private:
    int scale; //need to save for copy constructor
    int groupId;
    AvlRankTree groupLevelTree;
    int* levelZeroScoreArr;
    DynamicHashTable GroupPlayerHash;

public:
    Group(int groupId,int scale);
    ~Group();
    Group(const Group& group);
    void MergeGroups(Group* group);
    Group& operator=(const Group& group)=delete;
    int getGroupId() const;
    void decreseScoreAtLevelZeroScoreArr(int score);
    void increaseScoreAtLevelZeroScoreArr(int score);
    void removeScoreFromLevelAtRankTree(int level,int score);
    void insertScoreFromLevelAtRankTree(int level,int score);
    int getTotalNumPeopleAtGroup();
    int getTotalNumPeopleAtTree();
    void removePlayerFromHash(int player_id);
    void addPlayerToHash(const shared_ptr<Player>& new_player);
    int getNumPeopleAtLevelZeroWithScore(int score);
    double getPrecentOfPlayersWithScoreBetweenBounds(int score,int lowerLevel,int higherLevel,
                          int* error, int numPeopleAtZero, int numPeopleAtZeroWithScore);
    int getGroupSumOfHighestMPlayerLevel(int sum,int m);
    void printGroupTree() ; //for debug
};

#endif /*GROUP_H*/