#pragma once
#include "IG2App.h"
#include "OgreAnimation.h"
#include <OgreTimer.h>
#include <vector>

class Emoted : public OgreBites::InputListener
{
public:
	Emoted(SceneManager* sm, double vel);
	void frameRendered(const Ogre::FrameEvent& evt) override;

private: 
	SceneManager* _mSM;
	
	Entity* _sinbad;
	Entity* _head;
	SceneNode* _sinbadNode;
	SceneNode* _headNode;
	SceneNode* _planeNode;

	std::vector<ParticleSystem*> _fireParticles;

	AnimationState* _sinbadAnimationState;
	AnimationState* _animationStateRunTop;
	AnimationState* _animationStateRunBase;
	AnimationState* _headAnimationState;

	int _movementLength;
	Real _duration;
	Vector3 _keyframePos;
	Real _durStep;

	bool _dancing;
	bool _sworded;

	Timer* _timer;

	void initScene();
	void initAnim();
	void initParticles();

	void createFires(SceneNode* parentNode, int numFires, float spacing);
};

