#pragma once
#include "irrlicht.h"
using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace std;

class Collision
{
public:
	Collision();
	~Collision();
	bool Collision::CheckCameraCollision(ICameraSceneNode * one, ISceneNode * two);
};

