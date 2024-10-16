#include "Pg_SDC_GUI_HelpWidget.h"
#include "easylogging++.h"


QHelpWidget::QHelpWidget(QWidget *parent) : QWidget(parent)
{
    this->setAutoFillBackground(true);
    this->resize(1024,680);
    this->setWindowFlags(Qt::FramelessWindowHint/* | Qt::WindowStaysOnTopHint*/);
    this->setAttribute(Qt::WA_QuitOnClose, true);
    this->setStyleSheet("background:rgb(237, 237, 237);");

    m_Btn_Homepage = new QPushButton(this);
    //m_Btn_Homepage->setStyleSheet("QPushButton{font-family:Microsoft YaHei;font-size:30px;color:black} QPushButton{background-color:transparent;border-image:url(:/image/image/allbutton.png)}""QPushButton:hover{font:bold;font-size:30px;color:white;background-color:transparent;border-image:url(:/image/image/allpress.png)}""QPushButton:pressed{font:bold;font-size:30px;color:white;background-color:transparent;border-image:url(:/image/image/allpress.png)}");
    m_Btn_Homepage->setStyleSheet("QPushButton{font-family:Microsoft YaHei;font-size:30px;color:black} QPushButton{background-color:transparent;border-image:url(:/image/image/allbutton.png)}");
    m_Btn_Homepage->setGeometry(QRect(this->width()/6*5+30, (this->height()-90)/7*6+60, (this->width()-60)/6, (this->height()-90)/7  ));
    m_Btn_Homepage->setText(CHINESESTRING("首页"));

    m_Btn_Return= new QPushButton(this);
    //m_Btn_Return->setStyleSheet("QPushButton{font-family:Microsoft YaHei;font-size:30px;color:black} QPushButton{background-color:transparent;border-image:url(:/image/image/allbutton.png)}""QPushButton:hover{font:bold;font-size:30px;color:white;background-color:transparent;border-image:url(:/image/image/allpress.png)}""QPushButton:pressed{font:bold;font-size:30px;color:white;background-color:transparent;border-image:url(:/image/image/allpress.png)}");
    m_Btn_Return->setStyleSheet("QPushButton{font-family:Microsoft YaHei;font-size:30px;color:black} QPushButton{background-color:transparent;border-image:url(:/image/image/allbutton.png)}");
    m_Btn_Return->setGeometry(QRect(30, (this->height()-90)/7*6+60, (this->width()-60)/6, (this->height()-90)/7  ));
    m_Btn_Return->setText(CHINESESTRING("返回"));

    m_FunctionFrame=new QWidget(this);
    m_FunctionFrame->setGeometry(QRect(30,  30, this->width()-60, (this->height()-90)/7*6 ));
    m_FunctionFrame->setStyleSheet("background-color:white;border-radius:15px;border: none;");

    m_Btn_Last=new QPushButton(m_FunctionFrame);
    m_Btn_Last->setGeometry(QRect(m_FunctionFrame->width()/5-m_Btn_Return->height()/2,  (m_FunctionFrame->height()/5)*4-m_Btn_Return->height()/2, m_Btn_Return->height()/2, m_Btn_Return->height()/2));
    m_Btn_Last->setStyleSheet("background-color: transparent;border-image:url(:/image/image/leftArrow.png);");
    
    m_Btn_Next=new QPushButton(m_FunctionFrame);
    m_Btn_Next->setGeometry(QRect((m_FunctionFrame->width()/5)*4-m_Btn_Return->height()/2,  (m_FunctionFrame->height()/5)*4-m_Btn_Return->height()/2, m_Btn_Return->height()/2, m_Btn_Return->height()/2));
    m_Btn_Next->setStyleSheet("background-color: transparent;border-image:url(:/image/image/rightArrow.png);");
    
    m_IntroImg_Background=new QLabel(m_FunctionFrame);
    m_IntroImg_Background->setGeometry(QRect(m_Btn_Last->geometry().x()+(m_Btn_Last->width()/2)*3,m_FunctionFrame->height()/10,m_Btn_Next->geometry().x()-m_Btn_Last->geometry().x()-m_Btn_Last->width()*2,(m_FunctionFrame->height()/5)*4));
    m_IntroImg_Background->setStyleSheet("background-color: transparent;border-radius:0;");
    
    for(int i=0;i<9;i++){
        m_IntroImgPages[i]=new QLabel(m_IntroImg_Background);
        int width=m_IntroImg_Background->width();
        int height=m_IntroImg_Background->height();
        m_IntroImgPages[i]->setGeometry(QRect(0,0,width,height));
        m_IntroImgPages[i]->setStyleSheet("background-color: transparent;border-radius:0;");
        m_IntroImgPages[i]->setStyleSheet(QString("background-color: transparent;border-image:url(:/image/image/Help0%1.png);").arg(i+1));
        m_IntroImgPages[i]->setVisible(false);
    }

    MoveWidget();
    //建立图片切换函数连接
    connect(m_Btn_Last,SIGNAL(clicked()),this,SLOT(Function_Qbtn_Left()),Qt::DirectConnection);
    connect(m_Btn_Next,SIGNAL(clicked()),this,SLOT(Function_Qbtn_Right()),Qt::DirectConnection);
    
}

QHelpWidget::~QHelpWidget()
{

}

void QHelpWidget::Initialize()
{
    // 初始化显示第一个图片，并确保它的大小和位置正确
    m_IntroImgPages[0]->setVisible(true);

    //追踪当前显示图片
    m_IntroImg_CurrentIndex=0;

}

//界面布局
void QHelpWidget::MoveWidget()
{
	this->setAutoFillBackground(true);
	int width = (this->width());
	int height = (this->height());
    m_Btn_Homepage->setGeometry(QRect( (width-60)/6*5+30,  (height-90)/7*6+60, (width-60)/6, (height-90)/7));
    m_Btn_Return->setGeometry(QRect(30,  (height-90)/7*6+60, (width-60)/6, (height-90)/7  ));
    
    m_FunctionFrame->setGeometry(QRect(30,  30, this->width()-60, (this->height()-90)/7*6 ));
 
    m_Btn_Last->setGeometry(QRect(m_FunctionFrame->width()/5-m_Btn_Return->height(),  (m_FunctionFrame->height()/5)*4-m_Btn_Return->height()/2, m_Btn_Return->height(), m_Btn_Return->height()));
    m_Btn_Next->setGeometry(QRect((m_FunctionFrame->width()/5)*4,  (m_FunctionFrame->height()/5)*4-m_Btn_Return->height()/2, m_Btn_Return->height(), m_Btn_Return->height()));

    m_IntroImg_Background->setGeometry(QRect(m_Btn_Last->geometry().x()+(m_Btn_Last->width()/2)*3,m_FunctionFrame->height()/10*2,m_Btn_Next->geometry().x()-m_Btn_Last->geometry().x()-m_Btn_Last->width()*2,(m_FunctionFrame->height()/5)*4));

    for(int i=0;i<9;i++){
        int width=m_IntroImg_Background->width();
        int height=m_IntroImg_Background->height();
        m_IntroImgPages[i]->setGeometry(QRect(0,0,width,height));
    }

	this->update();
}

void QHelpWidget::Function_Qbtn_Left()
{
    if(m_IntroImg_CurrentIndex > 0)
    {
        int nextIndex = m_IntroImg_CurrentIndex - 1;
        IntroImgPage_Slide(nextIndex, -1);
    }
    UpdateFrame();  
}

void QHelpWidget::Function_Qbtn_Right()
{
    if(m_IntroImg_CurrentIndex < 8)
    {
        int nextIndex = m_IntroImg_CurrentIndex + 1;
        IntroImgPage_Slide(nextIndex, 1);
    }
    UpdateFrame();  
}

void QHelpWidget::UpdateFrame()
{
    if(m_IntroImg_CurrentIndex == 8)
    {
        m_Btn_Next->setEnabled(false);
    }
    else if(m_IntroImg_CurrentIndex == 0)
    {
        m_Btn_Last->setEnabled(false);
    }
    else
    {
        m_Btn_Next->setEnabled(true);
        m_Btn_Last->setEnabled(true);
    }
}

void QHelpWidget::IntroImgPage_Slide(int index, int direction)
{
    QLabel *current_QLab_IntroImage = m_IntroImgPages[m_IntroImg_CurrentIndex];
    QWidget *next_QLab_IntroImage = m_IntroImgPages[index];

    int width=m_IntroImg_Background->width();

    next_QLab_IntroImage->setGeometry(direction * width, 0, width, m_IntroImg_Background->height());
    next_QLab_IntroImage->setVisible(true);

    QPropertyAnimation *currentAnim = new QPropertyAnimation(current_QLab_IntroImage, "pos");
    currentAnim->setDuration(300);
    currentAnim->setStartValue(QPoint(0, 0));
    currentAnim->setEndValue(QPoint(-direction * width, 0));

    QPropertyAnimation *nextAnim = new QPropertyAnimation(next_QLab_IntroImage, "pos");
    nextAnim->setDuration(300);
    nextAnim->setStartValue(QPoint(direction * width, 0));
    nextAnim->setEndValue(QPoint(0, 0));

    connect(currentAnim, &QPropertyAnimation::finished, [this, index, current_QLab_IntroImage]() {
        m_IntroImg_CurrentIndex=index;
        current_QLab_IntroImage->setVisible(false);
     });

    currentAnim->start(QAbstractAnimation::DeleteWhenStopped);
    nextAnim->start(QAbstractAnimation::DeleteWhenStopped);
}
