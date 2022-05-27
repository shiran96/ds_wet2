#ifndef DS_MANAGER_H
#define DS_MANAGER_H

#include "rank_tree.h"
#include "player.h"
#include "dynamic_hash_table.h"
#include "exception"
#include "library2.h"
#include "unionFind.h"
#include <memory>
using std::shared_ptr;

class DsManager
{
    public:
    int numOfGroups;
    int scale;
    DynamicHashTable AllplayersHashTable;
    int* AlllevelZeroScoreArr;
    unionFind unionFindGroups;
    AvlRankTree rankTree; //rank tree of levels including scores (level>0)

    DsManager(int k, int scale):numOfGroups(k),scale(scale),AllplayersHashTable(DynamicHashTable()),
        AlllevelZeroScoreArr(new int[scale+1]()),
        unionFindGroups(unionFind(k,scale)),rankTree(AvlRankTree(scale)){}
    ~DsManager()
    {
        delete[] AlllevelZeroScoreArr;
    }
    StatusType DsMergeGroups(int GroupID1, int GroupID2);
    StatusType DsAddPlayer(int PlayerID, int GroupID, int score);
    StatusType DsRemovePlayer(int PlayerID);
    StatusType DsIncreasePlayerIDLevel(int PlayerID, int LevelIncrease);
    StatusType DsChangePlayerIDScore(int PlayerID, int NewScore);
    StatusType DsGetPercentOfPlayersWithScoreInBounds(int GroupID, int score,
                            int lowerLevel, int higherLevel,double * players);
    StatusType DsAverageHighestPlayerLevelByGroup(int GroupID, int m, double * level);
};


#endif /*DS_MANAGER_H*/