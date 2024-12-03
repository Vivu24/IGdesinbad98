#include "Labyrinths.h"
#include "Wall.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include "Pearl.h"
#include "Sinbad.h"
#include "NormalEnemy.h"
#include "Transformer.h"
#include <OgreParticleSystem.h>

Labyrinths::Labyrinths(SceneManager* mSM, Sinbad* sinbad, OgreBites::TextBox* tb, int f, int c, string l, std::vector<char>& types) : 
    numFilas(f), numColumnas(c), sinbad_(sinbad), mSM_(mSM), textBox_(tb), lightType_(l)
{
    node_ = mSM_->getRootSceneNode()->createChildSceneNode("nLabyrinth");
    create(types);

    MeshManager::getSingleton().createPlane(
        "mPlane1080x800",
        ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        Plane(Vector3::UNIT_Z, 0),
        numColumnas * 98, numFilas * 98,
        100, 80,
        true,
        1,
        5.0, 5.0,   
        Vector3::UNIT_Y
    );

    // Floor
    Entity* planeEntity = mSM->createEntity("floor", "mPlane1080x800");
    planeEntity->setMaterialName(IG2App::getTexture(IG2App::SUELO));
    SceneNode* planeNode = mSM->getRootSceneNode()->createChildSceneNode("floorNode");
    planeNode->attachObject(planeEntity);
    planeNode->setPosition(Vector3(numColumnas * 49 + 49, numFilas * 49 + 49, -48));

    // Light
    initLight(lightType_);
    textBox_->appendText("Lives: " + to_string(sinbad_->lifes()) + "\nPoints: " + to_string(sinbad_->points()));
}

LabEntity* Labyrinths::getNextEntity(const Vector3& next) const
{
    int i = 0;
    while (next != lab_[i]->getPosition()) ++i;

    if (i == lab_.size()) return nullptr;
    else return lab_[i];
}

void Labyrinths::create(std::vector<char>& t)
{
    int a = 0;
    int j = numFilas; // fila
    int i = numColumnas; // columna
    while (a < t.size())
    {
        if (t[a] == 'x')
        {
            LabEntity* wall = new Wall(Vector3(i * 98, j * 98, 0), node_->createChildSceneNode(), mSM_, IG2App::getTexture(IG2App::MURO));
            lab_.push_back(wall);
        }
        else if (t[a] == 'o') {
            LabEntity* pearl = new Pearl(Vector3(i * 98, j * 98, 0), node_->createChildSceneNode(), mSM_, IG2App::getTexture(IG2App::PERLA));
            pearl->setScale(Vector3(0.1, 0.1, 0.1));
            lab_.push_back(pearl);
        }
        else if (t[a] == 'h') {
            sinbad_->setPosition(Vector3(i * 98, j * 98, 0));
            sinbad_->setScale(Vector3(8, 8, 8));
            sinbad_->setLab(this);

            LabEntity* pearl = new Pearl(Vector3(i * 98, j * 98, 0), node_->createChildSceneNode(), mSM_, IG2App::getTexture(IG2App::PERLA));
            pearl->setScale(Vector3(0.1, 0.1, 0.1));
            lab_.push_back(pearl);
        }
        else if (t[a] == 'v') {
            MovableEntity* enemy = new NormalEnemy(Vector3(i * 98, j * 98, 0), node_->createChildSceneNode(), mSM_);
            enemy->setLab(this);
            enemies_.push_back(enemy);

            LabEntity* pearl = new Pearl(Vector3(i * 98, j * 98, 0), node_->createChildSceneNode(), mSM_, IG2App::getTexture(IG2App::PERLA));
            pearl->setScale(Vector3(0.1, 0.1, 0.1));
            lab_.push_back(pearl);
        }
        else if (t[a] == 'V') {
            MovableEntity* enemy = new Transformer(Vector3(i * 98, j * 98, 0), node_->createChildSceneNode(), mSM_);
            enemy->setLab(this);
            enemies_.push_back(enemy);

            LabEntity* pearl = new Pearl(Vector3(i * 98, j * 98, 0), node_->createChildSceneNode(), mSM_, IG2App::getTexture(IG2App::PERLA));
            pearl->setScale(Vector3(0.1, 0.1, 0.1));
            lab_.push_back(pearl);
        }
        else if (t[a] == 's') {
            LabEntity* pearl = new Pearl(Vector3(i * 98, j * 98, 0), node_->createChildSceneNode(), mSM_, IG2App::getTexture(IG2App::PERLA));
            pearl->setScale(Vector3(0.1, 0.1, 0.1));
            lab_.push_back(pearl);

            ParticleSystem* pSys = mSM_->createParticleSystem("psSmoke" + to_string(i) + to_string(j), "example/fooogyParticle");
            pSys->setEmitting(true);
            SceneNode* nSys = pearl->getNode()->createChildSceneNode();
            nSys->attachObject(pSys);
            nSys->setPosition(0, 0, 100);
        }

        cout << t[a];

        --i;

        if (i == 0)
        {
            --j;
            i = numColumnas;
            cout << '\n';
        }

        ++a;
    }

    //std::cout << "fin";
}

void Labyrinths::initLight(const string& light)
{
    // The light
    light_ = mSM_->createLight("light");
    light_->setDiffuseColour(1.0f, 1.0f, 1.0f);
    // Node with the light attached
    mLightNode_ = mSM_->getRootSceneNode()->createChildSceneNode("nLight");
    mLightNode_->setPosition(sinbad_->getPosition().x, sinbad_->getPosition().y, sinbad_->getPosition().z + 100);
    mLightNode_->attachObject(light_);


    if (light == "directional") {
        light_->setType(Light::LT_DIRECTIONAL);
    }
    else if (light == "spotLight") {    // mirar point y spotlight
        light_->setType(Light::LT_SPOTLIGHT);
    }
    sinbad_->initLight(mLightNode_);
}

void Labyrinths::updateHud() const
{
    textBox_->clearText();

    textBox_->appendText("Lives: " + to_string(sinbad_->lifes()) + "\nPoints: " + to_string(sinbad_->points()));
    
}

