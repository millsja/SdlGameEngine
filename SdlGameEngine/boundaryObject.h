#ifndef BOUNDARYOBJECT_H
#define BOUNDARYOBJECT_H

#include "SDL.h"
#include "soundManager.h"
#include "iGameObject.h"
#include "iCollideable.h"
#include "scoreKeeper.h"
#include "ballObject.h"

class BoundaryObject : public IGameObject, public ICollideable 
{
public:
	BoundaryObject(int textureId, int x, int y, int w, int h, ScoreKeeper* scoreKeeper, ICollideable* ball, int playerReward, int enemyReward, SoundManager* soundManager, int soundId)
	{
		this->soundManager_ = soundManager;
		this->soundId_ = soundId;
		this->ball_ = ball;
		this->textureId_ = textureId;
		this->dest_.x = x;
		this->dest_.y = y;
		this->dest_.w = w;
		this->dest_.h = h;
		this->scoreKeeper_ = scoreKeeper;
		this->enemyReward_ = enemyReward;
		this->playerReward_ = playerReward;
	}
	void HandleEvents(SDL_Event* e, const Uint8* keystates = null) {}
	void SetLocation(int x, int y) { this->dest_.x = x; this->dest_.y = y; }
	SDL_Rect* GetDestination() { return &(this->dest_); }
	int GetTextureId() { return this->textureId_; };
	void ResolveCollision(ICollideable* object) 
	{ 
		if (object == this->ball_)
		{
			this->soundManager_->PlaySound(this->soundId_);
			this->scoreKeeper_->Update(this->playerReward_, this->enemyReward_);
		}
	}
private:
	int soundId_;
	SoundManager* soundManager_;
	ICollideable* ball_;
	int playerReward_;
	int enemyReward_;
	int textureId_;
	SDL_Rect dest_;
	ScoreKeeper* scoreKeeper_;
};

#endif
