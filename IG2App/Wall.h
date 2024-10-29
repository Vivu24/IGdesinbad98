#pragma once
#include "LabEntity.h"

class Wall : public LabEntity
{
public:
	Wall(Vector3 initPos, SceneNode* node, SceneManager* mSM);

	bool isWall() override { return true; }
private:
};

