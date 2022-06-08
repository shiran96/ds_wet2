
#include "ds.h"

StatusType DS::DSacquireCompany(int GroupID1, int GroupID2)
{
    if(GroupID1<=0 || GroupID2<=0 || GroupID1>numOfGroups || GroupID2>numOfGroups)
    {
        return INVALID_INPUT;
    }
    try
    {
        unionFindGroups.Union(GroupID1,GroupID2); //merging Hash may throw bad alloc
    }
    catch (std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType DS::DSaddEmployee(int PlayerID, int GroupID, int score)
{
    if (GroupID > numOfGroups || GroupID <= 0 || PlayerID <= 0 || score>scale || score<=0)
    {
        return INVALID_INPUT;
    }
    if (AllplayersHashTable.find(PlayerID) == true)
    {
        return FAILURE;
    }
    try
    {
        shared_ptr<Player> new_player(new Player(PlayerID, GroupID, score));
        AllplayersHashTable.insert(new_player); //may throw bad_alloc
        this->AlllevelZeroScoreArr[score]++;
        Group* gr = this->unionFindGroups.getGroup(GroupID);
        gr->increaseScoreAtLevelZeroScoreArr(score);
        gr->addPlayerToHash(new_player);
    }
    catch (const std::bad_alloc& e)
    {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;

}

StatusType DS::DSremoveEmployee(int PlayerID)
{
    if (PlayerID <= 0)
    {
        return INVALID_INPUT;
    }
    if (AllplayersHashTable.find(PlayerID) == false)
    {
        return FAILURE;
    }
    try
    {
        Node<shared_ptr<Player>>* player_data = AllplayersHashTable.getPlayerById(PlayerID);
        int player_level = player_data->data->getPlayerLevel();
        int player_score = player_data->data->getPlayerScore();
        int group_id = player_data->data->getPlayerGroupId();
        Group* gr = this->unionFindGroups.getGroup(group_id);
        if (player_level == 0)
        {
            gr->decreseScoreAtLevelZeroScoreArr(player_score);
            this->AlllevelZeroScoreArr[player_score]--;
        }
        else
        {
            gr->removeScoreFromLevelAtRankTree(player_level, player_score); //may throw bad_alloc
            this->rankTree.remove(player_level,player_score); //may throw bad_alloc
        }
        gr->removePlayerFromHash(PlayerID); //may throw bad_alloc
        AllplayersHashTable.remove(PlayerID); //may throw bad_alloc
    }
    catch (const std::bad_alloc& e)
    {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}


StatusType DS::DSemployeeSalaryIncrease(int PlayerID, int LevelIncrease)
{
    if(PlayerID<=0 || LevelIncrease <=0)
    {
        return INVALID_INPUT;
    }
    if(AllplayersHashTable.find(PlayerID)==false)
    {
        return FAILURE;
    }
    //the player exist
    Node<shared_ptr<Player>>* player=
                                AllplayersHashTable.getPlayerById(PlayerID);
    int playerOldLevel=player->data->getPlayerLevel();
    int playerScore=player->data->getPlayerScore();
    int playerNewLevel=playerOldLevel+LevelIncrease;
    player->data->setPlayerLevel(playerNewLevel); //thanks to shared ptr the player
                                                    //level got updated in all of his locations

    //remove old data regard the level
    if(playerOldLevel==0)
    {
        AlllevelZeroScoreArr[playerScore]--;
    }
    else //old level != 0
    {
        try
        {
            rankTree.remove(playerOldLevel,playerScore);
        }
        catch(std::bad_alloc& e)
        {
            return ALLOCATION_ERROR;
        }
    }
    //update the new data regard the level
    try
    {
        rankTree.insert(playerNewLevel,playerScore);
       // rankTree.printTree(); // added
    }
    catch (std::bad_alloc& e)
    {
        return ALLOCATION_ERROR;
    }
    //find the group of the player
    int playerGroupId=player->data->getPlayerGroupId();
    Group* playerGroup=unionFindGroups.getGroup(playerGroupId);
    //remove old info regard the player's level
    if(playerOldLevel==0)
    {
        playerGroup->decreseScoreAtLevelZeroScoreArr(playerScore);
    }
    else
    {
        try
        {
            playerGroup->removeScoreFromLevelAtRankTree(playerOldLevel,playerScore);
        }
        catch(std::bad_alloc& e)
        {
            return ALLOCATION_ERROR;
        }

    }
    //update the new info
    try
    {
        playerGroup->insertScoreFromLevelAtRankTree(playerNewLevel,playerScore);
    }
    catch(std::bad_alloc& e)
    {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}
StatusType DS::DSpromoteEmployee(int PlayerID, int NewScore)
{
    if(PlayerID<=0 || NewScore<= 0 || NewScore>this->scale)
    {
        return INVALID_INPUT;
    }
    if(AllplayersHashTable.find(PlayerID)==false)
    {
        return FAILURE;
    }
    Node<shared_ptr<Player>>* playerData=
            AllplayersHashTable.getPlayerById(PlayerID);
    int playerOldScore=playerData->data->getPlayerScore();
    int playerLevel=playerData->data->getPlayerLevel();
    playerData->data->setPlayerScore(NewScore);
    if(playerLevel==0)
    {
        this->AlllevelZeroScoreArr[playerOldScore]--;
        this->AlllevelZeroScoreArr[NewScore]++;
    }
    else
    {
        try
        {
            rankTree.remove(playerLevel,playerOldScore);
            rankTree.insert(playerLevel,NewScore);
        }
        catch(std::bad_alloc& e)
        {
            return ALLOCATION_ERROR;
        }
    }
    //update the data in the playerGroup:
    int playerGroupId=playerData->data->getPlayerGroupId();
    Group* playerGroup=unionFindGroups.getGroup(playerGroupId);
    if(playerLevel==0)
    {
        playerGroup->decreseScoreAtLevelZeroScoreArr(playerOldScore);
        playerGroup->increaseScoreAtLevelZeroScoreArr(NewScore);
    }
    else
    {
        try
        {
            playerGroup->removeScoreFromLevelAtRankTree(playerLevel,playerOldScore);
            playerGroup->insertScoreFromLevelAtRankTree(playerLevel,NewScore);
        }
        catch (std::bad_alloc& e)
        {
            return ALLOCATION_ERROR;
        }
    }
    return SUCCESS;
}

StatusType DS::DSavregeGradeInBounds(int GroupID, int score,
                                                  int lowerLevel, int higherLevel,double * players)
{
    if(GroupID<0 || GroupID>numOfGroups || players== nullptr)
    {
        return INVALID_INPUT;
    }
    if(higherLevel<lowerLevel)
    {
        *players=0;
        return FAILURE;
    }
    int error=0;
    int numPeopleAtLevelZero=0;
    int numPeopleAtLevelZeroWithScore=0;
    if(GroupID==0)
    {
        if(lowerLevel<=0) //need to count the players at level zero which aren't in the tree
        {
            int total=AllplayersHashTable.getNumPlayersAtHash();
            int notLevelZero=rankTree.getTotalNumPeopleAtTree();
            numPeopleAtLevelZero=total-notLevelZero;
            if(score>0 && score<=scale) //valid
            {
                numPeopleAtLevelZeroWithScore=this->AlllevelZeroScoreArr[score];
            }
        }
        try
        {
            // the next line may throw bad alloc
            *players=this->rankTree.getPrecentOfPlayersWithScoreBetweenBounds(score,lowerLevel,
                           higherLevel,&error,numPeopleAtLevelZero,numPeopleAtLevelZeroWithScore);
            if(error==-1)
            {
                return FAILURE;
            }
            return SUCCESS;
        }
        catch (std::bad_alloc& e)
        {
            *players=0;
            return ALLOCATION_ERROR;
        }
    }
    else
    {
        Group* group=unionFindGroups.getGroup(GroupID);
        if(lowerLevel<=0) //need to count the players at level zero which aren't in the tree
        {
            int total=group->getTotalNumPeopleAtGroup();
            int notLevelZero=group->getTotalNumPeopleAtTree();
            numPeopleAtLevelZero=total-notLevelZero;
            if(score>0 && score<=scale)
            {

                numPeopleAtLevelZeroWithScore=group->getNumPeopleAtLevelZeroWithScore(score);
            }
        }
        try
        {
            *players=group->getPrecentOfPlayersWithScoreBetweenBounds(score,lowerLevel,
              higherLevel,&error,numPeopleAtLevelZero,numPeopleAtLevelZeroWithScore);
            if(error==-1)
            {
                return FAILURE;
            }
            return SUCCESS;
        }
        catch (std::bad_alloc& e)
        {
            *players=0;
            return ALLOCATION_ERROR;
        }

    }
}

StatusType DS::DSsumOfGradeTopEmployee(int GroupID, int m, double * level)
{
    if( level== nullptr || GroupID>numOfGroups || GroupID<0 || m<=0  )
    {
        return INVALID_INPUT;
    }
    if(GroupID==0)
    {
        if(this->AllplayersHashTable.getNumPlayersAtHash() < m)
        {
            *level=0;
            return FAILURE;
        }
        try
        {
            if(this->rankTree.isTreeEmpty()==true)
            {
                *level=0; //all the players are at level 0
                return SUCCESS;
            }
            int numPeopleAtTree=rankTree.getTotalNumPeopleAtTree();
            int updated_m=(m < numPeopleAtTree)?m:numPeopleAtTree; //we will sum only not level0
            int sum=this->rankTree.getSumOfHighestMPlayerLevel(0,updated_m,rankTree.getRoot());
            *level=((double)sum)/((double)m);
            return SUCCESS;
        }
        catch(std::bad_alloc& e) //should not get here - nothing is allocated!
        {
            *level=0;
            return ALLOCATION_ERROR;
        }
    }
    else
    {
        Group* group=unionFindGroups.getGroup(GroupID);
        if(group->getTotalNumPeopleAtGroup()<m)
        {
            *level=0;
            return FAILURE;
        }
        try
        {
            if(group->getTotalNumPeopleAtTree()==0) //tree is empty- all players at level 0
            {
                *level=0;
                return SUCCESS;
            }
            //num people at tree > 0
            int numPeopleAtTree=group->getTotalNumPeopleAtTree();
            int updated_m=(m < numPeopleAtTree)?m:numPeopleAtTree; //we will sum only not level0
            int sum=group->getGroupSumOfHighestMPlayerLevel(0,updated_m);
            *level=((double)sum)/((double)m);
            return SUCCESS;
        }
        catch(std::bad_alloc& e) //should not get here - nothing is allocated!
        {
            *level=0;
            return ALLOCATION_ERROR;
        }
    }
}
