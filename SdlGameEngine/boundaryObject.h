#ifndef BOUNDARYOBJECT_H
#define BOUNDARYOBJECT_H

#include "iGameObject.h"
#include "iCollideable.h"
#include "scoreKeeper.h"
#include "SDL.h"

class BoundaryObject : public IGameObject, public ICollideable 
{
public:
	BoundaryObject(int textureId, int x, int y, int w, int h, ScoreKeeper* scoreKeeper, int playerReward = 0, int enemyReward = 0)
	{
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
	void ResolveCollision(ICollideable* object) { this->scoreKeeper_->Update(this->playerReward_, this->enemyReward_); }
private:
	int playerReward_;
	int enemyReward_;
	int textureId_;
	SDL_Rect dest_;
	ScoreKeeper* scoreKeeper_;
};

#endif
