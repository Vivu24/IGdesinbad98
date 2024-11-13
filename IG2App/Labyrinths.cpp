#include "Labyrinths.h"
#include "Wall.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include "Pearl.h"
#include "Sinbad.h"
#include "NormalEnemy.h"
#include "Transformer.h"

Labyrinths::Labyrinths(const string& archivo, SceneManager* mSM, Sinbad* sinbad, OgreBites::TextBox* tb) : 
    sinbad_(sinbad), mSM_(mSM), textBox_(tb)
{
    node_ = mSM_->getRootSceneNode()->createChildSceneNode("nLabyrinth");
    read(archivo);

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
    planeEntity->setMaterialName(floorMat_);
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

void Labyrinths::read(const string& archivo)
{
    ifstream fich(archivo);
    if (!fich.is_open())
    {
        cout << "Error al abrir archivo\n";
        exit(EXIT_FAILURE);
    }

    fich >> numFilas >> numColumnas >> pearlMat_ >> wallMat_ >> floorMat_ >> lightType_;

    char valor;
    int j = numFilas; // fila
    int i = numColumnas; // columna
    while (fich >> valor)
    {
        if (valor == 'x')
        {
            LabEntity* wall = new Wall(Vector3(i * 98, j * 98, 0), node_->createChildSceneNode(), mSM_, wallMat_);
            lab_.push_back(wall);
        }
        else if (valor == 'o') {
            LabEntity* pearl = new Pearl(Vector3(i * 98, j * 98, 0), node_->createChildSceneNode(), mSM_, pearlMat_);
            pearl->setScale(Vector3(0.1, 0.1, 0.1));
            lab_.push_back(pearl);
        }
        else if (valor == 'h') {
            sinbad_->setPosition(Vector3(i * 98, j * 98, 0));
            sinbad_->setScale(Vector3(8, 8, 8));
            sinbad_->setLab(this);

            LabEntity* pearl = new Pearl(Vector3(i * 98, j * 98, 0), node_->createChildSceneNode(), mSM_, pearlMat_);
            pearl->setScale(Vector3(0.1, 0.1, 0.1));
            lab_.push_back(pearl);
        }
        else if (valor == 'v') {
            MovableEntity* enemy = new NormalEnemy(Vector3(i * 98, j * 98, 0), node_->createChildSceneNode(), mSM_, 2);
            enemy->setLab(this);
            enemies_.push_back(enemy);

            LabEntity* pearl = new Pearl(Vector3(i * 98, j * 98, 0), node_->createChildSceneNode(), mSM_, pearlMat_);
            pearl->setScale(Vector3(0.1, 0.1, 0.1));
            lab_.push_back(pearl);
        }
        else if (valor == 'V') {
            MovableEntity* enemy = new Transformer(Vector3(i * 98, j * 98, 0), node_->createChildSceneNode(), mSM_, 2);
            enemy->setLab(this);
            enemies_.push_back(enemy);

            LabEntity* pearl = new Pearl(Vector3(i * 98, j * 98, 0), node_->createChildSceneNode(), mSM_, pearlMat_);
            pearl->setScale(Vector3(0.1, 0.1, 0.1));
            lab_.push_back(pearl);
        }

        cout << valor;

        --i;

        if (i == 0)
        {
            --j;
            i = numColumnas;
            cout << '\n';
        }

        if (!fich.good()) {
            cout << "Error en la lectura del archivo" << endl;
            break;
        }
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

