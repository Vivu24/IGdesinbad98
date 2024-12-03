#pragma once
#include "Enemy.h"
class Transformer :
    public Enemy
{
public:
    Transformer(const Vector3& initPos, SceneNode* node, SceneManager* mSM, int vel = 1);
	void frameRendered(const Ogre::FrameEvent& evt) override;

private:
	//Nos guardamos los nodos de las cosas que queremos que roten
	SceneNode* nPlaneta;
	SceneNode* nPlaneta2;

	Real angle_;

	Timer* timer_;
};

