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
	QPixmap grooveMaskPixmap;
	QPixmap groovePixmap;
	QPixmap handlePixmap;
	bool _blendWhite;

      public:
	LightingSliderStyle(QStyle *style, QString handleImage, QString backgroundImage, bool blendWhite = false)
	    : QProxyStyle(style)
	{
		setColor(QColor::fromRgba(0));

		this->handlePixmap = QPixmap(QString(handleImage));
		this->grooveMaskPixmap = QPixmap(QString(backgroundImage));
		this->_blendWhite = blendWhite;
	}

	void drawComplexControl(QStyle::ComplexControl control, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget) const;

	QRect subControlRect(ComplexControl cc, const QStyleOptionComplex *opt, SubControl sc, const QWidget *widget) const;

	int styleHint(QStyle::StyleHint hint, const QStyleOption *option,
		      const QWidget *widget, QStyleHintReturn *returnData) const;

	void setColor(QColor color);
};

#endif // LIGHTINGSLIDERSTYLE_H
