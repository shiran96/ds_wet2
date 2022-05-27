#ifndef PLAYER_H
#define PLAYER_H

class Player
{
    private:
    int playerId;
    int playerScore;
    int playerLevel;
    int playerGroupId;

    public:
    Player(int player_id, int player_group_id ,int player_score);
    ~Player() = default;
    Player(const Player& player) = default;
    Player& operator=(const Player& other) = default;
    
    //get the current information of the player
    int getPlayerId() const;
    int getPlayerGroupId() const;
    int getPlayerLevel() const;
    int getPlayerScore() const;
    
    //update the information of the player
    void setPlayerGroupId(int groupId);
    void setPlayerLevel(int level);
    void setPlayerScore(int score);

    // //operation for sorting players by level for AVL tree
    // //maybe class instead with operator()
    // friend bool operator<(const Player& p1, const Player& p2);
    // friend bool operator>(const Player& p1, const Player& p2);

};

#endif /*PLAYER_H*/