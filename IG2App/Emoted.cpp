#include "Emoted.h"
#include <OgreInput.h>
#include <OgreKeyFrame.h>
#include <OgreParticleSystem.h>

Emoted::Emoted(SceneManager* sm, double vel) :
    _mSM(sm), 
    _movementLength(50), _duration(16), _keyframePos(0, 0, 0), _durStep(_duration / 4),
    _dancing(true), _sworded(false),
    _timer(new Timer())
{
	initScene();
    initAnim();
    initParticles();
}

void Emoted::frameRendered(const Ogre::FrameEvent& evt)
{
    if (_dancing && _timer->getMilliseconds() >= 5000) 
    {
        _dancing = false;
        _sinbadAnimationState->setEnabled(false);
        _sinbadAnimationState = _mSM->getAnimationState("sinbadWalking");
        _sinbadAnimationState->setEnabled(true);

        _animationStateRunTop->setEnabled(true);
        _animationStateRunTop->setLoop(true);

        _animationStateRunBase->setEnabled(true);
        _animationStateRunBase->setLoop(true);
    }

    if (!_sworded && _timer->getMilliseconds() >= 9000)
    {
        _sworded = true;

        Entity* swordR = _mSM->createEntity("Sword.mesh");
        Entity* swordL = _mSM->createEntity("Sword.mesh");

        _sinbad->attachObjectToBone("Handle.R", swordR);
        _sinbad->attachObjectToBone("Handle.L", swordL);
    }

    if (!_dancing && _timer->getMilliseconds() >= 21000)
    {
        _dancing = true;
        _sinbadAnimationState = _sinbad->getAnimationState("Dance");
        _sinbadAnimationState->setEnabled(true);
        _sinbadAnimationState->setLoop(true);

        _animationStateRunTop->setEnabled(false);
        _animationStateRunBase->setEnabled(false);

        if (_sworded)
        {
            _sinbad->detachAllObjectsFromBone();
            _sworded = false;
        }

        _timer->reset();
    }

    _sinbadAnimationState->addTime(evt.timeSinceLastFrame);
    _animationStateRunTop->addTime(evt.timeSinceLastFrame);
    _animationStateRunBase->addTime(evt.timeSinceLastFrame);

    _headAnimationState->addTime(evt.timeSinceLastFrame);
}




void Emoted::initScene()
{
    // ESFERA
    Entity* sphereEntity = _mSM->createEntity("sphere", "uv_sphere.mesh");
    SceneNode* sphereNode = _mSM->getRootSceneNode()->createChildSceneNode("sphereNode");
    sphereNode->attachObject(sphereEntity);
    sphereEntity->setMaterialName("corrosion");
    sphereNode->setScale(0.25, 0.25, 0.25);
    sphereNode->setPosition(0, 0, -50);


    // PLANO
    MeshManager::getSingleton().createPlane(
        "mPlane150x300",
        ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        Plane(Vector3::UNIT_Z, 0),
        600, 150,
        100, 80,
        true,
        1,
        5.0, 5.0,
        Vector3::UNIT_Y
    );

    Entity* planeEntity = _mSM->createEntity("suelo", "mPlane150x300");
    _planeNode = _mSM->getRootSceneNode()->createChildSceneNode("sueloNode");
    _planeNode->attachObject(planeEntity);
    _planeNode->pitch(Degree(-90));
    //_planeNode->roll(Degree(90));
    _planeNode->setPosition(Vector3(0, -26, 15));
    _planeNode->setInitialState();
    planeEntity->setMaterialName("practica2/wavesShader");


    // SINBAD
    _sinbad = _mSM->createEntity("Sinbad.mesh");
    _sinbadNode = _mSM->getRootSceneNode()->createChildSceneNode("sinNode");
    _sinbadNode->attachObject(_sinbad);
    _sinbadNode->setScale(3, 3, 3);
    _sinbadNode->setPosition(0, -10, 0);
    _sinbadNode->setInitialState();

    // OGREHEAD
    _head = _mSM->createEntity("ogrehead.mesh");
    _headNode = _mSM->getRootSceneNode()->createChildSceneNode("headNode");
    _headNode->attachObject(_head);
    _headNode->setPosition(Vector3(-100, -10, 0));
    _headNode->setScale(0.5, 0.5, 0.5);
    _headNode->yaw(Degree(90));
    _headNode->setInitialState();
}

void Emoted::createFires(SceneNode* parentNode, int numFires, float spacing) {
    string particleName = "psFireCenter";
    ParticleSystem* pSysCenter = _mSM->createParticleSystem(particleName, "example/fireeeParticle");
    pSysCenter->setEmitting(true);

    SceneNode* fireNodeCenter = parentNode->createChildSceneNode("fireNodeCenter");
    fireNodeCenter->attachObject(pSysCenter);
    fireNodeCenter->setPosition(Vector3(0, 100, 0));
    fireNodeCenter->pitch(Degree(90));

    _fireParticles.push_back(pSysCenter);

    for (int i = 0; i < numFires; ++i) {
        std::string particleName = "psFire" + std::to_string(i);
        ParticleSystem* pSys = _mSM->createParticleSystem(particleName, "example/fireeeParticle");
        pSys->setEmitting(true);

        SceneNode* fireNode = parentNode->createChildSceneNode("fireNode" + std::to_string(i));
        fireNode->attachObject(pSys);

        float offsetX = (i % 2 == 0 ? 1 : -1) * spacing * ((i / 2) + 1);
        fireNode->setPosition(Vector3(offsetX, 100, 0));
        fireNode->pitch(Degree(90));

        _fireParticles.push_back(pSys);
    }
}

void Emoted::initParticles()
{
    ParticleSystem* pSys1 = _mSM->createParticleSystem("psSmoke", "example/smoookeParticle");
    pSys1->setEmitting(true);
    _headNode->attachObject(pSys1);

    createFires(_planeNode, 10, 25);
}

void Emoted::initAnim()
{
    Animation* animation;
    NodeAnimationTrack* track;
    TransformKeyFrame* kf;
#pragma region Sinbad
    animation = _mSM->createAnimation("sinbadWalking", _duration);
    animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
    track = animation->createNodeTrack(0);
    track->setAssociatedNode(_sinbadNode);

    // Keyframe 0
    kf = track->createNodeKeyFrame(0);

    // Keyframe 1 Giro
    kf = track->createNodeKeyFrame(1);
    kf->setRotation(Quaternion(Degree(90.0), Vector3(0, 1, 0)));

    // Keyframe 2 Derecha
    kf = track->createNodeKeyFrame(4);
    _keyframePos += Ogre::Vector3::UNIT_X * _movementLength;
    kf->setTranslate(_keyframePos);
    kf->setRotation(Quaternion(Degree(90.0), Vector3(0, 1, 0)));

    // Keyframe 3 Gira
    kf = track->createNodeKeyFrame(5);
    kf->setTranslate(_keyframePos);
    kf->setRotation(Quaternion(Degree(-90.0), Vector3(0, 1, 0)));

    // Keyframe 4 Izquierda
    kf = track->createNodeKeyFrame(11);
    _keyframePos += Ogre::Vector3::NEGATIVE_UNIT_X * _movementLength * 2;
    kf->setTranslate(_keyframePos);
    kf->setRotation(Quaternion(Degree(-90.0), Vector3(0, 1, 0)));

    // Keyframe 5 Gira
    kf = track->createNodeKeyFrame(12);
    kf->setTranslate(_keyframePos);
    kf->setRotation(Quaternion(Degree(90.0), Vector3(0, 1, 0)));

    // Keyframe 6 Derecha
    kf = track->createNodeKeyFrame(15);
    _keyframePos += Ogre::Vector3::UNIT_X * _movementLength;
    kf->setTranslate(_keyframePos);
    kf->setRotation(Quaternion(Degree(90.0), Vector3(0, 1, 0)));

    // Keyframe 7 Giro
    kf = track->createNodeKeyFrame(16);
    kf->setRotation(Quaternion(Degree(0.0), Vector3(0, 1, 0)));

    _sinbadAnimationState = _mSM->createAnimationState("sinbadWalking");

    _animationStateRunTop = _sinbad->getAnimationState("RunTop");
    _animationStateRunBase = _sinbad->getAnimationState("RunBase");

    _sinbadAnimationState = _sinbad->getAnimationState("Dance");
    _sinbadAnimationState->setEnabled(true);
#pragma endregion

#pragma region Head
    animation = _mSM->createAnimation("headWalking", _duration + 5);
    animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
    track = animation->createNodeTrack(1);
    track->setAssociatedNode(_headNode);

    // Keyframe 0 Quieto
    kf = track->createNodeKeyFrame(0);

    // Keyframe 1 Derecha
    kf = track->createNodeKeyFrame(9);
    _keyframePos += Ogre::Vector3::UNIT_X * _movementLength * 2;
    kf->setTranslate(_keyframePos);

    // Keyframe 2 Gira
    kf = track->createNodeKeyFrame(10);
    kf->setTranslate(_keyframePos);
    kf->setRotation(Quaternion(Degree(180.0), Vector3(0, 1, 0)));

    // Keyframe 3 Izquierda
    kf = track->createNodeKeyFrame(16);
    _keyframePos += Ogre::Vector3::NEGATIVE_UNIT_X * _movementLength * 2;
    kf->setTranslate(_keyframePos);
    kf->setRotation(Quaternion(Degree(180.0), Vector3(0, 1, 0)));

    // Keyframe 4 Gira
    kf = track->createNodeKeyFrame(17);
    kf->setTranslate(_keyframePos);

    // Keyframe 5 Derecha
    kf = track->createNodeKeyFrame(21);
    _keyframePos += Ogre::Vector3::UNIT_X * _movementLength * 2;
    kf->setTranslate(_keyframePos);
    kf->setScale(Vector3(0, 0, 0));

    _headAnimationState = _mSM->createAnimationState("headWalking");
    _headAnimationState->setEnabled(true);
    _headAnimationState->setLoop(true);
#pragma endregion

}
