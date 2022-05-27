
#include "library2.h"
#include "ds_manager.h"

void *Init(int k, int scale)
{
    if(k<=0 || scale<=0 || scale>200)
    {
        return NULL;
    }
    DsManager* CDS=new DsManager(k,scale);
    return (void*)CDS;
}

StatusType MergeGroups(void *DS, int GroupID1, int GroupID2)
{
    if(DS==NULL)
    {
        return INVALID_INPUT;
    }
    return static_cast<DsManager*>(DS)->DsMergeGroups(GroupID1,GroupID2);
}

StatusType AddPlayer(void *DS, int PlayerID, int GroupID, int score)
{
    if(DS==NULL)
    {
        return INVALID_INPUT;
    }
    return static_cast<DsManager*>(DS)->DsAddPlayer(PlayerID,GroupID,score);
}

StatusType RemovePlayer(void *DS, int PlayerID)
{
    if(DS==NULL)
    {
        return INVALID_INPUT;
    }
    return static_cast<DsManager*>(DS)->DsRemovePlayer(PlayerID);
}

StatusType IncreasePlayerIDLevel(void *DS, int PlayerID, int LevelIncrease)
{
    if(DS==NULL)
    {
        return INVALID_INPUT;
    }
    return static_cast<DsManager*>(DS)->DsIncreasePlayerIDLevel(PlayerID,LevelIncrease);
}

StatusType ChangePlayerIDScore(void *DS, int PlayerID, int NewScore)
{
    if(DS==NULL)
    {
        return INVALID_INPUT;
    }
    return static_cast<DsManager*>(DS)->DsChangePlayerIDScore(PlayerID,NewScore);
}

StatusType GetPercentOfPlayersWithScoreInBounds(void *DS, int GroupID, int score, int lowerLevel,
                                                int higherLevel, double * players)
{
    if(DS==NULL)
    {
        return INVALID_INPUT;
    }
    return static_cast<DsManager*>(DS)->DsGetPercentOfPlayersWithScoreInBounds(GroupID,score,
                                                 lowerLevel,higherLevel,players);
}

StatusType AverageHighestPlayerLevelByGroup(void *DS, int GroupID, int m, double * level)
{
    if(DS==NULL)
    {
        return INVALID_INPUT;
    }
    return static_cast<DsManager*>(DS)->DsAverageHighestPlayerLevelByGroup(GroupID,m,level);
}

StatusType GetPlayersBound(void *DS, int GroupID, int score, int m,
                           int * LowerBoundPlayers, int * HigherBoundPlayers)
{
    if(DS== NULL || LowerBoundPlayers==NULL || HigherBoundPlayers==NULL)
    {
        return INVALID_INPUT;
    }
    return SUCCESS;
}
void Quit(void** DS)
{
    delete (DsManager*)*DS;
    *DS=NULL;
}