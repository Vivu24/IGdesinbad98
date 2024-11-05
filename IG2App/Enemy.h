#pragma once
#include "MovableEntity.h"
#include <OgreTimer.h>

class Enemy :
    public MovableEntity
{
public:
    Enemy(Vector3 initPos, SceneNode* node, SceneManager* mSM, string mesh);
    Enemy(Vector3 initPos, SceneNode* node, SceneManager* mSM);

    void frameRendered(const Ogre::FrameEvent& evt) override;

private:
    void nextDirection();
};

