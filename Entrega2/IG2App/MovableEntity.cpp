#include "MovableEntity.h"
#include "LabEntity.h"
#include "Labyrinths.h"


// Constructora Normal
MovableEntity::MovableEntity(const Vector3& initPos, SceneNode* node, SceneManager* mSM, const string& mesh, int vel)
    : IG2Object(initPos, node, mSM, mesh), dir_(1, 0, 0), nextDir_(dir_), lab_(nullptr), lifes_(3), vel_(vel), walled_(false)
{
    directions_ = { Vector3(1, 0, 0), Vector3(-1, 0, 0), Vector3(0, 1, 0), Vector3(0, -1, 0) };
    mNode->pitch(Degree(90));
    mNode->rotate(getOrientation().getRotationTo(dir_), Ogre::Node::TS_WORLD);
}

// Constructora Boss
MovableEntity::MovableEntity(const Vector3& initPos, SceneNode* node, SceneManager* mSM, int vel)
    : IG2Object(initPos, node, mSM), dir_(1, 0, 0), nextDir_(dir_), lab_(nullptr), lifes_(3), vel_(vel), walled_(false)
{
    directions_ = { Vector3(1, 0, 0), Vector3(-1, 0, 0), Vector3(0, 1, 0), Vector3(0, -1, 0) };
    mNode->pitch(Degree(90));
    mNode->rotate(getOrientation().getRotationTo(dir_), Ogre::Node::TS_WORLD);
}

bool MovableEntity::intersection()
{
    return !(((!lab_->getNextEntity(getPosition() + (directions_[0] * 98))->isUncrossable() && !lab_->getNextEntity(getPosition() + (directions_[1] * 98))->isUncrossable()) &&
        (lab_->getNextEntity(getPosition() + (directions_[2] * 98))->isUncrossable() && lab_->getNextEntity(getPosition() + (directions_[3] * 98))->isUncrossable())) ||
        ((!lab_->getNextEntity(getPosition() + (directions_[2] * 98))->isUncrossable() && !lab_->getNextEntity(getPosition() + (directions_[3] * 98))->isUncrossable()) &&
        (lab_->getNextEntity(getPosition() + (directions_[0] * 98))->isUncrossable() && lab_->getNextEntity(getPosition() + (directions_[1] * 98))->isUncrossable())));
}

void MovableEntity::checkMovement()
{
    if(intersection())
    {
        LabEntity* nextLabEntity = lab_->getNextEntity(getPosition() + (nextDir_ * 98));

        if (nextLabEntity->isUncrossable())
        {
            walled_ = true;
        }
        else if (!nextLabEntity->isUncrossable() || nextLabEntity == nullptr)
        {
            walled_ = false;
            dir_ = nextDir_;
            mNode->rotate(getOrientation().getRotationTo(dir_, Vector3(0, 0, 1)), Ogre::Node::TS_WORLD);
        }
    }

}

void MovableEntity::move(const Vector3& direction) const
{
    mNode->translate(direction * vel_);
}
