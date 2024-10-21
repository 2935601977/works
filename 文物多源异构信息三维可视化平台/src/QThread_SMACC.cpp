#include "QThread_SMACC.h"
#include "SpectralUnmixingAPI.h"

#include <QFile>

QThread_SMACC::QThread_SMACC(QObject *parent)
	: QThread(parent)
{
}

QThread_SMACC::~QThread_SMACC()
{
}

void QThread_SMACC::UIPara2Thread(GDALDataset* dataset, int endmemN, QString outputFileA, QString outputFileE, void* _hwnd)
{
	m_DS = dataset;
	m_endmemN = endmemN;
	m_outputFileA = outputFileA;
	m_outputFileE = outputFileE;
	m_hwnd = _hwnd;
}

void QThread_SMACC::run(void)
{
	int ret = EndmemberExtractionInterface(m_DS, m_endmemN, m_outputFileA.toStdString().c_str(), m_outputFileE.toStdString().c_str(), m_hwnd);
	if (0 == ret)
	{
		if (QFile::exists(m_outputFileA))
		{
			emit Para2UI_LoadImage(m_outputFileA, false);
		}
		if (QFile::exists(m_outputFileE))
		{
			emit Para2UI_LoadImage(m_outputFileE, false);
		}
		emit CloseDlg();
	} 
	else
	{

	}
}

void QThread_SMACC::SMACCRelease()
{
	EndmemberExtractionRelease();
}