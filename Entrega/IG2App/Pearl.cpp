#include "Pearl.h"

Pearl::Pearl(const Vector3& initPos, SceneNode* node, SceneManager* mSM, const string& mat) : 
	LabEntity(initPos, node, mSM, "sphere.mesh", mat)
{

}
