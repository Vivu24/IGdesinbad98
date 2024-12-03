#pragma once
#include "MovableEntity.h"
#include <OgreTimer.h>

class Enemy :
    public MovableEntity
{
public:
    Enemy(const Vector3& initPos, SceneNode* node, SceneManager* mSM, const string& mesh, int vel);
    Enemy(const Vector3& initPos, SceneNode* node, SceneManager* mSM, int vel);

    void frameRendered(const Ogre::FrameEvent& evt) override;

private:
    void nextDirection();
};

