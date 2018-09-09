#pragma once
#include "irrlicht.h"
#include "MyEventReceiver.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace std;

//IGUIEnvironment * GUISetUp(IrrlichtDevice * device, IVideoDriver * driver);
class GUI
{
public:
	GUI(IGUIEnvironment * env, IrrlichtDevice * device);
	~GUI();
};

