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

	b1 = one->getBoundingBox();
	b2 = two->getBoundingBox();

	one->getRelativeTransformation().transformBoxEx(b1);

	two->getRelativeTransformation().transformBoxEx(b2);
	return b1.intersectsWithBox(b2);
}
