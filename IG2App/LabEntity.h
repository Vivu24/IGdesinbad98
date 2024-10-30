#pragma once
#include "IG2Object.h"
class LabEntity : public IG2Object
{
public:
	LabEntity(Vector3 initPos, SceneNode* node, SceneManager* mSM, string mesh);

	bool isDead_ = false;
public:
	virtual bool isWall() = 0;
};

