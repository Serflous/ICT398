#include "irrlicht.h"
#include <iostream>
#include "driverChoice.h"
#include "CSampleSceneNode.h"
#include "GUI.h"

#include <list>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace std;

int main(int argc, char* argv[])
{
	u32 width = 1280;
	u32 height = 720;

	SKeyMap keyMap[8];
	keyMap[0].Action = EKA_MOVE_FORWARD;
	keyMap[0].KeyCode = KEY_UP;
	keyMap[1].Action = EKA_MOVE_FORWARD;
	keyMap[1].KeyCode = KEY_KEY_W;

	keyMap[2].Action = EKA_MOVE_BACKWARD;
	keyMap[2].KeyCode = KEY_DOWN;
	keyMap[3].Action = EKA_MOVE_BACKWARD;
	keyMap[3].KeyCode = KEY_KEY_S;

	keyMap[4].Action = EKA_STRAFE_LEFT;
	keyMap[4].KeyCode = KEY_LEFT;
	keyMap[5].Action = EKA_STRAFE_LEFT;
	keyMap[5].KeyCode = KEY_KEY_A;

	keyMap[6].Action = EKA_STRAFE_RIGHT;
	keyMap[6].KeyCode = KEY_RIGHT;
	keyMap[7].Action = EKA_STRAFE_RIGHT;
	keyMap[7].KeyCode = KEY_KEY_D;
	IrrlichtDevice * device = createDevice(EDT_OPENGL,dimension2d<u32>(width, height), 16, false, false, false, 0);
    
	if (!device)
		return 1;// could not create selected driver.
	//Note that there is an 'L' in front of the string. The Irrlicht Engine uses wide character strings when displaying text.
	device->setWindowCaption(L"Engine");
	device->setResizable(true);
	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();

	//GUI stuff
	IGUIEnvironment* env = device->getGUIEnvironment();
	IGUISkin* skin = env->getSkin();
	IGUIFont* font = env->getFont("res/font/fonthaettenschweiler.bmp");
	if (font)
		skin->setFont(font);

	IGUIListBox * listbox = env->addListBox(rect<s32>(50, 140, 250, 210));
	SAppContext context;
	context.device = device;
	context.counter = 0;
	context.listbox = listbox;
	env->clear();

	// Then create the event receiver, giving it that context structure.
	MyEventReceiver receiver(context);

	// And tell the device to use our custom event receiver.
	device->setEventReceiver(&receiver);
	//end GUI Stuff

	vector3d<int> newVec();

	IAnimatedMesh* mesh = smgr->getMesh("res/models/sydney.md2");
	if (!mesh)
	{
		device->drop();
		return 1;
	}
	IAnimatedMeshSceneNode* nodes[100];
	for (int i = 0; i < 100; i++)
	{
		nodes[i] = smgr->addAnimatedMeshSceneNode(mesh);
		nodes[i]->setMaterialFlag(EMF_LIGHTING, false);
		nodes[i]->setMD2Animation(scene::EMAT_STAND);
		nodes[i]->setMaterialTexture(0, driver->getTexture("res/textures/sydney.bmp"));
		nodes[i]->setPosition(vector3df(10 + (i * 10), 20, 30));
		nodes[i]->setDebugDataVisible(EDS_BBOX);
	}
	CSampleSceneNode *myNode = new CSampleSceneNode(smgr->getRootSceneNode(), smgr, 666);
	ISceneNodeAnimator* anim = smgr->createRotationAnimator(vector3df(0.8f, 0, 0.8f));
	if (anim)
	{
		myNode->addAnimator(anim);
		anim->drop();
		anim = 0;
	}
	aabbox3d<f32> Box = myNode->getBoundingBox();	
	IMeshManipulator* newMan = smgr->getMeshManipulator();
	s32 polyCount = newMan->getPolyCount(mesh);
	
	struct snode
	{
		ISceneNode* node;
	};
	core::array<snode> blerg;
	snode newNode;
	newNode.node = myNode;
	blerg.push_back(newNode);

	smgr->addCameraSceneNodeFPS(0, 100, 0.5f, -1, keyMap, 8);
	device->getCursorControl()->setVisible(false);
	
	while (device->run())
	{

		driver->beginScene(true, true, SColor(255, 100, 101, 140));
		int fps = driver->getFPS();
		int lastFPS = -1;
		if (lastFPS != fps)
		{
			s32 polyCount = newMan->getPolyCount(mesh);
			core::stringw tmp(L"Irrlicht Engine [");
			tmp += driver->getName();
			tmp += device->getTimer()->getTime();
			tmp += L"] fps: ";
			tmp += fps;
			tmp += L" TEST: ";
			tmp += myNode->Collision(blerg[0].node, nodes[0]);
			
			tmp += L"    # of Nodes: ";
			
			tmp += blerg.size();
			//tmp += center.X;
			for (int j = 0; j < 100; j++)
			{
				myNode->Collision(blerg[0].node, nodes[j]);
			}
			device->setWindowCaption(tmp.c_str());
			lastFPS = fps;
		}
		smgr->drawAll();
		env->drawAll();
		driver->endScene();
	}
	device->drop();
	return 0;
}