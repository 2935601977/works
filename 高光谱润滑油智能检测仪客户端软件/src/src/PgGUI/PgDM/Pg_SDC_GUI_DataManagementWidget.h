#ifndef PG_SDC_GUI_DATAMANAGEMENTWIDGET_H
#define PG_SDC_GUI_DATAMANAGEMENTWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QScrollBar>
#include <QScrollArea>
#include <QLabel>
#include "Pg_SDC_GUI_EntryWidget.h"
#include <QGridLayout>
#include <vector>
#include <QList>
#include "qkeytools.h"

#ifndef CHINESESTRING
#define CHINESESTRING(a) QString::fromLocal8Bit(a)
#endif

class QMainWidget;                                                          // 前向声明

class QDMWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QDMWidget(QWidget *parent = nullptr);
    ~QDMWidget();

    void MoveWidget();                                                      // 界面布局显示
    void DateQuery(QMainWidget* mainWidget);                                // 数据查询函数，在MainWidget调用，传递父指针，可访问父类成员，获取当前查询对象
    void DateExport();                                                      // 数据导出函数，在MainWidget调用
    void ClearEntrys();                                                     // 清空Entrys，清理资源，每次查询需清空，确保当前只存储查询对象的数据
    void Initialize();
public:
    QPushButton*                    m_Btn_Return;                           // 返回上一页
    QPushButton*                    m_Btn_Homepage;                         // 返回主页       
    QScrollArea*                    m_QScrA_FunctionFrame;                  // 数据查询结果条目显示区域底层，可根据结果多少更改大小
    QWidget*                        m_ResultFrame;                          // 数据查询结果条目显示区域上层
    QList<EntryWidget*>             m_Entrys;                               // 数据查询结果条目列表
    QMainWidget*                    m_parent_MainWidget;                    // 访问父窗口指针
    EntryWidget*                    m_currentActiveEntry;                   // 当前激活的 EntryWidget
    int                             m_DataManaFlag;
    QLabel*                         m_Lab_Tip;                            // 中心提示框
    QLabel*                         m_RunLabel;
    QLabel*                         m_LabelGif;
// protected:
//     bool eventFilter(QObject *obj, QEvent *event) override;                 // 过滤详情页的鼠标事件，点击在详情页外部则关闭详情页

private:
    void InitialLayoutEntrys();                                              // 布局Entrys
    void ReLayoutEntrys();                                                  // 显示 downFrame 后重新布局 EntryWidgets
    void handleDownFrameRequested(EntryWidget* entryWidget);

};

#endif // PG_SDC_GUI_DATAMANAGEMENTWIDGET_H