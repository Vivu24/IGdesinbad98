#include "LabEntity.h"

LabEntity::LabEntity(Vector3 initPos, SceneNode* node, SceneManager* mSM, string mesh, string mat) : 
	material_(mat), IG2Object(initPos, node, mSM, mesh)
{
	this->setMaterialName(mat);
}
