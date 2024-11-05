#include "Enemy.h"
#include "LabEntity.h"
#include "Labyrinths.h"

// Constructora Normal
Enemy::Enemy(Vector3 initPos, SceneNode* node, SceneManager* mSM, string mesh) :
	MovableEntity(initPos, node, mSM, mesh) 
{
	std::cout << "Enemy";
}

// Constructora Boss
Enemy::Enemy(Vector3 initPos, SceneNode* node, SceneManager* mSM) :
    MovableEntity(initPos, node, mSM)
{
    std::cout << "Trnasformer";
}

void Enemy::frameRendered(const Ogre::FrameEvent& evt)
{
    move(dir_);
    Vector3 auxPos = mNode->getPosition();
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
    if (!lab_->getNextEntity(getPosition() + (Vector3(1, 0, 0) * 98))->isWall() &&
        distance > (lab_->getSinbad()->getPosition() - (getPosition() + (Vector3(1, 0, 0) * 98))).length()) {

        distance = (lab_->getSinbad()->getPosition() - getPosition()).length();
        auxDir = Vector3(1, 0, 0);
    }
    if (!lab_->getNextEntity(getPosition() + (Vector3(-1, 0, 0) * 98))->isWall() && 
        distance > (lab_->getSinbad()->getPosition() - (getPosition() + (Vector3(-1, 0, 0) * 98))).length()) {

        distance = (lab_->getSinbad()->getPosition() - getPosition()).length();
        auxDir = Vector3(-1, 0, 0);
    }
    if (!lab_->getNextEntity(getPosition() + (Vector3(0, 1, 0) * 98))->isWall() && 
        distance > (lab_->getSinbad()->getPosition() - (getPosition() + (Vector3(0, 1, 0) * 98))).length()) {

        distance = (lab_->getSinbad()->getPosition() - getPosition()).length();
        auxDir = Vector3(0, 1, 0);
    }
    if (!lab_->getNextEntity(getPosition() + (Vector3(0, -1, 0) * 98))->isWall() && 
        distance > (lab_->getSinbad()->getPosition() - (getPosition() + (Vector3(0, -1, 0) * 98))).length()) {

        distance = (lab_->getSinbad()->getPosition() - getPosition()).length();
        auxDir = Vector3(0, -1, 0);
    }

    nextDir_ = auxDir;
    checkMovement();
}
