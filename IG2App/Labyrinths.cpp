#include "Labyrinths.h"
#include "Wall.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include "Pearl.h"
#include "Sinbad.h"

Labyrinths::Labyrinths(string archivo, SceneManager* mSM, Sinbad* sinbad, OgreBites::TextBox* tb) : mSM_(mSM), sinbad_(sinbad), textBox_(tb)
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
        5.0, 5.0,   // nº repeticiones de la textura
        Vector3::UNIT_Y
    );

    Entity* planeEntity = mSM->createEntity("floor", "mPlane1080x800");
    planeEntity->setMaterialName(floorMat_);
    // Estaría guay alejar el ratio de repeticion de la text del suelo
    SceneNode* planeNode = mSM->getRootSceneNode()->createChildSceneNode("floorNode");
    planeNode->attachObject(planeEntity);
    planeNode->setPosition(Vector3(numColumnas * 48, numFilas * 48, -48));

    textBox_->appendText("Lives: " + to_string(sinbad_->lifes_) + "\nPoints: " + to_string(sinbad_->points_));
}

LabEntity* Labyrinths::getNextEntity(Vector3 next)
{
    int i = 0;
    while (next != lab_[i]->getPosition()) ++i;

    if (i == lab_.size()) return nullptr;
    else return lab_[i];
}

void Labyrinths::read(string archivo)
{
    ifstream fich(archivo);
    if (!fich.is_open())
    {
        cout << "Error al abrir archivo\n";
        exit(EXIT_FAILURE);
    }

    fich >> numFilas >> numColumnas;
    fich >> pearlMat_ 
        >> wallMat_ 
        >> floorMat_;

    char valor;
    int j = 0; // fila
    int i = 0; // columna
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

        cout << valor;

        ++i;

        if (i == numColumnas)
        {
            ++j;
            i = 0;
            cout << '\n';
        }

        if (!fich.good()) {
            cout << "Error en la lectura del archivo" << endl;
            break;
        }
    }

    //std::cout << "fin";
}

void Labyrinths::updateHUD()
{
    textBox_->clearText();

    textBox_->appendText("Lives: " + to_string(sinbad_->lifes_) + "\nPoints: " + to_string(sinbad_->points_));
    
}

