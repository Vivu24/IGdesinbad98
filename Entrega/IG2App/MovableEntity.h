#pragma once
#include "IG2Object.h"

class Labyrinths;

class MovableEntity :
    public IG2Object
{
public:
	MovableEntity(const Vector3& initPos, SceneNode* node, SceneManager* mSM, const string& mesh, int vel);	// Constructora Normal
	MovableEntity(const Vector3& initPos, SceneNode* node, SceneManager* mSM, int vel);	// Constructora Boss

	void setLab(Labyrinths* lab) { lab_ = lab; }
	void frameRendered(const Ogre::FrameEvent& evt) override {}
	int lifes() const { return lifes_; }

	Vector3 getNextDir() const { return dir_; }
protected:
	void checkMovement();
	void move(const Vector3& direction) const;
	bool intersection();

	std::vector<Vector3> directions_;
	Vector3 dir_;
	Vector3 nextDir_;
	Labyrinths* lab_;

	int lifes_;
	int vel_;

	bool walled_;
};

