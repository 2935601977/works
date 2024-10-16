#include "OCCWindow.h"


OCCWindow::OCCWindow(QWidget* Widget, const Quantity_NameOfColor theBackColor)
    : Aspect_Window(),
    m_Widget(Widget),
    m_dpiScale(Widget->devicePixelRatioF())
{
    SetBackground (theBackColor);
    m_XLeft   = qRound(m_dpiScale*m_Widget->rect().left());
    m_YTop    = qRound(m_dpiScale*m_Widget->rect().top());
    m_XRight  = qRound(m_dpiScale*m_Widget->rect().right());
    m_YBottom = qRound(m_dpiScale*m_Widget->rect().bottom());
}

//! Returns True if the window <me> is opened
//! and False if the window is closed.
Standard_Boolean OCCWindow::IsMapped() const
{
    return !(m_Widget->isMinimized() || m_Widget->isHidden());
}

//! Opens the window <me>.
void OCCWindow::Map() const{
    m_Widget->show();
    m_Widget->update();
}

//! Closes the window <me>.
void OCCWindow:: Unmap() const{
    m_Widget->hide();
    m_Widget->update();
}

//! Apply the resizing to the window <me>.
Aspect_TypeOfResize OCCWindow::DoResize() const
{
    int                 aMask = 0;
    Aspect_TypeOfResize aMode = Aspect_TOR_UNKNOWN;

    if ( !m_Widget->isMinimized() )
    {
        if ( Abs ( m_dpiScale*m_Widget->rect().left()   - m_XLeft   ) > 2 ) aMask |= 1;
        if ( Abs ( m_dpiScale*m_Widget->rect().right()  - m_XRight  ) > 2 ) aMask |= 2;
        if ( Abs ( m_dpiScale*m_Widget->rect().top()    - m_YTop    ) > 2 ) aMask |= 4;
        if ( Abs ( m_dpiScale*m_Widget->rect().bottom() - m_YBottom ) > 2 ) aMask |= 8;

        switch ( aMask )
        {
        case 0:
            aMode = Aspect_TOR_NO_BORDER;
            break;
        case 1:
            aMode = Aspect_TOR_LEFT_BORDER;
            break;
        case 2:
            aMode = Aspect_TOR_RIGHT_BORDER;
            break;
        case 4:
            aMode = Aspect_TOR_TOP_BORDER;
            break;
        case 5:
            aMode = Aspect_TOR_LEFT_AND_TOP_BORDER;
            break;
        case 6:
            aMode = Aspect_TOR_TOP_AND_RIGHT_BORDER;
            break;
        case 8:
            aMode = Aspect_TOR_BOTTOM_BORDER;
            break;
        case 9:
            aMode = Aspect_TOR_BOTTOM_AND_LEFT_BORDER;
            break;
        case 10:
            aMode = Aspect_TOR_RIGHT_AND_BOTTOM_BORDER;
            break;
        default:
            break;
        }  // end switch

        *( ( Standard_Integer* )&m_XLeft  ) = qRound(m_dpiScale*m_Widget->rect().left());
        *( ( Standard_Integer* )&m_XRight ) = qRound(m_dpiScale*m_Widget->rect().right());
        *( ( Standard_Integer* )&m_YTop   ) = qRound(m_dpiScale*m_Widget->rect().top());
        *( ( Standard_Integer* )&m_YBottom) = qRound(m_dpiScale*m_Widget->rect().bottom());
    }

    return aMode;
}

//! Apply the mapping change to the window <me>.
//! and returns TRUE if the window is mapped at screen.
Standard_Boolean OCCWindow::DoMapping() const
{
    return Standard_True;
};
void OCCWindow::Position (Standard_Integer& X1, Standard_Integer& Y1, Standard_Integer& X2, Standard_Integer& Y2) const 
{
    X1 = qRound(m_dpiScale*m_Widget->rect().left());
    X2 = qRound(m_dpiScale*m_Widget->rect().right());
    Y1 = qRound(m_dpiScale*m_Widget->rect().top());
    Y2 = qRound(m_dpiScale*m_Widget->rect().bottom());
}

//! Returns The Window SIZE in PIXEL
void OCCWindow::Size (Standard_Integer& Width, Standard_Integer& Height) const
{
    QRect aRect = m_Widget->rect();
    Width  = m_dpiScale*aRect.width();
    Height = m_dpiScale*aRect.height();
}

//! Returns The Window RATIO equal to the physical
//! WIDTH/HEIGHT dimensions
Standard_Real OCCWindow::Ratio() const
{
    QRect aRect = m_Widget->rect();
    return Standard_Real( aRect.right() - aRect.left() ) / Standard_Real( aRect.bottom() - aRect.top() );
}

//! Returns native Window handle (HWND on Windows, Window with Xlib, and so on)
Aspect_Drawable OCCWindow::NativeHandle() const
{
    return (Aspect_Drawable)m_Widget->winId();
}

//! Returns parent of native Window handle (HWND on Windows, Window with Xlib, and so on)
Aspect_Drawable OCCWindow::NativeParentHandle() const
{
    QWidget* parentWidget = m_Widget->parentWidget();
    if (parentWidget) {
        return (Aspect_Drawable)parentWidget->winId();
    }else{
        return 0;
    }
}

//! Returns native Window FB config (GLXFBConfig on Xlib)
Aspect_FBConfig OCCWindow::NativeFBConfig() const
{
    return nullptr;
}