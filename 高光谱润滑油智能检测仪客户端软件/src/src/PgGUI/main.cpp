#include "Pg_SDC_GUI_MainWidget.h"

#include <QApplication>
#include <QTime>
#include <QtGui>
#include <QWidget>
#include <QDesktopWidget>
#include <QDebug>
#include <QSplashScreen>
#include "easylogging++.h"
INITIALIZE_EASYLOGGINGPP

#if (defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64)
#include <windows.h>
#include <io.h>
#elif  (defined __linux__)
#include <unistd.h>
#include <stdlib.h>
#endif

bool SystemShutDown()
{
#if (defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64)
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;
     
    if (!OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
        return(false);
     
    LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,&tkp.Privileges[0].Luid);
    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    
    AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,(PTOKEN_PRIVILEGES)NULL, 0);
    if (GetLastError() != ERROR_SUCCESS)
        return false;

    if (!ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE,
    SHTDN_REASON_MAJOR_OPERATINGSYSTEM |
    SHTDN_REASON_MINOR_UPGRADE |
    SHTDN_REASON_FLAG_PLANNED));
     
     //shutdown or restart was successful
    return TRUE;
#elif  (defined __linux__) 
    system("shutdown /s /t 0");          //关机
    return TRUE;
#endif
}

int main(int argc, char *argv[])
{
    //qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    QApplication a(argc, argv); 

    // QApplication::setStyle("windowsxp");
    a.setWindowIcon(QIcon(":/image/image/logo.ico"));

    QSplashScreen splash(QPixmap(":/image/image/logo.ico"));
    splash.show();
    a.processEvents();

    //设置中文编码
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
#if _MSC_VER
    QTextCodec *codec = QTextCodec::codecForName("GBK");
#else
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
#endif
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#else
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
#endif

    // QTextCodec *codec = QTextCodec::codecForName("GB2312");
    // QTextCodec::setCodecForLocale(codec);
    //QTextCodec::setCodecForCStrings(codec);
    //QTextCodec::setCodecForTr(codec);
    QMainWidget* w = new QMainWidget();
    /*if (!w->onClicked_Connect())
    {
        w->close();
        a.exit(0);
        return 0;
    }
    else*/
    {
        w->show();

        splash.finish(w);

        a.connect(w, SIGNAL(close()), &a, SLOT(exit()));
        a.connect(w, SIGNAL(close()), &a, SLOT(quit()));
        a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(exit()));
        a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
        a.setQuitOnLastWindowClosed(true);

        int ret = a.exec();
        if (ret == 0)
        {
            a.closeAllWindows();
            a.exit(0);

            delete w;
            SystemShutDown();
            // HANDLE _handle = ::GetCurrentProcess();
            // ::TerminateProcess(_handle, 0);
            
        }
        return 0;
    }
}


