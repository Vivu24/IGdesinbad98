#include "Sinbad.h"
#include "Labyrinths.h"
#include "LabEntity.h"
#include "Pearl.h"

Sinbad::Sinbad(Vector3 initPos, SceneNode* node, SceneManager* mSM) : 
	IG2Object(initPos, node, mSM, "Sinbad.mesh"), lifes_(3), points_(0), dir_(1, 0, 0), nextDir_(dir_), onCenter_(false), mLightNode_(nullptr)
{
    mNode->rotate(getOrientation().getRotationTo(dir_));
    mNode->roll(Degree(90));
}

void Sinbad::checkMovement()
{
    LabEntity* nextLabEntity = lab_->getNextEntity(getPosition() + (nextDir_ * 98));

    if (nextLabEntity->isWall())
    {
        dir_ = Vector3(0, 0, 0);
        //cout << "Wall" << endl;
    }
    else if (!nextLabEntity->isWall() || nextLabEntity == nullptr) {
        dir_ = nextDir_;
        mNode->rotate(getOrientation().getRotationTo(dir_), Ogre::Node::TS_WORLD);
        //cout << "NoWall" << endl;
    }

}

void Sinbad::collisions()
{
    LabEntity* currentLabEntity = lab_->getNextEntity(getPosition());

    if (!currentLabEntity->isDead_ && getAABB().intersects(currentLabEntity->getAABB()))
    {
        currentLabEntity->setVisible(false);
        currentLabEntity->isDead_ = true;

        //std::cout << "10 pts" << "\n";
        addPoints(10);
        lab_->updateHUD();
    }
}


void Sinbad::move(Vector3 direction)
{
	mNode->translate(direction);
}

void Sinbad::addPoints(int p)
{
    points_ += p;
}

void Sinbad::initLight(Ogre::SceneNode* l)
{
    mLightNode_ = l;
}

void Sinbad::updateLight()
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
        collisions();
    }
}
