#if 0
#include <Windows.h>
#include <osgViewer/Viewer>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>
#include <osgUtil/SmoothingVisitor>

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

	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));

	return geom.get();
}

int main()
{
	osg::ref_ptr<osgViewer::Viewer> view1 = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root = new osg::Group();

	osg::ref_ptr<osg::Geometry> geometry = createQuad();

	osgUtil::SmoothingVisitor::smooth(*(geometry.get()));

	osg::ref_ptr<osg::Geode> geode = new osg::Geode();

	geode->addDrawable(geometry.get());

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

//Gxz is busy these days. I ma prepare for neut Ph.D position.come on. you are so young that can do anything that you wanted.
//Leave CY . name Forget Eleven. Just like her name Eleven

#endif
