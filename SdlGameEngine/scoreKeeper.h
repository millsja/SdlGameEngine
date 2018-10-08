#ifndef SCOREKEEPER_H
#define SCOREKEEPER_H

#include <stdio.h>
#include "SDL.h"
#include "utilities.h"
#include <memory>
#include <string>
#include <sstream>
#include "sdlClient.h"

enum GameStatusEnum { INCOMPLETE = 0, PLAYER_VICTORY = 1, ENEMY_VICTORY = 2 };

class ScoreKeeper
{
public:
	ScoreKeeper(SdlClient* sdlClient);
	void SetWinThreshold(int winThreshold) { this->winThreshold_ = winThreshold; }
	void Update(int newPlayerPoints, int newEnemyPoints);
	GameStatusEnum GetGameStatus();
	int GetPlayerScore() { return this->playerPoints_; }
	int GetEnemyScore() { return this->enemyPoints_; }
	SDL_Texture* GetScoreTexture(int& w, int& h);
private:
	int cachedW_;
	int cachedH_;
	SdlClient* sdlClient_;
	std::unique_ptr<SDL_Texture, SdlDeleter> cachedScoreTexture_;
	bool scoreChange_;
	int playerPoints_;
	int enemyPoints_;
	int winThreshold_;
};

#endif