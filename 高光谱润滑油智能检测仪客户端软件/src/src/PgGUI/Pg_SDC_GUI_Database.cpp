
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
