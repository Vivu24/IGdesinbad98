#pragma once
#include "IG2Object.h"
#include <OgreInput.h>

class Labyrinths;

class Sinbad : public IG2Object, OgreBites::InputListener
{
public:
	//Sinbad() {};

	Sinbad(Vector3 initPos, SceneNode* node, SceneManager* mSM);

	bool keyPressed(const OgreBites::KeyboardEvent& evt) override;
	void frameRendered(const Ogre::FrameEvent& evt) override;

	void checkMovement();
	void collisions();
	void move(Vector3 direction);
	void addPoints(int p);
	void setLab(Labyrinths* lab) { lab_ = lab; }
	void initLight(Ogre::SceneNode* l);
	void updateLight();

	int lifes_;
	int points_;

private:
	Vector3 dir_;
	Vector3 nextDir_;
	Labyrinths* lab_;

	Ogre::SceneNode* mLightNode_;

	bool onCenter_;
};

