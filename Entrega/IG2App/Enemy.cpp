#include "Enemy.h"
#include "LabEntity.h"
#include "Labyrinths.h"

// Constructora Normal
Enemy::Enemy(const Vector3& initPos, SceneNode* node, SceneManager* mSM, const string& mesh, int vel) :
	MovableEntity(initPos, node, mSM, mesh, vel) 
{
	std::cout << "Enemy";
}

// Constructora Boss
Enemy::Enemy(const Vector3& initPos, SceneNode* node, SceneManager* mSM, int vel) :
    MovableEntity(initPos, node, mSM, vel)
{
    std::cout << "Transformer";
}

void Enemy::frameRendered(const Ogre::FrameEvent& evt)
{
    move(dir_);
    const Vector3 auxPos = mNode->getPosition();
    // Enemigo Centrado
    if (((int)auxPos.x % 98 == 0) && ((int)auxPos.y % 98 == 0))
    {
        checkMovement();
        if (walled_ || intersection()) nextDirection();
    }
}

void Enemy::nextDirection()
{
    Vector3 auxDir;
    double distance = lab_->diagonal().length();

    for(auto direction : directions_)
    {
        if (!lab_->getNextEntity(getPosition() + (direction * 98))->isWall() &&
            distance > (lab_->getSinbad()->getPosition() - (getPosition() + (direction * 98))).length()) {

            distance = (lab_->getSinbad()->getPosition() - getPosition()).length();
            auxDir = direction;
        }
    }

    nextDir_ = auxDir;
    checkMovement();
}
