/* -*- mode: C++ ; c-file-style: "stroustrup" -*- *****************************
 * Qwt Widget Library
 * Copyright (C) 1997   Josef Wilgen
 * Copyright (C) 2002   Uwe Rathmann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the Qwt License, Version 1.0
 *****************************************************************************/

#include "qwt_dial_needle.h"
#include "qwt_global.h"
#include "qwt_math.h"
#include "qwt_painter.h"
#include <qapplication.h>
#include <qpainter.h>
#include <QPainterPath>

#if QT_VERSION < 0x040601
#define qFastSin(x) qSin(x)
#define qFastCos(x) qCos(x)
#endif

static void qwtDrawStyle1Needle( QPainter *painter,
    const QPalette &palette, QPalette::ColorGroup colorGroup,
    double length )
{
    const double r[] = { 0.4, 0.3, 1, 0.8, 1, 0.3, 0.4 };
    const double a[] = { -45, -20, -15, 0, 15, 20, 45 };

    QPainterPath path;
    for ( int i = 0; i < 7; i++ )
    {
        const double angle = a[i] / 180.0 * M_PI;
        const double radius = r[i] * length;

        const double x = radius * qFastCos( angle );
        const double y = radius * qFastSin( angle );

        path.lineTo( x, -y );
    }

    painter->setPen( Qt::NoPen );
    painter->setBrush( palette.brush( colorGroup, QPalette::Light ) );
    painter->drawPath( path );
}

static void qwtDrawStyle2Needle( QPainter *painter,
    const QPalette &palette, QPalette::ColorGroup colorGroup, double length )
{
    const double ratioX = 0.7;
    const double ratioY = 0.3;

    QPainterPath path1;
    path1.lineTo( ratioX * length, 0.0 );
    path1.lineTo( length, ratioY * length );

    QPainterPath path2;
    path2.lineTo( ratioX * length, 0.0 );
    path2.lineTo( length, -ratioY * length );

    painter->setPen( Qt::NoPen );

    painter->setBrush( palette.brush( colorGroup, QPalette::Light ) );
    painter->drawPath( path1 );

    painter->setBrush( palette.brush( colorGroup, QPalette::Dark ) );
    painter->drawPath( path2 );
}

static void qwtDrawShadedPointer( QPainter *painter, 
    const QColor &lightColor, const QColor &darkColor,
    double length, double width )
{
    const double peak = qMax( length / 10.0, 5.0 );

    const double knobWidth = width + 8;
    QRectF knobRect( 0, 0, knobWidth, knobWidth );
    knobRect.moveCenter( QPointF(0, 0) );

    QPainterPath path1;
    path1.lineTo( 0.0, 0.5 * width );
    path1.lineTo( length - peak, 0.5 * width );
    path1.lineTo( length, 0.0 );
    path1.lineTo( 0.0, 0.0 );

    QPainterPath arcPath1;
    arcPath1.arcTo( knobRect, 0.0, -90.0 );

    path1 = path1.united( arcPath1 );

    QPainterPath path2;
    path2.lineTo( 0.0, -0.5 * width );
    path2.lineTo( length - peak, -0.5 * width );
    path2.lineTo( length, 0.0 );
    path2.lineTo( 0.0, 0.0 );

    QPainterPath arcPath2;
    arcPath2.arcTo( knobRect, 0.0, 90.0 );

    path2 = path2.united( arcPath2 );

    painter->setPen( Qt::NoPen );

    painter->setBrush( lightColor );
    painter->drawPath( path1 );

    painter->setBrush( darkColor );
    painter->drawPath( path2 );
}

static void qwtDrawArrowNeedle( QPainter *painter,
    const QPalette &palette, QPalette::ColorGroup colorGroup,
    double length, double width )
{
    if ( width <= 0 )
        width = qMax( length * 0.06, 9.0 );

    const double peak = qMax( 2.0, 0.4 * width );

    QPainterPath path;
    path.moveTo( 0.0, 0.5 * width );
    path.lineTo( length - peak, 0.3 * width );
    path.lineTo( length, 0.0 );
    path.lineTo( length - peak, -0.3 * width );
    path.lineTo( 0.0, -0.5 * width );

    QRectF br = path.boundingRect();

    QPalette pal( palette.color( QPalette::Mid ) );
    QColor c1 = pal.color( QPalette::Light );
    QColor c2 = pal.color( QPalette::Dark );

    QLinearGradient gradient( br.topLeft(), br.bottomLeft() );
    gradient.setColorAt( 0.0, c1 );
    gradient.setColorAt( 0.5, c1 );
    gradient.setColorAt( 0.5001, c2 );
    gradient.setColorAt( 1.0, c2 );

    QPen pen( gradient, 1 );
    pen.setJoinStyle( Qt::MiterJoin );

    painter->setPen( pen );
    painter->setBrush( palette.brush( colorGroup, QPalette::Mid ) );

    painter->drawPath( path );
}

static void qwtDrawTriangleNeedle( QPainter *painter,
    const QPalette &palette, QPalette::ColorGroup colorGroup,
    double length )
{
    const double width = qRound( length / 3.0 );

    QPainterPath path[4];

    path[0].lineTo( length, 0.0 );
    path[0].lineTo( 0.0, width / 2 );

    path[1].lineTo( length, 0.0 );
    path[1].lineTo( 0.0, -width / 2 );

    path[2].lineTo( -length, 0.0 );
    path[2].lineTo( 0.0, width / 2 );

    path[3].lineTo( -length, 0.0 );
    path[3].lineTo( 0.0, -width / 2 );


    const int colorOffset =  10;
    const QColor darkColor = palette.color( colorGroup, QPalette::Dark );
    const QColor lightColor = palette.color( colorGroup, QPalette::Light );

    QColor color[4];
    color[0] = darkColor.light( 100 + colorOffset );
    color[1] = darkColor.dark( 100 + colorOffset );
    color[2] = lightColor.light( 100 + colorOffset );
    color[3] = lightColor.dark( 100 + colorOffset );

    painter->setPen( Qt::NoPen );

    for ( int i = 0; i < 4; i++ )
    {
        painter->setBrush( color[i] );
        painter->drawPath( path[i] );
    }
}

//! Constructor
QwtDialNeedle::QwtDialNeedle():
    d_palette( QApplication::palette() )
{
}

//! Destructor
QwtDialNeedle::~QwtDialNeedle()
{
}

/*!
    Sets the palette for the needle.

    \param palette New Palette
*/
void QwtDialNeedle::setPalette( const QPalette &palette )
{
    d_palette = palette;
}

/*!
  \return the palette of the needle.
*/
const QPalette &QwtDialNeedle::palette() const
{
    return d_palette;
}

/*!
  Draw the needle

  \param painter Painter
  \param center Center of the dial, start position for the needle
  \param length Length of the needle
  \param direction Direction of the needle, in degrees counter clockwise
  \param colorGroup Color group, used for painting
*/
void QwtDialNeedle::draw( QPainter *painter, 
    const QPointF &center, double length, double direction, 
    QPalette::ColorGroup colorGroup ) const
{
    painter->save();

    painter->translate( center );
    painter->rotate( -direction );

    drawNeedle( painter, length, colorGroup );

    painter->restore();
}

//!  Draw the knob
void QwtDialNeedle::drawKnob( QPainter *painter,
    double width, const QBrush &brush, bool sunken ) const
{
    QPalette palette( brush.color() );

    QColor c1 = palette.color( QPalette::Light );
    QColor c2 = palette.color( QPalette::Dark );

    if ( sunken )
        qSwap( c1, c2 );

    QRectF rect( 0.0, 0.0, width, width );
    rect.moveCenter( painter->combinedTransform().map( QPointF() ) );

    QLinearGradient gradient( rect.topLeft(), rect.bottomRight() );
    gradient.setColorAt( 0.0, c1 );
    gradient.setColorAt( 0.3, c1 );
    gradient.setColorAt( 0.7, c2 );
    gradient.setColorAt( 1.0, c2 );

    painter->save();

    painter->resetTransform();

    painter->setPen( QPen( gradient, 1 ) );
    painter->setBrush( brush );
    painter->drawEllipse( rect );

    painter->restore();
}

/*!
  Constructor

  \param style Style
  \param hasKnob With/Without knob
  \param mid Middle color
  \param base Base color
*/
QwtDialSimpleNeedle::QwtDialSimpleNeedle( Style style, bool hasKnob,
        const QColor &mid, const QColor &base ):
    d_style( style ),
    d_hasKnob( hasKnob ),
    d_width( -1 )
{
    QPalette palette;
    palette.setColor( QPalette::Mid, mid );
    palette.setColor( QPalette::Base, base );

    setPalette( palette );
}

/*!
  Set the width of the needle
  \param width Width
  \sa width()
*/
void QwtDialSimpleNeedle::setWidth( double width )
{
    d_width = width;
}

/*!
  \return the width of the needle
  \sa setWidth()
*/
double QwtDialSimpleNeedle::width() const
{
    return d_width;
}

/*!
 Draw the needle

 \param painter Painter
 \param length Length of the needle
 \param colorGroup Color group, used for painting
*/
void QwtDialSimpleNeedle::drawNeedle( QPainter *painter, 
    double length, QPalette::ColorGroup colorGroup ) const
{
    double knobWidth = 0.0;
    double width = d_width;

    if ( d_style == Arrow )
    {
        if ( width <= 0.0 )
            width = qMax(length * 0.06, 6.0);

        qwtDrawArrowNeedle( painter, 
            palette(), colorGroup, length, width );

        knobWidth = qMin( width * 2.0, 0.2 * length );
    }
    else
    {
        if ( width <= 0.0 )
            width = 5.0;
        
        QPen pen ( palette().brush( colorGroup, QPalette::Mid ), width );
        pen.setCapStyle( Qt::FlatCap );
    
        painter->setPen( pen );
        painter->drawLine( QPointF( 0.0, 0.0 ), QPointF( length, 0.0 ) );

        knobWidth = qMax( width * 3.0, 5.0 );
    }

    if ( d_hasKnob && knobWidth > 0.0 )
    {
        drawKnob( painter, knobWidth,
            palette().brush( colorGroup, QPalette::Base ), false );
    }
}

//! Constructor
QwtCompassMagnetNeedle::QwtCompassMagnetNeedle( Style style,
        const QColor &light, const QColor &dark ):
    d_style( style )
{
    QPalette palette;
    palette.setColor( QPalette::Light, light );
    palette.setColor( QPalette::Dark, dark );
    palette.setColor( QPalette::Base, Qt::gray );

    setPalette( palette );
}

/*!
    Draw the needle

    \param painter Painter
    \param length Length of the needle
    \param colorGroup Color group, used for painting
*/
void QwtCompassMagnetNeedle::drawNeedle( QPainter *painter, 
    double length, QPalette::ColorGroup colorGroup ) const
{
    if ( d_style == ThinStyle )
    {
        const double width = qMax( length / 6.0, 3.0 );

        const int colorOffset = 10;

        const QColor light = palette().color( colorGroup, QPalette::Light );
        const QColor dark = palette().color( colorGroup, QPalette::Dark );

        qwtDrawShadedPointer( painter,
            dark.light( 100 + colorOffset ),
            dark.dark( 100 + colorOffset ),
            length, width );
        
        painter->rotate( 180.0 );
    
        qwtDrawShadedPointer( painter,
            light.light( 100 + colorOffset ),
            light.dark( 100 + colorOffset ),
            length, width );
        
        const QBrush baseBrush = palette().brush( colorGroup, QPalette::Base );
        drawKnob( painter, width, baseBrush, true );
    }
    else
    {
        qwtDrawTriangleNeedle( painter, palette(), colorGroup, length );
    }
}

/*!
   Constructor

   \param style Arrow style
   \param light Light color
   \param dark Dark color
*/
QwtCompassWindArrow::QwtCompassWindArrow( Style style,
        const QColor &light, const QColor &dark ):
    d_style( style )
{
    QPalette palette;
    palette.setColor( QPalette::Light, light );
    palette.setColor( QPalette::Dark, dark );

    setPalette( palette );
}

/*!
 Draw the needle

 \param painter Painter
 \param length Length of the needle
 \param colorGroup Color group, used for painting
*/
void QwtCompassWindArrow::drawNeedle( QPainter *painter, 
    double length, QPalette::ColorGroup colorGroup ) const
{
    if ( d_style == Style1 )
        qwtDrawStyle1Needle( painter, palette(), colorGroup, length );
    else
        qwtDrawStyle2Needle( painter, palette(), colorGroup, length );
}
