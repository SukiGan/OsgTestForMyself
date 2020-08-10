#if 0

#include <Windows.h>

#include <osgViewer/Viewer> 

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>

#include <osg/CoordinateSystemNode>
#include <osg/ShapeDrawable>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>
#include <iostream>


osg::ref_ptr<osg::Node> createEarth()
{
	osg::ref_ptr<osg::ShapeDrawable> sd = new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0.0, 0.0, 0.0),
		osg::WGS_84_RADIUS_POLAR));

	osg::ref_ptr<osg::Geode> geode = new osg::Geode;

	geode->addDrawable(sd.get());

	std::string fileName("E:/OSG/data/OpenSceneGraph-Data/Images/land_shallow_topo_2048.jpg");

	geode->getOrCreateStateSet()->setTextureAttributeAndModes(0, 
		new osg::Texture2D(osgDB::readImageFile(fileName)));

	osg::ref_ptr<osg::CoordinateSystemNode> csn = new osg::CoordinateSystemNode;

	csn->setEllipsoidModel(new osg::EllipsoidModel());

	csn->addChild(geode.get());

	return csn.get();
}

int main()
{
	osg::ref_ptr<osgViewer::Viewer> view1 = new osgViewer::Viewer;

	osg::ref_ptr<osg::Group> root = new osg::Group();

	root->addChild(createEarth());

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
#include <osg/Group>
#include <osg/Geode>

#include <osg/Geometry>
#include <osg/Image>
#include <osg/Notify>
#include <osg/Texture>

#include <osg/StateSet>
#include <osg/StateAttribute>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>
#include <osgDB/Registry>

#include <osgUtil/Optimizer>

#include <iostream>

class MyCopyOp : public osg::CopyOp
{
protected:
	mutable int _number;
	mutable int _blank;
public:
	inline MyCopyOp(CopyFlags flags=SHALLOW_COPY):
		osg::CopyOp(flags),_blank(2),_number(5)
	{

	}

	inline void moveIn() const
	{
		_blank += _number;
	}

	inline void moveOut() const 
	{
		_blank -= _number;
	}

	inline void writeIndent() const
	{
		for (int i = 0; i < _blank; ++i)
		{
			std::cout << " ";
		}
	}

	virtual osg::Referenced* operator() (const osg::Referenced* ref) const
	{
		writeIndent();
		std::cout << "Copying Reference" << ref << std::endl;
		moveIn();
		osg::Referenced* ret_ref = CopyOp::operator()(ref);

		moveOut();
		return ret_ref;
	}

	virtual osg::Object* operator() (const osg::Object* obj) const
	{
		writeIndent();

		std::cout << "Copying Object" << obj;

		if (obj)
		{
			std::cout << " " << obj->className();
		}

		std::cout << std::endl;
		moveIn();
		osg::Object* ret_obj = CopyOp::operator()(obj);

		moveOut();

		return ret_obj;
	}

	virtual osg::Node* operator() (const osg::Node* node) const
	{
		writeIndent();
		std::cout << "Copying Node" << node;

		if (node)
		{
			std::cout << " " << node->className() << " " << node->getName() << " ";
		}

		std::cout << std::endl;

		moveIn();
		osg::Node* ret_node = CopyOp::operator()(node);

		moveOut();

		return ret_node;
	}

	virtual osg::Drawable* operator() (const osg::Drawable* drawable) const
	{
		writeIndent();

		std::cout << "Copying Drawable" << drawable;
		if (drawable)
		{
			std::cout << " " << drawable->className();
		}

		std::cout << std::endl;

		moveIn();

		osg::Drawable* ret_drawable = CopyOp::operator()(drawable);

		moveOut();

		return ret_drawable;
	}

	virtual osg::StateSet* operator() (const osg::StateSet* stateset) const
	{
		writeIndent();

		std::cout << "copying stateset" << stateset;

		if (stateset)
		{
			std::cout << " " << stateset->className();
		}

		std::cout << std::endl;

		moveIn();
		osg::StateSet* ret_stateset = CopyOp::operator()(stateset);
		moveOut();

		return ret_stateset;
	}

	virtual osg::StateAttribute* operator()(const osg::StateAttribute* arr) const
	{
		writeIndent();
		std::cout << "Copying stateAttribute" << arr;
		
		if (arr)
		{
			std::cout << " " << arr->className();
		}

		std::cout << std::endl;

		moveIn();

		osg::StateAttribute* ret_attr = CopyOp::operator()(arr);

		moveOut();

		return ret_attr;
	}

	virtual osg::Texture* operator()(const osg::Texture* text) const
	{
		writeIndent();
		std::cout << "Copying Texture" << text;

		if (text)
		{
			std::cout << " " << text->className();
		}

		std::cout << std::endl;
		moveIn();
		osg::Texture* ret_text = CopyOp::operator()(text);
		moveOut();

		return ret_text;
	}

	virtual osg::Image* operator()(const osg::Image* image) const
	{
		writeIndent();

		std::cout << "Copying Image" << image;

		if (image)
		{
			std::cout << " " << image->className();
		}
		std::cout << std::endl;

		moveIn();
		osg::Image* ret_image = CopyOp::operator()(image);
		moveOut();

		return ret_image;
	}
};

int main()
{
	osg::ref_ptr<osgViewer::Viewer> view1 = new osgViewer::Viewer();
	
	osg::ref_ptr<osg::Node> rootnode1 = osgDB::readNodeFile("E:/OSG/data/OpenSceneGraph-Data/glider.osg");

	osgUtil::Optimizer opt1;
	opt1.optimize(rootnode1.get());

	osg::ref_ptr<osg::Node> shallowCopy = dynamic_cast<osg::Node*>(rootnode1->clone(osg::CopyOp::SHALLOW_COPY));
	std::cout << "Finish" << std::endl;

	osg::ref_ptr<osg::Node> deepCopy = dynamic_cast<osg::Node*>(rootnode1->clone(osg::CopyOp::DEEP_COPY_ALL));
	std::cout << "Finish" << std::endl;

	osg::ref_ptr<osg::Node> myDeepCopy = dynamic_cast<osg::Node*>(rootnode1->clone(MyCopyOp(osg::CopyOp::DEEP_COPY_ALL)));
	std::cout << "Finish" << std::endl;

	view1->setSceneData(rootnode1.get());

	view1->realize();
	view1->run();

	return 0;

	return 0;
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

osg::ref_ptr<osg::Node> createQuad()
{
	

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

	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));
	
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	geode->addDrawable(geom.get());

	return geode.get();
}

int main()
{
	osg::ref_ptr<osgViewer::Viewer> view1 = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root1 = new osg::Group();

	root1->addChild(createQuad());

	osgUtil::Optimizer opt1;
	opt1.optimize(root1.get());

	view1->setSceneData(root1.get());

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
#include <osg/Geometry>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>

osg::ref_ptr<osg::Node> createQuad()
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();

	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();

	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();
	v->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));
	v->push_back(osg::Vec3(1.0f, 0.0f, 0.0f));
	v->push_back(osg::Vec3(1.0f, 0.0f, 0.0f));
	v->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));
	v->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));

	geom->setVertexArray(v.get());

	osg::ref_ptr<osg::DrawElementsUInt> quad = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);

	quad->push_back(0);
	quad->push_back(1);
	quad->push_back(2);
	quad->push_back(3);

	geom->addPrimitiveSet(quad.get());

	osg::ref_ptr<osg::DrawElementsUInt> triangle = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
	triangle->push_back(4);
	triangle->push_back(0);
	triangle->push_back(3);

	geom->addPrimitiveSet(triangle.get());
	
	osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array();
	vc->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	vc->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
	vc->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
	vc->push_back(osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f));

	osg::TemplateIndexArray<unsigned int, osg::Array::UIntArrayType, 4, 4>* colorIndex =
		new osg::TemplateIndexArray<unsigned int, osg::Array::UIntArrayType, 4, 4>();
	colorIndex->push_back(0);
	colorIndex->push_back(1);
	colorIndex->push_back(2);
	colorIndex->push_back(3);
	colorIndex->push_back(2);

	geom->setColorArray(vc.get());
	//Gxz:: setColorIndices is not a member of geomtery
	//geom->setColorIndices(colorIndex);

	geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
	
	osg::ref_ptr<osg::Vec3Array> nc = new osg::Vec3Array();
	nc->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));
	
	geom->setNormalArray(nc.get());
	geom->setNormalBinding(osg::Geometry::BIND_OVERALL);

	geode->addChild(geom.get());

	return geode.get();
}

int main()
{
	osg::ref_ptr<osgViewer::Viewer> view1 = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root = new osg::Group();

	root->addChild(createQuad());

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
#include <osg/ShapeDrawable>

#include <osg/LOD>

#include <osgUtil/Optimizer>

osg::ref_ptr<osg::Geode> createShape()
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();

	float radius = 0.8f;
	float height = 1.0f;

	osg::ref_ptr<osg::TessellationHints> hints = new osg::TessellationHints;
	hints->setDetailRatio(0.5f);

	geode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0.0f, 0.0f,
		0.0f), radius), hints.get()));

	geode->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(2.0f, 0.0f, 0.0f),
		2 * radius), hints.get()));

	geode->addDrawable(new osg::ShapeDrawable(new osg::Cone(osg::Vec3(4.0f, 0.0f, 0.0f),
		radius, height), hints.get()));

	geode->addDrawable(new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(6.0f, 0.0f, 0.0f),
		radius, height), hints.get()));

	geode->addDrawable(new osg::ShapeDrawable(new osg::Capsule(osg::Vec3(8.0f, 0.0f, 0.0f),
		radius, height), hints.get()));

	return geode.get();
}

int main()
{
	osg::ref_ptr<osgViewer::Viewer> view1 = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root = new osg::Group();

	root->addChild(createShape());

	osgUtil::Optimizer opt1;
	opt1.optimize(root);

	view1->setSceneData(root.get());

	view1->realize();

	view1->run();

	return 0;
}
#endif

#if 1

#endif