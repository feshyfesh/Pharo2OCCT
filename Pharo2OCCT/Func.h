#pragma once
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepBuilderAPI_MakeSolid.hxx>
#include <BRepBuilderAPI_MakePolygon.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBndLib.hxx>
#include <Bnd_Box.hxx>

#include <BRepAlgoAPI_Common.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepBuilderAPI_Transform.hxx>

#include <GProp_GProps.hxx>
#include <BRepGProp.hxx>
#include <TopExp_Explorer.hxx>

#include <gp_Trsf.hxx>
#include <gp_Vec.hxx>
#include <gp.hxx>
#include <gp_Vec.hxx>

#include <TopoDS.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Shell.hxx>
#include <TopoDS_Solid.hxx>

#include <IVtkTools_ShapeDataSource.hxx>
#include <vtkAutoInit.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyDataMapper.h>
#include <vtkNew.h>

#ifdef __cplusplus
extern "C" {
#endif 
class MyClass {
public:
	void createBox(float length, float height, float width);
	void createCone(float radBot, float height, float radTop);
};
	__declspec(dllexport)TopoDS_Shape Array[10];
	__declspec(dllexport)void displayShape(int n);

	__declspec(dllexport)typedef struct MyClass MyClass;
	__declspec(dllexport)MyClass* newClass();
	__declspec(dllexport)void deleteMyClass(MyClass* v);

	__declspec(dllexport)void setcreateBox(MyClass* v, float a, float b, float c);
	__declspec(dllexport)void runBox(float x, float y, float z);
	
	__declspec(dllexport)void setcreateCone(MyClass* v, float a, float b, float c);
	__declspec(dllexport)void runCone(float x, float y, float z);

	__declspec(dllexport)void createCyclinder(int noInArray, double rad, double height);
	__declspec(dllexport)void createSphere(int noInArray, float rad);
	__declspec(dllexport)void createCustomShape(int noInArray, int numPoints, float coordinates[]);
	__declspec(dllexport)void fuseShapes(int noInArray, int shapeInArray1, int shapeInArray2);
	__declspec(dllexport)void intersectionShape(int noInArray, int shapeInArray1, int shapeInArray2);
	__declspec(dllexport)TopoDS_Shape createCyclinder1(double rad, double height);
	__declspec(dllexport)double computeShapeVolume(int noInArray);
	__declspec(dllexport)int computeNumFaces(int noInArray);
	__declspec(dllexport)double computeLength(int noInArray);
	__declspec(dllexport)double computeHeight(int noInArray);
	__declspec(dllexport)double computeWidth(int noInArray);


#ifdef __cplusplus  
} // extern "C"  
#endif