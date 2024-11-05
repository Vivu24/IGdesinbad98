#pragma once
#include "MovableEntity.h"

class Sinbad : public MovableEntity
{
public:
	Sinbad(const Vector3& initPos, SceneNode* node, SceneManager* mSM, int vel = 1);

	bool keyPressed(const OgreBites::KeyboardEvent& evt) override;
	void frameRendered(const Ogre::FrameEvent& evt) override;

	void initLight(Ogre::SceneNode* l);
	int points() const { return points_; }
private:
	void collisions();
	void updateLight() const;
	void addPoints(int p);

	int points_;
	Ogre::SceneNode* mLightNode_;
};

