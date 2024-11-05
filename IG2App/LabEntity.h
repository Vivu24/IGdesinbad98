#pragma once
#include "IG2Object.h"
class LabEntity : public IG2Object
{
public:
	LabEntity(const Vector3& initPos, SceneNode* node, SceneManager* mSM, const string& mesh, const string& mat);
	bool isDead_ = false;
	virtual bool isWall() = 0;
protected:
	string material_;
};

