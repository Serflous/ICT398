// will-o-the-wisp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "irrlicht.h"
#include <iostream>
#include "driverChoice.h"
#include "CSampleSceneNode.h"



using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace std;

int main(int argc, char* argv[])
{
	/***************************************
	deviceType: Type of the device. This can currently be the Null-device, 
	one of the two software renderers, D3D8, D3D9, or OpenGL. In this example 
	we use EDT_SOFTWARE, but to try out, you might want to change it to EDT_BURNINGSVIDEO, 
	EDT_NULL, EDT_DIRECT3D8, EDT_DIRECT3D9, or EDT_OPENGL.

	windowSize: Size of the Window or screen in FullScreenMode to be created. In this example we use 640x480.
	bits: Amount of color bits per pixel. This should be 16 or 32. The parameter is often ignored when running in windowed mode.
	fullscreen: Specifies if we want the device to run in fullscreen mode or not.
	stencilbuffer: Specifies if we want to use the stencil buffer (for drawing shadows).
	vsync: Specifies if we want to have vsync enabled, this is only useful in fullscreen mode.
	eventReceiver: An object to receive events. We do not want to use this parameter here, and set it to 0.
	****************************************/
	IrrlichtDevice *device = createDevice(EDT_OPENGL,dimension2d<u32>(640,480), 16, false, false, false, 0);
    
	if (!device)
		return 1;// could not create selected driver.
	//Note that there is an 'L' in front of the string. The Irrlicht Engine uses wide character strings when displaying text.
	device->setWindowCaption(L"Will-o-the-Wisp");
	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	
	IGUIEnvironment* guienv = device->getGUIEnvironment();
	ILogger* logger = device->getLogger();
	vector3d<int> newVec();
	//guienv->addStaticText(L"This is the Irrlicht Software Renderer", rect<s32>(10, 10, 260, 22), true);

	IAnimatedMesh* mesh = smgr->getMesh("models/sydney.md2");
	if (!mesh)
	{
		device->drop();
		return 1;
	}
	
	IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(mesh);
	CSampleSceneNode *myNode = new CSampleSceneNode(smgr->getRootSceneNode(), smgr, 666);
	ISceneNodeAnimator* anim = smgr->createRotationAnimator(vector3df(0.8f, 0, 0.8f));
	if (anim)
	{
		myNode->addAnimator(anim);
		anim->drop();
		anim = 0;
	}
	aabbox3d<f32> Box = myNode->getBoundingBox();
	if (node)
	{
		node->setMaterialFlag(EMF_LIGHTING, false);
		node->setMD2Animation(scene::EMAT_STAND);
		node->setMaterialTexture(0, driver->getTexture("models/sydney.bmp"));
	}
	node->setDebugDataVisible(EDS_BBOX);
	smgr->addCameraSceneNode(0, vector3df(0, 30, -40), vector3df(0, 5, 0));
	IMeshManipulator* newMan = smgr->getMeshManipulator();
	s32 polyCount = newMan->getPolyCount(mesh);
	
	while (device->run())
	{
		driver->beginScene(true, true, SColor(255, 100, 101, 140));
		int fps = driver->getFPS();
		int lastFPS = -1;
		if (lastFPS != fps)
		{
			s32 polyCount = newMan->getPolyCount(mesh);
			core::stringw tmp(L"Movement Example - Irrlicht Engine [");
			tmp += driver->getName();
			tmp += device->getTimer()->getTime();
			tmp += L"] fps: ";
			tmp += fps;
			tmp += L" TEST: ";
			//tmp += checkID;

			device->setWindowCaption(tmp.c_str());
			lastFPS = fps;
		}
		smgr->drawAll();
		//guienv->drawAll();
		driver->endScene();
	}
	device->drop();
	return 0;
}

