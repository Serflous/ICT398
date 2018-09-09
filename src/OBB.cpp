#include "OBB.h"

OBB::OBB()
{

}

OBB::OBB(const OBB & other)
{
	MinValue = other.MinValue;
	MaxValue = other.MaxValue;
	Rotation = other.Rotation;
	CenterPoint = other.CenterPoint;
}

OBB::OBB(vector3d<f32> minValue, vector3d<f32> maxValue, vector3d<f32> rotation)
{
	MinValue = minValue;
	MaxValue = maxValue;
	quaternion quatRotation(rotation);
	Rotation = quatRotation;
	CenterPoint.X = (MaxValue.X - MinValue.X) / 2;
	CenterPoint.Y = (MaxValue.Y - MinValue.Y) / 2;
	CenterPoint.Z = (MaxValue.Z - MinValue.Z) / 2;
}

OBB::~OBB()
{

}

OBB OBB::BuildOBBFromMesh(IMeshSceneNode * node)
{
	aabbox3d<f32> aabb = node->getBoundingBox();
	vector3d<f32> translation = node->getRelativeTransformation().getTranslation();
	matrix4 transformation;
	transformation.setTranslation(translation);
	transformation.transformBoxEx(aabb);
	OBB obb(aabb.MinEdge, aabb.MaxEdge, node->getRelativeTransformation().getRotationDegrees());
	return obb;
}