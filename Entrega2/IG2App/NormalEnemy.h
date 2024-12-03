#pragma once
#include "Enemy.h"
class NormalEnemy :
    public Enemy
{
public:
    NormalEnemy(const Vector3& initPos, SceneNode* node, SceneManager* mSM, int vel = 1);
};

