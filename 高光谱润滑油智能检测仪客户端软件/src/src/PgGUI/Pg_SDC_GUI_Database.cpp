#include "Pg_SDC_GUI_Database.h"
#include "Pg_SDC_Config_Parameter.h"
#include "Pg_SDC_Func_Tools.h"

#include "easylogging++.h"
#include <QDateTime>
#include <QSqlError>


CSDCDatabase::CSDCDatabase()
{
    m_VecOilType.clear();
    m_VecDevicePara.clear();
    m_VecAlgorithm.clear();
    m_VecDevicePara.clear();                    
    m_VecAllDevicePara.clear(); 
    m_DeviceCaliPara.id = 0;
    m_DeviceCaliPara.parama = "";
    m_DeviceCaliPara.paramb = "";
    m_DeviceCaliPara.paramc = "";
    m_DeviceCaliPara.pixel_begin = "";
    m_DeviceCaliPara.pixel_end = "";
    m_DeviceCaliPara.fwhm = "";
    m_DeviceSpecPara.id = 0;
    m_DeviceSpecPara.data_value_gain = "";
    m_DeviceSpecPara.visible_light_integral = "";
    m_DeviceSpecPara.power_supply_bias = "";
    m_DeviceSpecPara.save_time = "";
    m_deviceInfo.id = 0;
    m_deviceInfo.deviceSN = "";
    m_deviceInfo.productSN = "";
    m_deviceInfo.save_time = "";
    m_Wavelengths.clear();
    m_CaliWhiteData.clear();
    m_CaliBackgroundData.clear();
}

CSDCDatabase::~CSDCDatabase()
{
    DisconnectDB();
    m_VecOilType.clear();
    m_VecDevicePara.clear();
    m_VecAlgorithm.clear();
    m_VecDevicePara.clear();                    
    m_VecAllDevicePara.clear();               
    m_DeviceCaliPara.id = 0;
    m_DeviceCaliPara.parama = "";
    m_DeviceCaliPara.paramb = "";
    m_DeviceCaliPara.paramc = "";
    m_DeviceCaliPara.pixel_begin = "";
    m_DeviceCaliPara.pixel_end = "";
    m_DeviceCaliPara.fwhm = "";
    m_DeviceSpecPara.id = 0;
    m_DeviceSpecPara.data_value_gain = "";
    m_DeviceSpecPara.visible_light_integral = "";
    m_DeviceSpecPara.power_supply_bias = "";
    m_DeviceSpecPara.save_time = "";
    m_deviceInfo.id = 0;
    m_deviceInfo.deviceSN = "";
    m_deviceInfo.productSN = "";
    m_deviceInfo.save_time = "";
    m_Wavelengths.clear();
    m_CaliWhiteData.clear();
    m_CaliBackgroundData.clear();
}

//数据库初始化
bool CSDCDatabase::ConnectDB()
{
    //连接数据库
    QString strExePath = QFileInfo(QCoreApplication::applicationFilePath()).absolutePath();
    if (QSqlDatabase::contains("OILDB"))
    {
        m_SqlDB = QSqlDatabase::database("OILDB");
    }
    else
    {
        m_SqlDB = QSqlDatabase::addDatabase("QSQLITE", "OILDB");
    }

    m_SqlDB.setDatabaseName(QString(strExePath) + QString("/") + QString("OILDB.db"));
    if (!m_SqlDB.open())
    {
        return false;
    }

    return true;
}

//数据库数据初始化
void CSDCDatabase::Initialize()
{
    if (m_SqlDB.open())
    {
        QSqlQuery qSqlquery(m_SqlDB);
        //获取设备信息
        QString qstrDeviceInfo = "SELECT * FROM ";
        qstrDeviceInfo += HYOIL_DATABASE_DEVICEINFO;
        qstrDeviceInfo += " ORDER BY id DESC LIMIT 1";
        qSqlquery.prepare(qstrDeviceInfo);
        if (qSqlquery.exec())
        {
            while (qSqlquery.next())
            {
                int id = qSqlquery.value("id").toInt();
                QString deviceSN = qSqlquery.value("deviceSN").toString();
                QString productSN = qSqlquery.value("productSN").toString();
                QString save_time = qSqlquery.value("save_time").toString();
                
                m_deviceInfo.id = id;
                m_deviceInfo.deviceSN = deviceSN;
                m_deviceInfo.productSN = productSN;                
                m_deviceInfo.save_time = save_time;
            }
        }
        else
        {
            QMessageBox qbox(QMessageBox::Warning, QString::fromLocal8Bit("异常提示框"), QString::fromLocal8Bit("设备信息初始化失败"));
            qbox.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("确 定"));
            //qbox.exec();
        }

        //品类
        QString qstrOILTYPE = "SELECT id,category_number,category_name,enable FROM ";
        qstrOILTYPE += HYOIL_DATABASE_OILTYPE;
        qSqlquery.prepare(qstrOILTYPE);
        if (qSqlquery.exec())
        {
            while (qSqlquery.next())
            {
                int id = qSqlquery.value("id").toInt();
                QString enable = qSqlquery.value("enable").toString();
                QString category_number = qSqlquery.value("category_number").toString();
                QString category_name = qSqlquery.value("category_name").toString();
                OILTYPE oiltypedata;
                oiltypedata.id = id;
                oiltypedata.category_number = category_number;
                oiltypedata.category_name = category_name;
                oiltypedata.enable = enable;
                m_VecAllOilType.push_back(oiltypedata);
                if(enable.compare("true") == 0)
                {
                    m_VecOilType.push_back(oiltypedata);
                }
            }
            if(m_VecOilType.size()==0)
            {
                QMessageBox qbox(QMessageBox::Warning, QString::fromLocal8Bit("异常提示框"), QString::fromLocal8Bit("没有可用的油液品类，请录入"));
                qbox.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("确 定"));
                //qbox.exec();
            }
            
        }
        else
        {
            QMessageBox qbox(QMessageBox::Warning, QString::fromLocal8Bit("异常提示框"), QString::fromLocal8Bit("油液品类初始化失败"));
            qbox.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("确 定"));
            qbox.exec();
        }

        //设备可以检测参数
        QString qstrParameter = "SELECT id,param_down,param_key,param_name,param_up,reserved,sort,unit,enable FROM ";
        qstrParameter += HYOIL_DATABASE_PARAMETER;
        qSqlquery.prepare(qstrParameter);
        if (qSqlquery.exec())
        {
            while (qSqlquery.next())
            {
                int id = qSqlquery.value("id").toInt();
                QString param_key = qSqlquery.value("param_key").toString();
                QString param_name = qSqlquery.value("param_name").toString();
                QString param_up = qSqlquery.value("param_up").toString();
                QString param_down = qSqlquery.value("param_down").toString();
                QString unit = qSqlquery.value("unit").toString();
                QString enable = qSqlquery.value("enable").toString();

                DEVICEPARAMETER deviceparadata;
                deviceparadata.id = id;
                deviceparadata.param_key = param_key;
                deviceparadata.param_name = param_name;
                deviceparadata.param_up = param_up;
                deviceparadata.param_down = param_down;
                deviceparadata.unit = unit;               
                deviceparadata.enable = enable;
                m_VecAllDevicePara.push_back(deviceparadata);
                if(enable.compare("true") == 0)
                {
                    m_VecDevicePara.push_back(deviceparadata);
                }
            }

            if(m_VecDevicePara.size()==0)
            {
                QMessageBox qbox(QMessageBox::Warning, QString::fromLocal8Bit("异常提示框"), QString::fromLocal8Bit("没有可用的检测指标，请录入"));
                qbox.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("确 定"));
                //qbox.exec();
            }
        }
        else
        {
            QMessageBox qbox(QMessageBox::Warning, QString::fromLocal8Bit("异常提示框"), QString::fromLocal8Bit("检测指标初始化失败"));
            qbox.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("确 定"));
            //qbox.exec();
        }

        //设备定标参数
        QString qstrCalibrateParameter = "SELECT * FROM ";
        qstrCalibrateParameter += HYOIL_DATABASE_CALIBRATEPARAMETER;
        qstrCalibrateParameter += " ORDER BY id DESC LIMIT 1";
        qSqlquery.prepare(qstrCalibrateParameter);
        if (qSqlquery.exec())
        {
            while (qSqlquery.next())
            {
                int id = qSqlquery.value("id").toInt();
                QString parama = qSqlquery.value("parama").toString();
                QString paramb = qSqlquery.value("paramb").toString();
                QString paramc = qSqlquery.value("paramc").toString();
                QString pixel_begin = qSqlquery.value("pixel_begin").toString();
                QString pixel_end = qSqlquery.value("pixel_end").toString();
                QString fwhm = qSqlquery.value("fwhm").toString();

                m_DeviceCaliPara.id = id;
                m_DeviceCaliPara.parama = parama;
                m_DeviceCaliPara.paramb = paramb;
                m_DeviceCaliPara.paramc = paramc;
                m_DeviceCaliPara.pixel_begin = pixel_begin;
                m_DeviceCaliPara.pixel_end = pixel_end;
                m_DeviceCaliPara.fwhm = fwhm;
            }
            if(m_DeviceCaliPara.id == 0)
            {
                QMessageBox qbox(QMessageBox::Warning, QString::fromLocal8Bit("异常提示框"), QString::fromLocal8Bit("没有可用的光谱定标参数，请录入"));
                qbox.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("确 定")); 
            }
        }
        else
        {
            QMessageBox qbox(QMessageBox::Warning, QString::fromLocal8Bit("异常提示框"), QString::fromLocal8Bit("光谱定标参数初始化失败"));
            qbox.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("确 定"));
            //qbox.exec();
        }

        //光谱参数
        QString qstrSpectralParameter = "SELECT * FROM ";
        qstrSpectralParameter += HYOIL_DATABASE_SPECTRALPARAMETER;
        qstrSpectralParameter += " ORDER BY id DESC LIMIT 1";
        qSqlquery.prepare(qstrSpectralParameter);
        if (qSqlquery.exec())
        {
            while (qSqlquery.next())
            {
                int id = qSqlquery.value("id").toInt();
                QString data_value_gain = qSqlquery.value("data_value_gain").toString();
                QString visible_light_integral = qSqlquery.value("visible_light_integral").toString();
                QString power_supply_bias = qSqlquery.value("power_supply_bias").toString();
                QString save_time = qSqlquery.value("save_time").toString();

                m_DeviceSpecPara.id = id;
                m_DeviceSpecPara.data_value_gain = data_value_gain;
                m_DeviceSpecPara.visible_light_integral = visible_light_integral;
                m_DeviceSpecPara.power_supply_bias = power_supply_bias;
                m_DeviceSpecPara.save_time = save_time;
            }
            if(m_DeviceSpecPara.id == 0)
            {
                QMessageBox qbox(QMessageBox::Warning, QString::fromLocal8Bit("异常提示框"), QString::fromLocal8Bit("没有可用的定标参数，请录入"));
                qbox.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("确 定"));
            }
        }
        else
        {
            QMessageBox qbox(QMessageBox::Warning, QString::fromLocal8Bit("异常提示框"), QString::fromLocal8Bit("定标参数初始化失败"));
            qbox.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("确 定"));
            //qbox.exec();
        }
        // for(int i = m_DeviceCaliPara.pixel_begin.toInt(); i <= m_DeviceCaliPara.pixel_end.toInt(); i++ )
        // {
        //     m_Wavelengths.push_back(m_DeviceCaliPara.parama.toDouble()*i*i+m_DeviceCaliPara.paramb.toDouble()*i+m_DeviceCaliPara.paramc.toDouble());
        // }

        //获取中心波长
        QString qstrWavelengths = "SELECT * FROM ";
        qstrWavelengths += HYOIL_DATABASE_WAVELENGTHS;
        qstrWavelengths += " ORDER BY id DESC LIMIT 1";
        qSqlquery.prepare(qstrWavelengths);
        if (qSqlquery.exec())
        {
            SPECTRALWAVELENGTHS  SpecWavelength;
            SpecWavelength.id = 0;
            SpecWavelength.wavelengths = "";
            SpecWavelength.save_time = "";
            while (qSqlquery.next())
            {
                int id = qSqlquery.value("id").toInt();
                QString wavelengths = qSqlquery.value("wavelengths").toString();
                QString save_time = qSqlquery.value("save_time").toString();
                
                SpecWavelength.id = id;
                SpecWavelength.wavelengths = wavelengths;
                SpecWavelength.save_time = save_time;
            }

            std::string strWavelengths = (SpecWavelength.wavelengths).toLocal8Bit().toStdString();
            if(strWavelengths.length() == 0)
            {
                QMessageBox qbox(QMessageBox::Warning, QString::fromLocal8Bit("异常提示框"), QString::fromLocal8Bit("没有可用的中心波长，请录入"));
                qbox.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("确 定"));
            }
            else
            {
                int n = strWavelengths.size();
                for (int i = 0; i < n; ++i)
                {
                    if (strWavelengths[i] == ',')
                    {
                        strWavelengths[i] = ' ';
                    }
                }
                std::istringstream streamWavelengths(strWavelengths);
                std::string str;
                while (streamWavelengths >> str)
                {
                    m_Wavelengths.push_back(std::atof(str.c_str()));
                }
            }
        }
        else
        {
            QMessageBox qbox(QMessageBox::Warning, QString::fromLocal8Bit("异常提示框"), QString::fromLocal8Bit("中心波长初始化失败"));
            qbox.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("确 定"));
            //qbox.exec();
        }
        
        //获取白板暗电流
        QString qstrCalibrateData = "SELECT * FROM ";
        qstrCalibrateData += HYOIL_DATABASE_CALIBRATEDATA;
        qstrCalibrateData += " ORDER BY id DESC LIMIT 1";
        qSqlquery.prepare(qstrCalibrateData);
        if (qSqlquery.exec())
        {
            m_CaliWhiteData.clear();
            m_CaliBackgroundData.clear();
            QString bzb_data = "";
            QString adl_data = "";
            while (qSqlquery.next())
            {
                int id = qSqlquery.value("id").toInt();
                bzb_data = qSqlquery.value("bzb_data").toString();
                adl_data = qSqlquery.value("adl_data").toString();
            }

            std::string strBzb_data = bzb_data.toLocal8Bit().toStdString();
            std::string strAdl_data = adl_data.toLocal8Bit().toStdString();
            if(strBzb_data.length() == 0 || strAdl_data.length() == 0)
            {
                QMessageBox qbox(QMessageBox::Warning, QString::fromLocal8Bit("异常提示框"), QString::fromLocal8Bit("获取白板暗电流失败"));
                qbox.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("确 定"));
            }
            else
            {
                int n = strAdl_data.size();
                for (int i = 0; i < n; ++i)
                {
                    if (strAdl_data[i] == ',')
                    {
                        strAdl_data[i] = ' ';
                    }
                }
                std::istringstream streamAdl_data(strAdl_data);
                std::string strAdl;
                while (streamAdl_data >> strAdl)
                {
                    m_CaliBackgroundData.push_back(std::atof(strAdl.c_str()));
                }

                n = strBzb_data.size();
                for (int i = 0; i < n; ++i)
                {
                    if (strBzb_data[i] == ',')
                    {
                        strBzb_data[i] = ' ';
                    }
                }
                std::istringstream streamBzb_data(strBzb_data);
                std::string strBzb;
                while (streamBzb_data >> strBzb)
                {
                    m_CaliWhiteData.push_back(std::atof(strBzb.c_str()));
                }
            }
        }   
        else
        {
            QMessageBox qbox(QMessageBox::Warning, QString::fromLocal8Bit("异常提示框"), QString::fromLocal8Bit("白板暗电流初始化失败"));
            qbox.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("确 定"));
            //qbox.exec();
        }

        //获取模型
        QString qstrAlgorithm = "SELECT * FROM ";
        qstrAlgorithm += HYOIL_DATABASE_ALGORITHM;
        qSqlquery.prepare(qstrAlgorithm);
        if (qSqlquery.exec())
        {
            while (qSqlquery.next())
            {
                int id = qSqlquery.value("id").toInt();
                QString ptype = qSqlquery.value("ptype").toString();
                int opertype = qSqlquery.value("opertype").toInt();
                QString deviceSN = qSqlquery.value("deviceSN").toString();
                QString index = qSqlquery.value("key").toString();
                QString model = qSqlquery.value("model").toString();
                QString name = qSqlquery.value("name").toString();
                QString save_time = qSqlquery.value("save_time").toString();
                ALGORITHM Algorithm;
                Algorithm.id = id;
                Algorithm.ptype = ptype;
                Algorithm.opertype = opertype;
                Algorithm.deviceSN = deviceSN;
                Algorithm.index = index;
                Algorithm.model = model;
                Algorithm.name = name;
                Algorithm.save_time = save_time;
                m_VecAlgorithm.push_back(Algorithm);
            }
        } 
        else
        {
            QMessageBox qbox(QMessageBox::Warning, QString::fromLocal8Bit("异常提示框"), QString::fromLocal8Bit("算法初始化失败"));
            qbox.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("确 定"));
            //qbox.exec();
        }     
    }
}

//重新获取
bool CSDCDatabase::InquireData(QString name)
{
    if (m_SqlDB.open())
    {
        if(name.compare(HYOIL_DATABASE_OILTYPE)==0)
        {
            m_VecOilType.clear();
            QSqlQuery qSqlquery(m_SqlDB);
            QString qstrOILTYPE = "SELECT id,category_number,category_name,enable FROM ";
            qstrOILTYPE += HYOIL_DATABASE_OILTYPE;
            qSqlquery.prepare(qstrOILTYPE);
            if (qSqlquery.exec())
            {
                while (qSqlquery.next())
                {
                    int id = qSqlquery.value("id").toInt();
                    QString enable = qSqlquery.value("enable").toString();
                    QString category_number = qSqlquery.value("category_number").toString();
                    QString category_name = qSqlquery.value("category_name").toString();

                    OILTYPE oiltypedata;
                    oiltypedata.id = id;
                    oiltypedata.category_number = category_number;
                    oiltypedata.category_name = category_name;
                    m_VecAllOilType.push_back(oiltypedata);
                    if(enable.compare("true") == 0)
                    {                       
                        m_VecOilType.push_back(oiltypedata);
                    }
                    
                }
            }
            else
            {           
                return false;
            }
            if(m_VecOilType.size()==0)
            {
                QMessageBox qbox(QMessageBox::Warning, QString::fromLocal8Bit("异常提示框"), QString::fromLocal8Bit("没有可用的油液品类，请录入"));
                qbox.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("确 定"));
            }
        }
        else if(name.compare(HYOIL_DATABASE_PARAMETER)==0)
        {
            m_VecAllDevicePara.clear();
            m_VecDevicePara.clear();
            QString qstrParameter = "SELECT id,param_down,param_key,param_name,param_up,reserved,sort,unit,enable FROM ";
            qstrParameter += HYOIL_DATABASE_PARAMETER;
            QSqlQuery qSqlquery(m_SqlDB);
            qSqlquery.prepare(qstrParameter);
            if (qSqlquery.exec())
            {
                while (qSqlquery.next())
                {
                    int id = qSqlquery.value("id").toInt();
                    QString param_key = qSqlquery.value("param_key").toString();
                    QString param_name = qSqlquery.value("param_name").toString();
                    QString param_up = qSqlquery.value("param_up").toString();
                    QString param_down = qSqlquery.value("param_down").toString();
                    QString unit = qSqlquery.value("unit").toString();
                    QString enable = qSqlquery.value("enable").toString();

                    DEVICEPARAMETER deviceparadata;
                    deviceparadata.id = id;
                    deviceparadata.param_key = param_key;
                    deviceparadata.param_name = param_name;
                    deviceparadata.param_up = param_up;
                    deviceparadata.param_down = param_down;
                    deviceparadata.unit = unit;               
                    deviceparadata.enable = enable;
                    m_VecAllDevicePara.push_back(deviceparadata);
                    if(enable.compare("true") == 0)
                    {
                        m_VecDevicePara.push_back(deviceparadata);
                    }
                }
            }
            else
            {           
                return false;
            }
            if(m_VecDevicePara.size()==0)
            {
                QMessageBox qbox(QMessageBox::Warning, QString::fromLocal8Bit("异常提示框"), QString::fromLocal8Bit("没有可用的检测指标，请录入"));
                qbox.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("确 定"));
            }
        }       
        else if(name.compare(HYOIL_DATABASE_CALIBRATEPARAMETER)==0)
        {
             QString qstrCalibrateParameter = "SELECT * FROM ";
            qstrCalibrateParameter += HYOIL_DATABASE_CALIBRATEPARAMETER;
            qstrCalibrateParameter += " ORDER BY id DESC LIMIT 1";
            QSqlQuery qSqlquery(m_SqlDB);
            qSqlquery.prepare(qstrCalibrateParameter);
            if (qSqlquery.exec())
            {
                while (qSqlquery.next())
                {
                    int id = qSqlquery.value("id").toInt();
                    QString parama = qSqlquery.value("parama").toString();
                    QString paramb = qSqlquery.value("paramb").toString();
                    QString paramc = qSqlquery.value("paramc").toString();
                    QString pixel_begin = qSqlquery.value("pixel_begin").toString();
                    QString pixel_end = qSqlquery.value("pixel_end").toString();
                    QString fwhm = qSqlquery.value("fwhm").toString();

                    m_DeviceCaliPara.id = id;
                    m_DeviceCaliPara.parama = parama;
                    m_DeviceCaliPara.paramb = paramb;
                    m_DeviceCaliPara.paramc = paramc;
                    m_DeviceCaliPara.pixel_begin = pixel_begin;
                    m_DeviceCaliPara.pixel_end = pixel_end;
                    m_DeviceCaliPara.fwhm = fwhm;
                }
                if(m_DeviceCaliPara.id == 0)
                {
                    QMessageBox qbox(QMessageBox::Warning, QString::fromLocal8Bit("异常提示框"), QString::fromLocal8Bit("没有可用的设备指标，请录入"));
                    qbox.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("确 定")); 
                }
            }
            else
            {           
                return false;
            }
        }       
        else if(name.compare(HYOIL_DATABASE_SPECTRALPARAMETER)==0)
        {
            //光谱参数
            QString qstrSpectralParameter = "SELECT * FROM ";
            qstrSpectralParameter += HYOIL_DATABASE_SPECTRALPARAMETER;
            qstrSpectralParameter += " ORDER BY id DESC LIMIT 1";
            QSqlQuery qSqlquery(m_SqlDB);
            qSqlquery.prepare(qstrSpectralParameter);
            if (qSqlquery.exec())
            {
                while (qSqlquery.next())
                {
                    int id = qSqlquery.value("id").toInt();
                    QString data_value_gain = qSqlquery.value("data_value_gain").toString();
                    QString visible_light_integral = qSqlquery.value("visible_light_integral").toString();
                    QString power_supply_bias = qSqlquery.value("power_supply_bias").toString();
                    QString save_time = qSqlquery.value("save_time").toString();

                    m_DeviceSpecPara.id = id;
                    m_DeviceSpecPara.data_value_gain = data_value_gain;
                    m_DeviceSpecPara.visible_light_integral = visible_light_integral;
                    m_DeviceSpecPara.power_supply_bias = power_supply_bias;
                    m_DeviceSpecPara.save_time = save_time;
                }
                if(m_DeviceSpecPara.id == 0)
                {
                    QMessageBox qbox(QMessageBox::Warning, QString::fromLocal8Bit("异常提示框"), QString::fromLocal8Bit("没有可用的光谱指标，请录入"));
                    qbox.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("确 定"));
                }
            }
            else
            {           
                return false;
            }
        }
        else if(name.compare(HYOIL_DATABASE_WAVELENGTHS)==0)
        {
            QString qstrWavelengths = "SELECT * FROM ";
            qstrWavelengths += HYOIL_DATABASE_WAVELENGTHS;
            qstrWavelengths += " ORDER BY id DESC LIMIT 1";
            QSqlQuery qSqlquery(m_SqlDB);
            qSqlquery.prepare(qstrWavelengths);
            if (qSqlquery.exec())
            {
                SPECTRALWAVELENGTHS  SpecWavelength;
                SpecWavelength.id = 0;
                SpecWavelength.wavelengths = "";
                SpecWavelength.save_time = "";
                while (qSqlquery.next())
                {
                    int id = qSqlquery.value("id").toInt();
                    QString wavelengths = qSqlquery.value("wavelengths").toString();
                    QString save_time = qSqlquery.value("save_time").toString();
                    
                    SpecWavelength.id = id;
                    SpecWavelength.wavelengths = wavelengths;
                    SpecWavelength.save_time = save_time;
                }

                std::string strWavelengths = (SpecWavelength.wavelengths).toLocal8Bit().toStdString();
                if(strWavelengths.length() == 0)
                {
                    QMessageBox qbox(QMessageBox::Warning, QString::fromLocal8Bit("异常提示框"), QString::fromLocal8Bit("没有可用的中心波长，请录入"));
                    qbox.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("确 定"));
                }
                else
                {
                    int n = strWavelengths.size();
                    for (int i = 0; i < n; ++i)
                    {
                        if (strWavelengths[i] == ',')
                        {
                            strWavelengths[i] = ' ';
                        }
                    }
                    std::istringstream streamWavelengths(strWavelengths);
                    std::string str;
                    while (streamWavelengths >> str)
                    {
                        m_Wavelengths.push_back(std::atof(str.c_str()));
                    }
                }
            }
            else
            {           
                return false;
            }
        }
        else if(name.compare(HYOIL_DATABASE_CALIBRATEDATA)==0)
        {
            QString qstrCalibrateData = "SELECT * FROM ";
            qstrCalibrateData += HYOIL_DATABASE_CALIBRATEDATA;
            qstrCalibrateData += " ORDER BY id DESC LIMIT 1";
            QSqlQuery qSqlquery(m_SqlDB);
            qSqlquery.prepare(qstrCalibrateData);
            if (qSqlquery.exec())
            {
                m_CaliWhiteData.clear();
                m_CaliBackgroundData.clear();
                QString bzb_data = "";
                QString adl_data = "";
                while (qSqlquery.next())
                {
                    int id = qSqlquery.value("id").toInt();
                    bzb_data = qSqlquery.value("bzb_data").toString();
                    adl_data = qSqlquery.value("adl_data").toString();
                }

                std::string strBzb_data = bzb_data.toLocal8Bit().toStdString();
                std::string strAdl_data = adl_data.toLocal8Bit().toStdString();
                if(strBzb_data.length() == 0 || strAdl_data.length() == 0)
                {
                    QMessageBox qbox(QMessageBox::Warning, QString::fromLocal8Bit("异常提示框"), QString::fromLocal8Bit("获取白板暗电流失败"));
                    qbox.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("确 定"));
                }
                else
                {
                    int n = strAdl_data.size();
                    for (int i = 0; i < n; ++i)
                    {
                        if (strAdl_data[i] == ',')
                        {
                            strAdl_data[i] = ' ';
                        }
                    }
                    std::istringstream streamAdl_data(strAdl_data);
                    std::string strAdl;
                    while (streamAdl_data >> strAdl)
                    {
                        m_CaliBackgroundData.push_back(std::atof(strAdl.c_str()));
                    }

                    n = strBzb_data.size();
                    for (int i = 0; i < n; ++i)
                    {
                        if (strBzb_data[i] == ',')
                        {
                            strBzb_data[i] = ' ';
                        }
                    }
                    std::istringstream streamBzb_data(strBzb_data);
                    std::string strBzb;
                    while (streamBzb_data >> strBzb)
                    {
                        m_CaliWhiteData.push_back(std::atof(strBzb.c_str()));
                    }
                }
            } 
            else
            {         
                return false;
            }
        }   
        else if(name.compare(HYOIL_DATABASE_ALGORITHM)==0)
        {
            QString qstrAlgorithm = "SELECT * FROM ";
            qstrAlgorithm += HYOIL_DATABASE_ALGORITHM;
            QSqlQuery qSqlquery(m_SqlDB);
            qSqlquery.prepare(qstrAlgorithm);
            if (qSqlquery.exec())
            {
                m_VecAlgorithm.clear();
                while (qSqlquery.next())
                {
                    int id = qSqlquery.value("id").toInt();
                    QString ptype = qSqlquery.value("ptype").toString();
                    int opertype = qSqlquery.value("opertype").toInt();
                    QString deviceSN = qSqlquery.value("deviceSN").toString();
                    QString index = qSqlquery.value("key").toString();
                    QString model = qSqlquery.value("model").toString();
                    QString name = qSqlquery.value("name").toString();
                    QString save_time = qSqlquery.value("save_time").toString();
                    ALGORITHM Algorithm;
                    Algorithm.id = id;
                    Algorithm.ptype = ptype;
                    Algorithm.opertype = opertype;
                    Algorithm.deviceSN = deviceSN;
                    Algorithm.index = index;
                    Algorithm.model = model;
                    Algorithm.name = name;
                    Algorithm.save_time = save_time;
                    m_VecAlgorithm.push_back(Algorithm);
                }
            } 
            else
            {         
                return false;
            }
        }
        else if(name.compare(HYOIL_DATABASE_DEVICEINFO)==0)
        {
            QString qstrDeviceInfo = "SELECT * FROM ";
            qstrDeviceInfo += HYOIL_DATABASE_DEVICEINFO;
            qstrDeviceInfo += " ORDER BY id DESC LIMIT 1";
            QSqlQuery qSqlquery(m_SqlDB);
            qSqlquery.prepare(qstrDeviceInfo);
            if (qSqlquery.exec())
            {
                while (qSqlquery.next())
                {
                    int id = qSqlquery.value("id").toInt();
                    QString deviceSN = qSqlquery.value("deviceSN").toString();
                    QString productSN = qSqlquery.value("productSN").toString();
                    QString save_time = qSqlquery.value("save_time").toString();
                    ALGORITHM Algorithm;
                    m_deviceInfo.id = id;
                    m_deviceInfo.deviceSN = deviceSN;
                    m_deviceInfo.productSN = productSN;
                    m_deviceInfo.save_time = save_time;
                }
            } 
            else
            {         
                return false;
            }
        }
    }
    else
    {
        return false;
    }
    return true;
}

//插入
bool CSDCDatabase::InsertData(QString name)
{
    if (m_SqlDB.open())
    {
        if(name.compare(HYOIL_DATABASE_CALIBRATEDATA)==0)
        {
            QSqlQuery qSqlinsert(m_SqlDB);
            QString qstrInsert = "insert into ";
            qstrInsert += HYOIL_DATABASE_CALIBRATEDATA;
            qstrInsert += "(id,save_time,bzb_data,adl_data,sid,cid)""values(:id,:save_time,:bzb_data,:adl_data,:sid,:cid)";
            qSqlinsert.prepare(qstrInsert);
            char tm[32];
            CTools::get_time_str(tm);
            qSqlinsert.bindValue(":save_time", tm);                                                                                  //采集时间
            std::string whiteData = "",backgroundData = "";
            for(int i = 0; i < m_CaliWhiteData.size(); i++)
            {
                if(i == m_CaliWhiteData.size()-1)
                {
                    whiteData += std::to_string(m_CaliWhiteData[i]);
                }
                else
                {
                    whiteData += std::to_string(m_CaliWhiteData[i]);
                    whiteData += ",";
                }
            }
            for(int i = 0; i < m_CaliBackgroundData.size(); i++)
            {
                if(i == m_CaliBackgroundData.size()-1)
                {
                    backgroundData += std::to_string(m_CaliBackgroundData[i]);
                }
                else
                {
                    backgroundData += std::to_string(m_CaliBackgroundData[i]);
                    backgroundData += ",";
                }
            }
            qSqlinsert.bindValue(":bzb_data", whiteData.c_str());                                                                                     
            qSqlinsert.bindValue(":adl_data", backgroundData.c_str()); 
            qSqlinsert.bindValue(":sid", m_DeviceSpecPara.id);                                           
            qSqlinsert.bindValue(":cid", m_DeviceCaliPara.id);                                              

            if (!qSqlinsert.exec())
            {
                return false;
            }

            qSqlinsert.exec("SELECT last_insert_rowid() from oil_client_calibrate_data");
            if (qSqlinsert.next())
            {
                m_CaliBackgroundId = qSqlinsert.value(0).toInt(); //ID 就是最后一次插入数据自增的id
            }
        }
        // else if(name.compare(HYOIL_DATABASE_CALIBRATEPARAMETER)==0)
        // {
        //     QSqlQuery qSqlinsert(m_SqlDB);
        //     qSqlinsert.prepare("insert into oil_client_calibrate_parameter(id,parama,paramb,paramc,pixel_begin,pixel_end,fwhm,save_time)""values(:id,:parama,:paramb,:paramc,:pixel_begin,:pixel_end,:fwhm,:save_time)");

        //     qSqlinsert.bindValue(":parama", m_DeviceSpecPara.id);   
        //     qSqlinsert.bindValue(":save_time", m_CaliTime.c_str());                                                                                     //采集时间
        //     std::string whiteData = "",backgroundData = "";
            
        //     qSqlinsert.bindValue(":bzb_data", whiteData.c_str());                                                                                     
        //     qSqlinsert.bindValue(":adl_data", backgroundData.c_str()); 
        //     qSqlinsert.bindValue(":spec_para_id", m_DeviceSpecPara.id);                                           
        //     qSqlinsert.bindValue(":cali_para_id", m_DeviceCaliPara.id);                                              

        //     if (!qSqlinsert.exec())
        //     {
        //         return false;
        //     }

        //     qSqlinsert.exec("SELECT last_insert_rowid() from oil_client_calibrate_data");
        //     if (qSqlinsert.next())
        //     {
        //         m_CaliBackgroundId = qSqlinsert.value(0).toInt(); //ID 就是最后一次插入数据自增的id
        //     }

        // }
        return true;
    }

    return false;
}

//校准数据查询
QVector<CLIENTCALIBRATEDATA> CSDCDatabase::Calibrate_DateQuery(const QString& startDateTimeStr, const QString& endDateTimeStr)
{
    QVector<CLIENTCALIBRATEDATA> client_calibrate_data;
    if(m_SqlDB.open())
    {
        QSqlQuery qSqlquery(m_SqlDB);
        qSqlquery.exec("PRAGMA foreign_keys = ON;");           
        QString queryStr = QString(
            "SELECT %1.id, %1.save_time, %1.bzb_data, %1.adl_data, "
            "%2.visible_light_integral, %2.data_value_gain, %2.power_supply_bias, "
            "%3.parama, %3.paramb, %3.paramc, %3.pixel_begin, %3.pixel_end, %3.fwhm "
            "FROM %1 "
            "JOIN %2 ON %1.sid = %2.id "
            "JOIN %3 ON %1.cid = %3.id "
            "WHERE %1.save_time BETWEEN :start_datetime AND :end_datetime"
        ).arg(HYOIL_DATABASE_CALIBRATEDATA, HYOIL_DATABASE_SPECTRALPARAMETER, HYOIL_DATABASE_CALIBRATEPARAMETER);

        qSqlquery.prepare(queryStr);
        qSqlquery.bindValue(":start_datetime", startDateTimeStr);
        qSqlquery.bindValue(":end_datetime", endDateTimeStr); 
        if (qSqlquery.exec())
        {
            
            while (qSqlquery.next())
            {
                // 处理查询结果
                CLIENTCALIBRATEDATA data;
                
                data.id=qSqlquery.value("id").toInt();
                data.device_calibrate_parameter.parama=qSqlquery.value("parama").toString();
                data.device_calibrate_parameter.paramb=qSqlquery.value("paramb").toString();
                data.device_calibrate_parameter.paramc=qSqlquery.value("paramc").toString();
                data.device_calibrate_parameter.pixel_begin=qSqlquery.value("pixel_begin").toString();
                data.device_calibrate_parameter.pixel_end=qSqlquery.value("pixel_end").toString();
                data.device_calibrate_parameter.fwhm=qSqlquery.value("fwhm").toString();
                data.spectral_parameter.data_value_gain=qSqlquery.value("data_value_gain").toString();
                data.spectral_parameter.visible_light_integral=qSqlquery.value("visible_light_integral").toString();
                data.spectral_parameter.power_supply_bias=qSqlquery.value("power_supply_bias").toString();
                data.save_time=qSqlquery.value("save_time").toString();              
                // data.save_time=QDateTime::fromString(qSqlquery.value("save_time").toString(), "yyyyMMddhhmmsszzz").toString("yyyy-MM-dd hh:mm:ss");

                QStringList bzbdataList = qSqlquery.value("bzb_data").toString().split(",");
                for (const QString& bzbdata : bzbdataList) {
                    data.bzbData.push_back(bzbdata.toInt());
                }
                QStringList adl_dataList=qSqlquery.value("adl_data").toString().split(",");
                   for (const QString& adldata : adl_dataList) {
                    data.adlData.push_back(adldata.toInt());
                }
                

                QSqlQuery wavelengthQuery(m_SqlDB);
                wavelengthQuery.prepare(QString("SELECT wavelengths FROM %1 ORDER BY id DESC LIMIT 1").arg(HYOIL_DATABASE_WAVELENGTHS));
                if (wavelengthQuery.exec() && wavelengthQuery.next())
                {
                    QString wavelengthsStr = wavelengthQuery.value("wavelengths").toString();
                    QStringList wavelengthsList = wavelengthsStr.split(",");
                    for (const QString& wavelength : wavelengthsList)
                    {
                        data.wavelengths.push_back(wavelength.toDouble());
                    }
                }

                client_calibrate_data.push_back(data);  
            }
            return client_calibrate_data;
        }   
        else
        {
            QMessageBox::critical(nullptr, "Database Error", qSqlquery.lastError().text());
        }
    }
    else{
          QMessageBox::critical(nullptr, "Database Error", m_SqlDB.lastError().text());
    }
    // 在查询失败或数据库打开失败时返回一个空的 QVector
    return QVector<CLIENTCALIBRATEDATA>();
}

// // //样本采集数据查询
QVector<SAMPLECOLLECTION> CSDCDatabase::Sample_DateQuery(const QString& startDateTimeStr, const QString& endDateTimeStr, const QString& oilType)
{
    QVector<SAMPLECOLLECTION> client_sample_data;

    int OILcategory_id = 0;
    QString category_number;
    for (const OILTYPE& VecoilType : m_VecOilType)
    {
        if (VecoilType.category_name == oilType)
        {
            category_number = VecoilType.category_number;
            OILcategory_id = VecoilType.id;
            break;
        }
    }
    if (OILcategory_id==0)
    {
        return QVector<SAMPLECOLLECTION>();
    }

    if (m_SqlDB.open())
    {
        QSqlQuery qSqlquery(m_SqlDB);

        QString queryStr = QString(
            "SELECT %1.id, %1.oil_category_id, %1.oil_num, "
            "%2.bzb_data, %2.adl_data, "
            "%3.cid AS d_cid, %3.dn, %3.reflectance, %3.save_time, "
            "%4.parama, %4.paramb, %4.paramc, %4.pixel_begin, %4.pixel_end, %4.fwhm, "
            "%5.visible_light_integral, %5.data_value_gain, %5.power_supply_bias "
            "FROM %1 "
            "JOIN %2 ON %1.id = %2.cid "
            "JOIN %3 ON %1.id = %3.cid "
            "JOIN %4 ON %4.id = %1.cid "
            "JOIN %5 ON %5.id = %1.sid "
            "WHERE %3.save_time BETWEEN :start_datetime AND :end_datetime AND %1.oil_category_id = :OILcategory_id"
        ).arg(HYOIL_DATABASE_SAMPLEMASTER,
              HYOIL_DATABASE_SAMPLEWHITEBACKGROUND,
              HYOIL_DATABASE_SAMPLEDATA,
              HYOIL_DATABASE_CALIBRATEPARAMETER,
              HYOIL_DATABASE_SPECTRALPARAMETER);

        qSqlquery.prepare(queryStr);
        qSqlquery.bindValue(":start_datetime", startDateTimeStr);
        qSqlquery.bindValue(":end_datetime", endDateTimeStr);
        qSqlquery.bindValue(":OILcategory_id", OILcategory_id);


        if (qSqlquery.exec())
        {
            while (qSqlquery.next())
            {
                SAMPLECOLLECTION data;

                int id=qSqlquery.value("id").toInt();
                data.id=id;
                data.oiltype.category_number=category_number;
                data.oilNumber=qSqlquery.value("oil_num").toString();

                // 解析标准板电流数据
                QStringList bzb_datalist = qSqlquery.value("bzb_data").toString().split(",");
                for (const QString& bzb_data : bzb_datalist) {
                        data.bzbData.push_back(bzb_data.toInt());
                    }

                // 解析暗电流数据
                QStringList adl_datalist = qSqlquery.value("adl_data").toString().split(",");
                for (const QString& adl_data : adl_datalist) {
                        data.adlData.push_back(adl_data.toInt());
                    }

                //保存设备参数和光谱参数
                data.device_calibrate_parameter.parama=qSqlquery.value("parama").toString();
                data.device_calibrate_parameter.paramb=qSqlquery.value("paramb").toString();
                data.device_calibrate_parameter.paramc=qSqlquery.value("paramc").toString();
                data.device_calibrate_parameter.pixel_begin=qSqlquery.value("pixel_begin").toString();
                data.device_calibrate_parameter.pixel_end=qSqlquery.value("pixel_end").toString();
                data.device_calibrate_parameter.fwhm=qSqlquery.value("fwhm").toString();
                data.spectral_parameter.visible_light_integral=qSqlquery.value("visible_light_integral").toString();
                data.spectral_parameter.data_value_gain=qSqlquery.value("data_value_gain").toString();
                data.spectral_parameter.power_supply_bias=qSqlquery.value("power_supply_bias").toString();

                QStringList dn_datalist = qSqlquery.value("dn").toString().split(",");
                for (const QString& dn_data : dn_datalist) {
                    data.dnData.push_back(dn_data);
                }

                QStringList reflectance_datalist=qSqlquery.value("reflectance").toString().split(",");
                for (const QString& reflectance_data : reflectance_datalist) {
                    data.reflectivityData.push_back(reflectance_data);
                }
                data.save_time=qSqlquery.value("save_time").toString();

                QSqlQuery indexQuery(m_SqlDB);
                QString indexQueryStr = QString(
                    "SELECT cid AS i_cid, param_key, param_name, param_value "
                    "FROM %1 "
                    "WHERE i_cid = :id"
                    ).arg(HYOIL_DATABASE_SAMPLEINDEX);

                indexQuery.prepare(indexQueryStr);
                indexQuery.bindValue(":id", id);

                if (indexQuery.exec())
                    {
                        while (indexQuery.next())
                        {
                            int cid = indexQuery.value("i_cid").toInt();

                            INDEXDATA indexData;

                            indexData.param_cid=indexQuery.value("i_cid").toInt();

                            indexData.param_key = indexQuery.value("param_key").toString();

                            indexData.param_name = indexQuery.value("param_name").toString();

                            indexData.param_value = indexQuery.value("param_value").toString();

                            for(int i=0;i < m_VecAllDevicePara.size();i++){
                                if(m_VecAllDevicePara[i].param_key==indexData.param_key){
                                    indexData.unit = m_VecAllDevicePara[i].unit;
                                    break;
                                }
                            }

                            data.index_data.push_back(indexData);
                            
                        }
                        
                    }

                client_sample_data.push_back(data);
            }

            return client_sample_data;
        }
        else
        {
            QMessageBox::critical(nullptr, "Database Error", qSqlquery.lastError().text());
        }
    }
    
    else
    {
        QMessageBox::critical(nullptr, "Database Error", m_SqlDB.lastError().text());
    }

    return QVector<SAMPLECOLLECTION>();
}

//元素检测数据查询
QVector<ELEMENTDETECTION> CSDCDatabase::Element_DateQuery(const QString& startDateTimeStr, const QString& endDateTimeStr, const QString& oilType)
{
    QVector<ELEMENTDETECTION> client_element_data;

    int OILcategory_id = 0;
    QString category_number;
    for (const OILTYPE& VecoilType : m_VecOilType)
    {
        if (VecoilType.category_name == oilType)
        {
            category_number = VecoilType.category_number;
            OILcategory_id = VecoilType.id;
            break;
        }
    }
    if (OILcategory_id==0)
    {
        return QVector<ELEMENTDETECTION>();
    }

     if(m_SqlDB.open())
    {
        QSqlQuery qSqlquery(m_SqlDB);
        QString queryStr = QString(
            "SELECT %1.id,%1.oil_category_id, %1.oil_num, "
            "%2.bzb_data, %2.adl_data, "
            "%3.dn, %3.reflectance, %3.save_time, "
            "%4.parama, %4.paramb, %4.paramc, %4.pixel_begin, %4.pixel_end, %4.fwhm, "
            "%5.visible_light_integral, %5.data_value_gain, %5.power_supply_bias "
            "FROM %1 "
            "JOIN %2 ON %1.id = %2.cid "
            "JOIN %3 ON %1.id = %3.cid "
            "JOIN %4 ON %4.id = %1.cid "
            "JOIN %5 ON %5.id = %1.sid "
            "WHERE %3.save_time BETWEEN :start_datetime AND :end_datetime "
            "AND %1.oil_category_id = :OILcategory_id"
        ).arg(HYOIL_DATABASE_DETECTIONMASTER,
            HYOIL_DATABASE_DETECTIONWHITEBACKGROUND, 
            HYOIL_DATABASE_DETECTIONDATA,
            HYOIL_DATABASE_CALIBRATEPARAMETER,
            HYOIL_DATABASE_SPECTRALPARAMETER);

        qSqlquery.prepare(queryStr);
        qSqlquery.bindValue(":start_datetime", startDateTimeStr);
        qSqlquery.bindValue(":end_datetime", endDateTimeStr); 
        qSqlquery.bindValue(":OILcategory_id", OILcategory_id);
        
         if (qSqlquery.exec())
        {
            QMap<int, ELEMENTDETECTION> elementDtctionMap;

            while (qSqlquery.next())
            {
                int id = qSqlquery.value("id").toInt();
                if (!elementDtctionMap.contains(id))
                {
                    ELEMENTDETECTION data;
                    data.id = id;
                    data.oiltype.category_number=category_number;
                    data.oilNumber=qSqlquery.value("oil_num").toString();
                    data.save_time = qSqlquery.value("save_time").toString();

                    // 解析标准板电流数据
                    QStringList bzb_datalist = qSqlquery.value("bzb_data").toString().split(",");
                    for (const QString& bzb_data : bzb_datalist) {
                        data.bzb_data.push_back(bzb_data.toInt());
                    }

                    // 解析暗电流数据
                    QStringList adl_datalist = qSqlquery.value("adl_data").toString().split(",");
                    for (const QString& adl_data : adl_datalist) {
                        data.adl_data.push_back(adl_data.toInt());
                    }

                    QStringList dn_datalist = qSqlquery.value("dn").toString().split(",");
                    for (const QString& dn_data : dn_datalist) {
                        data.dn_data.push_back(dn_data);
                    }

                    QStringList reflectance_datalist = qSqlquery.value("reflectance").toString().split(",");
                    for (const QString& reflectance_data : reflectance_datalist) {
                        data.reflectance_data.push_back(reflectance_data);
                    }

                    //保存设备参数和光谱参数
                    data.device_calibrate_parameter.parama=qSqlquery.value("parama").toString();
                    data.device_calibrate_parameter.paramb=qSqlquery.value("paramb").toString();
                    data.device_calibrate_parameter.paramc=qSqlquery.value("paramc").toString();
                    data.device_calibrate_parameter.pixel_begin=qSqlquery.value("pixel_begin").toString();
                    data.device_calibrate_parameter.pixel_end=qSqlquery.value("pixel_end").toString();
                    data.device_calibrate_parameter.fwhm=qSqlquery.value("fwhm").toString();
                    data.spectral_parameter.visible_light_integral=qSqlquery.value("visible_light_integral").toString();
                    data.spectral_parameter.data_value_gain=qSqlquery.value("data_value_gain").toString();
                    data.spectral_parameter.power_supply_bias=qSqlquery.value("power_supply_bias").toString();

                    elementDtctionMap.insert(id, data);
                }
            }

            // 获取第一次查询结果中的所有id
            QStringList idList;
            for (auto it = elementDtctionMap.begin(); it != elementDtctionMap.end(); ++it) {
                idList << QString::number(it.key());
            }
            QString idStr = idList.join(",");
            QString indexQueryStr = QString(
                "SELECT cid, param_key, param_name, param_value "
                "FROM %1 "
                "WHERE cid  IN (%2)"
            ).arg(HYOIL_DATABASE_DETECTIONINDEX, idStr);

            qSqlquery.prepare(indexQueryStr);

            if (qSqlquery.exec())
            {
                while (qSqlquery.next())
                {
                    int cid = qSqlquery.value("cid").toInt();

                    if (elementDtctionMap.contains(cid))
                    {
                        INDEXDATA indexData;

                        indexData.param_cid=qSqlquery.value("cid").toInt();

                        indexData.param_key = qSqlquery.value("param_key").toString();

                        indexData.param_name = qSqlquery.value("param_name").toString();

                        indexData.param_value = qSqlquery.value("param_value").toString();

                        for(int i=0;i < m_VecAllDevicePara.size();i++){
                            if(m_VecAllDevicePara[i].param_key==indexData.param_key){
                                indexData.unit = m_VecAllDevicePara[i].unit;
                                break;
                            }
                        }

                        elementDtctionMap[cid].index_data.push_back(indexData);
                    }
                }
            }

            // 将 QMap 中的所有对象转换为 QVector 并返回
            client_element_data = elementDtctionMap.values().toVector();
            return client_element_data;
        }
        
        if (qSqlquery.exec())
        {
            QMap<int, ELEMENTDETECTION> elementDtctionMap;
            while (qSqlquery.next())
            {
                // 处理查询结果
                ELEMENTDETECTION data;
                
                data.id=qSqlquery.value("id").toInt();
                data.oiltype.category_number=qSqlquery.value("oil_num").toString();         
                data.save_time=QDateTime::fromString(qSqlquery.value("save_time").toString(), "yyyyMMddhhmmsszzz").toString("yyyy-MM-dd hh:mm:ss");

                QStringList dn_datalist=qSqlquery.value("dn_data").toString().split(",");
                   for (const QString& dnData : dn_datalist) {
                    data.dn_data.push_back(dnData);
                }
                QStringList reflectivity_datalist=qSqlquery.value("reflectivity").toString().split(",");
                   for (const QString& reflectivity_data : reflectivity_datalist) {
                    data.reflectance_data.push_back(reflectivity_data);
                }

                client_element_data.push_back(data);  
            }
            return client_element_data;     
        }           
    
        else
        {
            QMessageBox::critical(nullptr, "Database Error", qSqlquery.lastError().text());
        }
    }
    else{
          QMessageBox::critical(nullptr, "Database Error", m_SqlDB.lastError().text());
    }
    
    return QVector<ELEMENTDETECTION>();
}

void CSDCDatabase::DisconnectDB()
{
    //关闭数据库
    m_SqlDB.close();
}
