#ifndef PG_SDC_GUI_ENTRYWIDGET_H
#define PG_SDC_GUI_ENTRYWIDGET_H

#include <QWidget>
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QRect>
#include "Pg_SDC_GUI_Database.h"
#include <QEvent>
#include <QMouseEvent>
#include <QScrollArea>
#include <QFrame>
#include <QSize>
#include "qwt_plot_panner.h"
#include "qwt_date_scale_draw.h"
#include "qwt_plot_canvas.h"
#include "qwt_plot_magnifier.h"
#include "qwt_plot_grid.h"
#include "qwt_plot.h"
#include "qwt_plot_layout.h"
#include "qwt_plot_curve.h"
#include <qwt_plot_dict.h>
#include "qwt_legend.h"
#include "qwt_legend_label.h"
#include "qwt_column_symbol.h"
#include "qwt_series_data.h"
#include "qwt_symbol.h"
#include "qwt_plot_picker.h"
#include "qwt_picker_machine.h"

#ifndef CHINESESTRING
#define CHINESESTRING(a) QString::fromLocal8Bit(a)
#endif


enum DataType 
{
    CalibrationData,
    SampleCollectionData,
    ElementDetectionData
};

enum DownFrameType
{
    DownFrame_None,
    DownFrame_Parameter,
    DownFrame_Curve,
    DownFrame_SampleCollection_Details,
    DownFrame_ElementDetection_Details
};

class EntryWidget : public QWidget                                  // 数据查询对应的每个条目，n条数据==n个条目，显示在数据管理页面的查询结果
{
    Q_OBJECT
public:
    explicit EntryWidget(QWidget *parent = nullptr, QSize size = QSize());

    int                 width;                                     // 显示查询结果条目框的大小
    int                 height;

    QWidget*            m_Widget;                                   // 当前条目的widget
    QWidget*            m_Up_Frame;                                 // 上部框架
    QLabel*             m_OIL_Label;                                // 油品标签
    QLabel*             m_TimeLabel;                                // 时间标签
    QPushButton*        m_btn_Parameter;                            // 设备校准参数按钮
    QPushButton*        m_btn_Curve;                                // 设备校准曲线按钮
    QPushButton*        m_btn_sample_collection_Details;            // 样本采集详情按钮
    QPushButton*        m_btn_element_detection_Details;            // 元素检测详情按钮
    QFrame*             m_separator;                                //分割线
    QScrollArea*        m_Down_ScrollArea;
    QWidget*            m_Down_Frame;
    QwtPlot*			m_QwtPlot;	        			//光谱曲线显示
    QwtPlotCurve*		m_QwtPlotCurve_Background;
    QwtPlotCurve*		m_QwtPlotCurve_WhiteBoard;
    QwtLegend *         m_Qwtlegend;
    QwtPlotGrid *       m_grid; 

public:
    void MoveWidget();                                              // 默认界面显示，默认为设备校准数据的条目界面显示
    void SignalsConnect();
    void SampleCollection_EntryWidget_Showed();                     // 样本采集对应的entrywidget显示界面
    void ElementDetection_Entrywidget_Showed();                     // 元素检测对应的entrywidget显示界面
    void ClearDownFrame();                                          // 清空DownFrame的详情页显示，清理资源，每次只显示当前需要显示的详情页

signals:
    void downFrameRequested(EntryWidget* entryWidget);

public:
    DataType            m_DataType;                                 // 当前条目对应的数据类型

private:
    DownFrameType       m_DownFrameType;                            // 当前显示的详情页类型

private slots:
    void showDownFrame(); 
    void ParameterDisplay();                                        // 设备校准参数按钮点击，显示详情页
    void CurveDisplay();                                            // 设备校准曲线按钮点击，显示详情页
    void SampleCollectionDetailsDisplay();                          // 样本采集详情按钮点击，显示详情页
    void ElementDetectionDetailsDisplay();                          // 元素检测详情按钮点击，显示详情页
    void showItem(const QVariant &itemInfo, bool on);
public:
    CLIENTCALIBRATEDATA calibrate_dataValue;                        // 设备校准数据查询返回
    SAMPLECOLLECTION    sample_collection_dataValue;                // 样本采集数据查询返回
    ELEMENTDETECTION    element_detection_dataValue;                // 元素检测数据查询返回数据
};

#endif // PG_SDC_GUI_ENTRYWIDGET_H