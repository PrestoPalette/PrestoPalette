#ifndef LIGHTINGSLIDERSTYLE_H
#define LIGHTINGSLIDERSTYLE_H

#include <QObject>
#include <QWidget>
#include <QProxyStyle>
#include <QPainter>
#include <QStyleOption>
#include <QtWidgets/QCommonStyle>

class LightingSliderStyle : public QProxyStyle
{
    Q_OBJECT

public:
    LightingSliderStyle(QStyle *style)
	:QProxyStyle(style)
    {}

    ~LightingSliderStyle() {}

    void drawPrimitive(PrimitiveElement element, const QStyleOption *option,
		       QPainter *painter, const QWidget *widget) const;

    void drawComplexControl(QStyle::ComplexControl control, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget) const;

};


#endif // LIGHTINGSLIDERSTYLE_H
