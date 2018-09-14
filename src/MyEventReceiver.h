/*
* @Author Mason Tolman
*/

#pragma once
#include <irrlicht.h>
#include "driverChoice.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


struct SAppContext
{
	IrrlichtDevice * device;
	s32             counter;
	IGUIListBox*    listbox;
};

// Define some values that we'll use to identify individual GUI controls.
enum
{
	GUI_ID_QUIT_BUTTON = 101,
	GUI_ID_NEW_WINDOW_BUTTON,
	GUI_ID_FILE_OPEN_BUTTON,
	GUI_ID_TRANSPARENCY_SCROLL_BAR
};

void setSkinTransparency(s32 alpha, irr::gui::IGUISkin * skin);
class MyEventReceiver : public IEventReceiver
{
public:
	MyEventReceiver(SAppContext & context) : Context(context) { }
	
	SKeyMap keyMap[8];

	bool CHECKER = false;

	bool getChecker()
	{
		return CHECKER;
	}

	// This is used to check whether a key is being held down
	virtual bool IsKeyDown(EKEY_CODE keyCode) const
	{
		return KeyIsDown[keyCode];
	}

	virtual bool OnEvent(const SEvent& event)
	{


		
		bool OnceDone = false;
		if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
			if (!event.KeyInput.PressedDown)
			{
				OnceDone = false;
			}
				
			if (event.KeyInput.PressedDown && !OnceDone)
			{
				switch (event.KeyInput.Key)
				{
				case KEY_KEY_Q:
				{
					//TODO: move this to a more suitable location, its being set up everytime a button is pressed

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

					//END TODO::
					if (Context.device->getCursorControl()->isVisible())
					{

						//video::ITexture* images = Context.device->getVideoDriver()->getTexture("res/picture/SplashScreen.png");
						////Context.device->getVideoDriver()->makeColorKeyTexture(images, core::position2d<s32>(0, 0));
						//Context.device->getVideoDriver()->getMaterial2D().TextureLayer[0].BilinearFilter = true;
						//Context.device->getVideoDriver()->getMaterial2D().AntiAliasing = video::EAAM_FULL_BASIC;
						////Context.device->getVideoDriver()->enableMaterial2D();
						//Context.device->getVideoDriver()->draw2DImage(images, core::position2d<s32>(500, 500));

						Context.device->getCursorControl()->setVisible(false);
						ICameraSceneNode * curCam = Context.device->getSceneManager()->getActiveCamera();
						ICameraSceneNode * newCam = Context.device->getSceneManager()->addCameraSceneNodeFPS(0, 100, 0.05f, -1, keyMap, 8);
						newCam->setPosition(vector3df(curCam->getAbsolutePosition().X, curCam->getAbsolutePosition().Y, curCam->getAbsolutePosition().Z));
						newCam->setTarget(vector3df(curCam->getTarget().X, curCam->getTarget().Y, curCam->getTarget().Z));
						Context.device->getSceneManager()->setActiveCamera(newCam);
						Context.device->getGUIEnvironment()->saveGUI(L"gui", 0);
						Context.device->getGUIEnvironment()->clear();

						CHECKER = false;
						OnceDone = true;
					}
					else
					{
						Context.device->getCursorControl()->setVisible(true);
						ICameraSceneNode * curCam = Context.device->getSceneManager()->getActiveCamera();
						//Context.device->getSceneManager()->addCameraSceneNode(0, vector3df(0, 30, -40), vector3df(0, 5, 0),3);
						
						Context.device->getSceneManager()->addCameraSceneNode(0, vector3df(curCam->getAbsolutePosition().X, curCam->getAbsolutePosition().Y, curCam->getAbsolutePosition().Z), vector3df(curCam->getTarget().X, curCam->getTarget().Y, curCam->getTarget().Z));
						//Context.device->getSceneManager()->setActiveCamera;
						
						Context.device->getGUIEnvironment()->loadGUI(L"gui", 0);
						CHECKER = true;
						OnceDone = true;
					}
				}
				case KEY_F1:
				{
					//Context.device->closeDevice();
				}
				default:
					break;
				}
			}
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
		}

		//if (event.KeyInput.Key == irr::KEY_F1)
		//{
		//	Context.device->closeDevice();
		//}

		if (event.EventType == EET_GUI_EVENT)
		{
			s32 id = event.GUIEvent.Caller->getID();
			IGUIEnvironment* env = Context.device->getGUIEnvironment();

			switch (event.GUIEvent.EventType)
			{
			case EGET_SCROLL_BAR_CHANGED:
				if (id == GUI_ID_TRANSPARENCY_SCROLL_BAR)
				{
					s32 pos = ((IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
					setSkinTransparency(pos, env->getSkin());
				}
				break;
			case EGET_BUTTON_CLICKED:
				switch (id)
				{
				case GUI_ID_QUIT_BUTTON:
					Context.device->closeDevice();
					return true;

				case GUI_ID_NEW_WINDOW_BUTTON:
				{
					Context.listbox->addItem(L"Window created");
					Context.counter += 30;
					if (Context.counter > 200)
						Context.counter = 0;

					IGUIWindow* window = env->addWindow(
						rect<s32>(100 + Context.counter, 100 + Context.counter, 300 + Context.counter, 200 + Context.counter),
						false, // modal?
						L"Test window");
					stringw tmp = L"X: ";
					tmp += Context.device->getSceneManager()->getActiveCamera()->getBoundingBox().getCenter().X;
					env->addStaticText(tmp.c_str(),
						rect<s32>(35, 35, 140, 50),
						true, // border?
						false, // wordwrap?
						window);
					tmp = L"Y: ";
					tmp += Context.device->getSceneManager()->getActiveCamera()->getBoundingBox().getCenter().Y;
					env->addStaticText(tmp.c_str(),
						rect<s32>(35, 55, 140, 70),
						true, // border?
						false, // wordwrap?
						window);
					tmp = L"Z: ";
					tmp += Context.device->getSceneManager()->getActiveCamera()->getBoundingBox().getArea();
					env->addStaticText(tmp.c_str(),
						rect<s32>(35, 75, 140, 90),
						true, // border?
						false, // wordwrap?
						window);
				}
				return true;

				case GUI_ID_FILE_OPEN_BUTTON:
					Context.listbox->addItem(L"File open");
					// There are some options for the file open dialog
					// We set the title, make it a modal window, and make sure
					// that the working directory is restored after the dialog
					// is finished.
					env->addFileOpenDialog(L"Please choose a file.", true, 0, -1, true);
					return true;

				default:
					return false;
				}
				break;

			case EGET_FILE_SELECTED:
			{
				// show the model filename, selected in the file dialog
				IGUIFileOpenDialog* dialog =
					(IGUIFileOpenDialog*)event.GUIEvent.Caller;
				Context.listbox->addItem(dialog->getFileName());
			}
			break;

			default:
				break;
			}
		}

		return false;
	}

private:
	SAppContext & Context;
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
};


