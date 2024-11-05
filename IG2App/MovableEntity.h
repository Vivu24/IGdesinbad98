#pragma once
#include "IG2Object.h"

class Labyrinths;

class MovableEntity :
    public IG2Object
{
public:
	MovableEntity(Vector3 initPos, SceneNode* node, SceneManager* mSM, string mesh);	// Constructora Normal
	MovableEntity(Vector3 initPos, SceneNode* node, SceneManager* mSM);	// Constructora Boss

	void setLab(Labyrinths* lab) { lab_ = lab; }
	void frameRendered(const Ogre::FrameEvent& evt) override {};

	Vector3 getNextDir() { return dir_; }
	bool intersection();
public:
	void checkMovement();
	void move(Vector3 direction);

	Vector3 dir_;
	Vector3 nextDir_;
	Labyrinths* lab_;

	int lifes_;

	bool walled_;
};

