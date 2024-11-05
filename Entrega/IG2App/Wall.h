#pragma once
#include "LabEntity.h"

class Wall : public LabEntity
{
public:
	Wall(const Vector3& initPos, SceneNode* node, SceneManager* mSM, const string& mat);

	bool isWall() override { return true; }
};

