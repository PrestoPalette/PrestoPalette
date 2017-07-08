#include <QDebug>
#include <qdrawutil.h>

#include "lightingsliderstyle.h"

void LightingSliderStyle::drawComplexControl(QStyle::ComplexControl control, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget) const
{
	const QStyleOptionComplex *opt;
	QPainter *p;

	opt = option;
	p = painter;

	if (control == CC_Slider)
	{
		if (const QStyleOptionSlider *slider = qstyleoption_cast<const QStyleOptionSlider *>(opt))
		{
			QRect groove = subControlRect(CC_Slider, slider, SC_SliderGroove, widget);
			QRect handle = subControlRect(CC_Slider, slider, SC_SliderHandle, widget);

			if ((slider->subControls & SC_SliderGroove) && groove.isValid())
			{

				Qt::BGMode oldMode = p->backgroundMode();
				p->setBackgroundMode(Qt::TransparentMode);
				p->drawPixmap(widget->rect(), groovePixmap);
				p->setBackgroundMode(oldMode);
			}

			if (slider->subControls & SC_SliderHandle)
			{
				Qt::BGMode oldMode = p->backgroundMode();
				p->setBackgroundMode(Qt::TransparentMode);
				auto handlePixMap = QPixmap(_handleImage);
				p->drawPixmap(handle.x(), handle.y(), handlePixMap);
				p->setBackgroundMode(oldMode);
			}
		}
	}
	else
	{
		QProxyStyle::drawComplexControl(control, option, painter, widget);
	}
}

int LightingSliderStyle::styleHint(QStyle::StyleHint hint,
				   const QStyleOption *option = 0, const QWidget *widget = 0,
				   QStyleHintReturn *returnData = 0) const
{
	if (hint == QStyle::SH_Slider_AbsoluteSetButtons)
		return (Qt::LeftButton | Qt::MidButton);
	return QProxyStyle::styleHint(hint, option, widget, returnData);
}

void LightingSliderStyle::setColor(QColor ambientColor)
{
	groovePixmap = QPixmap(_backgroundImage);
	QImage alphaMask(groovePixmap.toImage());

	QImage bg = QPixmap(QString::fromUtf8(":/main/graphics/AlphaSliderBG.png")).toImage();

	qreal r, g, b, alpha;
	r = ambientColor.redF();
	g = ambientColor.greenF();
	b = ambientColor.blueF();

	for(int x = 0; x < alphaMask.width(); x++)
	{
		for(int y = 0; y < alphaMask.height(); y++)
		{
			alpha = alphaMask.pixelColor(x, y).alphaF();

			if (this->_blendWhite)
			{
				QColor backgroundColor = bg.pixelColor(x, y);

				// alpha blending equation
				// out = alpha * new + (1 - alpha) * old
				// since we are blending with white and white is 1.0, it drops out of the equation
				qreal rn, gn, bn;
				rn = alpha + (1.0f - alpha) * r;
				gn = alpha + (1.0f - alpha) * g;
				bn = alpha + (1.0f - alpha) * b;
				alphaMask.setPixelColor(x, y, QColor::fromRgbF(rn, gn, bn, backgroundColor.alphaF()));
			}
			else
			{
				alphaMask.setPixelColor(x, y, QColor::fromRgbF(r, g, b, alpha));
			}
		}
	}

	groovePixmap = QPixmap::fromImage(alphaMask);
}
