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

float Collision::ComputeRadius(IMeshSceneNode * node)
{
	IMesh * mesh = node->getMesh();
	for (int i = 0; i < mesh->getMeshBufferCount(); i++)
	{
		IMeshBuffer * buffer = mesh->getMeshBuffer(i);
		void * vertBuffer = buffer->getVertices();
	}
	return 0;
}