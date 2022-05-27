
#include "player.h"

Player::Player(int player_id, int player_group_id ,int player_score):
    playerId(player_id),playerScore(player_score),playerLevel(0),
    playerGroupId(player_group_id)
    {};

int Player::getPlayerId() const
{
    return this->playerId;
}
int Player::getPlayerGroupId() const
{
    return this->playerGroupId;
}

int Player::getPlayerLevel() const
{
    return this->playerLevel;
}
int Player::getPlayerScore() const
{
    return this->playerScore;
}

void Player::setPlayerGroupId(int groupId)
{
    this->playerGroupId=groupId;
}

void Player::setPlayerLevel(int level)
{
    this->playerLevel=level;
}
void Player::setPlayerScore(int score)
{
    this->playerScore=score;
}

