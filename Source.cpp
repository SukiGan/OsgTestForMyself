#if 0
#include <Windows.h> 

#include<osgViewer/Viewer>
#include<osgDB/ReadFile>


#pragma comment( lib, "opengl32.lib") 


int main()
{
	osgViewer::Viewer viewer;

	viewer.setSceneData(osgDB::readNodeFile("E:/OSG/data/OpenSceneGraph-Data/cow.osg"));
	return viewer.run();
}
#endif


#if 0
#include <Windows.h>

#include <osgViewer/Viewer>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>

int main()
{
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root = new osg::Group();

	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("E:/OSG/data/OpenSceneGraph-Data/cow.osg");

	root->addChild(node.get());

	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());

	viewer->setSceneData(root.get());

	viewer->realize();

	viewer->run();

	return 0;
}
#endif

#if 0
#include <Windows.h>

//Osg Lib
#include <osgViewer/Viewer>
#include <osg/Node>
#include <osg/Geometry>
#include <osg/Group>
#include <osg/Billboard>
#include <osg/Texture2D>
#include <osg/Image>
#include <osg/PositionAttitudeTransform>
#include <osg/MatrixTransform>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>

osg::ref_ptr<osg::Node> createBillboardTree(osg::ref_ptr<osg::Image> image)
{
	osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();
	
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();

	v->push_back(osg::Vec3(-0.5f, 0.0f, -0.5f));
	v->push_back(osg::Vec3(0.5f, 0.0f, -0.5f));
	v->push_back(osg::Vec3(0.5f, 0.0f, 0.5f));
	v->push_back(osg::Vec3(-0.5f, 0.0f, 0.5f));

	geometry->setVertexArray(v.get());

	osg::ref_ptr<osg::Vec3Array> normal = new osg::Vec3Array();
	normal->push_back(osg::Vec3(1.0f, 0.0f, 0.0f) ^ osg::Vec3(0.0f, 0.0f,1.0f));

	geometry->setNormalArray(normal.get());
	
	//ÉèÖÃÎÆÀí
	geometry->setNormalBinding(osg::Geometry::BIND_OVERALL);
	osg::ref_ptr<osg::Vec2Array> vt = new osg::Vec2Array();

	vt->push_back(osg::Vec2(0.0f, 0.0f));
	vt->push_back(osg::Vec2(1.0f, 0.0f));
	vt->push_back(osg::Vec2(1.0f, 1.0f));
	vt->push_back(osg::Vec2(0.0f, 1.0f));

	geometry->setTexCoordArray(0, vt.get());

	//»æÖÆ
	geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));
	
	if (image.get())
	{
		osg::ref_ptr<osg::StateSet> stateset = new osg::StateSet();

		osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D();

		texture->setImage(image.get());
		
		stateset->setTextureAttributeAndModes(0, texture, osg::StateAttribute::ON);

		stateset->setMode(GL_BLEND, osg::StateAttribute::ON);

		stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

		geometry->setStateSet(stateset.get());
	}

	osg::ref_ptr<osg::Billboard> billBoard1 = new osg::Billboard();
	billBoard1->setMode(osg::Billboard::POINT_ROT_EYE);
	billBoard1->addDrawable(geometry.get(), osg::Vec3(5.0f, 0.0f, 0.0f));

	osg::ref_ptr<osg::Billboard> billBoard2 = new osg::Billboard();
	billBoard2->setMode(osg::Billboard::AXIAL_ROT);
	billBoard2->setAxis(osg::Vec3(0.0f, 0.0f, 0.0f));
	billBoard2->addDrawable(geometry.get(), osg::Vec3(10.0f, 0.0f, 0.0f));

	osg::ref_ptr<osg::Group> billBoard = new osg::Group();
	billBoard->addChild(billBoard1.get());
	billBoard->addChild(billBoard2.get());

	return  billBoard.get();
}

int main()
{ 
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root = new osg::Group();

	osg::ref_ptr<osg::Image> image = osgDB::readImageFile("E:/OSG/data/OpenSceneGraph-Data/Images/tree0.rgba");

	osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform();
	pat->setScale(osg::Vec3(5.0f, 5.0f, 5.0f));
	pat->addChild(createBillboardTree(image.get()));

	root->addChild(pat.get());

	root->addChild(osgDB::readNodeFile("E:/OSG/data/OpenSceneGraph-Data/cow.osg"));

	osgUtil::Optimizer optimize1;
	optimize1.optimize(root.get());

	viewer->setSceneData(root.get());

	viewer->realize();

	viewer->run();

	return 0;

}
#endif

#if 0
#include <Windows.h>

#include <osgViewer/Viewer>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/PositionAttitudeTransform>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>

int main()
{
	osg::ref_ptr<osgViewer::Viewer> view = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root = new osg::Group();

	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("E:/OSG/data/OpenSceneGraph-Data/cow.osg");

	osg::ref_ptr<osg::PositionAttitudeTransform> pt1 = new osg::PositionAttitudeTransform();

	pt1->setPosition(osg::Vec3(-10.f, 0.0f, 0.0f));

	pt1->setScale(osg::Vec3(0.5f, 0.5f, 0.5f));

	pt1->addChild(node.get());
	
	osg::ref_ptr<osg::PositionAttitudeTransform> pt2 = new osg::PositionAttitudeTransform();

	pt2->setPosition(osg::Vec3(10.0f, 0.0f, 0.0f));

	pt2->addChild(node.get());

	root->addChild(pt1.get());
	root->addChild(pt2.get());

	osgUtil::Optimizer opt1;
	opt1.optimize(root.get());

	view->setSceneData(root.get());

	view->realize();

	view->run();

	return 0;

}
#endif

#if 1

#endif