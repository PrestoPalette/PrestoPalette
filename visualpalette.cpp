#include "visualpalette.h"
#include <math.h>
#include <QDebug>
#include <QBitmap>

VisualPalette::VisualPalette(QWidget *parent) : QWidget(parent)
{
	layout = new QGridLayout(this);
	this->setLayout(layout);

	lastTotalColors = 7;
	lastMixString = 5;

	resetSwatches();
}

void VisualPalette::setColorAt(int column, int row, const QColor &fillColor)
{
	QLabel *swatch;
	auto cell = this->layout->itemAtPosition(row, column);
	if (cell == NULL)
	{
		return;
	}

	swatch = (QLabel *)this->layout->itemAtPosition(row, column)->widget();

	auto pm = new QPixmap(":/main/graphics/PaintSwatch.png");
	auto pxr = new QPixmap(pm->size());
	pxr->fill(fillColor);
	pxr->setMask(pm->createMaskFromColor(Qt::transparent));
	swatch->setPixmap(*pxr);

	swatch->setScaledContents(true);
}

void VisualPalette::resetSwatches()
{
	QLayoutItem *child;
	while ((child = layout->takeAt(0)) != 0)
	{
		QWidget* widget = child->widget();
		layout->removeWidget(widget);
		delete widget;
	}

	swatches.clear();

	swatches.reserve(lastTotalColors * lastMixString);

	int row_width = lastTotalColors;
	int col_height = lastMixString;

	for (int y = 0; y < col_height; y++)
	{
		for (int x = 0; x < row_width; x++)
		{
			auto swatch = new QLabel(this);

			/* with spaces between cells */
			/*swatch->setStyleSheet("\
			QLabel {\
			border: 0; \
			margin: 0px 0px 0px 0px; \
			}");*/

			/* with no space at all between cells */
			/*
			swatch->setStyleSheet("\
			QLabel {\
			border: 0; \
			margin: -13px -13px -13px -13px; \
			}");
			*/

			swatches.push_back(swatch);
			layout->addWidget(swatch, y, x);
			layout->setSpacing(0);
		}
	}
}

template<class T>
const T& clamp(const T& x, const T& lower, const T& upper) {
    return std::max(lower, std::min(x, upper));
}

void VisualPalette::_setColor(int column, int row, QColor &unmodifiedColor, qreal light_darkMultiplier, qreal ambientColorAlpha, bool enableLighting, QColor &in_ambientColor, qreal ambientColorBrightness, bool interpolate, bool go_dark)
{
	QColor newColor;
	QColor ambientColor = in_ambientColor;
	qreal r, g, b, light_r, light_g, light_b, litOriginal_r, litOriginal_g, litOriginal_b;

	r = (float)unmodifiedColor.red();
	g = (float)unmodifiedColor.green();
	b = (float)unmodifiedColor.blue();

	/* first light it */
	if (enableLighting)
	{
		light_r = ((255.0 - (float)ambientColor.red()) * ambientColorBrightness) + (float)ambientColor.red();
		light_g = ((255.0 - (float)ambientColor.green()) * ambientColorBrightness) + (float)ambientColor.green();
		light_b = ((255.0 - (float)ambientColor.blue()) * ambientColorBrightness) + (float)ambientColor.blue();

		// alpha blending equation
		// out = alpha * new + (1 - alpha) * old
		r = ambientColorAlpha * light_r + (1.0f - ambientColorAlpha) * r;
		g = ambientColorAlpha * light_g + (1.0f - ambientColorAlpha) * g;
		b = ambientColorAlpha * light_b + (1.0f - ambientColorAlpha) * b;
	}

	litOriginal_r = r;
	litOriginal_g = g;
	litOriginal_b = b;

	if (go_dark ==false)
	{
		r = ((255.0 - r) * light_darkMultiplier) + r;
		g = ((255.0 - g) * light_darkMultiplier) + g;
		b = ((255.0 - b) * light_darkMultiplier) + b;
	}
	else
	{
		r = r * light_darkMultiplier;
		g = g * light_darkMultiplier;
		b = b * light_darkMultiplier;
	}

	if (interpolate)
	{
		//(1 - t) * v0 + t * v1;
		// which direction?
		if(litOriginal_r < r)
		{
			r = (1.0 - 0.5f) * litOriginal_r + 0.5f * r;
			g = (1.0 - 0.5f) * litOriginal_g + 0.5f * g;
			b = (1.0 - 0.5f) * litOriginal_b + 0.5f * b;
		}
		else
		{
			r = (1.0 - 0.5f) * r + 0.5f * litOriginal_r;
			g = (1.0 - 0.5f) * g + 0.5f * litOriginal_g;
			b = (1.0 - 0.5f) * b + 0.5f * litOriginal_b;
		}
	}

	newColor = QColor(clamp(r, 0.0, 255.0), clamp(g, 0.0, 255.0), clamp(b, 0.0, 255.0));

	setColorAt(column, row, newColor);
}

void VisualPalette::Formulate(QVector<QColor> combinedColors, QVector<QColor> primaryColors, QVector<QColor> secondaryColors,
			      QColor neutral, int mixString, qreal stringLight, qreal stringDark,
			      bool enableLighting, QColor ambientColor, qreal ambientColorBrightness,
			      qreal ambientColorAlpha)
{
	/*
	 * Sort them clockwise order from hottest with is yellow.
	 * Use first in clockwise order
	 */

	// TODO -- sort the colors according to john's specification

	// top line moves closer to white
	// second line linear interpolates between middle and top
	// third line is un-modified
	// fourth line is linear interpolated between middle and bottom
	// bottom line moves closer to black

	int totalColors = combinedColors.length();

	int midLine;

	if (mixString == 3)
	{
		midLine = 1;
	}
	else if (mixString == 5)
	{
		midLine = 2;
	}
	else
	{
		midLine = 0;
	}

	// only call reset if necessary, otherwise, there will be flicker
	if ((this->lastMixString != mixString) || (this->lastTotalColors != totalColors))
	{
		this->lastMixString = mixString;
		this->lastTotalColors = totalColors;
		resetSwatches();
	}

	// set the midline first
	for (int i = 0; i < totalColors; i++)
	{
		_setColor(i, midLine, combinedColors[i], 0.0, ambientColorAlpha, enableLighting, ambientColor, ambientColorBrightness, false, false);
	}

	// first and last lines
	if (mixString > 1)
	{
		for (int i = 0; i < totalColors; i++)
		{
			_setColor(i, 0, combinedColors[i], stringLight, ambientColorAlpha, enableLighting, ambientColor, ambientColorBrightness, false, false);
		}

		for (int i = 0; i < totalColors; i++)
		{
			_setColor(i, mixString - 1, combinedColors[i], 1.0f - stringDark, ambientColorAlpha, enableLighting, ambientColor, ambientColorBrightness, false, true);
		}
	}

	// 2nd and 4th lines
	if (mixString == 5)
	{
		for (int i = 0; i < totalColors; i++)
		{
			_setColor(i, 1, combinedColors[i], stringLight, ambientColorAlpha, enableLighting, ambientColor, ambientColorBrightness, true, false);
		}

		for (int i = 0; i < totalColors; i++)
		{
			_setColor(i, 3, combinedColors[i], 1.0f - stringDark, ambientColorAlpha, enableLighting, ambientColor, ambientColorBrightness, true, true);
		}
	}
}
