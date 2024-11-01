#include "Wall.h"

Wall::Wall(Vector3 initPos, SceneNode* node, SceneManager* mSM, string mat) :
    LabEntity(initPos, node, mSM, "cube.mesh", mat)
{

}
