#pragma once
#include <string>
#include <vector>
#include "IG2App.h"
#include <OgreTrays.h>

class LabEntity;
class Sinbad;

using namespace std;

class Labyrinths
{
public:
	Labyrinths(string archivo, Ogre::SceneManager* mSM, Sinbad* sinbad, OgreBites::TextBox* tb);
	
	Sinbad* getSinbad() { return sinbad_; }
	Vector3 getCenter() { return Vector3(numFilas * 49, numColumnas * 49, 0); };
	int getNumFilas() { return numFilas; }
	int getNumColumnas() { return numColumnas; }
	LabEntity* getNextEntity(Vector3 next);
	void updateHUD();

private:
	int numFilas;
	int numColumnas;

	std::vector<LabEntity*> lab_;
	Sinbad* sinbad_;

	Ogre::SceneManager* mSM_;

	Ogre::SceneNode* node_;

	OgreBites::TextBox* textBox_ = nullptr;

	string floorMat_ = "";
	string wallMat_ = "";
	string pearlMat_ = "";

	void read(string archivo);
};

