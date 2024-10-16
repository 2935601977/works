#include "Pg_SDC_GUI_DataManagementWidget.h"
#include "Pg_SDC_GUI_MainWidget.h"
#include "Pg_SDC_GUI_Message.h"
#include <algorithm>
#include "Pg_SDC_GUI_EntryWidget.h"
#include <QScroller>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include "qwt_legend.h"
#include "qwt_scale_draw.h"
#include <QMovie>
#include "xlsxdocument.h"

QDMWidget::QDMWidget(QWidget *parent) :
    QWidget(parent),
    m_Entrys(),
    m_currentActiveEntry(nullptr),      
    m_parent_MainWidget(nullptr)                                     
    
{

    this->setAutoFillBackground(true);
    this->resize(1024,680);
    this->setWindowFlags(Qt::FramelessWindowHint/* | Qt::WindowStaysOnTopHint*/);
    this->setAttribute(Qt::WA_QuitOnClose, true);
    this->setStyleSheet("QWidget { background:rgb(237, 237, 237); }");

    m_Btn_Homepage = new QPushButton(this);
    //m_Btn_Homepage->setStyleSheet("QPushButton{font-family:Microsoft YaHei;font-size:30px;color:black} QPushButton{background-color:transparent;border-image:url(:/image/image/allbutton.png)}""QPushButton:hover{font:bold;font-size:30px;color:white;background-color:transparent;border-image:url(:/image/image/allpress.png)}""QPushButton:pressed{font:bold;font-size:30px;color:white;background-color:transparent;border-image:url(:/image/image/allpress.png)}");
    m_Btn_Homepage->setStyleSheet("QPushButton{font-family:Microsoft YaHei;font-size:30px;color:black} QPushButton{background-color:transparent;border-image:url(:/image/image/allbutton.png)}");
    m_Btn_Homepage->setGeometry(QRect(this->width()/6*5+30, (this->height()-90)/7*6+60, (this->width()-60)/6, (this->height()-90)/7  ));
    m_Btn_Homepage->setText(CHINESESTRING("首页"));

    m_Btn_Return= new QPushButton(this);
    //m_Btn_Return->setStyleSheet("QPushButton{font-family:Microsoft YaHei;font-size:30px;color:black} QPushButton{background-color:transparent;border-image:url(:/image/image/allbutton.png)}""QPushButton:hover{font:bold;font-size:30px;color:white;background-color:transparent;border-image:url(:/image/image/allpress.png)}""QPushButton:pressed{font:bold;font-size:30px;color:white;background-color:transparent;border-image:url(:/image/image/allpress.png)}");
    m_Btn_Return->setStyleSheet("QPushButton{font-family:Microsoft YaHei;font-size:30px;color:black} QPushButton{background-color:transparent;border-image:url(:/image/image/allbutton.png)}");
    m_Btn_Return->setGeometry(QRect(30, (this->height()-90)/7*6+60, (this->width()-60)/6, (this->height()-90)/7  ));
    m_Btn_Return->setText(CHINESESTRING("返回"));
    m_Btn_Return->setVisible(false);

    m_QScrA_FunctionFrame=new QScrollArea(this);
    m_QScrA_FunctionFrame->setGeometry(QRect(30,  30, this->width()-60, (this->height()-90)/7*6 ));
    m_QScrA_FunctionFrame->setStyleSheet("QScrollArea {background-color:white;border-radius:15px;padding:15px 0 15px 0px;}");

    m_QScrA_FunctionFrame->verticalScrollBar()->setStyleSheet(
        "QScrollBar:vertical{width:25px;background-color:white;border:none;padding-top:0px;padding-bottom:0px;}"
        "QScrollBar::handle:vertical{width:25px;background:rgba(69, 178, 255,100%);border-radius:4px;height:5px;}"
        "QScrollBar::handle:vertical:hover{width:25px;background:rgba(69, 178, 255,100%);border-radius:4px;height:5px;}"
        "QScrollBar::add-line:vertical{background-color:white;border:none;height:0px;width:25px;subcontrol-position:bottom;}"
        "QScrollBar::sub-line:vertical{background-color:white;border:none;height:0px;width:25px;subcontrol-position:top;}"
        "QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical{background-color: white;}"
    );
    m_QScrA_FunctionFrame->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QScroller *sc = QScroller::scroller(m_QScrA_FunctionFrame);
    QScroller::ScrollerGestureType gesture = QScroller::TouchGesture;
    sc->grabGesture(m_QScrA_FunctionFrame, gesture); 

    m_ResultFrame=new QWidget(m_QScrA_FunctionFrame);
    m_ResultFrame->setStyleSheet("QWidget {background-color:white;border-radius:15px;border: none;}");
    m_QScrA_FunctionFrame->setWidget(m_ResultFrame);
    m_QScrA_FunctionFrame->setWidgetResizable(true);  

    m_Lab_Tip=new QLabel(m_QScrA_FunctionFrame);
    m_Lab_Tip->setStyleSheet("QLabel{font-family:Microsoft YaHei;font-size:30px;color:rgb(0,0,0)} QLabel{background-color:transparent}");
    m_Lab_Tip->setAlignment(Qt::AlignCenter);
    m_Lab_Tip->setVisible(false);
    m_Lab_Tip->setText(CHINESESTRING("请选择筛选条件后查询"));

    m_RunLabel=new QLabel(m_ResultFrame);
    m_RunLabel->setStyleSheet("QLabel{font-family:Microsoft YaHei;font-size:30px;color:rgb(0,0,0)} QLabel{background-color:transparent}");
    m_RunLabel->setAlignment(Qt::AlignCenter);
    m_RunLabel->setVisible(false);
    m_RunLabel->setText(CHINESESTRING("查询中"));

    m_LabelGif = new QLabel(m_ResultFrame);
    m_LabelGif->setStyleSheet("QLabel{{background-repeat:no-repeat;background-position:center;background-origin:border;background-image: url(:/img/bg0.png);}");
    m_LabelGif->setVisible(false);
    QMovie *gif = new QMovie(":/image/image/loading.gif");
    //gif->setScaledSize(m_LabelGif->size());
    m_LabelGif->setMovie(gif);
    gif->start();

    m_DataManaFlag = 0;
    MoveWidget();
    
    QkeyTools::getInstance()/*->Init(QkeyTools::BOTTOM, QkeyTools::GRAY, 10, 10)*/;


   // installEventFilter(this);                                                // 为 DownFrame 添加事件过滤器，在析构函数中移除

}

QDMWidget::~QDMWidget()
{   
    
}

void QDMWidget::MoveWidget()
{
    m_Btn_Return->setGeometry(QRect(30,  (this->height()-90)/7*6+60, (this->width()-60)/6, (this->height()-90)/7  ));
    m_Btn_Homepage->setGeometry(QRect((this->width()-60)/6*5+30,  (this->height()-90)/7*6+60, (this->width()-60)/6, (this->height()-90)/7  ));
    m_QScrA_FunctionFrame->setGeometry(QRect(30,  30, this->width()-60, (this->height()-90)/7*6 )); 
    m_Lab_Tip->setGeometry(QRect(m_QScrA_FunctionFrame->width()/2-m_Lab_Tip->width()/2,  m_QScrA_FunctionFrame->height()/2-m_Lab_Tip->height()/2, m_QScrA_FunctionFrame->width()/2,m_QScrA_FunctionFrame->height()/2));   
    m_RunLabel->setGeometry(QRect(m_QScrA_FunctionFrame->width()/2-m_Lab_Tip->width()/2,  m_QScrA_FunctionFrame->height()/2-m_Lab_Tip->height()/2, m_QScrA_FunctionFrame->width()/2,m_QScrA_FunctionFrame->height()/2));   
    m_LabelGif->setGeometry(QRect(m_QScrA_FunctionFrame->width()/2-m_Lab_Tip->width()/2,  m_QScrA_FunctionFrame->height()/2+m_Lab_Tip->height()/2+10, m_QScrA_FunctionFrame->width()/2,m_QScrA_FunctionFrame->height()/2));   
    this->update();
}

void QDMWidget::Initialize()
{
    m_DataManaFlag = 0;
    ClearEntrys();
}

// 数据查询函数
void QDMWidget::DateQuery(QMainWidget* mainWidget)
{
    m_Lab_Tip->setVisible(false);
    m_RunLabel->setVisible(true);
    m_LabelGif->setVisible(true);
    m_parent_MainWidget=mainWidget;
    connect(m_parent_MainWidget->m_Left_Frame->m_Leftframe_OilTypeComboBox,&QComboBox::currentTextChanged,this,[=](){
        ClearEntrys();
        m_parent_MainWidget->m_Left_Frame->m_Leftframe_btn_DataExport->setVisible(false);
    },Qt::UniqueConnection);                                                    // 确保槽函数只连接一次
    
    ClearEntrys();
  
    m_parent_MainWidget->m_Database->ConnectDB();                               // 连接数据库

    // 获取日期范围和数据来源(设备校准或样本采集或元素检测)
    QString startDateTimeStr=m_parent_MainWidget->m_Left_Frame->m_Leftframe_StartDate->date().toString("yyyyMMdd") + "000000000";
    QString endDateTimeStr=m_parent_MainWidget->m_Left_Frame->m_Leftframe_EndDate->date().toString("yyyyMMdd") + "235959999";
    QString DateSource=m_parent_MainWidget->m_Left_Frame->m_Leftframe_DataSourceCombox->currentText();

    QSize entryInSize(m_QScrA_FunctionFrame->size());
    // 设备校准数据查询
    if(DateSource==CHINESESTRING("设备校准"))
    {
        // m_parent_MainWidget->m_Database->Calibrate_DateQuery(startDateTimeStr,endDateTimeStr);
        QVector<CLIENTCALIBRATEDATA> data = m_parent_MainWidget->m_Database->Calibrate_DateQuery(startDateTimeStr, endDateTimeStr);
        qDeleteAll(m_Entrys);
        m_Entrys.clear();
        for (const CLIENTCALIBRATEDATA& dataEntry : data)
        {
            EntryWidget* entry = new EntryWidget(m_ResultFrame, entryInSize);
            entry->calibrate_dataValue = dataEntry;
            entry->m_TimeLabel->setText(QDateTime::fromString(entry->calibrate_dataValue.save_time, "yyyyMMddhhmmsszzz").toString("yyyy-MM-dd hh:mm:ss"));
            entry->m_DataType = CalibrationData;
            m_Entrys.push_back(entry);

        }

        // 对 m_Entrys 进行排序
        std::sort(m_Entrys.begin(), m_Entrys.end(), [](EntryWidget* a, EntryWidget* b) {
            QDateTime timeA = QDateTime::fromString(a->calibrate_dataValue.save_time, "yyyyMMddhhmmsszzz");
            QDateTime timeB = QDateTime::fromString(b->calibrate_dataValue.save_time, "yyyyMMddhhmmsszzz");
            return timeA < timeB;
        });  
    }

    // 样本采集数据查询
    else if(DateSource==CHINESESTRING("样本采集"))
    {
        QString oilType=m_parent_MainWidget->m_Left_Frame->m_Leftframe_OilTypeComboBox->currentText();
        QVector<SAMPLECOLLECTION> data=m_parent_MainWidget->m_Database->Sample_DateQuery(startDateTimeStr,endDateTimeStr,oilType);
        qDeleteAll(m_Entrys);
        m_Entrys.clear();
        for (const SAMPLECOLLECTION& dataEntry : data)
        {
            EntryWidget* entry = new EntryWidget(m_ResultFrame, entryInSize);
            entry->sample_collection_dataValue = dataEntry;
            entry->m_TimeLabel->setText(QDateTime::fromString(entry->sample_collection_dataValue.save_time, "yyyyMMddhhmmsszzz").toString("yyyy-MM-dd hh:mm:ss"));
            entry->m_OIL_Label->setText(oilType + CHINESESTRING("润滑油-")+ entry->sample_collection_dataValue.oilNumber);
            entry->SampleCollection_EntryWidget_Showed();
            m_Entrys.push_back(entry);
        }
        
        std::sort(m_Entrys.begin(), m_Entrys.end(), [](EntryWidget* a, EntryWidget* b) {
            QDateTime timeA = QDateTime::fromString(a->sample_collection_dataValue.save_time, "yyyyMMddhhmmsszzz");
            QDateTime timeB = QDateTime::fromString(b->sample_collection_dataValue.save_time, "yyyyMMddhhmmsszzz");
            return timeA < timeB;
        });
    }

    // 元素检测数据查询
    else if(DateSource==CHINESESTRING("元素检测"))
    {
        QString oilType=m_parent_MainWidget->m_Left_Frame->m_Leftframe_OilTypeComboBox->currentText();
        QVector<ELEMENTDETECTION> data=m_parent_MainWidget->m_Database->Element_DateQuery(startDateTimeStr,endDateTimeStr,oilType);
        qDeleteAll(m_Entrys);
        m_Entrys.clear();
        for (const ELEMENTDETECTION& dataEntry : data)
        {
            EntryWidget* entry = new EntryWidget(m_ResultFrame,entryInSize);
            entry->element_detection_dataValue = dataEntry;
            entry->m_TimeLabel->setText(QDateTime::fromString(entry->element_detection_dataValue.save_time, "yyyyMMddhhmmsszzz").toString("yyyy-MM-dd hh:mm:ss"));
            entry->m_OIL_Label->setText(oilType + CHINESESTRING("润滑油-")+ entry->element_detection_dataValue.oilNumber);
            entry->ElementDetection_Entrywidget_Showed();
            m_Entrys.push_back(entry);
        }
        // 对 m_Entrys 进行排序
        std::sort(m_Entrys.begin(), m_Entrys.end(), [](EntryWidget* a, EntryWidget* b) {
            QDateTime timeA = QDateTime::fromString(a->element_detection_dataValue.save_time, "yyyyMMddhhmmsszzz");
            QDateTime timeB = QDateTime::fromString(b->element_detection_dataValue.save_time, "yyyyMMddhhmmsszzz");
            return timeA < timeB;
        });

    }

    for (int i = 0; i < m_Entrys.size(); i++)
    {
        m_Entrys[i]->setVisible(true);
        m_Entrys[i]->raise();
        connect(m_Entrys[i], &EntryWidget::downFrameRequested, this, &QDMWidget::handleDownFrameRequested,Qt::DirectConnection);
    }
    

    InitialLayoutEntrys();
}

//数据导出到excel保存
void QDMWidget::DateExport()
{
    //没用数据则不会导出
    if (m_Entrys.isEmpty()) {
        return;
    }
    QString startDate=m_parent_MainWidget->m_Left_Frame->m_Leftframe_StartDate->date().toString("yyyyMMdd") ;
    QString endDate=m_parent_MainWidget->m_Left_Frame->m_Leftframe_EndDate->date().toString("yyyyMMdd");
    QString DateSource=m_parent_MainWidget->m_Left_Frame->m_Leftframe_DataSourceCombox->currentText();

    // 通过判断第一个元素的数据类型得知当前要保存的数据类型(设备校准、样本采集或元素检测数据)
    if(m_Entrys[0]->m_DataType==CalibrationData)
    {

        // QString filePath;
        // do {
        //     filePath = QFileDialog::getSaveFileName(nullptr, CHINESESTRING("数据导出"), "", CHINESESTRING("Excel Files (*.xlsx)"));
        //     if (filePath.isEmpty()) {
        //         // 用户点击取消或关闭对话框时退出
        //         return;
        //     }
            
        //     if (!filePath.endsWith(".xlsx")) {
        //         // 如果文件名不符合要求，可以提示用户并重新打开对话框
        //         filePath.clear();
        //     }
        // } while (filePath.isEmpty() || !filePath.endsWith(".xlsx"));

        QkeyTools::getInstance()->show();
        QString filePath = QFileDialog::getSaveFileName(nullptr, CHINESESTRING("Save File"), "", ("Excel Files (*.xlsx)"));
        QkeyTools::getInstance()->hide();
        
        if (filePath.isEmpty()) {
            return;
        }


        QXlsx::Document xlsx;
         // 写入表头
        xlsx.write("A1", CHINESESTRING("ID"));
        xlsx.write("B1", CHINESESTRING("校准时间"));
        xlsx.write("C1", CHINESESTRING("参数a"));
        xlsx.write("D1", CHINESESTRING("参数b"));
        xlsx.write("E1", CHINESESTRING("参数c"));
        xlsx.write("F1", CHINESESTRING("FWHM"));
        xlsx.write("G1", CHINESESTRING("波段像素"));
        xlsx.write("H1", CHINESESTRING("积分"));
        xlsx.write("I1", CHINESESTRING("增益"));
        xlsx.write("J1", CHINESESTRING("偏压"));
        xlsx.write("K1", CHINESESTRING("标准版电流"));
        xlsx.write("L1", CHINESESTRING("暗电流"));

        int row=2;
        for (EntryWidget* entry : m_Entrys) {
            const auto& data = entry->calibrate_dataValue;
            // 写入每行数据
            xlsx.write("A" + QString::number(row), data.id);
            xlsx.write("B" + QString::number(row), QDateTime::fromString(data.save_time, "yyyyMMddhhmmsszzz").toString("yyyy-MM-dd hh:mm:ss"));
            xlsx.write("C" + QString::number(row), data.device_calibrate_parameter.parama);
            xlsx.write("D" + QString::number(row), data.device_calibrate_parameter.paramb);
            xlsx.write("E" + QString::number(row), data.device_calibrate_parameter.paramc);
            xlsx.write("F" + QString::number(row), data.device_calibrate_parameter.fwhm);
            xlsx.write("G" + QString::number(row), data.device_calibrate_parameter.pixel_begin+CHINESESTRING("-")+data.device_calibrate_parameter.pixel_end);
            xlsx.write("H" + QString::number(row), data.spectral_parameter.data_value_gain);
            xlsx.write("I" + QString::number(row), data.spectral_parameter.visible_light_integral);
            xlsx.write("J" + QString::number(row), data.spectral_parameter.power_supply_bias);

            // 将adlData集合转换为字符串表示，使用逗号分隔数值
            QString bzbDatas = QString::fromStdString(std::accumulate(data.bzbData.begin(), data.bzbData.end(), std::string(), [](const std::string& a, int b) {
                return a + (a.length() > 0 ? "," : "") + std::to_string(b);
            }));
            xlsx.write("K" + QString::number(row), bzbDatas);

            QString adlDatas = QString::fromStdString(std::accumulate(data.adlData.begin(), data.adlData.end(), std::string(), [](const std::string& a, int b) {
                return a + (a.length() > 0 ? "," : "") + std::to_string(b);
            }));
            xlsx.write("L" + QString::number(row), adlDatas);

            row++;        
        }
        xlsx.selectSheet("Sheet1");


        //判断excel是否保存
        if (xlsx.saveAs(filePath)) {

        } else {

        }

    }

    else if(m_Entrys[0]->m_DataType==SampleCollectionData)
    {
        QString oilname=m_parent_MainWidget->m_Left_Frame->m_Leftframe_OilTypeComboBox->currentText();

        //对样本采集数据进行导出到xlsx
        QString filePath = QFileDialog::getSaveFileName(nullptr, "Save File", "", "Excel Files (*.xlsx)");
        if (filePath.isEmpty()) {
            return;
        }

        QXlsx::Document xlsx;

        // 创建第一个Sheet并写入表头
        xlsx.addSheet("Sheet1");
        xlsx.selectSheet("Sheet1");
        xlsx.write("A1", CHINESESTRING("ID"));
        xlsx.write("B1", CHINESESTRING("检测时间"));
        xlsx.write("C1", CHINESESTRING("油液品类"));
        xlsx.write("D1", CHINESESTRING("油液编号"));     
        xlsx.write("E1", CHINESESTRING("参数key"));
        xlsx.write("F1", CHINESESTRING("参数名称"));
        xlsx.write("G1", CHINESESTRING("参数值"));
        xlsx.write("H1", CHINESESTRING("标准版电流"));
        xlsx.write("I1", CHINESESTRING("暗电流")); 
        xlsx.write("J1", CHINESESTRING("参数a"));
        xlsx.write("K1", CHINESESTRING("参数b"));
        xlsx.write("L1", CHINESESTRING("参数c"));
        xlsx.write("M1", CHINESESTRING("波段像素"));
        xlsx.write("N1", CHINESESTRING("FWHM"));
        xlsx.write("O1", CHINESESTRING("积分"));
        xlsx.write("P1", CHINESESTRING("增益"));
        xlsx.write("Q1", CHINESESTRING("偏压"));

        // 创建第二个Sheet并写入表头
        xlsx.addSheet("Sheet2");
        xlsx.selectSheet("Sheet2");
        xlsx.write("A1", CHINESESTRING("ID"));
        xlsx.write("B1", CHINESESTRING("检测时间"));
        xlsx.write("C1", CHINESESTRING("DN值"));
        xlsx.write("D1", CHINESESTRING("反射率"));

        int row1 = 2;  // Sheet1的行号
        int row2 = 2;  // Sheet2的行号

        for (EntryWidget* entry : m_Entrys) 
        {
            const auto& data = entry->sample_collection_dataValue;

            // 拼接参数数据
            QStringList paramKeys;
            QStringList paramNames;
            QStringList paramValues;
            // 写入第一张表的内容
            for (const INDEXDATA& indexData : data.index_data) 
            {
                paramKeys.append(indexData.param_key);
                paramNames.append(indexData.param_name);
                paramValues.append(indexData.param_value);
            }
            // 将参数拼接成一个字符串写入到单元格
            xlsx.selectSheet("Sheet1");
            
            xlsx.write("A" + QString::number(row1), data.id);
            xlsx.write("B" + QString::number(row1), QDateTime::fromString(data.save_time, "yyyyMMddhhmmsszzz").toString("yyyy-MM-dd hh:mm:ss"));
            xlsx.write("C" + QString::number(row1), oilname); 
            xlsx.write("D" + QString::number(row1), data.oilNumber);
            xlsx.write("E" + QString::number(row1), paramKeys.join("; "));
            xlsx.write("F" + QString::number(row1), paramNames.join("; "));
            xlsx.write("G" + QString::number(row1), paramValues.join("; ")); 

            xlsx.write("H" + QString::number(row1), QString::fromStdString(std::accumulate(data.bzbData.begin(), data.bzbData.end(), std::string(), [](const std::string& a, int b) {
                return a + (a.length() > 0 ? "," : "") + std::to_string(b);
            })));
            
            xlsx.write("I" + QString::number(row1), QString::fromStdString(std::accumulate(data.adlData.begin(), data.adlData.end(), std::string(), [](const std::string& a, int b) {
                return a + (a.length() > 0 ? "," : "") + std::to_string(b);
            })));

            xlsx.write("J" + QString::number(row1), data.device_calibrate_parameter.parama);
            xlsx.write("K" + QString::number(row1), data.device_calibrate_parameter.paramb);
            xlsx.write("L" + QString::number(row1), data.device_calibrate_parameter.paramc);
            xlsx.write("M" + QString::number(row1), data.device_calibrate_parameter.pixel_begin + CHINESESTRING("-") + data.device_calibrate_parameter.pixel_end);
            xlsx.write("N" + QString::number(row1), data.device_calibrate_parameter.fwhm);
            xlsx.write("O" + QString::number(row1), data.spectral_parameter.data_value_gain);
            xlsx.write("P" + QString::number(row1), data.spectral_parameter.visible_light_integral);
            xlsx.write("Q" + QString::number(row1), data.spectral_parameter.power_supply_bias);

            row1++;

            // 写入第二张表的内容
            xlsx.selectSheet("Sheet2");
            xlsx.write("A" + QString::number(row2), data.id);
            xlsx.write("B" + QString::number(row2), QDateTime::fromString(data.save_time, "yyyyMMddhhmmsszzz").toString("yyyy-MM-dd hh:mm:ss"));
            xlsx.write("C" + QString::number(row2), QStringList::fromVector(QVector<QString>::fromStdVector(data.dnData)).join(", "));
            xlsx.write("D" + QString::number(row2), QStringList::fromVector(QVector<QString>::fromStdVector(data.reflectivityData)).join(", "));

            row2++;
            
        } 
        xlsx.selectSheet("Sheet1");

        if (xlsx.saveAs(filePath)) {
            
        } else {
           
        }
    }
   
    else if(m_Entrys[0]->m_DataType==ElementDetectionData)
    {
        QString oilname=m_parent_MainWidget->m_Left_Frame->m_Leftframe_OilTypeComboBox->currentText();

        //对元素检测数据进行导出到xlsx
        QString filePath = QFileDialog::getSaveFileName(nullptr, "Save File", "", "Excel Files (*.xlsx)");
        if (filePath.isEmpty()) {
            
            return;
        }

        
        QXlsx::Document xlsx;

        xlsx.addSheet("Sheet1");
        xlsx.selectSheet("Sheet1");
        xlsx.write("A1", CHINESESTRING("ID"));
        xlsx.write("B1", CHINESESTRING("检测时间"));
        xlsx.write("C1", CHINESESTRING("油液品类"));
        xlsx.write("D1", CHINESESTRING("油液编号"));
        xlsx.write("E1", CHINESESTRING("参数key"));
        xlsx.write("F1", CHINESESTRING("参数名称"));
        xlsx.write("G1", CHINESESTRING("参数值"));
        xlsx.write("H1", CHINESESTRING("标准版电流"));
        xlsx.write("I1", CHINESESTRING("暗电流")); 
        xlsx.write("J1", CHINESESTRING("参数a"));
        xlsx.write("K1", CHINESESTRING("参数b"));
        xlsx.write("L1", CHINESESTRING("参数c"));
        xlsx.write("M1", CHINESESTRING("波段像素"));
        xlsx.write("N1", CHINESESTRING("FWHM"));
        xlsx.write("O1", CHINESESTRING("积分"));
        xlsx.write("P1", CHINESESTRING("增益"));
        xlsx.write("Q1", CHINESESTRING("偏压"));

        // 创建第二个Sheet并写入表头
        xlsx.addSheet("Sheet2");
        xlsx.selectSheet("Sheet2");
        xlsx.write("A1", CHINESESTRING("ID"));
        xlsx.write("B1", CHINESESTRING("检测时间"));
        xlsx.write("C1", CHINESESTRING("DN值"));
        xlsx.write("D1", CHINESESTRING("反射率"));

        int row1 = 2;  // Sheet1的行号
        int row2 = 2;  // Sheet2的行号

        
        for (EntryWidget* entry : m_Entrys) 
        {
            const auto& data = entry->element_detection_dataValue;

            // 拼接参数数据
            QStringList paramKeys;
            QStringList paramNames;
            QStringList paramValues;

            for (const INDEXDATA& indexData : data.index_data) {
                paramKeys.append(indexData.param_key);
                paramNames.append(indexData.param_name);
                paramValues.append(indexData.param_value);
            }

            // 写入第一张表的内容
            xlsx.selectSheet("Sheet1");
            xlsx.write("A" + QString::number(row1), data.id);
            xlsx.write("B" + QString::number(row1), QDateTime::fromString(data.save_time, "yyyyMMddhhmmsszzz").toString("yyyy-MM-dd hh:mm:ss"));
            xlsx.write("C" + QString::number(row1), oilname); 
            xlsx.write("D" + QString::number(row1), data.oilNumber);  
            xlsx.write("E" + QString::number(row1), paramKeys.join("; "));
            xlsx.write("F" + QString::number(row1), paramNames.join("; "));
            xlsx.write("G" + QString::number(row1), paramValues.join("; "));

            xlsx.write("H" + QString::number(row1), QString::fromStdString(std::accumulate(data.bzb_data.begin(), data.bzb_data.end(), std::string(), [](const std::string& a, int b) {
                return a + (a.length() > 0 ? "," : "") + std::to_string(b);
            })));
            
            xlsx.write("I" + QString::number(row1), QString::fromStdString(std::accumulate(data.adl_data.begin(), data.adl_data.end(), std::string(), [](const std::string& a, int b) {
                return a + (a.length() > 0 ? "," : "") + std::to_string(b);
            })));

            xlsx.write("J" + QString::number(row1), data.device_calibrate_parameter.parama);
            xlsx.write("K" + QString::number(row1), data.device_calibrate_parameter.paramb);
            xlsx.write("L" + QString::number(row1), data.device_calibrate_parameter.paramc);
            xlsx.write("M" + QString::number(row1), data.device_calibrate_parameter.pixel_begin + CHINESESTRING("-") + data.device_calibrate_parameter.pixel_end);
            xlsx.write("N" + QString::number(row1), data.device_calibrate_parameter.fwhm);
            xlsx.write("O" + QString::number(row1), data.spectral_parameter.data_value_gain);
            xlsx.write("P" + QString::number(row1), data.spectral_parameter.visible_light_integral);
            xlsx.write("Q" + QString::number(row1), data.spectral_parameter.power_supply_bias);

            row1++;
            // 写入第二张表的内容
        
            xlsx.selectSheet("Sheet2");
            xlsx.write("A" + QString::number(row2), data.id);
            xlsx.write("B" + QString::number(row2), QDateTime::fromString(data.save_time, "yyyyMMddhhmmsszzz").toString("yyyy-MM-dd hh:mm:ss"));
            xlsx.write("C" + QString::number(row2), QStringList::fromVector(QVector<QString>::fromStdVector(data.dn_data)).join(", "));
            xlsx.write("D" + QString::number(row2), QStringList::fromVector(QVector<QString>::fromStdVector(data.reflectance_data)).join(", "));

            row2++;
            
        } 
        xlsx.selectSheet("Sheet1");

        //判断数据是否写入到excel
        if (xlsx.saveAs(filePath)) {
            
        } else {
            
        }
    }
       
}

void QDMWidget::InitialLayoutEntrys()
{
    if (m_Entrys.isEmpty())
    {
        Message msgBox(this, MsgBoxType_Info2, QString::fromLocal8Bit("查询无数据"));
		msgBox.setWindowTitle(QString::fromLocal8Bit("提示框"));
        m_parent_MainWidget->m_Mask_Frame->setVisible(true); 
        this->stackUnder(m_parent_MainWidget->m_Mask_Frame); 
	    msgBox.exec();
        m_parent_MainWidget->m_Mask_Frame->setVisible(false);
        m_Lab_Tip->setVisible(true);
        m_RunLabel->setVisible(false);
        m_LabelGif->setVisible(false);
        return;
    }
    m_Lab_Tip->setVisible(false);
    m_RunLabel->setVisible(false);
    m_LabelGif->setVisible(false);
    int x_left=m_ResultFrame->width() / 13;
    int x_right=m_ResultFrame->width() / 13 * 7;
    int y_spaceing=m_QScrA_FunctionFrame->height() / 13 * 3;

    if (m_Entrys[0]->m_DataType != DataType::CalibrationData)
    {
        y_spaceing=m_QScrA_FunctionFrame->height() / 13 * 4;
    }
    
    int up_padding=m_QScrA_FunctionFrame->height() / 13 ;
    int bottom_padding=m_QScrA_FunctionFrame->height() / 13 / 3;

    int y = up_padding;
    int a=1;
    for (int i = 0; i < m_Entrys.size(); i++) {
        EntryWidget* entry = m_Entrys[i];

        if (a == 1) {
            entry->move(x_left, y);
        } else if (a == 2) {
            entry->move(x_right, y);
            y += y_spaceing;
            a = 0;
        }
        a++;
    }
    m_parent_MainWidget->m_Left_Frame->m_Leftframe_btn_DataExport->setVisible(true);
    // int totalMinHeight = y + y_spaceing;
    int totalMinHeight = m_Entrys.last()->y()+ m_Entrys.last()->m_Up_Frame->height() + bottom_padding;
    m_ResultFrame->setMinimumHeight(totalMinHeight); 

    this->update();
}

void QDMWidget::ReLayoutEntrys()
{
    if (m_Entrys.isEmpty())
    {
        return;
    }

    int x_left=m_ResultFrame->width() / 13;
    int x_right=m_ResultFrame->width() / 13 * 7;
    int y_spaceing=m_QScrA_FunctionFrame->height() / 13 * 3;

    if (m_Entrys[0]->m_DataType != DataType::CalibrationData)
    {
        y_spaceing=m_QScrA_FunctionFrame->height() / 13 * 4;
    }

    int bottom_padding=m_QScrA_FunctionFrame->height() / 13 / 3;

    // 获取当前活动的 Entry 的索引
    int activeIndex = m_Entrys.indexOf(m_currentActiveEntry);

    if(activeIndex==m_Entrys.size()-1 || activeIndex==m_Entrys.size()-2)
    {   
        //最后一个entry显示downframe或者倒数第二个，无论最后一行是两个还是一个entry都使用这条件
        //所有的entry都不需要调动位置，此时只需要更改m_ResultFrame的高度
        int totalHeight=m_currentActiveEntry->y() + m_currentActiveEntry->m_Widget->height() + bottom_padding;
        m_ResultFrame->setFixedHeight(totalHeight);

    }
    else if (activeIndex==m_Entrys.size()-3)
    {
        //最后一行是两个entry，即当前entry在第二列
        if(m_currentActiveEntry->x() == x_right)
        {
            m_Entrys[activeIndex+2]->move(x_left, m_Entrys[activeIndex+1]->y()+y_spaceing);
        }
        //最后一行是一个entry，当前entry在第一列
        else{
            m_Entrys[activeIndex+2]->move(x_right, m_Entrys[activeIndex+1]->y()+y_spaceing);
        }
        int totalHeight=m_currentActiveEntry->y() + m_currentActiveEntry->m_Widget->height() + bottom_padding;
        m_ResultFrame->setFixedHeight(totalHeight);

    }
    else if(activeIndex==m_Entrys.size()-4)
    {
        if(m_currentActiveEntry->x() == x_right)
        {
            m_Entrys[activeIndex+2]->move(x_left, m_Entrys[activeIndex+1]->y()+y_spaceing);
            m_Entrys[activeIndex+3]->move(x_left, m_Entrys[activeIndex+2]->y()+y_spaceing);
        }
        else{
            m_Entrys[activeIndex+2]->move(x_right, m_Entrys[activeIndex+1]->y()+y_spaceing);
            m_Entrys[activeIndex+3]->move(x_right, m_Entrys[activeIndex+2]->y()+y_spaceing);
        }

        int totalHeight=m_currentActiveEntry->y() + m_currentActiveEntry->m_Widget->height() + bottom_padding;
        if (m_Entrys[0]->m_DataType != DataType::CalibrationData){
            totalHeight = m_Entrys.last()->y()+ m_Entrys.last()->m_Up_Frame->height() + bottom_padding;
        }
        m_ResultFrame->setFixedHeight(totalHeight);
    }

    else{
        if (m_Entrys[0]->m_DataType == DataType::CalibrationData){            
            if(m_currentActiveEntry->x() == x_left )
                {
                    m_Entrys[activeIndex+2]->move(x_right, m_Entrys[activeIndex+1]->y()+y_spaceing);
                    m_Entrys[activeIndex+3]->move(x_right, m_Entrys[activeIndex+2]->y()+y_spaceing);
                    m_Entrys[activeIndex+4]->move(x_right, m_Entrys[activeIndex+3]->y()+y_spaceing);
                }
                else{
                    m_Entrys[activeIndex+2]->move(x_left, m_Entrys[activeIndex+1]->y()+ y_spaceing);
                    m_Entrys[activeIndex+3]->move(x_left, m_Entrys[activeIndex+2]->y()+ y_spaceing);
                    m_Entrys[activeIndex+4]->move(x_left, m_Entrys[activeIndex+3]->y()+ y_spaceing);
                }

                //downFrame下方区域布局---默认是m_Entrys[activeIndex+4]在第二列，即下行从左往右一行两列，if解决第一列情况
                int y=m_Entrys[activeIndex+4]->y() + y_spaceing;
                int a=1;
                if(m_Entrys[activeIndex+4]->x()==x_left){
                    y=m_Entrys[activeIndex+4]->y();
                    a=2;
                }
                for(int i = activeIndex+5;i<m_Entrys.size();i++)
                {
                    EntryWidget* entry = m_Entrys[i];
                    if (a == 1) 
                    {
                        entry->move(x_left, y);
                    } else if (a == 2) {
                        entry->move(x_right, y);
                        y += y_spaceing;
                        a = 0;
                    }
                    a++;
                }
            }
        else{
            if(m_currentActiveEntry->x() == x_left )
                {
                    m_Entrys[activeIndex+2]->move(x_right, m_Entrys[activeIndex+1]->y()+y_spaceing);
                    m_Entrys[activeIndex+3]->move(x_right, m_Entrys[activeIndex+2]->y()+y_spaceing);
                }
                else{
                    m_Entrys[activeIndex+2]->move(x_left, m_Entrys[activeIndex+1]->y()+ y_spaceing);
                    m_Entrys[activeIndex+3]->move(x_left, m_Entrys[activeIndex+2]->y()+ y_spaceing);
                }

                int y=m_Entrys[activeIndex+3]->y() + y_spaceing;
                int a=1;
                if(m_Entrys[activeIndex+3]->x()==x_left){
                    y=m_Entrys[activeIndex+3]->y();
                    a=2;
                }
                for(int i = activeIndex+4;i<m_Entrys.size();i++)
                {
                    EntryWidget* entry = m_Entrys[i];
                    if (a == 1) 
                    {
                        entry->move(x_left, y);
                    } else if (a == 2) {
                        entry->move(x_right, y);
                        y += y_spaceing;
                        a = 0;
                    }
                    a++;
                }
        }

        // int totalHeight=m_Entrys.last()->geometry().y() + y_spaceing;
        int totalHeight = m_Entrys.last()->y()+ m_Entrys.last()->m_Up_Frame->height() + bottom_padding;
        m_ResultFrame->setFixedHeight(totalHeight);
    }
    
    this->update();
}

void QDMWidget::handleDownFrameRequested(EntryWidget* entryWidget)
{
    if(m_currentActiveEntry==nullptr)
    {
        m_currentActiveEntry=entryWidget;
        InitialLayoutEntrys();
        ReLayoutEntrys();
    }
    else if (m_currentActiveEntry && m_currentActiveEntry != entryWidget)
    {
        //新的entry显示downframe
        m_currentActiveEntry->ClearDownFrame();
        m_currentActiveEntry = entryWidget;
        InitialLayoutEntrys();
        ReLayoutEntrys();
    }
    else if(m_currentActiveEntry==entryWidget)
    {
        //同一个entry活动---切换显示或者隐藏
        bool showDown=m_currentActiveEntry->m_Down_Frame->isVisible();
        if(showDown)
        {
            m_currentActiveEntry = entryWidget;
            InitialLayoutEntrys();
            ReLayoutEntrys();
        }
        else
        {
            m_currentActiveEntry->ClearDownFrame();
            m_currentActiveEntry=nullptr;
            InitialLayoutEntrys();
        }
    }
}

void QDMWidget::ClearEntrys()
{

    // 删除 EntryWidget 实例
    qDeleteAll(m_Entrys);
    m_Entrys.clear(); 
    m_currentActiveEntry=nullptr;

    m_Lab_Tip->setVisible(true);
    // 恢复界面初始化时的大小
    m_ResultFrame->setMinimumHeight(m_QScrA_FunctionFrame->height()-m_QScrA_FunctionFrame->height()/13);
    
}

// bool QDMWidget::eventFilter(QObject *obj, QEvent *event)
// {
    // if (event->type() == QEvent::MouseButtonPress && m_currentActiveEntry != nullptr)
    // {
    //     QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
    //     QPoint globalPos = mouseEvent->globalPos();
    //     QPoint localPos = m_currentActiveEntry->m_Down_ScrollArea->mapFromGlobal(globalPos);

    //     // 检查点击位置是否在 m_Up_Frame 的区域内
    //     if (!m_currentActiveEntry->m_Down_ScrollArea->rect().contains(localPos))
    //     {
    //         // 如果点击位置不在 m_Down_Frame 内，关闭 m_Down_Frame
    //         m_currentActiveEntry->ClearDownFrame();
    //         m_currentActiveEntry=nullptr;
    //         InitialLayoutEntrys();
    //     }
    // }

//     return QWidget::eventFilter(obj, event);
// }
