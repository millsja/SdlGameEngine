#ifndef BLOCKSTATE_H
#define BLOCKSTATE_H

#include "utilities.h"
#include "iGameState.h"
#include "sdlClient.h"
#include "iCollideable.h"
#include "textureCollection.h"
#include "collisionDetector.h"
#include <map>
#include <string>
#include <vector>
#include "iGameObject.h"
#include "playerObject.h"
#include "enemyObject.h"
#include "boundaryObject.h"
#include "ballObject.h"
#include "scoreKeeper.h"
#include <sstream>
#include <memory>

#define string std::string

enum TextureIdEnum { NO_RENDER = 0, SPRITE_1 = 1, SPRITE_2 = 2, SPRITE_3 = 3 };

class BlockState : public IGameState
{
public:
	BlockState(SdlClient* sdlClient);
	void Sleep();
	void Start();
private:
	ScoreKeeper scoreKeeper_;
	CollisionDetector collisionDetector_;
	SdlClient* sdlClient_;
	TextureCollection collection_;
	std::vector<std::unique_ptr<IGameObject>> objects_;
};

#endif