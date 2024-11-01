#pragma once
#include "LabEntity.h"

class Pearl : public LabEntity
{
public:
	Pearl(Vector3 initPos, SceneNode* node, SceneManager* mSM, string mat);

	bool isWall() override { return false; }
private:
};

