#pragma once
#include "MovableEntity.h"

class Sinbad : public MovableEntity
{
public:
	//Sinbad() {};

	Sinbad(Vector3 initPos, SceneNode* node, SceneManager* mSM);

	bool keyPressed(const OgreBites::KeyboardEvent& evt) override;
	void frameRendered(const Ogre::FrameEvent& evt) override;

	void initLight(Ogre::SceneNode* l);

	int points_;

private:
	void collisions();
	void updateLight();
	void addPoints(int p);

	Ogre::SceneNode* mLightNode_;
};

