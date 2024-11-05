#include "LabEntity.h"

LabEntity::LabEntity(const Vector3& initPos, SceneNode* node, SceneManager* mSM, const string& mesh, const string& mat) : 
	IG2Object(initPos, node, mSM, mesh), material_(mat)
{
	this->setMaterialName(mat);
}
