
#include "employee.h"

Employee::Employee(int player_id, int player_group_id ,int player_score):
    playerId(player_id),playerScore(player_score),playerLevel(0),
    playerGroupId(player_group_id){}

int Employee::getPlayerId() const
{
    return this->playerId;
}
int Employee::getPlayerGroupId() const
{
    return this->playerGroupId;
}

int Employee::getPlayerLevel() const
{
    return this->playerLevel;
}
int Employee::getPlayerScore() const
{
    return this->playerScore;
}

void Employee::setPlayerGroupId(int groupId)
{
    this->playerGroupId=groupId;
}

void Employee::setPlayerLevel(int level)
{
    this->playerLevel=level;
}
void Employee::setPlayerScore(int score)
{
    this->playerScore=score;
}

