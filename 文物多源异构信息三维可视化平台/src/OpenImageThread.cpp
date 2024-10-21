#include "OpenImageThread.h"
#include "TemporaryFileType.h"
#include "docks\filesdock.h"


OpenImageThread::OpenImageThread()
{
	m_Running = false;
	m_loadLeftTree = false;
}

OpenImageThread::~OpenImageThread()
{
}

void OpenImageThread::setLeftTreeBool() 
{
	m_loadLeftTree = true;
}

//停止全波段加载
void OpenImageThread::HandleStop()
{
	m_Running = true;
}

void OpenImageThread::run()
{
	if (0 == m_qVManager->QAddImageData(m_qVecBandSel, m_flag_loadimage, m_bIsTemporalDimension))
	{
		//加载图像数据
		emit LoadImageThreeBand(m_loadLeftTree);
	}
	m_loadLeftTree = false;
}
