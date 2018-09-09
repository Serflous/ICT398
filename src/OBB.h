#pragma once
#include "irrlicht.h"

using namespace irr;
using namespace core;
using namespace scene;

class OBB
{
public:
	OBB();
	OBB(vector3d<f32> minValue, vector3d<f32> maxValue, vector3d<f32> rotation);
	OBB(const OBB & other);
	~OBB();

	static OBB BuildOBBFromMesh(IMeshSceneNode * node);
public:


public:
	vector3d<f32> MinValue;
	vector3d<f32> MaxValue;
	quaternion Rotation;
	vector3d<f32> CenterPoint;

};