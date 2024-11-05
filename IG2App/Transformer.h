#pragma once
#include "Enemy.h"
class Transformer :
    public Enemy
{
public:
    Transformer(Vector3 initPos, SceneNode* node, SceneManager* mSM);

private:
	SceneNode* ObjectNode = nullptr;

	double NodeScale = 0.025;
	double PetScale = 0.1;
	double ArmaScale = 0.05;
	double PatScale = 0.005;

	//Nos guardamos los nodos de las cosas que queremos que roten
	SceneNode* Nnudo1;
	SceneNode* Nnudo2;
};

