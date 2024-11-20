#ifndef __IG2App_H__
#define __IG2App_H__

#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <sstream>
#include <iostream>
#include <string>

#include "Sinbad.h"

class Labyrinths;

class IG2App : public  OgreBites::IG2ApplicationContext, OgreBites::InputListener{

public:
    explicit IG2App() : IG2ApplicationContext("IG2App") { };  // new -> setup()
    virtual ~IG2App() { };                                    // delete -> shutdown()

    static string getTexture(int i) { return mTextures[i]; }

    enum Textrues
    {
        PERLA,
        MURO,
        SUELO
    };

protected:
    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener
    virtual void setup();
    virtual void shutdown();
    virtual void setupScene();
    void setupIntro();
    void setupGame();
    void read(const string& archivo);

    //Ogre::SceneNode* mSinbadNode = nullptr;

    #pragma region P0
    /*Ogre::SceneNode* mDrakeNode = nullptr;
    Ogre::SceneNode* mSwordNode = nullptr;
    Ogre::SceneNode* mHelmetNode = nullptr;
    Ogre::SceneNode* mHeadNode = nullptr;
    Ogre::SceneNode* mFacialNode = nullptr;
    Ogre::SceneNode* mLowBath = nullptr;
    Ogre::SceneNode* mHighBath = nullptr;

    Ogre::SceneNode* mBodySnow = nullptr;
    Ogre::SceneNode* mHeadSnow = nullptr;
    Ogre::SceneNode* mEyeLSnow = nullptr;
    Ogre::SceneNode* mEyeRSnow = nullptr;
    Ogre::SceneNode* mNoseSnow = nullptr;
    Ogre::SceneNode* mMouthSnow = nullptr;
    Ogre::SceneNode* mBB8JhonSnow = nullptr;*/
    #pragma endregion

    #pragma region P1
    Ogre::SceneNode* mCube = nullptr;
    Labyrinths* mLab = nullptr;
    Sinbad* mSinbad = nullptr;
    #pragma endregion


      
    Ogre::SceneManager* mSM = nullptr;
    OgreBites::TrayManager* mTrayMgr = nullptr;
    
    Ogre::Light* light = nullptr;
    Ogre::SceneNode* mLightParent = nullptr;
    Ogre::SceneNode* mLightNode = nullptr;
    
    Ogre::SceneNode* mCamNode = nullptr;
    OgreBites::CameraMan* mCamMgr = nullptr;

    OgreBites::Label* mLabel = nullptr;
    OgreBites::TextBox* mTextBox= nullptr;
    OgreBites::TrayManager* mHUDManager = nullptr;

    string lightType_;
    static std::vector<string> mTextures;
    std::vector<char> mLabTypes;
    int numFilas, numColumnas;
};

#endif
