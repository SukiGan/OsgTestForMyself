#if 0
#include <Windows.h>

#include <osgViewer/Viewer>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/ShapeDrawable>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>
#include <osgUtil/Tessellator>

osg::ref_ptr<osg::Geode> tesslatorGeometry()
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();

	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();
	geode->addDrawable(geom.get());

	const float wall[5][3] =
	{
		{2200.0f, 0.0f, 1130.0f},
		{2600.0f, 0.0f, 1130.0f},
		{2600.0f, 0.0f, 1340.0f},
		{2400.0f, 0.0f, 1440.0f},
		{2200.0f, 0.0f, 1340.0f}
	};

	const float door[4][3] =
	{
		{2360.0f, 0.0f, 1130.0f},
		{2440.0f, 0.0f, 1130.0f},
		{2440.0f, 0.0f, 1230.0f},
		{2360.0f, 0.0f, 1230.0f}
	};

	const float wind[16][3] =
	{
		{2240.0f, 0.0f, 1180.0f},
		{2330.0f, 0.0f, 1180.0f},
		{2330.0f, 0.0f, 1220.0f},
		{2240.0f, 0.0f, 1220.0f},
		{2460.0f, 0.0f, 1180.0f},
		{2560.0f, 0.0f, 1180.0f},
		{2560.0f, 0.0f, 1220.0f},
		{2460.0f, 0.0f, 1220.0f},

		{2240.0f, 0.0f, 1280.0f},
		{2330.0f, 0.0f, 1280.0f},
		{2330.0f, 0.0f, 1320.0f},
		{2240.0f, 0.0f, 1320.0f},
		{2460.0f, 0.0f, 1280.0f},
		{2560.0f, 0.0f, 1280.0f},
		{2560.0f, 0.0f, 1320.0f},
		{2460.0f, 0.0f, 1320.0f}
	};
	
	osg::ref_ptr<osg::Vec3Array> coords = new osg::Vec3Array();
	geom->setVertexArray(coords.get());

	osg::ref_ptr<osg::Vec3Array>normal = new osg::Vec3Array();
	normal->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));
	geom->setNormalArray(normal.get());
	geom->setNormalBinding(osg::Geometry::BIND_OVERALL);

	for (int i = 0; i < 5; ++i)
	{
		coords->push_back(osg::Vec3(wall[i][0], wall[i][1], wall[i][2]));
	}
	
	for (int i = 0; i < 4; ++i)
	{
		coords->push_back(osg::Vec3(door[i][0], door[i][1], door[i][2]));
	}

	for (int i = 0; i < 16; ++i)
	{
		coords->push_back(osg::Vec3(wind[i][0], wind[i][1], wind[i][2]));
	}
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 5, 20));

	osg::ref_ptr<osgUtil::Tessellator> tscx = new osgUtil::Tessellator();

	tscx->setTessellationType(osgUtil::Tessellator::TESS_TYPE_GEOMETRY);
	tscx->setBoundaryOnly(false);
	tscx->setWindingType(osgUtil::Tessellator::TESS_WINDING_ODD);

	tscx->retessellatePolygons(*(geom.get()));

	return geode.get();
}

int main()
{
	osg::ref_ptr<osgViewer::Viewer> view1 = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root = new osg::Group();

	osg::ref_ptr<osg::Geode> geode = tesslatorGeometry();

	root->addChild(geode.get());
	
	osgUtil::Optimizer opt1;
	opt1.optimize(root.get());

	view1->setSceneData(root.get());

	view1->realize();

	view1->run();

	return 0;
}
#endif

#if 0
#include <Windows.h>

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <osgGA/StateSetManipulator>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/PositionAttitudeTransform>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>
#include <osgUtil/Simplifier>

int main()
{
	osg::ref_ptr<osgViewer::Viewer> view1 = new osgViewer::Viewer();

	view1->addEventHandler(new osgGA::StateSetManipulator(view1->getCamera()->getOrCreateStateSet()));

	osg::ref_ptr<osg::Group> root = new osg::Group();

	float sampleRatio = 0.3f;
	float maxError = 4.0f;
	osgUtil::Simplifier simplifier(sampleRatio, maxError);

	osg::ref_ptr<osg::Node> node1 = osgDB::readNodeFile("E:/OSG/data/OpenSceneGraph-Data/cow.osg");

	osg::ref_ptr<osg::Node> node2 = (osg::Node*)(node1->clone(osg::CopyOp::DEEP_COPY_ALL));

	
	osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform();
	pat->setPosition(osg::Vec3(10.0f, 0.0f, 0.0f));
	pat->addChild(node2.get());
	pat->accept(simplifier);

	root->addChild(node1.get());
	root->addChild(pat.get());

	osgUtil::Optimizer opt1;
	opt1.optimize(root.get());

	view1->setSceneData(root.get());

	view1->realize();

	view1->run();

	return 0;

}


#endif

#if 0
#include <Windows.h>

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/Geometry>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgGA/StateSetManipulator>

#include <osgUtil/Optimizer>
#include <osgUtil/DelaunayTriangulator>

//Gxz::"Tex.h"
//#include "Tex.h"

int main()
{
	osg::ref_ptr<osgViewer::Viewer> view1 = new osgViewer::Viewer();

	view1->addEventHandler(new osgGA::StateSetManipulator(view1->getCamera()->getOrCreateStateSet()));

	osg::ref_ptr<osg::Group> root = new osg::Group();

	osg::ref_ptr<osg::Vec3Array> coords = new osg::Vec3Array();

	unsigned int n = sizeof(vertex) / sizeof(float[3]);

	for (int i = 0; i < n; ++i)
	{
		coords->push_back(osg::Vec3(vertex[i][0], vertex[i][1], vertex[i][2]));
	}

	osg::ref_ptr<osgUtil::DelaunayTriangulator> dt = new osgUtil::DelaunayTriangulator(coords.get());

	dt->triangulate();

	osg::ref_ptr<osg::Geometry> geomtery = new osg::Geometry();

	geomtery->setVertexArray(coords.get());

	geomtery->addPrimitiveSet(dt->getTriangles());

	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	geode->addDrawable(geomtery.get());

	root->addChild(geode.get());

	osgUtil::Optimizer opt1;
	opt1.optimize(root.get());

	view1->setSceneData(root.get());

	view1->realize();

	view1->run();

	return 0;
}

#endif

#if 1
#include <Windows.h>

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgGA/StateSetManipulator>

#include <osgUtil/Optimizer>
//#include <osgUtil/TriStripVisitor>

osg::ref_ptr<osg::Geometry> createQuad()
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();

	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();

	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();
	v->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));
	v->push_back(osg::Vec3(1.0f, 0.0f, 0.0f));
	v->push_back(osg::Vec3(1.0f, 0.0f, 1.0f));
	v->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));

	geom->setVertexArray(v.get());

	osg::ref_ptr<osg::Vec2Array> vt = new osg::Vec2Array();
	vt->push_back(osg::Vec2(0.0f, 0.0f));
	vt->push_back(osg::Vec2(1.0f, 0.0f));
	vt->push_back(osg::Vec2(1.0f, 1.0f));
	vt->push_back(osg::Vec2(0.0f, 1.0f));

	geom->setTexCoordArray(0, vt.get());

	osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array();
	vc->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	vc->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
	vc->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
	vc->push_back(osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f));

	geom->setColorArray(vc.get());
	geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

	osg::ref_ptr<osg::Vec3Array> nc = new osg::Vec3Array();
	nc->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));
	geom->setNormalArray(nc.get());
	geom->setNormalBinding(osg::Geometry::BIND_OVERALL);

	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));

	return geom.get();
}

int main()
{
	osg::ref_ptr<osgViewer::Viewer> view1 = new osgViewer::Viewer();

	view1->addEventHandler(new osgGA::StateSetManipulator(view1->getCamera()->getOrCreateStateSet()));

	osg::ref_ptr<osg::Group> root = new osg::Group();

	osg::ref_ptr<osg::Geometry> geom2 = createQuad();

	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	geode->addChild(geom2.get());

	root->addChild(geode.get());

	osgUtil::Optimizer opt1;
	opt1.optimize(root.get());

	view1->setSceneData(root.get());

	view1->realize();

	view1->run();

	return 0;


	return 0;
}


#endif