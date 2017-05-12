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
	// remove existing widgets
	for(auto s : swatches)
	{
		layout->removeWidget(s);
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
			swatch->setStyleSheet("\
			QLabel {\
			border: 0; \
			margin: 0px 0px 0px 0px; \
			}");

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

	/*for (int y = 0; y < col_height; y++)
	{
		for (int x = 0; x < row_width; x++)
		{
			//setColorAt(x, y, Qt::gray);
		}
	}*/
}

void VisualPalette::_setColor(int column, int row, QColor &combinedColor, qreal componentMultiplier, qreal ambientColorAlpha, bool enableLighting, QColor &ambientColor, qreal ambientColorBrightness)
{
	QColor newColor;

	// alpha blending equation
	// out = alpha * new + (1 - alpha) * old
	if (enableLighting)
	{
		newColor = QColor(ambientColorAlpha * ambientColor.red() + (1.0f - ambientColorAlpha) * combinedColor.red(), ambientColorAlpha * ambientColor.green() + (1.0f - ambientColorAlpha) * combinedColor.green(), ambientColorAlpha * ambientColor.blue() + (1.0f - ambientColorAlpha) * combinedColor.blue());
	}
	else
	{
		newColor = combinedColor;
	}

	newColor = QColor(newColor.red() * componentMultiplier, newColor.green() * componentMultiplier, newColor.blue() * componentMultiplier);

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
		midLine = 1;
	}

	if ((this->lastMixString != mixString) || (this->lastTotalColors != totalColors))
	{
		this->lastMixString = mixString;
		this->lastTotalColors = totalColors;

		resetSwatches();
	}

	float lastLineFactor =  1.0f;

	// set the midline first
	for (int i = 0; i < totalColors; i++)
	{
		_setColor(i, midLine, combinedColors[i], lastLineFactor, ambientColorAlpha, enableLighting, ambientColor, ambientColorBrightness);
	}

	// first and last lines
	if (mixString > 1)
	{
		if (mixString == 5)
		{
			lastLineFactor = 0.7f;
		}

		for (int i = 0; i < totalColors; i++)
		{
			_setColor(i, 0, combinedColors[i], stringLight * lastLineFactor, ambientColorAlpha, enableLighting, ambientColor, ambientColorBrightness);
		}

		for (int i = 0; i < totalColors; i++)
		{
			_setColor(i, mixString - 1, combinedColors[i], stringDark * lastLineFactor, ambientColorAlpha, enableLighting, ambientColor, ambientColorBrightness);
		}
	}

	// 2nd and 4th lines
	if (mixString == 5)
	{
		lastLineFactor = 0.8f;

		for (int i = 0; i < totalColors; i++)
		{
			_setColor(i, 1, combinedColors[i], stringLight * lastLineFactor, ambientColorAlpha, enableLighting, ambientColor, ambientColorBrightness);
		}

		for (int i = 0; i < totalColors; i++)
		{
			_setColor(i, 3, combinedColors[i], stringDark * lastLineFactor, ambientColorAlpha, enableLighting, ambientColor, ambientColorBrightness);
		}
	}
}
