#ifndef SCOREKEEPER_H
#define SCOREKEEPER_H

#include <stdio.h>

enum GameStatusEnum { INCOMPLETE = 0, PLAYER_VICTORY = 1, ENEMY_VICTORY = 2 };

class ScoreKeeper
{
public:
	ScoreKeeper();
	void SetWinThreshold(int winThreshold) { this->winThreshold_ = winThreshold; }
	void Update(int newPlayerPoints, int newEnemyPoints);
	GameStatusEnum GetGameStatus();
private:
	int playerPoints_;
	int enemyPoints_;
	int winThreshold_;
};

#endif