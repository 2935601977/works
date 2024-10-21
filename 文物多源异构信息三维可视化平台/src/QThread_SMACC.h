#ifndef __QTHREAD_SMACC_H__
#define __QTHREAD_SMACC_H__

#include "CommonMacro.h"

#include <QThread>

class QThread_SMACC : public QThread
{
	Q_OBJECT

public:
	QThread_SMACC(QObject *parent=0);
	~QThread_SMACC();

	void SMACCRelease();

protected:
	void run(void);

private:
	void*												m_hwnd;
	int													m_endmemN;
	QString												m_outputFileA;
	QString												m_outputFileE;
	GDALDataset*										m_DS;

public slots:
	/** 接收ui界面传递的参数*/
	void UIPara2Thread(GDALDataset* dataset, int endmemN, QString outputFileA, QString outputFileE, void* _hwnd);

signals:
	/** 传递文件路径参数到ui界面*/
	void Para2UI_LoadImage(QString clsPath, bool isload2layer = true);

	void CloseDlg();
};
#endif