#ifndef __OPENIMAGETHREAD_H__
#define __OPENIMAGETHREAD_H__
#include <QtCore\QThread>

#include "QViewManager.h"


class FilesDock;
class OpenImageThread : public QThread
{
	Q_OBJECT
public:
	OpenImageThread();
	virtual ~OpenImageThread();
	
	void HandleStop();

	inline void setVManager(QViewManager* qVManager) { m_qVManager = qVManager; }
	inline void setFlagLoadImg(int flag_loadimage) { m_flag_loadimage = flag_loadimage; }
	inline void setVecBandSel(QVECBANDSEL qVecBand) { m_qVecBandSel = qVecBand; }
	inline void setTemporalDimFlag(bool bIsTemporalDimension) { m_bIsTemporalDimension = bIsTemporalDimension; }

private:
	HASCRImageProcessor::HASCRImageDataManager*			m_HASCR_ImgDM;
	int													m_flag_loadimage;
	QString												m_firstLoad;
	QVector<int>										m_qvecBand;
	QViewManager*										m_qVManager;
	HASCRImageProcessor::ImageData*						m_imageData;
	bool												m_isFirstLoad;
	bool												m_loadLeftTree;
	bool												m_Running;
	QVECBANDSEL											m_qVecBandSel;
	bool												m_bIsTemporalDimension;

protected:
	void run();

signals:
	void LoadImageThreeBand(bool isK);
	//设置进度最大值
	void SendBands(int num);
	//发送进度值 
	void SendLongProgressBar(int num);

public slots:
	void setLeftTreeBool();
};
#endif //__OPENIMAGETHREAD_H__
