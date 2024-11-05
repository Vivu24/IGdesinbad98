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
	Labyrinths(const string& archivo, Ogre::SceneManager* mSM, Sinbad* sinbad, OgreBites::TextBox* tb);
	
	Vector3 diagonal() const { return Vector3(numColumnas * 98, numFilas * 98, 0); }
	Sinbad* getSinbad() const { return sinbad_; }
	Vector3 getCenter() const { return Vector3(numFilas * 49, numColumnas * 49, 0); };
	LabEntity* getNextEntity(const Vector3& next) const;
	std::vector<MovableEntity*> getMovableEntities() { return enemies_; };
	void updateHud() const;

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
	string floorMat_;
	string wallMat_;
	string pearlMat_;

	// Light
	string lightType_;
	Ogre::Light* light_;
	Ogre::SceneNode* mLightNode_;

	void read(const string& archivo);
	void initLight(const string& light);
};
