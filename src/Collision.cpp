#include "Collision.h"



Collision::Collision()
{
}


Collision::~Collision()
{
}

bool Collision::CheckCameraCollision(ICameraSceneNode * one, ISceneNode * two)
{
	aabbox3d<f32> b1, b2;

	//b1 = one->getBoundingBox();
	b2 = two->getBoundingBox();
	matrix4 transformation = one->getRelativeTransformation();
	b1.MinEdge.X = transformation.getTranslation().X - 1;
	b1.MinEdge.Y = transformation.getTranslation().Y - 1;
	b1.MinEdge.Z = transformation.getTranslation().Z - 1;

	b1.MaxEdge.X = transformation.getTranslation().X + 1;
	b1.MaxEdge.Y = transformation.getTranslation().Y + 1;
	b1.MaxEdge.Z = transformation.getTranslation().Z + 1;

	//one->getRelativeTransformation().transformBoxEx(b1);

	//two->getRelativeTransformation().transformBoxEx(b2);
	return b1.intersectsWithBox(b2);
}

bool Collision::BoxCollision(ISceneNode* one, aabbox3df two) {
	aabbox3d<f32> b1, b2;

	b1 = one->getBoundingBox();
	b2 = two;

	one->getRelativeTransformation().transformBoxEx(b1);

	
	return b1.intersectsWithBox(b2);
}


float Collision::ComputeRadius(IMeshSceneNode * node)
{
	aabbox3d<f32> box = node->getBoundingBox();

	float distX = box.MaxEdge.X - box.MinEdge.X;
	float distY = box.MaxEdge.Y - box.MinEdge.Y;
	float distZ = box.MaxEdge.Z - box.MinEdge.Z;

	return max_<float>(distX, max_<float>(distY, distZ)) / 2;
}