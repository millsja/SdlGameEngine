#ifndef BLOCKSTATE_H
#define BLOCKSTATE_H

#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <memory>
#include "utilities.h"
#include "iGameState.h"
#include "sdlClient.h"
#include "iCollideable.h"
#include "textureCollection.h"
#include "collisionDetector.h"
#include "iGameObject.h"
#include "playerObject.h"
#include "enemyObject.h"
#include "boundaryObject.h"
#include "ballObject.h"
#include "scoreKeeper.h"
#include "soundManager.h"

enum TextureIdEnum { NO_RENDER = 0, SPRITE_1 = 1, SPRITE_2 = 2, SPRITE_3 = 3 };
enum SoundEffectEnum { HIT = 0, SCORE = 1, WIN = 2, LOSE = 3 };

class BlockState : public IGameState
{
public:
	BlockState(SdlClient* sdlClient, int maxPoints, bool accelerate, float maxSpeed);
	void Sleep();
	void Start();
private:
	ScoreKeeper scoreKeeper_;
	SoundManager soundManager_;
	CollisionDetector collisionDetector_;
	SdlClient* sdlClient_;
	TextureCollection collection_;
	std::vector<std::unique_ptr<IGameObject>> objects_;
};

#endif