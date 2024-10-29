#include "Labyrinths.h"
#include "Wall.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include "Pearl.h"
#include "Sinbad.h"

Labyrinths::Labyrinths(string archivo, SceneManager* mSM, Sinbad* sinbad) : mSM_(mSM), sinbad_(sinbad)
{
    node_ = mSM_->getRootSceneNode()->createChildSceneNode("nLabyrinth");
    read(archivo);
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

    char valor;
    int j = 0; // fila
    int i = 0; // columna
    while (fich >> valor)
    {
        if (valor == 'x')
        {
            LabEntity* wall = new Wall(Vector3(i * 98, j * 98, 0), node_->createChildSceneNode(), mSM_);
            lab_.push_back(wall);
        }
        else if (valor == 'o') {
            LabEntity* pearl = new Pearl(Vector3(i * 98, j * 98, 0), node_->createChildSceneNode(), mSM_);
            pearl->setScale(Vector3(0.1, 0.1, 0.1));
            lab_.push_back(pearl);
        }
        else if (valor == 'h') {
            sinbad_->setPosition(Vector3(i * 98, j * 98, 0));
            sinbad_->setScale(Vector3(8, 8, 8));
            sinbad_->setLab(this);

            LabEntity* pearl = new Pearl(Vector3(i * 98, j * 98, 0), node_->createChildSceneNode(), mSM_);
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

    std::cout << "fin";
}

