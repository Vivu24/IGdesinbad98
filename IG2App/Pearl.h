#pragma once
#include "LabEntity.h"

class Pearl : public LabEntity
{
public:
	Pearl(const Vector3& initPos, SceneNode* node, SceneManager* mSM, const string& mat);

	bool isWall() override { return false; }
};

