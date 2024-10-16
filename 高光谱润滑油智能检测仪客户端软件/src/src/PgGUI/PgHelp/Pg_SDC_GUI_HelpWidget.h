#ifndef PG_SDC_GUI_HELPWIDGET_H
#define PG_SDC_GUI_HELPWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QPropertyAnimation>

#ifndef CHINESESTRING
#define CHINESESTRING(a) QString::fromLocal8Bit(a)
#endif

class QHelpWidget : public QWidget
{
    Q_OBJECT

public:
    QHelpWidget(QWidget *parent = 0);
    ~QHelpWidget();

    void MoveWidget();
    void Initialize();
public:
    int             m_IntroImg_CurrentIndex;

    QWidget*        m_FunctionFrame;

    QLabel*         m_IntroImg_Background;
    QLabel*         m_IntroImgPages[9];

    QPushButton*    m_Btn_Return;
    QPushButton*    m_Btn_Homepage;
    QPushButton*    m_Btn_Last;
    QPushButton*    m_Btn_Next;

private:
    void IntroImgPage_Slide(int index,int direction);
    void UpdateFrame();
private slots:
    void Function_Qbtn_Left();
    void Function_Qbtn_Right();

};

#endif // PG_SDC_GUI_HELP_HELPWIDGET_H
