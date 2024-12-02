#include "Emoted.h"
#include <OgreInput.h>
#include <OgreKeyFrame.h>

Emoted::Emoted(SceneManager* sm, double vel) :
    _mSM(sm), 
    _movementLength(50), _duration(16), _keyframePos(0, 0, 0), _durStep(_duration / 4),
    _dancing(true), _sworded(false),
    _timer(new Timer())
{
	initScene();
    initAnim();
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
}

void Emoted::initScene()
{
    // PLANO
    MeshManager::getSingleton().createPlane(
        "mPlane150x300",
        ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        Plane(Vector3::UNIT_Z, 0),
        150, 300,
        100, 80,
        true,
        1,
        5.0, 5.0,
        Vector3::UNIT_Y
    );

    Entity* planeEntity = _mSM->createEntity("suelo", "mPlane150x300");
    planeEntity->setMaterialName(IG2App::getTexture(IG2App::MURO));
    SceneNode* planeNode = _mSM->getRootSceneNode()->createChildSceneNode("sueloNode");
    planeNode->attachObject(planeEntity);
    planeNode->pitch(Degree(-90));
    planeNode->roll(Degree(90));
    planeNode->setPosition(Vector3(0, -26, 15));


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
    _headNode->setPosition(Vector3(-90, 0, 0));
    _headNode->yaw(Degree(90));
}

void Emoted::initAnim()
{
    Animation* animation = _mSM->createAnimation("sinbadWalking", _duration);
    animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
    NodeAnimationTrack* track = animation->createNodeTrack(0);
    track->setAssociatedNode(_sinbadNode);
    TransformKeyFrame* kf;

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
}
