#pragma once
#include "LabEntity.h"

class Pearl : public LabEntity
{
public:
	Pearl(Vector3 initPos, SceneNode* node, SceneManager* mSM);

	bool isWall() override { return false; }
private:
};

