#include "IG2App.h"
#include "Emoted.h"
#include "Labyrinths.h"
#include <OgreTechnique.h>

using namespace Ogre;
using namespace std;

std::vector<std::string> IG2App::mTextures;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt){
        
    // ESC key finished the rendering...
    if (evt.keysym.sym == SDLK_ESCAPE){
        getRoot()->queueEndRendering();
    }
    else if (evt.keysym.sym == SDLK_k) {
        cout << "Position of Sinbad: " << mSinbad->getPosition() << endl;
        cout << "Position of the camera: " << mCamNode->getPosition() << endl;
    }
    else if (evt.keysym.sym == SDLK_s) {
        removeInputListener(mEmoted);
        removeInputListener(mCamMgr);
        setupGame();
    }

    return true;
}

void IG2App::shutdown(){
    
  mShaderGenerator->removeSceneManager(mSM);
  mSM->removeRenderQueueListener(mOverlaySystem);  
					
  mRoot->destroySceneManager(mSM);  

  delete mTrayMgr;  mTrayMgr = nullptr;
  delete mCamMgr; mCamMgr = nullptr;
  
  // do not forget to call the base 
  IG2ApplicationContext::shutdown(); 
}

void IG2App::setup(void){
    
    // do not forget to call the base first
    IG2ApplicationContext::setup();

    // Create the scene manager
    mSM = mRoot->createSceneManager();

    // Register our scene with the RTSS
    mShaderGenerator->addSceneManager(mSM);

    mSM->addRenderQueueListener(mOverlaySystem);
    mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow.render);
    mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    addInputListener(mTrayMgr);
    
    // HUD
    mHUDManager = new OgreBites::TrayManager("HUDManager", mWindow.render);
    mLabel = mHUDManager->createLabel(OgreBites::TL_BOTTOMRIGHT, "TitleLabel", "Stage: ", 500.0);
    mTextBox = mHUDManager->createTextBox(OgreBites::TL_BOTTOMRIGHT, "TextBox", "Game Info Here!", 500.0, 100.0);

    addInputListener(mHUDManager);

    // Adds the listener for this object
    addInputListener(this);
    setupScene();
}

void IG2App::setupScene(void){
    
    //------------------------------------------------------------------------
    // Creating the camera

    mCam = mSM->createCamera("Cam");
    mCam->setNearClipDistance(1);
    mCam->setFarClipDistance(10000);
    mCam->setAutoAspectRatio(true);
    //cam->setPolygonMode(Ogre::PM_WIREFRAME);

    mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
    mCamNode->attachObject(mCam);


    // and tell it to render into the main window
    Viewport* vp = getRenderWindow()->addViewport(mCam);

    vp->setBackgroundColour(Ogre::ColourValue(0.7, 0.8, 0.9));

    mCamMgr = new OgreBites::CameraMan(mCamNode);
    addInputListener(mCamMgr);
    mCamMgr->setStyle(OgreBites::CS_ORBIT);
    

#pragma region P0

    //------------------------------------------------------------------------
    // Creating Sinbad

    //Ogre::Entity* ent = mSM->createEntity("Sinbad.mesh");
    //mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
    //mSinbadNode->attachObject(ent);

    //// Show bounding box
    //mSinbadNode->showBoundingBox(true);
    //
    //// Set position of Sinbad
    ////mSinbadNode->setPosition(x, y, z);
    //
    //// Set scale of Sinbad
    //mSinbadNode->setScale(15, 15, 15);
    //
    ////mSinbadNode->yaw(Ogre::Degree(-45));
    ////mSinbadNode->setVisible(false);    


    //------------------------------------------------------------------------
    // Creating Drake

    //Ogre::Entity* ent2 = mSM->createEntity("dragon.mesh");
    //mDrakeNode = mSM->getRootSceneNode()->createChildSceneNode("nDrake");
    //mDrakeNode->attachObject(ent2);

    //// Show bounding box
    //mDrakeNode->showBoundingBox(true);

    //// Set position of Sinbad
    //mDrakeNode->setPosition(235, 10, 355);
    //mDrakeNode->setDirection(Ogre::Vector3(0, 0, 1));

    //// Set scale of Sinbad
    //mDrakeNode->setScale(2, 2, 2);

    ////mSinbadNode->yaw(Ogre::Degree(-45));
    ////mSinbadNode->setVisible(false);  
    
    //------------------------------------------------------------------------
    // Creating Sword

    //Ogre::Entity* ent3 = mSM->createEntity("Sword.mesh");
    //mSwordNode = mSM->getRootSceneNode()->createChildSceneNode("nSword");
    //mSwordNode->attachObject(ent3);

    //// Show bounding box
    //mSwordNode->showBoundingBox(true);

    //// Set position of Sinbad
    ////mSwordNode->setPosition(0, -100, 100);
    ////mSwordNode->setDirection(Ogre::Vector3(0, 0, 1));

    //// Set scale of Sinbad
    //mSwordNode->setScale(20, 20, 20);

    ////mSinbadNode->yaw(Ogre::Degree(-45));
    ////mSinbadNode->setVisible(false);   

    //------------------------------------------------------------------------
    // Creating Helmet

    //Ogre::Entity* ent4 = mSM->createEntity("DamagedHelmet.mesh");
    //mHelmetNode = mSM->getRootSceneNode()->createChildSceneNode("nHelmet");
    //mHelmetNode->attachObject(ent4);

    //// Show bounding box
    //mHelmetNode->showBoundingBox(true);

    //// Set position of Sinbad
    ////mSwordNode->setPosition(0, -100, 100);
    ////mSwordNode->setDirection(Ogre::Vector3(0, 0, 1));

    //// Set scale of Sinbad
    //mHelmetNode->setScale(20, 20, 20);

    //mHelmetNode->pitch(Ogre::Degree(90));
    ////mSinbadNode->setVisible(false);   

    //------------------------------------------------------------------------
    // Creating OgreHead

    //Ogre::Entity* ent5 = mSM->createEntity("ogrehead.mesh");
    //mHeadNode = mSM->getRootSceneNode()->createChildSceneNode("nHead");
    //mHeadNode->attachObject(ent5);

    //// Show bounding box
    //mHeadNode->showBoundingBox(true);

    //// Set position of Sinbad
    ////mSwordNode->setPosition(0, -100, 100);
    ////mSwordNode->setDirection(Ogre::Vector3(0, 0, 1));

    //// Set scale of Sinbad
    //mHeadNode->setScale(20, 20, 20);

    ////mHeadNode->pitch(Ogre::Degree(90));
    ////mSinbadNode->setVisible(false);  

    //------------------------------------------------------------------------
    // Creating OgreHead

    //Ogre::Entity* ent6 = mSM->createEntity("facial.mesh");
    //mFacialNode = mSM->getRootSceneNode()->createChildSceneNode("nFacial");
    //mFacialNode->attachObject(ent6);

    //// Show bounding box
    //mFacialNode->showBoundingBox(true);

    //// Set position of Sinbad
    ////mSwordNode->setPosition(0, -100, 100);
    ////mSwordNode->setDirection(Ogre::Vector3(0, 0, 1));

    //// Set scale of Sinbad
    //mFacialNode->setScale(5, 5, 5);

    ////mHeadNode->pitch(Ogre::Degree(90));
    ////mSinbadNode->setVisible(false); 

    //------------------------------------------------------------------------
    // Creating LowBath

    //Ogre::Entity* ent7 = mSM->createEntity("RomanBathLower.mesh");
    //mLowBath = mSM->getRootSceneNode()->createChildSceneNode("nBathLow");
    //mLowBath->attachObject(ent7);

    //// Show bounding box
    //mLowBath->showBoundingBox(true);

    //// Set position of Sinbad
    ////mSwordNode->setPosition(0, -100, 100);
    ////mSwordNode->setDirection(Ogre::Vector3(0, 0, 1));

    //// Set scale of Sinbad
    ////mLowBath->setScale(5, 5, 5);

    ////mHeadNode->pitch(Ogre::Degree(90));
    ////mSinbadNode->setVisible(false); 

    //// Creating HighBath

    //Ogre::Entity* ent8 = mSM->createEntity("RomanBathUpper.mesh");
    //mHighBath = mSM->getRootSceneNode()->createChildSceneNode("nBathHigh");
    //mHighBath->attachObject(ent8);

    //// Show bounding box
    //mHighBath->showBoundingBox(true);

    //// Set position of Sinbad
    ////mSwordNode->setPosition(0, -100, 100);
    ////mSwordNode->setDirection(Ogre::Vector3(0, 0, 1));

    //// Set scale of Sinbad
    ////mHighBath->setScale(5, 5, 5);

    ////mHeadNode->pitch(Ogre::Degree(90));
    ////mSinbadNode->setVisible(false); 

    //------------------------------------------------------------------------
    // Creating OgreHead

    // Body
    //Ogre::Entity* entParent = mSM->createEntity("sphere.mesh");
    //mBodySnow = mSM->getRootSceneNode()->createChildSceneNode("nParent");
    //mBodySnow->attachObject(entParent);

    //// Head
    //Ogre::Entity* entChild1 = mSM->createEntity("sphere.mesh");
    //mHeadNode = mBodySnow->createChildSceneNode("nChild1");
    //mHeadNode->attachObject(entChild1);
    //mHeadNode->setScale(0.6, 0.6, 0.6);
    //mHeadNode->translate(0, 150, 0);

    //// BB8 (Ombligo)
    //Ogre::Entity* entChild2 = mSM->createEntity("sphere.mesh");
    //mBB8JhonSnow= mBodySnow->createChildSceneNode("nChild2");
    //mBB8JhonSnow->attachObject(entChild2);
    //mBB8JhonSnow->setScale(0.1, 0.1, 0.1);
    //mBB8JhonSnow->translate(0, 0, 100);

    // Ojo Derecho
    //Ogre::Entity* entChild3 = mSM->createEntity("sphere.mesh");
    //mEyeRSnow = mBodySnow->createChildSceneNode("nChild3");
    //mEyeRSnow->attachObject(entChild3);
    //mEyeRSnow->setScale(0.1, 0.1, 0.1);
    //mEyeRSnow->translate(25, 160, 50);

    //// Ojo Izquierdo
    //Ogre::Entity* entChild4 = mSM->createEntity("sphere.mesh");
    //mEyeLSnow = mBodySnow->createChildSceneNode("nChild4");
    //mEyeLSnow->attachObject(entChild4);
    //mEyeLSnow->setScale(0.1, 0.1, 0.1);
    //mEyeLSnow->translate(-25, 160, 50);

    //// Nariz
    //Ogre::Entity* entChild5 = mSM->createEntity("sphere.mesh");
    //mNoseSnow = mBodySnow->createChildSceneNode("nChild5");
    //mNoseSnow->attachObject(entChild5);
    //mNoseSnow->setScale(0.1, 0.1, 0.1);
    //mNoseSnow->translate(0, 150, 60);

    //// Boca
    //Ogre::Entity* entChild6 = mSM->createEntity("sphere.mesh");
    //mMouthSnow = mBodySnow->createChildSceneNode("nChild6");
    //mMouthSnow->attachObject(entChild6);
    //mMouthSnow->setScale(0.25, 0.05, 0.1);
    //mMouthSnow->translate(0, 125, 50);

#pragma endregion

#pragma region P1

    // CuboPrueba
    /*Ogre::Entity* ent1 = mSM->createEntity("cube.mesh");
    mCube = mSM->getRootSceneNode()->createChildSceneNode("nCube");
    mCube->attachObject(ent1);
    mCube->translate(0, 0, 0);
    mCube->showBoundingBox(true);
    mCube->setScale(1, 1, 1);*/

#pragma endregion
    

    // P2
    read("stage1.txt");
    setupIntro();
}

void IG2App::setupIntro()
{
    // Creating the light
    
    //mSM->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
    Light* luz = mSM->createLight("Luz");
    luz->setType(Ogre::Light::LT_DIRECTIONAL);
    luz->setDiffuseColour(0.75, 0.75, 0.75);

    mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
    //mLightNode = mCamNode->createChildSceneNode("nLuz");
    mLightNode->attachObject(luz);
    mLightNode->setDirection(Ogre::Vector3(0, -1, 0));

    mEmoted = new Emoted(mSM, 0.5);
    addInputListener(mEmoted);
}

void IG2App::setupGame()
{   
    // Limpiamos Escena
    mSM->clearScene();

    // Rehacer config de camara
    mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
    mCamNode->attachObject(mCam);

    mCamMgr = new OgreBites::CameraMan(mCamNode);
    //addInputListener(mCamMgr);
    mCamMgr->setStyle(OgreBites::CS_ORBIT);

    // Skyplane
    Plane plane;
    plane.d = 1000;
    plane.normal = Ogre::Vector3::UNIT_Z;

    mSM->setSkyPlane
    (
        true,
        plane,
        "practica2/spaceSkyZoomLightShader",
        10,
        1,
        true,
        1.5,
        50,
        50,
        ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME
    );

    // Sinbad
    mSinbad = new Sinbad(Vector3(), mSM->getRootSceneNode()->createChildSceneNode(), mSM, 2);

    // Laberinto
    mLab = new Labyrinths(mSM, mSinbad, mTextBox, numFilas, numColumnas, lightType_, mLabTypes);

    // Listeners
    addInputListener(mSinbad);
    for (int i = 0; i < mLab->getMovableEntities().size(); ++i)
        addInputListener(mLab->getMovableEntities()[i]);

    Vector3 auxLabPos = mLab->getCenter();
    mCamNode->setPosition(auxLabPos.x, auxLabPos.y, auxLabPos.z + 3000);
    mCamNode->lookAt(auxLabPos, Ogre::Node::TS_WORLD);

}

void IG2App::read(const string& archivo)
{
    ifstream fich(archivo);
    if (!fich.is_open())
    {
        cout << "Error al abrir archivo\n";
        exit(EXIT_FAILURE);
    }

    string perla, muro, suelo;

    fich >> numFilas 
        >> numColumnas
        >> perla
        >> muro
        >> suelo
        >> lightType_;

    mTextures.push_back(perla);
    mTextures.push_back(muro);
    mTextures.push_back(suelo);

    char valor;
    while (fich >> valor)
    {
        mLabTypes.push_back(valor);
    }
}


