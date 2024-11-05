#include "Wall.h"

Wall::Wall(const Vector3& initPos, SceneNode* node, SceneManager* mSM, const string& mat) :
    LabEntity(initPos, node, mSM, "cube.mesh", mat)
{

}
