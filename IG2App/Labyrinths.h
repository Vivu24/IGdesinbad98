#pragma once
#include <string>
#include <vector>
#include "IG2App.h"

class LabEntity;
class Sinbad;

using namespace std;

class Labyrinths
{
public:
	Labyrinths(string archivo, Ogre::SceneManager* mSM, Sinbad* sinbad);
	
	Sinbad* getSinbad() { return sinbad_; }
	Vector3 getCenter() { return Vector3(numFilas * 49, numColumnas * 49, 0); };
	int getNumFilas() { return numFilas; }
	int getNumColumnas() { return numColumnas; }
	LabEntity* getNextEntity(Vector3 next);

private:
	int numFilas;
	int numColumnas;

	std::vector<LabEntity*> lab_;
	Sinbad* sinbad_;

	Ogre::SceneManager* mSM_;

	Ogre::SceneNode* node_;

	void read(string archivo);
};

