#include "NormalEnemy.h"

NormalEnemy::NormalEnemy(const Vector3& initPos, SceneNode* node, SceneManager* mSM, const int vel) :
	Enemy(initPos, node, mSM, "ogrehead.mesh", vel)
{
}
