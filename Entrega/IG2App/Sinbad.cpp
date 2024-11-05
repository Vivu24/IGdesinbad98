#include "Sinbad.h"
#include "Labyrinths.h"
#include "LabEntity.h"

Sinbad::Sinbad(const Vector3& initPos, SceneNode* node, SceneManager* mSM, const int vel) : 
	MovableEntity(initPos, node, mSM, "Sinbad.mesh", vel), points_(0), mLightNode_(nullptr)
{
    std::cout << "Sinbad";
}

void Sinbad::addPoints(const int p)
{
    points_ += p;
}

void Sinbad::initLight(Ogre::SceneNode* l)
{
    mLightNode_ = l;
}

void Sinbad::collisions()
{
    LabEntity* currentLabEntity = lab_->getNextEntity(getPosition());

    if (!currentLabEntity->isDead_ && getAABB().intersects(currentLabEntity->getAABB()))
    {
        currentLabEntity->setVisible(false);
        currentLabEntity->isDead_ = true;

        addPoints(10);
        lab_->updateHud();
    }
}

void Sinbad::updateLight() const
{
    mLightNode_->setPosition(this->mNode->getPosition().x, this->mNode->getPosition().y, this->mNode->getPosition().z + 100);
}

bool Sinbad::keyPressed(const OgreBites::KeyboardEvent& evt) 
{
    // Movimiento Sinbad
    if (evt.keysym.sym == SDLK_UP) {
        nextDir_ = Vector3(0, 1, 0);
    }
    else if (evt.keysym.sym == SDLK_DOWN) {
        nextDir_ = Vector3(0, -1, 0);
    }
    else if (evt.keysym.sym == SDLK_LEFT) {
        nextDir_ = Vector3(-1, 0, 0);
    }
    else if (evt.keysym.sym == SDLK_RIGHT) {
        nextDir_ = Vector3(1, 0, 0);
    }
    return true;
}

void Sinbad::frameRendered(const Ogre::FrameEvent& evt)
{
    move(dir_);
    Vector3 auxPos = mNode->getPosition();
    updateLight();
    // Sinbad Centrado
    if (((int)auxPos.x % 98 == 0) && ((int)auxPos.y % 98 == 0))
    {
        checkMovement();
        if (walled_) dir_ = Vector3(0, 0, 0);
        collisions();
    }
}
