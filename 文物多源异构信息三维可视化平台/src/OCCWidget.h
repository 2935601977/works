#ifndef OCCWIDGET_H
#define OCCWIDGET_H

#include <QWidget>

#include "V3d_Viewer.hxx"
#include "V3d_view.hxx"
#include "AIS_InteractiveContext.hxx"


class OCCWidget : public QWidget
{
    Q_OBJECT
public:
    OCCWidget(QWidget *parent = nullptr);

protected:
    enum Action3d
    {
        Action3d_Nothing,
        Action3d_Panning,//平移
        Action3d_Zooming,//缩放
        Action3d_Rotation//旋转
    };
    QPaintEngine* paintEngine() const override;
    void paintEvent( QPaintEvent* /*theEvent*/ ) override;
    void resizeEvent( QResizeEvent* /*theEvent*/ ) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

private:
	TopoDS_Shape MakeBottle(const Standard_Real myWidth, const Standard_Real myHeight, const Standard_Real myThickness);

private:
    Handle(V3d_Viewer)						m_viewer = nullptr;
    Handle(V3d_View)						m_view = nullptr;
    Handle(AIS_InteractiveContext)			m_context = nullptr;
    Standard_Integer						m_x;  //记录鼠标平移坐标X
    Standard_Integer						m_y;  //记录鼠标平移坐标y
    Standard_Integer						m_z;  //记录鼠标平移坐标z
    Action3d								m_mode;       //平移、缩放、旋转
    double									m_dpiScale;

public:
	void LoadAndDisplay3Dmodel(const QString& file_path);
	void UnDisplay3Dmodel();
};
#endif // OCCWIDGET_H