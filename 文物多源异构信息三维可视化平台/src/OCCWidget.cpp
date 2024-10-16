#include "OCCWidget.h"
#include "OCCWindow.h"

#include <QMouseEvent>

#include <Aspect_DisplayConnection.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <AIS_Shape.hxx>
#include <BRep_Tool.hxx>

#include <BRepAlgoAPI_Fuse.hxx>

#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_Transform.hxx>

#include <BRepFilletAPI_MakeFillet.hxx>

#include <BRepLib.hxx>

#include <BRepOffsetAPI_MakeThickSolid.hxx>
#include <BRepOffsetAPI_ThruSections.hxx>

#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakePrism.hxx>

#include <GC_MakeArcOfCircle.hxx>
#include <GC_MakeSegment.hxx>

#include <GCE2d_MakeSegment.hxx>

#include <gp.hxx>
#include <gp_Ax1.hxx>
#include <gp_Ax2.hxx>
#include <gp_Ax2d.hxx>
#include <gp_Dir.hxx>
#include <gp_Dir2d.hxx>
#include <gp_Pnt.hxx>
#include <gp_Pnt2d.hxx>
#include <gp_Trsf.hxx>
#include <gp_Vec.hxx>

#include <Geom_CylindricalSurface.hxx>
#include <Geom_Plane.hxx>
#include <Geom_Surface.hxx>
#include <Geom_TrimmedCurve.hxx>

#include <Geom2d_Ellipse.hxx>
#include <Geom2d_TrimmedCurve.hxx>

#include <TopExp_Explorer.hxx>

#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Compound.hxx>

#include <TopTools_ListOfShape.hxx>

#include <Quantity_NameOfColor.hxx>

#include <QFile>
#include <QFileInfo>
#include <StlAPI_Reader.hxx>
#include <AIS_Shape.hxx>
#include <BRepMesh_IncrementalMesh.hxx>
#include <STEPControl_Reader.hxx>
#include <IGESControl_Reader.hxx>
#include <StlAPI_Reader.hxx>
#include <BRep_Builder.hxx>
#include <BRepTools.hxx>
#include <IFSelect_ReturnStatus.hxx>
#include <QApplication>

OCCWidget::OCCWidget(QWidget *parent)
	: QWidget{ parent }, m_dpiScale(this->devicePixelRatioF())
{
    //this->setStyleSheet("border-width: 1px; border-style: solid; border-color: rgb(207, 221, 228); background-color: rgb(211, 243, 255)");
	// 直接绘制在屏幕上
    this->setAttribute(Qt::WA_PaintOnScreen);
	this->setAttribute(Qt::WA_NoSystemBackground);
	this->setBackgroundRole(QPalette::NoRole);
	this->setFocusPolicy(Qt::StrongFocus);
    // 创建连接显示设备
    Handle(Aspect_DisplayConnection) m_Aspect_DisplayConnect = new Aspect_DisplayConnection();
    // 创建3D接口定义图形驱动
    Handle(OpenGl_GraphicDriver) driver = new OpenGl_GraphicDriver(m_Aspect_DisplayConnect);
    // 创建3D查看器对象，并指定图形驱动
    m_viewer = new V3d_Viewer(driver);
	m_viewer->SetDefaultLights();
	m_viewer->SetLightOn();
	//Handle(Graphic3d_GraphicDriver) theGraphicDriver = ((COCCDemoApp*)AfxGetApp())->GetGraphicDriver();
    // 创建交互上下文对象，关联到3D查看器
    m_context = new AIS_InteractiveContext(m_viewer);
    // 创建视图，并关联到3D查看器
    m_view = m_viewer->CreateView();
    // 获取窗口句柄并创建OCCT_Window
    OCCWindow* wind = new OCCWindow(this);
    // 设置视图窗口
    m_view->SetWindow(wind);
	m_view->SetBackgroundColor(Quantity_Color(30. / 255., 42. / 255., 94. / 255., Quantity_TOC_RGB));
    if (!wind->IsMapped()) wind->Map();
 //   // 绘制立方体
	//TopoDS_Shape box = BRepPrimAPI_MakeBox(100, 100, 100);
	//Handle(AIS_Shape) box_AIS = new AIS_Shape(box);
	//Graphic3d_MaterialAspect material(Graphic3d_NOM_GOLD);
	//m_context->SetMaterial(box_AIS, material, Standard_True);
	//m_context->SetDisplayMode(box_AIS, 1, Standard_True);
	////box_AIS->SetColor(static_cast<Quantity_NameOfColor>((10 + 40) % 400));
	//m_context->SetColor(box_AIS, Quantity_NameOfColor::Quantity_NOC_GREEN, Standard_True);
	//const Handle(AIS_InteractiveObject)& anIOAISBottle = box_AIS;
	//m_context->SetSelected(anIOAISBottle, Standard_True);
	//m_view->FitAll();
	//m_context->Display(box_AIS, Standard_True);
	//m_context->UpdateCurrentViewer();
	//m_context->AutomaticHilight();

	//设置高亮模型
	//Handle(Prs3d_Drawer) aHighlightStyle = m_context->HighlightStyle(); // 获取高亮风格
	//aHighlightStyle->SetMethod(Aspect_TOHM_COLOR);                      // 颜色显示方式              
	//aHighlightStyle->SetColor(Quantity_NOC_RED4);         // 设置高亮颜色  
	//aHighlightStyle->SetDisplayMode(1); // 1整体高亮 2包围盒
	//m_context->Display(box_AIS, Standard_True);

	//MakeBottle
	//TopoDS_Shape aBottle = MakeBottle(50, 70, 30);
	//Handle(AIS_Shape) AISBottle = new AIS_Shape(aBottle);
	//Graphic3d_MaterialAspect material(Graphic3d_NOM_GOLD);
	//m_context->SetMaterial(AISBottle, material, Standard_True);
	//m_context->SetDisplayMode(AISBottle, 1, Standard_True);
	////m_context->SetColor(AISBottle, Quantity_NameOfColor::Quantity_NOC_GREEN, Standard_True);
	//m_context->Display(AISBottle, Standard_False);
	//const Handle(AIS_InteractiveObject)& anIOAISBottle = AISBottle;
	//m_context->SetSelected(anIOAISBottle, Standard_False);
	//m_view->FitAll();

	//QString file_path = "D:/FFFFF/Progoo/HASCR/3rdParty_x64/opencascade-7.3.0/data/occ/Ball.brep";
	//LoadAndDisplay3Dmodel(file_path);
}

QPaintEngine* OCCWidget::paintEngine() const
{
    return nullptr;
}

void OCCWidget::paintEvent( QPaintEvent* /*theEvent*/ )
{
    m_view->Redraw();
}

void OCCWidget::resizeEvent( QResizeEvent* /*theEvent*/ )
{
    if( !m_view.IsNull() )
    {
        m_view->MustBeResized();
    }
}

void OCCWidget::mousePressEvent(QMouseEvent* event)
{
    if ((event->buttons() & Qt::RightButton)) //平移 鼠标右键
    {
        m_mode = Action3d_Panning;
        m_x = event->pos().x();
        m_y = event->pos().y();
    }
    else if (event->buttons() & Qt::LeftButton) //旋转 鼠标左键
    {
        m_mode = Action3d_Rotation;
        m_view->StartRotation(m_dpiScale*event->pos().x(), m_dpiScale*event->pos().y());
    }
}

void OCCWidget::mouseReleaseEvent(QMouseEvent* event)
{
    m_mode = Action3d_Nothing;
}

void OCCWidget::mouseMoveEvent(QMouseEvent* event)
{
    switch (m_mode)
    {
    case OCCWidget::Action3d_Panning:
        m_view->Pan(m_dpiScale*(event->pos().x() - m_x), m_dpiScale*(m_y - event->pos().y()));
        m_x = event->pos().x();
        m_y = event->pos().y();
        break;
    case OCCWidget::Action3d_Rotation:
        m_view->Rotation(m_dpiScale*event->pos().x(), m_dpiScale*event->pos().y());
        break;
    default:
        break;
    }
}

void OCCWidget::wheelEvent(QWheelEvent* event)
{
    // 根据鼠标滚轮方向进行缩放
    double aFactor = 5;

    double aX = event->pos().x();
    double aY = event->pos().y();

    if (event->angleDelta().y() > 0)
    {
        aX += aFactor;
        aY += aFactor;
    }
    else
    {
        aX -= aFactor;
        aY -= aFactor;
    }
    m_view->StartZoomAtPoint(m_dpiScale*event->pos().x(), m_dpiScale*event->pos().y());
    m_view->ZoomAtPoint(event->pos().x(), event->pos().y(), aX, aY);
}


void OCCWidget::LoadAndDisplay3Dmodel(const QString& file_path)
{
	if (!QFile::exists(file_path)) {
		return;
	}

	TopoDS_Shape shape;
	std::string ext = QFileInfo(file_path).suffix().toLower().toStdString();

	bool success = false;

	if (ext == "stl") {
		StlAPI_Reader reader;
		success = reader.Read(shape, file_path.toStdString().c_str());
	}
	else if (ext == "step" || ext == "stp") {
		STEPControl_Reader reader;
		if (reader.ReadFile(file_path.toStdString().c_str()) == IFSelect_RetDone) {
			reader.TransferRoots();
			shape = reader.OneShape();
			success = true;
		}
	}
	else if (ext == "iges" || ext == "igs") {
		IGESControl_Reader reader;
		if (reader.ReadFile(file_path.toStdString().c_str()) == IFSelect_RetDone) {
			reader.TransferRoots();
			shape = reader.OneShape();
			success = true;
		}
	}
	else if (ext == "brep") {
		BRep_Builder builder;
		BRepTools::Read(shape, file_path.toStdString().c_str(), builder);
		success = true;
	}

	if (success) {
		// 清除之前的模型
		if (!m_context.IsNull())
		{
			m_context->EraseAll(Standard_True);
		}

		Handle(AIS_Shape) aisShape = new AIS_Shape(shape);
		Graphic3d_MaterialAspect material(Graphic3d_NOM_PLASTIC);
		m_context->SetMaterial(aisShape, material, Standard_True);
		m_context->SetDisplayMode(aisShape, AIS_Shaded, Standard_True);
		m_context->Display(aisShape, Standard_True);
		m_view->FitAll();
		m_context->UpdateCurrentViewer();

		QApplication::processEvents();  // 确保视图在加载期间得到更新
	}
	else {
	}
}

void OCCWidget::UnDisplay3Dmodel()
{
	if (!m_context.IsNull()) 
	{
		m_context->EraseAll(Standard_True);
	}
}

TopoDS_Shape OCCWidget::MakeBottle(const Standard_Real myWidth, const Standard_Real myHeight, const Standard_Real myThickness)
{
	// Profile : Define Support Points
	gp_Pnt aPnt1(-myWidth / 2., 0, 0);
	gp_Pnt aPnt2(-myWidth / 2., -myThickness / 4., 0);
	gp_Pnt aPnt3(0, -myThickness / 2., 0);
	gp_Pnt aPnt4(myWidth / 2., -myThickness / 4., 0);
	gp_Pnt aPnt5(myWidth / 2., 0, 0);

	// Profile : Define the Geometry
	Handle(Geom_TrimmedCurve) anArcOfCircle = GC_MakeArcOfCircle(aPnt2, aPnt3, aPnt4);
	Handle(Geom_TrimmedCurve) aSegment1 = GC_MakeSegment(aPnt1, aPnt2);
	Handle(Geom_TrimmedCurve) aSegment2 = GC_MakeSegment(aPnt4, aPnt5);

	// Profile : Define the Topology
	TopoDS_Edge anEdge1 = BRepBuilderAPI_MakeEdge(aSegment1);
	TopoDS_Edge anEdge2 = BRepBuilderAPI_MakeEdge(anArcOfCircle);
	TopoDS_Edge anEdge3 = BRepBuilderAPI_MakeEdge(aSegment2);
	TopoDS_Wire aWire = BRepBuilderAPI_MakeWire(anEdge1, anEdge2, anEdge3);

	// Complete Profile
	gp_Ax1 xAxis = gp::OX();
	gp_Trsf aTrsf;

	aTrsf.SetMirror(xAxis);
	BRepBuilderAPI_Transform aBRepTrsf(aWire, aTrsf);
	TopoDS_Shape aMirroredShape = aBRepTrsf.Shape();
	TopoDS_Wire aMirroredWire = TopoDS::Wire(aMirroredShape);

	BRepBuilderAPI_MakeWire mkWire;
	mkWire.Add(aWire);
	mkWire.Add(aMirroredWire);
	TopoDS_Wire myWireProfile = mkWire.Wire();

	// Body : Prism the Profile
	TopoDS_Face myFaceProfile = BRepBuilderAPI_MakeFace(myWireProfile);
	gp_Vec aPrismVec(0, 0, myHeight);
	TopoDS_Shape myBody = BRepPrimAPI_MakePrism(myFaceProfile, aPrismVec);

	// Body : Apply Fillets
	BRepFilletAPI_MakeFillet mkFillet(myBody);
	TopExp_Explorer anEdgeExplorer(myBody, TopAbs_EDGE);
	while (anEdgeExplorer.More()) {
		TopoDS_Edge anEdge = TopoDS::Edge(anEdgeExplorer.Current());
		//Add edge to fillet algorithm
		mkFillet.Add(myThickness / 12., anEdge);
		anEdgeExplorer.Next();
	}

	myBody = mkFillet.Shape();

	// Body : Add the Neck	
	gp_Pnt neckLocation(0, 0, myHeight);
	gp_Dir neckAxis = gp::DZ();
	gp_Ax2 neckAx2(neckLocation, neckAxis);

	Standard_Real myNeckRadius = myThickness / 4.;
	Standard_Real myNeckHeight = myHeight / 10.;

	BRepPrimAPI_MakeCylinder MKCylinder(neckAx2, myNeckRadius, myNeckHeight);
	TopoDS_Shape myNeck = MKCylinder.Shape();

	myBody = BRepAlgoAPI_Fuse(myBody, myNeck);

	// Body : Create a Hollowed Solid
	TopoDS_Face   faceToRemove;
	Standard_Real zMax = -1;

	for (TopExp_Explorer aFaceExplorer(myBody, TopAbs_FACE); aFaceExplorer.More(); aFaceExplorer.Next()) {
		TopoDS_Face aFace = TopoDS::Face(aFaceExplorer.Current());
		// Check if <aFace> is the top face of the bottle抯 neck 
		Handle(Geom_Surface) aSurface = BRep_Tool::Surface(aFace);
		if (aSurface->DynamicType() == STANDARD_TYPE(Geom_Plane)) {
			Handle(Geom_Plane) aPlane = Handle(Geom_Plane)::DownCast(aSurface);
			gp_Pnt aPnt = aPlane->Location();
			Standard_Real aZ = aPnt.Z();
			if (aZ > zMax) {
				zMax = aZ;
				faceToRemove = aFace;
			}
		}
	}

	TopTools_ListOfShape facesToRemove;
	facesToRemove.Append(faceToRemove);
	BRepOffsetAPI_MakeThickSolid aSolidMaker;
	aSolidMaker.MakeThickSolidByJoin(myBody, facesToRemove, -myThickness / 50, 1.e-3);
	myBody = aSolidMaker.Shape();
	// Threading : Create Surfaces
	Handle(Geom_CylindricalSurface) aCyl1 = new Geom_CylindricalSurface(neckAx2, myNeckRadius * 0.99);
	Handle(Geom_CylindricalSurface) aCyl2 = new Geom_CylindricalSurface(neckAx2, myNeckRadius * 1.05);

	// Threading : Define 2D Curves
	gp_Pnt2d aPnt(2. * M_PI, myNeckHeight / 2.);
	gp_Dir2d aDir(2. * M_PI, myNeckHeight / 4.);
	gp_Ax2d anAx2d(aPnt, aDir);

	Standard_Real aMajor = 2. * M_PI;
	Standard_Real aMinor = myNeckHeight / 10;

	Handle(Geom2d_Ellipse) anEllipse1 = new Geom2d_Ellipse(anAx2d, aMajor, aMinor);
	Handle(Geom2d_Ellipse) anEllipse2 = new Geom2d_Ellipse(anAx2d, aMajor, aMinor / 4);
	Handle(Geom2d_TrimmedCurve) anArc1 = new Geom2d_TrimmedCurve(anEllipse1, 0, M_PI);
	Handle(Geom2d_TrimmedCurve) anArc2 = new Geom2d_TrimmedCurve(anEllipse2, 0, M_PI);
	gp_Pnt2d anEllipsePnt1 = anEllipse1->Value(0);
	gp_Pnt2d anEllipsePnt2 = anEllipse1->Value(M_PI);

	Handle(Geom2d_TrimmedCurve) aSegment = GCE2d_MakeSegment(anEllipsePnt1, anEllipsePnt2);
	// Threading : Build Edges and Wires
	TopoDS_Edge anEdge1OnSurf1 = BRepBuilderAPI_MakeEdge(anArc1, aCyl1);
	TopoDS_Edge anEdge2OnSurf1 = BRepBuilderAPI_MakeEdge(aSegment, aCyl1);
	TopoDS_Edge anEdge1OnSurf2 = BRepBuilderAPI_MakeEdge(anArc2, aCyl2);
	TopoDS_Edge anEdge2OnSurf2 = BRepBuilderAPI_MakeEdge(aSegment, aCyl2);
	TopoDS_Wire threadingWire1 = BRepBuilderAPI_MakeWire(anEdge1OnSurf1, anEdge2OnSurf1);
	TopoDS_Wire threadingWire2 = BRepBuilderAPI_MakeWire(anEdge1OnSurf2, anEdge2OnSurf2);
	BRepLib::BuildCurves3d(threadingWire1);
	BRepLib::BuildCurves3d(threadingWire2);

	// Create Threading 
	BRepOffsetAPI_ThruSections aTool(Standard_True);
	aTool.AddWire(threadingWire1);
	aTool.AddWire(threadingWire2);
	aTool.CheckCompatibility(Standard_False);

	TopoDS_Shape myThreading = aTool.Shape();

	// Building the Resulting Compound 
	TopoDS_Compound aRes;
	BRep_Builder aBuilder;
	aBuilder.MakeCompound(aRes);
	aBuilder.Add(aRes, myBody);
	aBuilder.Add(aRes, myThreading);

	return aRes;
}