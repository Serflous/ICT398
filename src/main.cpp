#include "irrlicht.h"
#include <iostream>
#include "driverChoice.h"
#include "CSampleSceneNode.h"
#include "GUI.h"
#include "NewSceneNode.h"
#include "Collision.h"
#include "irrArray.h"
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
	env->addButton(rect<s32>(10, 240, 110, 240 + 32), 0, GUI_ID_QUIT_BUTTON,
		L"Quit", L"Exits Program");
	env->addButton(rect<s32>(10, 280, 110, 280 + 32), 0, GUI_ID_NEW_WINDOW_BUTTON,
		L"New Window", L"Launches a new Window");
	env->addButton(rect<s32>(10, 320, 110, 320 + 32), 0, GUI_ID_FILE_OPEN_BUTTON,
		L"File Open", L"Opens a file");
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
	IAnimatedMesh* mesh = smgr->getMesh("res/models/sydney.md2");
	IMesh* ECLMesh = smgr->getMesh("res/models/ECL_baked.obj");
	if (!mesh)
	{
		device->drop();
		return 1;
	}

	if (!ECLMesh)
	{
		device->drop();
		return 1;
	}
	S3DVertex Vertices[4];
	NewSceneNode * chairs[56];
	core::array<NewSceneNode> chair;
	int modifier = 0;
	for (int rows = 0; rows < 8; rows++)
	{
		for (int i = 0; i < 7; i++)
		{
			chairs[(i * rows) + i] = new NewSceneNode(smgr->getRootSceneNode(), smgr, 1 + i,
				S3DVertex(3, 70, 2, 1, 1, 0, SColor(0, 0, 0, 0), 0, 1),
				S3DVertex(3, 70, -2, 1, 0, 0, SColor(0, 0, 0, 0), 1, 1),
				S3DVertex(3, 75, 0, 0, 1, 1, SColor(0, 0, 0, 0), 1, 0),
				S3DVertex(0, 70, -2, 0, 0, 1, SColor(0, 0, 0, 0), 0, 0));
			chairs[(i * rows) + i]->setPosition(vector3df(-22 + (rows *8.2), 11.5 - (rows * 2.9), 13.5 + (i * 6)));

		}
	}
	for (int rows = 0; rows < 8; rows++)
	{
		for (int i = 0; i < 7; i++)
		{
			chair.push_back( NewSceneNode(smgr->getRootSceneNode(), smgr, 1 + i,
				S3DVertex(3, 70, 2, 1, 1, 0, SColor(0, 0, 0, 0), 0, 1),
				S3DVertex(3, 70, -2, 1, 0, 0, SColor(0, 0, 0, 0), 1, 1),
				S3DVertex(3, 75, 0, 0, 1, 1, SColor(0, 0, 0, 0), 1, 0),
				S3DVertex(0, 70, -2, 0, 0, 1, SColor(0, 0, 0, 0), 0, 0)));
			chair.getLast().setPosition(vector3df(-22 + (rows *8.2), 11.5 - (rows * 2.9), 13.5 + (i * 6)));
		}
	}

	Vertices[0] = video::S3DVertex(10, 0, 10, 1, 1, 0,
		video::SColor(0, 0, 0, 0), 0, 1);
	Vertices[1] = video::S3DVertex(20, 0, -10, 1, 0, 0,
		video::SColor(0, 0, 0, 0), 1, 1);
	Vertices[2] = video::S3DVertex(10, 20, 0, 0, 1, 1,
		video::SColor(0, 0, 0, 0), 1, 0);
	Vertices[3] = video::S3DVertex(0, 0, -10, 0, 0, 1,
		video::SColor(0, 0, 0, 0), 0, 0);

	//CSampleSceneNode * ECLNode = new CSampleSceneNode(smgr->getRootSceneNode(), smgr, 666);
	IMeshSceneNode * staticNodes[1];

	staticNodes[0] = smgr->addMeshSceneNode(ECLMesh);
	staticNodes[0]->setMaterialFlag(EMF_LIGHTING, false);
	staticNodes[0]->setMaterialTexture(0, driver->getTexture("res/models/ECL_Texture.png"));
	staticNodes[0]->setPosition(vector3df(10, 60, 30));
	staticNodes[0]->setRotation(vector3df(270, 90, 0));
	staticNodes[0]->setScale(vector3df(3, 3, 3));

	//CSampleSceneNode *myNode = new CSampleSceneNode(smgr->getRootSceneNode(), smgr, 666);
	//ISceneNodeAnimator* anim = smgr->createRotationAnimator(vector3df(0.8f, 0, 0.8f));
	//if (anim)
	//{
	//	myNode->addAnimator(anim);
	//	anim->drop();
	//	anim = 0;
	//}	
	IMeshManipulator* newMan = smgr->getMeshManipulator();
	s32 polyCount = newMan->getPolyCount(mesh);
	
	struct snode
	{
		ISceneNode* node;
	};
	core::array<snode> blerg;
	snode newNode;
	blerg.push_back(newNode);

	smgr->addCameraSceneNodeFPS(0, 100, 0.05f, -1, keyMap, 8, true)->setPosition(vector3df(55, 68, 50));
	device->getCursorControl()->setVisible(false);

	aabbox3d<f32> camBox = aabbox3d<f32>(vector3df(3, 3, 3), vector3df(3, 3, 3));
	driver->draw3DBox(camBox, video::SColor(255, 255, 0, 0));
	Collision collisionChecker;
	SMaterial Material;
	OBB obb = OBB::BuildOBBFromMesh(staticNodes[0]);
	vector3df prevCamPos = smgr->getActiveCamera()->getPosition();



	while (device->run() && driver)
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
			
			smgr->getActiveCamera()->updateAbsolutePosition();
			aabbox3df cambox = aabbox3df(vector3df(smgr->getActiveCamera()->getAbsolutePosition().X, smgr->getActiveCamera()->getAbsolutePosition().Y, smgr->getActiveCamera()->getAbsolutePosition().Z));
			
			for (int x = 0; x < size(chair); x++)
			{
				if (collisionChecker.BoxCollision(&chair[x], cambox)) {
					tmp += L" Collision Detected ";
					smgr->getActiveCamera()->setPosition(prevCamPos);
				}
			}
			prevCamPos = smgr->getActiveCamera()->getPosition();
			tmp += L" Box Collision: ";
			//tmp += collisionChecker.BoxCollision(chairs[25], cambox);
			tmp += L" Size OF array: ";
			tmp += size(chair);
			tmp += L" Cam Pos X: ";
			tmp += smgr->getActiveCamera()->getAbsolutePosition().X;
			tmp += L" Cam Pos Y: ";
			tmp += smgr->getActiveCamera()->getAbsolutePosition().Y;
			tmp += L" Cam Pos Z: ";
			tmp += smgr->getActiveCamera()->getAbsolutePosition().Z;

			//tmp += center.X;
			//for (int j = 0; j < 100; j++)
			//{
			//	//myNode->Collision(blerg[0].node, nodes[j]);
			//	collisionChecker.CheckCameraCollision(smgr->getActiveCamera(), nodes[j]);
			//}
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