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
private:
	QPixmap groovePixmap;
	QString _handleImage;
	QString _backgroundImage;
	bool _blendWhite;
public:
    LightingSliderStyle(QStyle *style, QString handleImage, QString backgroundImage, bool blendWhite = false)
	:QProxyStyle(style)
    {
	    setColor(QColor::fromRgba(0));

	    this->_handleImage = QString(handleImage);
	    this->_backgroundImage = QString(backgroundImage);
	    this->_blendWhite = blendWhite;
    }

    //void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    void drawComplexControl(QStyle::ComplexControl control, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget) const;

    int styleHint(QStyle::StyleHint hint, const QStyleOption* option,
    const QWidget* widget, QStyleHintReturn* returnData) const;

    void setColor(QColor color);
};


#endif // LIGHTINGSLIDERSTYLE_H
