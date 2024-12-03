#include "Transformer.h"

Transformer::Transformer(const Vector3& initPos, SceneNode* node, SceneManager* mSM, const int vel) :
	Enemy(initPos, node, mSM, vel), angle_(25), timer_(new Timer())
{
    auto nSol = mNode->createChildSceneNode();

    nPlaneta = nSol->createChildSceneNode();
    nPlaneta2 = nSol->createChildSceneNode();  

    auto fuego = nPlaneta->createChildSceneNode(); 
    auto aire = nPlaneta->createChildSceneNode();
    auto tierra = nPlaneta->createChildSceneNode();

    auto fuego2 = nPlaneta2->createChildSceneNode();
    auto aire2 = nPlaneta2->createChildSceneNode();
    auto tierra2 = nPlaneta2->createChildSceneNode();

    auto cola = nSol->createChildSceneNode();


    Entity* Cuerpo = mSM->createEntity("sphere.mesh");
    nSol->attachObject(Cuerpo);
    nSol->setScale(Vector3(0.2, 0.2, 0.2));

    Entity* Saturno = mSM->createEntity("sphere.mesh");
    nPlaneta->attachObject(Saturno);
    nPlaneta->setScale(Vector3(0.25, 0.25, 0.25));
    nPlaneta->setPosition(Vector3(150, 0, 0));

    Entity* Neptuno = mSM->createEntity("sphere.mesh");
    nPlaneta2->attachObject(Neptuno);
    nPlaneta2->setScale(Vector3(0.25, 0.25, 0.25));
    nPlaneta2->setPosition(Vector3(-150, 0, 0));

    Entity* f = mSM->createEntity("ogrehead.mesh");
    fuego->attachObject(f);
    fuego->setPosition(Vector3(0, Saturno->getBoundingRadius(), 0));
    fuego->setScale(Vector3(2, 2, 2));

    Entity* a = mSM->createEntity("ogrehead.mesh");
    aire->attachObject(a);
    aire->setScale(Vector3(2, 2, 2));
    aire->roll(Degree(90));
    aire->setPosition(-Vector3(Saturno->getBoundingRadius(), 0, 0));

    Entity* t = mSM->createEntity("ogrehead.mesh");
    tierra->attachObject(t);
    tierra->setScale(Vector3(2, 2, 2));
    tierra->roll(Degree(-90));
    tierra->setPosition(Vector3(Saturno->getBoundingRadius(), 0, 0));

    Entity* f2 = mSM->createEntity("ogrehead.mesh");
    fuego2->attachObject(f2);
    fuego2->setPosition(Vector3(0, Neptuno->getBoundingRadius(), 0));
    fuego2->setScale(Vector3(2, 2, 2));

    Entity* a2 = mSM->createEntity("ogrehead.mesh");
    aire2->attachObject(a2);
    aire2->setScale(Vector3(2, 2, 2));
    aire2->roll(Degree(90));
    aire2->setPosition(-Vector3(Neptuno->getBoundingRadius(), 0, 0));

    Entity* t2 = mSM->createEntity("ogrehead.mesh");
    tierra2->attachObject(t2);
    tierra2->setScale(Vector3(2, 2, 2));
    tierra2->roll(Degree(-90));
    tierra2->setPosition(Vector3(Neptuno->getBoundingRadius(), 0, 0));

    Entity* c = mSM->createEntity("knot.mesh");
    cola->attachObject(c);
    cola->setScale(Vector3(0.5, 0.5, 0.5));
    cola->setPosition(Vector3(0, 0, -Cuerpo->getBoundingRadius() + 50));
}

void Transformer::frameRendered(const Ogre::FrameEvent& evt)
{
    nPlaneta->rotate(Quaternion(Radian(angle_), Vector3(0, 0, 1)));
    nPlaneta2->rotate(Quaternion(Radian(-angle_), Vector3(0, 0, 1)));

    if (timer_->getMilliseconds() >= 10000) 
    {
        timer_->reset();
        angle_ *= -1;
    }

    Enemy::frameRendered(evt);
}
