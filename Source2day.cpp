#if 0
#include <Windows.h>

#include <osgViewer/Viewer>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/Geometry>
#include <osg/AutoTransform>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgText/Text>

#include <osgUtil/Optimizer>

#include <iostream>

osg::ref_ptr<osg::Node> createAutoTransform(osg::Vec3& Position, float size,
	std::string& label, osg::AutoTransform::AutoRotateMode autoMode,
	osgText::Text::AxisAlignment axisAlignment)
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();

	std::string font("E:/OSG/data/OpenSceneGraph-Data/fonts/times.ttf");
	osg::ref_ptr<osgText::Text> text1 = new osgText::Text();

	geode->addDrawable(text1.get());

	text1->setFont(font);
	text1->setFontResolution(128.0f, 128.0f);
	text1->setCharacterSize(size);

	text1->setAlignment(osgText::Text::CENTER_CENTER);

	text1->setAxisAlignment(axisAlignment);
	text1->setText(label);
	geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	osg::ref_ptr<osg::AutoTransform> at = new osg::AutoTransform();

	at->addChild(geode.get());
	at->setAutoRotateMode(autoMode);

	at->setAutoScaleToScreen(false);

	at->setMinimumScale(0.0f);
	at->setMaximumScale(5.0f);

	at->setPosition(Position);

	return at.get();

}

int main()
{
	osg::ref_ptr<osgViewer::Viewer> view1 = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root = new osg::Group();

	std::string text("Gxz Cand");

	osg::Vec3 pos(0.0f, 0.0f, 0.0f);
	root->addChild(createAutoTransform(pos, 60.0f,
		text, osg::AutoTransform::ROTATE_TO_SCREEN, osgText::Text::XY_PLANE));

	root->addChild(createAutoTransform(pos, 60.0f,
		text, osg::AutoTransform::NO_ROTATION, osgText::Text::XY_PLANE));

	root->addChild(createAutoTransform(pos, 60.0f,
		text, osg::AutoTransform::ROTATE_TO_CAMERA, osgText::Text::XY_PLANE));

	osgUtil::Optimizer opt;
	opt.optimize(root.get());

	view1->setSceneData(root.get());

	view1->realize();

	view1->run();

	return 0;
}
#endif

#if 0
#include <Windows.h>

#include <osgViewer/Viewer>
#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/Switch>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>

int main()
{
	osg::ref_ptr<osgViewer::Viewer> view1 = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root = new osg::Group();

	osg::ref_ptr<osg::Node> node1 = new osg::Node();
	node1 = osgDB::readNodeFile("E:/OSG/data/OpenSceneGraph-Data/cow.osg");

	osg::ref_ptr<osg::Node> node2 = osgDB::readNodeFile("E:/OSG/data/OpenSceneGraph-Data/glider.osg");

	osg::ref_ptr<osg::Switch> swh1 = new osg::Switch();
	swh1->addChild(node1.get(), false);
	swh1->addChild(node2.get(), true);

	root->addChild(swh1);

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

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/LOD>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>


int main()
{
	osg::ref_ptr<osgViewer::Viewer> view1 = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root = new osg::Group();

	osg::ref_ptr<osg::Node> node1 = new osg::Node();

	node1 = osgDB::readNodeFile("E:/OSG/data/OpenSceneGraph-Data/cow.osg");

	osg::ref_ptr<osg::Node> node2 = osgDB::readNodeFile("E:/OSG/data/OpenSceneGraph-Data/glider.osg");
	
	osg::ref_ptr<osg::LOD> lode = new osg::LOD();

	lode->addChild(node1.get(), 0.0f, 30.0f);
	lode->addChild(node2.get(), 30.0f, 100.0f);

	osgDB::writeNodeFile(*(lode.get()),"E:/OSG/data/OpenSceneGraph-Data/lode.osg");

	root->addChild(lode.get());

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

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/PagedLOD>

#include <osgUtil/Optimizer>
#include <osg/PositionAttitudeTransform>
#include <osg/MatrixTransform>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgGA/TrackballManipulator>

#include <iostream>

osg::ref_ptr<osg::Group> createPageLOD()
{
	osg::ref_ptr<osg::PagedLOD> page = new osg::PagedLOD();

	page->setCenter(osg::Vec3(0.0f, 0.0f, 0.0f));

	page->setFileName(0,"E:/OSG/data/OpenSceneGraph-Data/cow.osg");
	page->setRange(0, 0.0f, 50.0f);

	page->setFileName(1, "E:/OSG/data/OpenSceneGraph-Data/glider.osg");
	page->setRange(1, 50.0f, 100.0f);

	page->setFileName(2, "E:/OSG/data/OpenSceneGraph-Data/cessna.osg");
	page->setRange(2, 100.0f, 200.0f);

	return page.get();
}

int main()
{
	osg::ref_ptr<osgViewer::Viewer> view1 = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root = new osg::Group();
	osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform();

	mt->addChild(createPageLOD());

	osg::Matrix m;
	m.makeRotate(60.0f, 0.0f, 0.0f, 1.0f);

	mt->setMatrix(m);

	root->addChild(mt.get());

	osgDB::writeNodeFile(*root, "E:/OSG/data/OpenSceneGraph-Data/page.osg");

	osgUtil::Optimizer pt1;
	pt1.optimize(root.get());

	view1->setSceneData(root.get());

	view1->realize();

	view1->run();

	return 0;
}
#endif 

#if 0
//Gxz::appearance some error on debug  #include <osgSim/Impostor>
#include <Windows.h>

#include <osgViewer/Viewer>

#include <osg/Geode>
#include <osg/Node>
#include <osg/Group>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>


#include <osgSim/Impostor>
#include <osgUtil/Optimizer>

int main()
{
	osg::ref_ptr<osgViewer::Viewer> view1 = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root = new osg::Group();

	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("E:/OSG/data/OpenSceneGraph-Data/cow.osg");

	osg::ref_ptr<osgSim::Impostor> impostor = new osgSim::Impostor();
	impostor->setImpostorThreshold(50.0f);
	impostor->addChild(node.get(), 0, 10000.0f);

	root->addChild(impostor.get());

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

#include <osg/Node>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/StateSet>

#include <osg/ConvexPlanarOccluder>
#include <osg/BoundingBox>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>

#include <iostream>

osg::ref_ptr<osg::Node> createOccluder(const osg::Vec3& v1,
	const osg::Vec3& v2, const osg::Vec3& v3, const osg::Vec3& v4)
{
	osg::ref_ptr<osg::OccluderNode> occluderNode = new osg::OccluderNode();

	osg::ref_ptr<osg::ConvexPlanarOccluder> cpo = new osg::ConvexPlanarOccluder;

	occluderNode->setOccluder(cpo.get());
	occluderNode->setName("occluder");

	osg::ConvexPlanarPolygon& occluder = cpo->getOccluder();
	occluder.add(v1);
	occluder.add(v2);
	occluder.add(v3);
	occluder.add(v4);

	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;

	osg::ref_ptr<osg::Vec3Array> coords = new osg::Vec3Array(occluder.getVertexList().begin(),
		occluder.getVertexList().end());

	geom->setVertexArray(coords);

	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array(1);
	(*colors)[0].set(1.0f, 1.0f, 1.0f, 0.5f);
	geom->setColorArray(colors.get());
	geom->setColorBinding(osg::Geometry::BIND_OVERALL);

	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));

	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	geode->addDrawable(geom.get());

	osg::ref_ptr<osg::StateSet> stateset = new osg::StateSet();
	stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	stateset->setMode(GL_BLEND, osg::StateAttribute::ON);
	stateset->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

	geom->setStateSet(stateset.get());

	occluderNode->addChild(geode.get());

	return occluderNode.get();
}

osg::ref_ptr<osg::Group> createOccludersAroundModel(osg::ref_ptr<osg::Node> model)
{
	osg::ref_ptr<osg::Group> scene = new osg::Group;
	scene->setName("GxzScene");

	scene->addChild(model.get());
	model->setName("cow.osg");

	const osg::BoundingSphere bs = model->getBound();

	osg::BoundingBox bb;
	bb.expandBy(bs);

	scene->addChild(createOccluder(bb.corner(0),
		bb.corner(1),
		bb.corner(5),
		bb.corner(4)));

	scene->addChild(createOccluder(bb.corner(1),
		bb.corner(3),
		bb.corner(7),
		bb.corner(5)));

	scene->addChild(createOccluder(bb.corner(2),
		bb.corner(0),
		bb.corner(4),
		bb.corner(6)));

	scene->addChild(createOccluder(bb.corner(3),
		bb.corner(2),
		bb.corner(6),
		bb.corner(7)));
	
	return scene.get();
}

int main()
{
	osg::ref_ptr<osgViewer::Viewer> view1 = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root = new osg::Group();

	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("E:/OSG/data/OpenSceneGraph-Data/cow.osg");

	root->addChild(createOccludersAroundModel(node.get()));

	osgUtil::Optimizer opt1;
	opt1.optimize(root.get());

	view1->setSceneData(root.get());

	view1->realize();

	view1->run();

	return 0;

}
#endif