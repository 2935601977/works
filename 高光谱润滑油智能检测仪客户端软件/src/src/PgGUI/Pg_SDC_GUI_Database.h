////////////////////////////////////////////////////////////////////////////////////
//
//	油液客户端------数据库。
//	工具类。
//
//	天津中科谱光信息技术有限公司		2024年6月
//
//	设计者：
//	编码：
//
//	版权所有(2024)
//
////////////////////////////////////////////////////////////////////////////////////
#ifndef PG_SDC_GUI_DATABASE_H
#define PG_SDC_GUI_DATABASE_H

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QThread>
#include <QFileInfo>
#include <QMessageBox>
#include <QApplication>
#include <QMap>
#include <QVector>

typedef struct  _DEVICEINFO
{
    int id;
    QString deviceSN;
    QString productSN;
    QString save_time;
}DEVICEINFO;

typedef struct  _ALGORITHM
{
    int id;
    QString ptype;
    int opertype;
    QString deviceSN;
    QString index;
    QString model;
    QString name;
    QString save_time;
}ALGORITHM;

typedef struct  _OILTYPE
{
    int id;
    QString category_number;
    QString category_name;
    QString enable;
}OILTYPE;

typedef struct  _DEVICEPARAMETER
{
    int id;
    QString param_key;
    QString param_name;
    QString param_up;
    QString param_down;
    QString unit;
    QString enable;
}DEVICEPARAMETER;

typedef struct  _DEVICECALIBRATEPARAMETER
{
    int id;
    QString parama;
    QString paramb;
    QString paramc;
    QString pixel_begin;
    QString pixel_end;
    QString fwhm;
}DEVICECALIBRATEPARAMETER;

typedef struct  _DEVICESPECTRALPARAMETER
{
    int id;
    QString data_value_gain;
    QString visible_light_integral;
    QString power_supply_bias;
    QString save_time;
}DEVICESPECTRALPARAMETER;

typedef struct  _SPECTRALWAVELENGTHS
{
    int id;
    QString wavelengths;
    QString save_time;
}SPECTRALWAVELENGTHS;

typedef struct _CLIENTCALIBRATEDATA
{
    int                         id;
    DEVICECALIBRATEPARAMETER    device_calibrate_parameter;
    DEVICESPECTRALPARAMETER     spectral_parameter;
    std::vector<double>         wavelengths;                      
    std::vector<int>            bzbData;                   
    std::vector<int>            adlData;  
    QString                     save_time;
    
}CLIENTCALIBRATEDATA;                                                       //设备校准数据存储结构


typedef struct _INDEXDATA
{
    int                     id;
    QString                 param_key;
    QString                 param_name;
    QString                 param_value;
    QString                 unit;
    int                     param_cid;  
}INDEXDATA;                                                                 //参数指标数据存储结构

typedef struct _SAMPLECOLLECTION
{   
    int                                     id;
    OILTYPE                                 oiltype;
    QString                                 oilNumber;
    std::vector<int>                        bzbData;                   
    std::vector<int>                        adlData;
    std::vector<INDEXDATA>                  index_data; 
    std::vector<QString>                    dnData;                   
    std::vector<QString>                    reflectivityData; 
    QString                                 save_time;
    DEVICECALIBRATEPARAMETER                device_calibrate_parameter;
    DEVICESPECTRALPARAMETER                 spectral_parameter;
}SAMPLECOLLECTION;                                                          //样本采集数据存储结构

typedef struct _ELEMENTDETECTION
{
    int                                 id;
    OILTYPE                             oiltype;
    QString                             oilNumber;
    std::vector<INDEXDATA>              index_data;
    std::vector<int>                    bzb_data; 
    std::vector<int>                    adl_data;    
    std::vector<QString>                dn_data;              
    std::vector<QString>                reflectance_data;  
    DEVICECALIBRATEPARAMETER            device_calibrate_parameter;
    DEVICESPECTRALPARAMETER             spectral_parameter;
    QString                             save_time;
}ELEMENTDETECTION;                                                          //元素检测数据存储结构                                                         //元素检测数据存储结构


class CSDCDatabase
{
public:
    CSDCDatabase();
    ~CSDCDatabase();

    bool ConnectDB();
    void Initialize();
    bool InsertData(QString name);
    bool InquireData(QString name);
    void setWhiteData(std::vector<int> CaliWhiteData)
    {
        m_CaliWhiteData.clear();
        for(int i = 0; i < CaliWhiteData.size(); i++)
        {
            m_CaliWhiteData.push_back(CaliWhiteData[i]);
        }
    }
    void setBackgroundData(std::vector<int> CaliBackgroundData)
    {
        m_CaliBackgroundData.clear();
        for(int i = 0; i < CaliBackgroundData.size(); i++)
        {
            m_CaliBackgroundData.push_back(CaliBackgroundData[i]);
        }
    }
    std::vector<double> getWavelengths(){ return m_Wavelengths;};

     //设备校准数据查询函数
    QVector<CLIENTCALIBRATEDATA> Calibrate_DateQuery(const QString& startDateTimeStr, const QString& endDateTimeStr);

    //样本采集数据查询函数
    QVector<SAMPLECOLLECTION> Sample_DateQuery(const QString& startDateTimeStr, const QString& endDateTimeStr, const QString& oilType);

    //元素检测数据查询函数
    QVector<ELEMENTDETECTION> Element_DateQuery(const QString& startDateTimeStr, const QString& endDateTimeStr, const QString& oilType);


public:
    QSqlDatabase                        m_SqlDB;                            //数据库
    DEVICEINFO                          m_deviceInfo;                       //设备信息
    QVector<OILTYPE>                    m_VecOilType;                       //油液品类
    QVector<OILTYPE>                    m_VecAllOilType;                    //全部油液品类
    QVector<DEVICEPARAMETER>            m_VecDevicePara;                    //设备可以检测的元素
    QVector<DEVICEPARAMETER>            m_VecAllDevicePara;                 //全部元素
    DEVICECALIBRATEPARAMETER            m_DeviceCaliPara;                   //设备参数               
    DEVICESPECTRALPARAMETER             m_DeviceSpecPara;                   //光谱参数
    std::vector<double>                 m_Wavelengths;                      //中心波长
    std::vector<int>                    m_CaliWhiteData;                    //白板
    std::vector<int>                    m_CaliBackgroundData;               //暗电流
    QVector<ALGORITHM>                  m_VecAlgorithm;                     //算法包

private:
    int                                 m_CaliBackgroundId;                 //白板暗电流

private:
    void DisconnectDB();

};
#endif // PG_SDC_GUI_DATABASE_H
