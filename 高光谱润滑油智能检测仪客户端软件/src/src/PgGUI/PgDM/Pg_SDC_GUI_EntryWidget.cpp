#include "Pg_SDC_GUI_EntryWidget.h"
#include <QGridLayout>
#include <QScrollBar>
#include <QScroller>



EntryWidget::EntryWidget(QWidget *parent, QSize size) : QWidget(parent)
{
    // width=964;
    // height=504;
    width=size.width();
    height=size.height();
    m_DataType=CalibrationData;

    this->setAutoFillBackground(true);
    this->setWindowFlags(Qt::FramelessWindowHint/* | Qt::WindowStaysOnTopHint*/);
    this->setAttribute(Qt::WA_QuitOnClose, true);
    this->setAttribute(Qt::WA_TranslucentBackground);

    this->resize(width,height);
    this->setStyleSheet("background-color:transparent; border-image:none;");

    m_Widget=new QWidget(this);
    m_Widget->setStyleSheet("background-color:transparent; border-image:none;");
    m_Widget->setVisible(true);

    m_Up_Frame=new QWidget(m_Widget);
    m_Up_Frame->setStyleSheet("background-color:transparent;border-image: url(:/image/image/entry_up.png);");
    m_Up_Frame->setVisible(true);

    // 创建时间标签
    m_TimeLabel = new QLabel(m_Up_Frame);
    m_TimeLabel->setStyleSheet("QLabel { font-family:Source Han Sans CN-Bold; font-size:16px; font-weight: bold; color: #333333; background-color:transparent;}" "QLabel{border-image:none;}");
    m_TimeLabel->setVisible(true);

    m_OIL_Label = new QLabel(m_Up_Frame);
    m_OIL_Label->setStyleSheet("QLabel { font-family: 'Source Han Sans CN'; font-size: 28px; color: #333333; font-weight: bold; background-color: transparent; border-image: none; }");
    m_OIL_Label->setVisible(false);


    // 创建参数按钮
    m_btn_Parameter = new QPushButton(m_Up_Frame);
    m_btn_Parameter->setStyleSheet("QPushButton{font-family:Microsoft YaHei; font-size:16px; color:black;}" "QPushButton{background-color:rgb(236,114,112); border-radius:5px;border-image:none;}");
    m_btn_Parameter->setText(CHINESESTRING("参数"));
    m_btn_Parameter->setVisible(true);

    // 创建曲线按钮
    m_btn_Curve = new QPushButton(m_Up_Frame);
    m_btn_Curve->setStyleSheet("QPushButton{font-family:Microsoft YaHei; font-size:16px; color:black;}" "QPushButton{background-color:rgb(121,131,236); border-radius:5px;border-image:none;}");
    m_btn_Curve->setText(CHINESESTRING("曲线"));
    m_btn_Curve->setVisible(true);

    //创建样本采集下标按键
    m_btn_sample_collection_Details=new QPushButton(m_Up_Frame);
    m_btn_sample_collection_Details->setStyleSheet("QPushButton{background-color:transparent;border-image:none;};");
    m_btn_sample_collection_Details->setVisible(false);

    //创建元素检测下标按键
    m_btn_element_detection_Details=new QPushButton(m_Up_Frame);
    m_btn_element_detection_Details->setStyleSheet("QPushButton{background-color:transparent;border-image:none;};");
    m_btn_element_detection_Details->setVisible(false);

    m_Down_ScrollArea = new QScrollArea(m_Widget);
    m_Down_ScrollArea->setStyleSheet("background-color: transparent; border-image:none;");
    m_Down_ScrollArea->verticalScrollBar()->setStyleSheet(
        "QScrollBar:vertical{width:20px;background-color:transparent;border:none;padding-top:0px;padding-bottom:0px;}"
        "QScrollBar::handle:vertical{width:15px;background:#cccccc;height:5px;}"
        "QScrollBar::handle:vertical:hover{width:5px;background:#cccccc;height:5px;}"
        "QScrollBar::add-line:vertical{background-color:transparent;border:none;height:0px;width:5px;subcontrol-position:bottom;}"
        "QScrollBar::sub-line:vertical{background-color:transparent;border:none;height:0px;width:5px;subcontrol-position:top;}"
        "QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical{background-color: transparent;}"
    );
    m_Down_ScrollArea->setWidgetResizable(true);
    m_Down_ScrollArea->setVisible(false);
    m_Down_ScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QScroller *sc = QScroller::scroller(m_Down_ScrollArea);
    QScroller::ScrollerGestureType gesture = QScroller::TouchGesture;
    sc->grabGesture(m_Down_ScrollArea, gesture); 
    m_Down_Frame = new QWidget(m_Down_ScrollArea);
    m_Down_Frame->setStyleSheet("background-color: transparent; border-image:none;");
    m_Down_Frame->raise();
    m_Down_Frame->setVisible(false);
    m_Down_ScrollArea->setWidget(m_Down_Frame);

    /*/////////////////////曲线显示模块/////////////////////*/
    m_QwtPlot = new QwtPlot(m_Down_Frame);
    m_QwtPlot->setStyleSheet("color:black;background-color: transparent;");
    m_QwtPlot->plotLayout()->setAlignCanvasToScales(true);
	m_QwtPlot->setAxisTitle(QwtPlot::yLeft, CHINESESTRING("DN值"));
	m_QwtPlot->setAxisTitle(QwtPlot::xBottom, CHINESESTRING("波长"));

    QwtPlotCanvas *canvas=new QwtPlotCanvas(m_QwtPlot);
    canvas->setPalette(Qt::transparent);
    m_QwtPlot->setCanvas( canvas );

    QPalette pal_Qwtplot;
	QColor base_Qwtplot = QColor(Qt::transparent).dark(150);
	pal_Qwtplot.setColor(QPalette::Base, Qt::white);
	pal_Qwtplot.setColor(QPalette::Window, base_Qwtplot.dark(150));
	pal_Qwtplot.setColor(QPalette::Mid, base_Qwtplot.dark(110));
	pal_Qwtplot.setColor(QPalette::Light, base_Qwtplot.light(170));
	pal_Qwtplot.setColor(QPalette::Dark, base_Qwtplot.dark(170));
	pal_Qwtplot.setColor(QPalette::Text, base_Qwtplot.dark(200).light(800));
	pal_Qwtplot.setColor(QPalette::WindowText, base_Qwtplot.dark(200));
	m_QwtPlot->setPalette(pal_Qwtplot);
	m_QwtPlot->plotLayout()->setAlignCanvasToScales(true);
    m_QwtPlot->setAxisAutoScale(QwtPlot::yLeft,true);
    // QwtPlotPanner *panner = new QwtPlotPanner(m_QwtPlot->canvas());
	// panner->setMouseButton(Qt::LeftButton);
	// QwtPlotMagnifier* zoom = new QwtPlotMagnifier(m_QwtPlot->canvas());
	// zoom->setWheelModifiers(Qt::NoModifier);
	// zoom->setAxisEnabled(QwtPlot::xBottom, true);
	// zoom->setAxisEnabled(QwtPlot::yLeft, true);
	// // Setting Magnifier
	// QwtPlotMagnifier* zoom_x = new QwtPlotMagnifier(m_QwtPlot->canvas());
	// QwtPlotMagnifier* zoom_y = new QwtPlotMagnifier(m_QwtPlot->canvas());
	// // Shift+MouseWheel --> Magnifier x
	// zoom_x->setWheelModifiers(Qt::ShiftModifier);
	// zoom_x->setAxisEnabled(QwtPlot::xBottom, true);
	// zoom_x->setAxisEnabled(QwtPlot::yLeft, false);
	// // CTRL + MouseWheel --> Magnifier y
	// zoom_y->setWheelModifiers(Qt::ControlModifier);
	// zoom_y->setAxisEnabled(QwtPlot::xBottom, false);
	// zoom_y->setAxisEnabled(QwtPlot::yLeft, true);

    m_QwtPlotCurve_WhiteBoard = new QwtPlotCurve("标准板");
    m_QwtPlotCurve_Background = new QwtPlotCurve("暗电流");

    m_grid = new QwtPlotGrid();
    m_grid->enableX( false );//设置网格线
    m_grid->enableY( true );
    m_grid->setMajorPen( Qt::black, 0, Qt::DotLine );
    m_grid->attach(m_QwtPlot );

    m_Qwtlegend = new QwtLegend(m_QwtPlot);
    m_Qwtlegend->setDefaultItemMode( QwtLegendData::ReadOnly );//图例可被点击
    m_QwtPlot->insertLegend(m_Qwtlegend, QwtPlot::RightLegend );
    //connect( m_Qwtlegend, SIGNAL( checked( const QVariant &, bool, int ) ),SLOT( showItem( const QVariant &, bool ) ) );//点击图例操作


    m_separator=new QFrame(m_Down_ScrollArea);
    m_separator->setFrameShape(QFrame::HLine);
    m_separator->setFrameShadow(QFrame::Sunken);
    m_separator->setLineWidth(1);
    m_separator->setStyleSheet("background-color:  #cccccc;");
    m_separator->setVisible(false);

    MoveWidget();
    SignalsConnect();
    ClearDownFrame();
}

void EntryWidget::MoveWidget()
{   
    m_Widget->setGeometry(QRect(0,0,width/13*5,height/13*11));
    m_Up_Frame->setGeometry(QRect(0,0,width/13*5,height/13*2));
    m_TimeLabel->setGeometry(QRect(m_Up_Frame->width()/16*1,0,m_Up_Frame->width()/16*8,m_Up_Frame->height())); 
    m_btn_Parameter->setGeometry(QRect(m_Up_Frame->width()/16*9,(m_Up_Frame->height()/5*2)-10,m_Up_Frame->width()/16*3,m_Up_Frame->height()/5*3));
    m_btn_Curve->setGeometry(QRect(m_Up_Frame->width()/16*13-10,(m_Up_Frame->height()/5*2)-10,m_Up_Frame->width()/16*3,m_Up_Frame->height()/5*3));
  
    m_btn_sample_collection_Details->setGeometry(QRect(0,0,m_Up_Frame->width(),m_Up_Frame->height()));
    m_btn_element_detection_Details->setGeometry(QRect(0,0,m_Up_Frame->width(),m_Up_Frame->height()));
 
    m_Down_ScrollArea->setGeometry(QRect(0,m_Up_Frame->height(),width/13*5,height/13*9));
    m_Down_Frame->setGeometry(QRect(0,0,width/13*5,height/13));
    m_separator->setGeometry(QRect(m_Down_ScrollArea->width()/10/2,0,m_Down_ScrollArea->width()/10*9,1));

    this->update();
}

void EntryWidget::SignalsConnect()
{
    connect(m_btn_Parameter,SIGNAL(clicked()),this,SLOT(showDownFrame()));
    connect(m_btn_Curve,SIGNAL(clicked()),this,SLOT(showDownFrame()));
    connect(m_btn_sample_collection_Details,SIGNAL(clicked()),this,SLOT(showDownFrame()));
    connect(m_btn_element_detection_Details,SIGNAL(clicked()),this,SLOT(showDownFrame()));
}

void EntryWidget::showDownFrame()
{
        if (sender() == m_btn_Parameter)
        {
            ParameterDisplay();
        }
        else if (sender() == m_btn_Curve)
        {
            CurveDisplay();
        }
        else if (sender() == m_btn_sample_collection_Details)
        {
            SampleCollectionDetailsDisplay();
        }
        else if (sender() == m_btn_element_detection_Details)
        {
            ElementDetectionDetailsDisplay();
        }

        emit downFrameRequested(this);
    
}

void EntryWidget::ParameterDisplay()
{
    if (m_DownFrameType==DownFrame_Parameter)
    {
        ClearDownFrame();
        return;
    }
    ClearDownFrame();
    m_Down_ScrollArea->setWidgetResizable(false);
    QGridLayout* layout = new QGridLayout(m_Down_Frame);
    layout->setContentsMargins(m_Down_ScrollArea->width()/6, m_Down_ScrollArea->height()/8, m_Down_ScrollArea->width()/6, m_Down_ScrollArea->height()/8 );

    // 显示详细参数
    QStringList labels = { CHINESESTRING("参数a"), CHINESESTRING("参数b"), CHINESESTRING("参数c"), CHINESESTRING("波段像素"), CHINESESTRING("FWHM"), CHINESESTRING("增益"), CHINESESTRING("积分"), CHINESESTRING("偏压") };
    QStringList values = {calibrate_dataValue.device_calibrate_parameter.parama, calibrate_dataValue.device_calibrate_parameter.paramb, calibrate_dataValue.device_calibrate_parameter.paramc,
                        calibrate_dataValue.device_calibrate_parameter.pixel_begin + "-" + calibrate_dataValue.device_calibrate_parameter.pixel_end, calibrate_dataValue.device_calibrate_parameter.fwhm, 
                        calibrate_dataValue.spectral_parameter.data_value_gain,calibrate_dataValue.spectral_parameter.visible_light_integral, calibrate_dataValue.spectral_parameter.power_supply_bias };

    for (int i = 0; i < labels.size(); ++i) {
        QLabel* label = new QLabel(labels[i], m_Down_Frame);
        QLabel* value = new QLabel(values[i], m_Down_Frame);
        label->setStyleSheet("QLabel { font-family:Microsoft YaHei; font-size:20px; color:black; background-color:transparent;}" "QLabel{border-image:none;}");
        value->setStyleSheet("QLabel { font-family:Microsoft YaHei; font-size:20px; color:black; background-color:transparent;}" "QLabel{border-image:none;}");
                        
        label->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
        value->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
                    
        layout->addWidget(label, i, 0);
        layout->addWidget(value, i, 1);
    }
    m_Down_Frame->setLayout(layout);
    m_Down_ScrollArea->setVisible(true);
    m_Down_Frame->setVisible(true);
    m_DownFrameType=DownFrame_Parameter;
    int spacing = layout->verticalSpacing();


    m_separator->setVisible(true);
    m_Up_Frame->setStyleSheet("background-color: transparent; border-image: none;");
    m_Widget->setStyleSheet("background-color:transparent; border-image:url(:/image/image/entry_down.png);");
}

void EntryWidget::CurveDisplay()
{

    if (m_DownFrameType==DownFrame_Curve) 
    {
        ClearDownFrame();
        return;
    }

    ClearDownFrame();

    m_Down_ScrollArea->setWidgetResizable(false);
    m_QwtPlot->setVisible(true);
    //  /*/////////////////////曲线显示模块/////////////////////*/
    // QwtPlot *Plot = new QwtPlot(m_Down_Frame);
    // Plot->setStyleSheet("color:black;");
    // Plot->plotLayout()->setAlignCanvasToScales(true);
	// Plot->setAxisTitle(QwtPlot::yLeft, CHINESESTRING("DN值"));
	// Plot->setAxisTitle(QwtPlot::xBottom, CHINESESTRING("波长"));

    // QwtPlotCanvas *canvas=new QwtPlotCanvas(Plot);
    // canvas->setPalette(Qt::transparent);
    // Plot->setCanvas( canvas );

    // QPalette pal_Qwtplot;
	// QColor base_Qwtplot = QColor(Qt::white).dark(150);
	// pal_Qwtplot.setColor(QPalette::Base, Qt::white);
	// pal_Qwtplot.setColor(QPalette::Window, base_Qwtplot.dark(150));
	// pal_Qwtplot.setColor(QPalette::Mid, base_Qwtplot.dark(110));
	// pal_Qwtplot.setColor(QPalette::Light, base_Qwtplot.light(170));
	// pal_Qwtplot.setColor(QPalette::Dark, base_Qwtplot.dark(170));
	// pal_Qwtplot.setColor(QPalette::Text, base_Qwtplot.dark(200).light(800));
	// pal_Qwtplot.setColor(QPalette::WindowText, base_Qwtplot.dark(200));
	// Plot->setPalette(pal_Qwtplot);
	// Plot->plotLayout()->setAlignCanvasToScales(true);
    // Plot->setAxisAutoScale(QwtPlot::yLeft,true);
    // // QwtPlotPanner *panner = new QwtPlotPanner(Plot->canvas());
	// // panner->setMouseButton(Qt::LeftButton);
	// // QwtPlotMagnifier* zoom = new QwtPlotMagnifier(Plot->canvas());
	// // zoom->setWheelModifiers(Qt::NoModifier);
	// // zoom->setAxisEnabled(QwtPlot::xBottom, true);
	// // zoom->setAxisEnabled(QwtPlot::yLeft, true);
	// // // Setting Magnifier
	// // QwtPlotMagnifier* zoom_x = new QwtPlotMagnifier(Plot->canvas());
	// // QwtPlotMagnifier* zoom_y = new QwtPlotMagnifier(Plot->canvas());
	// // // Shift+MouseWheel --> Magnifier x
	// // zoom_x->setWheelModifiers(Qt::ShiftModifier);
	// // zoom_x->setAxisEnabled(QwtPlot::xBottom, true);
	// // zoom_x->setAxisEnabled(QwtPlot::yLeft, false);
	// // // CTRL + MouseWheel --> Magnifier y
	// // zoom_y->setWheelModifiers(Qt::ControlModifier);
	// // zoom_y->setAxisEnabled(QwtPlot::xBottom, false);
	// // zoom_y->setAxisEnabled(QwtPlot::yLeft, true);

    // QwtPlotCurve *QwtPlotCurve_WhiteBoard = new QwtPlotCurve();
    // QwtPlotCurve *QwtPlotCurve_Background = new QwtPlotCurve();

    // QwtPlotGrid *grid = new QwtPlotGrid();
    // grid->enableX( false );//设置网格线
    // grid->enableY( true );
    // grid->setMajorPen( Qt::black, 0, Qt::DotLine );
    // grid->attach(Plot );

    // QwtLegend *legend = new QwtLegend();
    // legend->setDefaultItemMode( QwtLegendData::Checkable );//图例可被点击
    // Plot->insertLegend( legend, QwtPlot::TopLegend );
    // connect( legend, SIGNAL( checked( const QVariant &, bool, int ) ),SLOT( showItem( const QVariant &, bool ) ) );//点击图例操作
    
    QPen pen_whiteBoard;
    pen_whiteBoard.setColor(QColor(255,112, 64));
    pen_whiteBoard.setWidth(2);
    QPen pen_background;
    pen_background.setColor(QColor(86, 160, 31));
    pen_background.setWidth(2);

    //----------------设置栅格线-------------------//

    m_QwtPlotCurve_WhiteBoard->setPen(pen_whiteBoard);
    m_QwtPlotCurve_Background->setPen(pen_background);
            
    m_QwtPlotCurve_WhiteBoard->setStyle(QwtPlotCurve::Lines);									//画线
    m_QwtPlotCurve_WhiteBoard->setRenderHint(QwtPlotItem::RenderAntialiased, true);		//线条光滑化 

    m_QwtPlotCurve_Background->setStyle(QwtPlotCurve::Lines);									//画线
    m_QwtPlotCurve_Background->setRenderHint(QwtPlotItem::RenderAntialiased, true);		//线条光滑化 
    
    QVector<double> x(calibrate_dataValue.wavelengths.size());
    std::copy(calibrate_dataValue.wavelengths.begin(), calibrate_dataValue.wavelengths.end(), x.begin());
                    
    QVector<double> yWhiteboard(calibrate_dataValue.bzbData.size());
    std::transform(calibrate_dataValue.bzbData.begin(), calibrate_dataValue.bzbData.end(), yWhiteboard.begin(), [](int val) { return static_cast<double>(val); });
    QVector<double> yBackground(calibrate_dataValue.adlData.size());
    std::transform(calibrate_dataValue.adlData.begin(), calibrate_dataValue.adlData.end(), yBackground.begin(), [](int val) { return static_cast<double>(val); });

    double minX = *std::min_element(x.begin(), x.end());
    double maxX = *std::max_element(x.begin(), x.end());
    double minY = std::min(*std::min_element(yWhiteboard.begin(), yWhiteboard.end()), *std::min_element(yBackground.begin(), yBackground.end()));
    double maxY = std::max(*std::max_element(yWhiteboard.begin(), yWhiteboard.end()), *std::max_element(yBackground.begin(), yBackground.end()));

    m_QwtPlot->setAxisScale(QwtPlot::yLeft, minY, maxY + (maxY - minY)*0.25);
    m_QwtPlot->setAxisScale(QwtPlot::xBottom, minX, maxX);

    QPolygonF ptsWhiteboard;
    for (int i = 0; i < yWhiteboard.size(); i++)
    {
        ptsWhiteboard.append(QPointF(calibrate_dataValue.wavelengths[i], yWhiteboard[i]));
    }

    QPolygonF ptsBackground;
    for (int i = 0; i < yBackground.size(); i++)
    {
        ptsBackground.append(QPointF(calibrate_dataValue.wavelengths[i], yBackground[i]));
    }


    m_QwtPlotCurve_Background->setSamples(ptsBackground);
    m_QwtPlotCurve_Background->attach(m_QwtPlot);

    m_QwtPlotCurve_WhiteBoard->setSamples(ptsWhiteboard);
    m_QwtPlotCurve_WhiteBoard->attach(m_QwtPlot);

    m_QwtPlotCurve_Background->setLegendAttribute(m_QwtPlotCurve_Background->LegendShowLine);
    m_QwtPlotCurve_WhiteBoard->setLegendAttribute(m_QwtPlotCurve_WhiteBoard->LegendShowLine);
    // // //--------------设置图例可以被点击来确定是否显示曲线-----------------------//
    QwtPlotItemList items = m_QwtPlot->itemList( QwtPlotItem::Rtti_PlotCurve );
    for ( int i = 0; i < items.size(); i++ )
    {
        const QVariant itemInfo =m_QwtPlot->itemToInfo( items[i] );    
        QwtLegendLabel *legendLabel = qobject_cast<QwtLegendLabel *>( m_Qwtlegend->legendWidget( itemInfo ) );
        // if ( legendLabel )
        //     legendLabel->setChecked( true );//
        items[i]->setVisible( true );
    }
    
    m_Qwtlegend->update();
    m_QwtPlot->repaint();
    m_QwtPlot->replot();
    m_QwtPlot->setAutoReplot(true);
    m_QwtPlot->setGeometry(QRect(m_Down_Frame->width()/18, m_Down_Frame->height()/10*0.5, m_Down_Frame->width()/18*16, m_Down_Frame->height()/10*9));
    //m_Qwtlegend->setGeometry(QRect(m_Down_Frame->width()/4, m_Down_Frame->height()/10*3 , m_Down_Frame->width()*6/8, m_Down_Frame->height()/12));
    m_Down_ScrollArea->setVisible(true);
    m_Down_Frame->setVisible(true);
    m_DownFrameType=DownFrame_Curve;

    m_separator->setVisible(true);
    m_Up_Frame->setStyleSheet("background-color: transparent; border-image: none;");
    m_Widget->setStyleSheet("background-color:transparent; border-image:url(:/image/image/entry_down.png);");
}

void EntryWidget::SampleCollectionDetailsDisplay()
{
    if (m_DownFrameType==DownFrame_SampleCollection_Details)
    {
        ClearDownFrame();
        return;
    }
    ClearDownFrame();
    QGridLayout* layout = new QGridLayout(m_Down_Frame);
    layout->setContentsMargins(m_Down_ScrollArea->width()/13*2, m_Down_ScrollArea->height()/13, m_Down_ScrollArea->width()/13*2, m_Down_ScrollArea->height()/13 );
    layout->setVerticalSpacing(m_Down_ScrollArea->height()/13);
    layout->setAlignment(Qt::AlignTop);

     // 显示指标数据
    QStringList labels;
    QStringList values;

    for (int i = 0; i < sample_collection_dataValue.index_data.size(); i++) {
        // 从 `index_data` 获取参数信息
        // QString paramKeyName = sample_collection_dataValue.index_data[i].param_key + " \t(" + sample_collection_dataValue.index_data[i].param_name + ")";
        QString paramKeyName = sample_collection_dataValue.index_data[i].param_name;
        //QString paramValue = sample_collection_dataValue.index_data[i].param_value + CHINESESTRING("ppm");
        QString paramValue = sample_collection_dataValue.index_data[i].param_value + sample_collection_dataValue.index_data[i].unit;
        
        labels.append(paramKeyName);
        values.append(paramValue);
    }

    for (int i = 0; i < labels.size(); i++) {
        QLabel* keyLabel = new QLabel(labels[i], m_Down_Frame);
        QLabel* valueLabel = new QLabel(values[i], m_Down_Frame);

        keyLabel->setStyleSheet("QLabel { font-family:Microsoft YaHei; font-size:20px; color:black; background-color:transparent;}" "QLabel{border-image:none;}");
        valueLabel->setStyleSheet("QLabel { font-family:Microsoft YaHei; font-size:20px; color:black; background-color:transparent;}" "QLabel{border-image:none;}");
                            
        keyLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
        valueLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);

        layout->addWidget(keyLabel, i, 0);
        layout->addWidget(valueLabel, i, 1);
    }


    m_Down_Frame->setLayout(layout);
    m_Down_ScrollArea->setVisible(true);
    m_Down_Frame->setVisible(true);
    m_DownFrameType=DownFrame_SampleCollection_Details;

    m_separator->setVisible(true);
    m_Up_Frame->setStyleSheet("background-color: transparent; border-image: none;");
    m_Widget->setStyleSheet("background-color:transparent; border-image:url(:/image/image/entry_down.png);");
}

void EntryWidget::ElementDetectionDetailsDisplay()
{
    if (m_DownFrameType==DownFrame_ElementDetection_Details)
    {
        ClearDownFrame();
        return;
    }    
    ClearDownFrame();
    QGridLayout* layout = new QGridLayout(m_Down_Frame);
    layout->setContentsMargins(m_Down_ScrollArea->width()/13*2, m_Down_ScrollArea->height()/13, m_Down_ScrollArea->width()/13*2, m_Down_ScrollArea->height()/13 );
    layout->setVerticalSpacing(m_Down_ScrollArea->height()/13);
    layout->setAlignment(Qt::AlignTop);
    
    QStringList labels;
    QStringList values;

    for (int i = 0; i < element_detection_dataValue.index_data.size(); i++) {
        // 从 `index_data` 获取参数信息
        // QString paramKeyName = element_detection_dataValue.index_data[i].param_key + " \t(" + element_detection_dataValue.index_data[i].param_name + ")";
        QString paramKeyName = element_detection_dataValue.index_data[i].param_name;
        //QString paramValue = element_detection_dataValue.index_data[i].param_value + CHINESESTRING("ppm");
        QString paramValue = element_detection_dataValue.index_data[i].param_value + element_detection_dataValue.index_data[i].unit;

        labels.append(paramKeyName);
        values.append(paramValue);
    }

    for (int i = 0; i < labels.size(); i++) {
        QLabel* keyLabel = new QLabel(labels[i], m_Down_Frame);
        QLabel* valueLabel = new QLabel(values[i], m_Down_Frame);

        keyLabel->setStyleSheet("QLabel { font-family:Microsoft YaHei; font-size:20px; color:black; background-color:transparent;}" "QLabel{border-image:none;}");
        valueLabel->setStyleSheet("QLabel { font-family:Microsoft YaHei; font-size:20px; color:black; background-color:transparent;}" "QLabel{border-image:none;}");
        keyLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
        valueLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);

        layout->addWidget(keyLabel, i, 0);
        layout->addWidget(valueLabel, i, 1);
    }
    
    // m_btn_element_detection_Details->setStyleSheet("QPushButton{border-image:url(:/image/image/up_arrow.png);background-color:transparent};");

    m_Down_Frame->setLayout(layout);
    m_Down_ScrollArea->setVisible(true);
    m_Down_Frame->setVisible(true);
    m_DownFrameType=DownFrame_ElementDetection_Details;

    m_separator->setVisible(true);
    m_Up_Frame->setStyleSheet("background-color: transparent; border-image: none;");
    m_Widget->setStyleSheet("background-color:transparent; border-image:url(:/image/image/entry_down.png);");

}

// 样本采集对应的entry条目布局显示
void EntryWidget::SampleCollection_EntryWidget_Showed()
{
    m_DataType=SampleCollectionData;

    m_Up_Frame->setGeometry(QRect(0,0,width/13*5,height/13*3));

    m_OIL_Label->setGeometry(QRect(m_Up_Frame->width()/16*1,m_Up_Frame->height()/7*1,m_Up_Frame->width()/16*15,m_Up_Frame->height()/5*2));
    m_OIL_Label->setVisible(true);

    m_TimeLabel->setGeometry(QRect(m_Up_Frame->width()/16*1,m_OIL_Label->height()+10,m_Up_Frame->width()/16*15,m_Up_Frame->height()/5*2)); 
    m_TimeLabel->setStyleSheet("QLabel { font-family:Source Han Sans CN; font-size:24px; font-weight: Regular; color: #333333; background-color:transparent;}" "QLabel{border-image:none;}");
    m_Down_ScrollArea->setGeometry(QRect(0,m_Up_Frame->height(),width/13*5,height/13*8));
    m_Down_Frame->setGeometry(QRect(0,0,width/13*5,height/13*8));

    m_btn_sample_collection_Details->setGeometry(QRect(0,0,m_Up_Frame->width(),m_Up_Frame->height()));

    m_btn_Parameter->setVisible(false);
    m_btn_Curve->setVisible(false);
    m_btn_sample_collection_Details->setVisible(true);
    m_btn_element_detection_Details->setVisible(false);
}

// 元素检测对应的entry条目布局显示
void EntryWidget::ElementDetection_Entrywidget_Showed()
{
    m_DataType=ElementDetectionData;

    m_Up_Frame->setGeometry(QRect(0,0,width/13*5,height/13*3));

    m_OIL_Label->setGeometry(QRect(m_Up_Frame->width()/16*1,m_Up_Frame->height()/7*1,m_Up_Frame->width()/16*15,m_Up_Frame->height()/5*2));
    m_OIL_Label->setVisible(true);

    m_TimeLabel->setGeometry(QRect(m_Up_Frame->width()/16*1,m_OIL_Label->height()+10,m_Up_Frame->width()/16*15,m_Up_Frame->height()/5*2)); 
    m_TimeLabel->setStyleSheet("QLabel { font-family:Source Han Sans CN; font-size:24px; font-weight: Regular; color: #333333; background-color:transparent;}" "QLabel{border-image:none;}");
    m_Down_ScrollArea->setGeometry(QRect(0,m_Up_Frame->height(),width/13*5,height/13*8));
    m_Down_Frame->setGeometry(QRect(0,0,width/13*5,height/13*8));

    m_btn_element_detection_Details->setGeometry(QRect(0,0,m_Up_Frame->width(),m_Up_Frame->height()));

    m_btn_Parameter->setVisible(false);
    m_btn_Curve->setVisible(false);
    m_btn_sample_collection_Details->setVisible(false);
    m_btn_element_detection_Details->setVisible(true);
}

//清楚downframe页面布局和释放资源
void EntryWidget::ClearDownFrame()
{
    QLayout *layout = m_Down_Frame->layout();  
    if (layout) {
        QLayoutItem *child;
        while ((child = layout->takeAt(0)) != nullptr) {
            if (child->widget()) {
                delete child->widget();
            }
            delete child;
        }
        delete layout;
    }

    m_QwtPlot->setVisible(false);

    m_Down_Frame->setVisible(false);

    m_separator->setVisible(false);
    m_DownFrameType=DownFrame_None;

    

    m_Up_Frame->setStyleSheet("border-image: url(:/image/image/entry_up.png);");
    m_Widget->setStyleSheet("background:transparent; border-image:none;");

    m_Down_ScrollArea->setWidgetResizable(true);
}

//点击图例，显示相应的曲线
void EntryWidget::showItem(const QVariant &itemInfo, bool on)
{
    QwtPlotItem *plotItem =m_QwtPlot->infoToItem( itemInfo );
    if ( plotItem )
        plotItem->setVisible( on );
    m_QwtPlot->setAxisAutoScale(QwtPlot::yLeft,true);
    m_QwtPlot->replot();
}