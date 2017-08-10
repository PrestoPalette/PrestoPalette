#include <QDebug>
#include <qdrawutil.h>
#include <QStyleOptionComplex>

#include "lightingsliderstyle.h"

QRect LightingSliderStyle::subControlRect(ComplexControl control,
					  const QStyleOptionComplex *option,
					  SubControl subControl,
					  const QWidget *widget) const
{
	QRect rect;
    int tickOffset = 0;
    int thickness = 21;  // height
    int len = 21;  // width

    if (control == CC_Slider)
    {
        if (const QStyleOptionSlider *slider = qstyleoption_cast<const QStyleOptionSlider *>(option))
        {
             bool horizontal = slider->orientation == Qt::Horizontal;

            if (subControl == SC_SliderHandle)
            {
                int sliderPos = sliderPositionFromValue(slider->minimum, slider->maximum + 1, slider->sliderPosition, (horizontal ? slider->rect.width() : slider->rect.height()) - len, slider->upsideDown);

                if (horizontal)
                    rect.setRect(slider->rect.x() +  sliderPos, slider->rect.y() +  tickOffset, len, thickness);
                else
                    rect.setRect(slider->rect.x() +  tickOffset, slider->rect.y() +  sliderPos, thickness, len);
            }

            if (subControl == SC_SliderGroove)
            {
                if (horizontal)
                    rect.setRect(slider->rect.x(), slider->rect.y() + tickOffset, slider->rect.width(), thickness);
                else
                    rect.setRect(slider->rect.x() + tickOffset, slider->rect.y(), thickness, slider->rect.height());
            }

            return visualRect(slider->direction, slider->rect, rect);
        }
    }

    return QCommonStyle::subControlRect(control, option, subControl, widget);

}

void LightingSliderStyle::drawComplexControl(QStyle::ComplexControl control,
					     const QStyleOptionComplex *option,
					     QPainter *painter,
					     const QWidget *widget) const
{
	if (control == CC_Slider)
	{
		if (const QStyleOptionSlider *slider = qstyleoption_cast<const QStyleOptionSlider *>(option))
		{
			QRect groove = subControlRect(CC_Slider, slider, SC_SliderGroove, widget);
			QRect handle = subControlRect(CC_Slider, slider, SC_SliderHandle, widget);

			if ((slider->subControls & SC_SliderGroove) && groove.isValid())
			{
				Qt::BGMode oldMode = painter->backgroundMode();
				painter->setBackgroundMode(Qt::TransparentMode);
				painter->drawPixmap(groove, groovePixmap);
				painter->setBackgroundMode(oldMode);
			}

			if ((slider->subControls & SC_SliderHandle) && handle.isValid())
			{
				Qt::BGMode oldMode = painter->backgroundMode();
				painter->setBackgroundMode(Qt::TransparentMode);
				painter->drawPixmap(handle, handlePixmap);
				painter->setBackgroundMode(oldMode);
			}
		}
	}
	else
	{
		QProxyStyle::drawComplexControl(control, option, painter, widget);
	}
}

int LightingSliderStyle::styleHint(QStyle::StyleHint hint,
				   const QStyleOption *option = 0,
				   const QWidget *widget = 0,
				   QStyleHintReturn *returnData = 0) const
{
	if (hint == QStyle::SH_Slider_AbsoluteSetButtons)
	{
		return (Qt::LeftButton | Qt::MidButton);
	}

	return QProxyStyle::styleHint(hint, option, widget, returnData);
}

void LightingSliderStyle::setColor(QColor ambientColor)
{
	QImage alphaMask(grooveMaskPixmap.toImage());

	QImage bg = QPixmap(QString::fromUtf8(":/main/graphics/AlphaSliderBG.png")).toImage();

	qreal r, g, b, alpha;
	r = ambientColor.redF();
	g = ambientColor.greenF();
	b = ambientColor.blueF();

	for (int x = 0; x < alphaMask.width(); x++)
	{
		for (int y = 0; y < alphaMask.height(); y++)
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
