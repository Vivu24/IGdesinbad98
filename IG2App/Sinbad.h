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

	void setLab(Labyrinths* lab) { lab_ = lab; }
private:
	void collisions();
	void checkMovement();
	void addPoints(int p);
	void move(Vector3 direction);

	int lifes_;
	int points_;

	Vector3 dir_;
	Vector3 nextDir_;
	Labyrinths* lab_;

	bool onCenter_;
};

