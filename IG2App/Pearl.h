#pragma once
#include "LabEntity.h"

class Pearl : public LabEntity
{
public:
	Pearl(const Vector3& initPos, SceneNode* node, SceneManager* mSM, const string& mat);

	bool isUncrossable() override { return false; }
};

