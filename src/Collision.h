#pragma once
#include "irrlicht.h"
#include "OBB.h"
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
	bool CheckCameraCollision(ICameraSceneNode * one, ISceneNode * two);
	float ComputeRadius(IMeshSceneNode * node);
};