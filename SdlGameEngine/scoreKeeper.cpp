#include "scoreKeeper.h"

ScoreKeeper::ScoreKeeper(SdlClient* sdlClient)
{
	this->sdlClient_ = sdlClient;
	this->scoreChange_ = true;
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
	this->scoreChange_ = true;
	this->enemyPoints_ += newEnemyPoints;
	this->playerPoints_ += newPlayerPoints;
	printf("p: %d; e %d\n", this->playerPoints_, this->enemyPoints_);
}

SDL_Texture* ScoreKeeper::GetScoreTexture()
{
	if (this->scoreChange_ == true)
	{
		this->scoreChange_ = false;
		std::ostringstream scoreStream;
		scoreStream << this->GetPlayerScore() << " | " << this->GetEnemyScore();
		std::string scores = scoreStream.str();
		SDL_Color textColor = { 0, 0, 0};
		this->sdlClient_->RenderText(scores, textColor, 0, 0);
	}

	return this->cachedScoreTexture_.get();
}