#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include "Func.h"

VTK_MODULE_INIT(vtkRenderingOpenGL)
VTK_MODULE_INIT(vtkInteractionStyle)

extern "C" {

	MyClass* newClass() {
		return new MyClass;
	}
	void deleteMyClass(MyClass* v) {
		delete v;
	}

	void displayShape(int noInArray) {
		vtkNew<vtkRenderWindow>	renwin;
		vtkNew<vtkRenderer> ren;
		renwin->AddRenderer(ren.Get());

		vtkNew<vtkInteractorStyleTrackballCamera> istyle;
		vtkNew<vtkRenderWindowInteractor> iren;

		iren->SetRenderWindow(renwin.Get());
		iren->SetInteractorStyle(istyle.Get());

		vtkNew<IVtkTools_ShapeDataSource> occSource;
		occSource->SetShape(new IVtkOCC_Shape(Array[noInArray]));

		vtkNew<vtkPolyDataMapper> mapper;

		mapper->SetInputConnection(occSource->GetOutputPort());

		vtkNew<vtkActor> actor;
		actor->SetMapper(mapper.Get());
		ren->AddActor(actor.Get());

		renwin->Render();
		iren->Start();
	}

	void MyClass::createBox(float length, float height, float width) {
		BRepPrimAPI_MakeBox mkBox(length, height, width);
		const TopoDS_Shape& shape = mkBox.Shape();
		Array[0] = shape;
	}
	void setcreateBox(MyClass* v, float a, float b, float c) {
		v->createBox(a, b, c);
	}
	void runBox(float x, float y, float z) {
		struct MyClass* c = newClass();
		setcreateBox(c, x, y, z);
		deleteMyClass(c);
	}

	void MyClass::createCone(float radBot, float height, float radTop) {
		BRepPrimAPI_MakeCone coneMaker(radBot,radTop,height);
		const TopoDS_Shape& shape = coneMaker.Shape();
		Array[1] = shape;
	}
	void setcreateCone(MyClass* v, float a, float b, float c) {
		v->createCone(a, b, c);
	}
	void runCone(float x, float y, float z) {
		struct MyClass* c = newClass();
		setcreateCone(c, x, y, z);
		deleteMyClass(c);
	}

	void createCyclinder(int noInArray, double rad, double height) {
		BRepPrimAPI_MakeCylinder cylinderMaker(rad, height);
		const TopoDS_Shape& shape = cylinderMaker.Shape();
		Array[noInArray] = shape;
	}

	TopoDS_Shape createCyclinder1(double rad, double height) {
		BRepPrimAPI_MakeCylinder cylinderMaker(rad, height);
		const TopoDS_Shape& shape = cylinderMaker.Shape();
		return shape;
	}

	void createSphere(int noInArray, float rad) {
		BRepPrimAPI_MakeSphere sphereMaker(rad);
		const TopoDS_Shape& shape = sphereMaker.Shape();
		Array[noInArray] = shape;
	}

	void createCustomShape(int noInArray, int numPoints, float coordinates[]) {
		// Convert the float coordinates to gp_Pnt objects
		gp_Pnt* points = new gp_Pnt[numPoints];
		for (int i = 0; i < numPoints; ++i) {
			points[i] = gp_Pnt(coordinates[i * 3], coordinates[i * 3 + 1], coordinates[i * 3 + 2]);
		}
		// Create a polygonal wire from the points
		BRepBuilderAPI_MakePolygon polygonMaker;
		for (int i = 0; i < numPoints; ++i) {
			polygonMaker.Add(points[i]);
		}
		polygonMaker.Close();  // Close the polygon
		TopoDS_Wire wireShape = polygonMaker.Wire();
		// Extrude the wire into a prism
		gp_Vec prismVec(0, 0, 10);
		BRepPrimAPI_MakePrism prismMaker(wireShape, prismVec);
		const TopoDS_Shape& shape = prismMaker.Shape();
		delete[] points;
		Array[noInArray] = shape;
	}

	void fuseShapes(int noInArray, int shapeInArray1, int shapeInArray2) {
		// Move the second box so that it intersects with the first one
		gp_Trsf transformation;
		transformation.SetTranslation(gp_Vec(5, 10, 15));
		BRepBuilderAPI_Transform transformMaker(Array[shapeInArray2], transformation, Standard_True);
		Array[shapeInArray2] = transformMaker.Shape();
		// Fuse the two boxes together
		BRepAlgoAPI_Fuse fuseMaker(Array[shapeInArray1], Array[shapeInArray2]);
		TopoDS_Shape resultShape = fuseMaker.Shape();
		Array[noInArray] = resultShape;
	}

	void intersectionShape(int noInArray, int shapeInArray1, int shapeInArray2) {
		// Translate the sphere so that it intersects with the box
		gp_Trsf translation;
		translation.SetTranslation(gp_Vec(5.0, 10.0, 15.0));
		BRepBuilderAPI_Transform transformMaker(Array[shapeInArray1], translation);
		Array[shapeInArray1] = transformMaker.Shape();
		// Compute the intersection of the box and the sphere
		BRepAlgoAPI_Common commonMaker(Array[shapeInArray2], Array[shapeInArray1]);
		TopoDS_Shape intersectionShape = commonMaker.Shape();
		Array[noInArray] = intersectionShape;
	}

	double computeShapeVolume(int noInArray){
		GProp_GProps volumeProps;
		BRepGProp::VolumeProperties(Array[noInArray], volumeProps);
		return volumeProps.Mass();
	}

	int computeNumFaces(int noInArray){
		int numFaces = 0;
		TopExp_Explorer explorer(Array[noInArray], TopAbs_FACE);
		while (explorer.More()) {
			const TopoDS_Face& face = TopoDS::Face(explorer.Current());
			++numFaces;
			explorer.Next();
		}
		return numFaces;
	}

	double computeLength(int noInArray) {
		Bnd_Box boundingBox;
		BRepBndLib::Add(Array[noInArray], boundingBox);
		double xmin, ymin, zmin, xmax, ymax, zmax,length;
		boundingBox.Get(xmin, ymin, zmin, xmax, ymax, zmax);
		length = xmax - xmin;
		return length;
	}
	double computeHeight(int noInArray) {
		Bnd_Box boundingBox;
		BRepBndLib::Add(Array[noInArray], boundingBox);
		double xmin, ymin, zmin, xmax, ymax, zmax, height;
		boundingBox.Get(xmin, ymin, zmin, xmax, ymax, zmax);
		height = ymax - ymin;
		return height;
	}
	double computeWidth(int noInArray) {
		Bnd_Box boundingBox;
		BRepBndLib::Add(Array[noInArray], boundingBox);
		double xmin, ymin, zmin, xmax, ymax, zmax, width;
		boundingBox.Get(xmin, ymin, zmin, xmax, ymax, zmax);
		width = zmax - zmin;
		return width;
	}
}

