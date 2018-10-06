#include "scoreKeeper.h"

ScoreKeeper::ScoreKeeper()
{
	this->winThreshold_ = 0;
	this->enemyPoints_ = 0;
	this->playerPoints_ = 0;
}

GameStatusEnum ScoreKeeper::GetGameStatus()
{
	if (this->enemyPoints_ >= this->winThreshold_)
	{
		return GameStatusEnum::ENEMY_VICTORY;
	}
	else if (this->playerPoints_ >= this->winThreshold_)
	{
		return GameStatusEnum::PLAYER_VICTORY;
	}
	else
	{
		return GameStatusEnum::INCOMPLETE;
	}
}

void ScoreKeeper::Update(int newPlayerPoints, int newEnemyPoints)
{
	this->enemyPoints_ += newEnemyPoints;
	this->playerPoints_ += newPlayerPoints;
	printf("p: %d; e %d\n", this->playerPoints_, this->enemyPoints_);
}