#include "irrlicht.h"

#include <iostream>
#include "driverChoice.h"
#pragma once
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace std;



class NewSceneNode : public ISceneNode
{
	aabbox3d<f32> Box2;
	S3DVertex Vertices2[4];
	SMaterial Material;
public:
	NewSceneNode(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id, S3DVertex vert1, S3DVertex vert2, S3DVertex vert3, S3DVertex vert4)
		: scene::ISceneNode(parent, mgr, id)
	{
		Material.Wireframe = true;
		Material.Lighting = false;

		Vertices2[0] = vert1;
		Vertices2[1] = vert2;
		Vertices2[2] = vert3;
		Vertices2[3] = vert4;

		Box2.reset(Vertices2[0].Pos);
		for (s32 i = 1; i < 4; ++i)
			Box2.addInternalPoint(Vertices2[i].Pos);

	}

	virtual void OnRegisterSceneNode()
	{
		if (IsVisible)
			SceneManager->registerNodeForRendering(this);


		ISceneNode::OnRegisterSceneNode();
	}

	virtual void render()
	{
		u16 indices[] = { 0,2,3, 2,1,3, 1,0,3, 2,0,1 };
		video::IVideoDriver* driver = SceneManager->getVideoDriver();

		driver->setMaterial(Material);
		driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
		//driver->drawVertexPrimitiveList(&Vertices[0], 4, &indices[0], 4, video::EVT_STANDARD, scene::EPT_TRIANGLES, video::EIT_16BIT);
		driver->draw3DBox(Box2, video::SColor(255, 0, 255, 0));
	}

	virtual const aabbox3d<f32>& getBoundingBox() const
	{
		return Box2;
	}

	virtual u32 getMaterialCount() const
	{
		return 1;
	}

	virtual video::SMaterial& getMaterial(u32 i)
	{
		return Material;
	}
};

