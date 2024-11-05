#pragma once
#include "Enemy.h"
class NormalEnemy :
    public Enemy
{
public:
    NormalEnemy(Vector3 initPos, SceneNode* node, SceneManager* mSM);
};

