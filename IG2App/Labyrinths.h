#pragma once
#include <string>
#include <vector>
#include "IG2App.h"
#include <OgreTrays.h>

class LabEntity;
class MovableEntity;

using namespace std;

class Labyrinths
{
public:
	Labyrinths(string archivo, Ogre::SceneManager* mSM, Sinbad* sinbad, OgreBites::TextBox* tb);
	
	Vector3 diagonal() { return Vector3(numColumnas * 98, numFilas * 98, 0); }
	Sinbad* getSinbad() { return sinbad_; }
	Vector3 getCenter() { return Vector3(numFilas * 49, numColumnas * 49, 0); };
	LabEntity* getNextEntity(Vector3 next);
	std::vector<MovableEntity*> getMovableEntities() { return enemies_; };
	void updateHUD();

private:
	int numFilas;
	int numColumnas;

	std::vector<LabEntity*> lab_;
	std::vector<MovableEntity*> enemies_;
	Sinbad* sinbad_;

	Ogre::SceneManager* mSM_;

	Ogre::SceneNode* node_;

	OgreBites::TextBox* textBox_ = nullptr;

	// Texture
	string floorMat_ = "";
	string wallMat_ = "";
	string pearlMat_ = "";

	// Light
	string lightType_ = "";
	Ogre::Light* light_ = nullptr;
	Ogre::SceneNode* mLightNode_ = nullptr;

	void read(string archivo);
	void initLight(string light);
};

