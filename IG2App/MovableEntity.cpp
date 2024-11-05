#include "MovableEntity.h"
#include "LabEntity.h"
#include "Labyrinths.h"


// Constructora Normal
MovableEntity::MovableEntity(Vector3 initPos, SceneNode* node, SceneManager* mSM, string mesh)
    : IG2Object(initPos, node, mSM, mesh), lifes_(3), dir_(1, 0, 0), nextDir_(dir_), lab_(nullptr), walled_(false)
{
    mNode->rotate(getOrientation().getRotationTo(dir_));
    mNode->roll(Degree(90));
}

// Constructora Boss
MovableEntity::MovableEntity(Vector3 initPos, SceneNode* node, SceneManager* mSM)
    : IG2Object(initPos, node, mSM), lifes_(3), dir_(1, 0, 0), nextDir_(dir_), lab_(nullptr), walled_(false)
{
    mNode->rotate(getOrientation().getRotationTo(dir_));
    mNode->roll(Degree(90));
}

bool MovableEntity::intersection()
{
    return !(((!lab_->getNextEntity(getPosition() + (Vector3(1, 0, 0) * 98))->isWall() && !lab_->getNextEntity(getPosition() + (Vector3(-1, 0, 0) * 98))->isWall()) &&
        (lab_->getNextEntity(getPosition() + (Vector3(0, 1, 0) * 98))->isWall() && lab_->getNextEntity(getPosition() + (Vector3(0, -1, 0) * 98))->isWall())) ||
        ((!lab_->getNextEntity(getPosition() + (Vector3(0, 1, 0) * 98))->isWall() && !lab_->getNextEntity(getPosition() + (Vector3(0, -1, 0) * 98))->isWall()) &&
        (lab_->getNextEntity(getPosition() + (Vector3(1, 0, 0) * 98))->isWall() && lab_->getNextEntity(getPosition() + (Vector3(-1, 0, 0) * 98))->isWall())));
}

void MovableEntity::checkMovement()
{
    if(intersection())
    {
        LabEntity* nextLabEntity = lab_->getNextEntity(getPosition() + (nextDir_ * 98));

        if (nextLabEntity->isWall())
        {
            walled_ = true;
            //cout << "Wall" << endl;
        }
        else if (!nextLabEntity->isWall() || nextLabEntity == nullptr)
        {
            walled_ = false;
            dir_ = nextDir_;
            2012
            //cout << "NoWall" << endl;
        }
    }

}

void MovableEntity::move(Vector3 direction)
{
    mNode->translate(direction * 2);
}
