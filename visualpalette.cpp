#include "visualpalette.h"
#include <math.h>
#include <QDebug>
#include <QBitmap>
#include <QtMath>
#include <QEvent>
#include <QMouseEvent>

#define DEFAULT_PALETTE_WIDTH 9.0
#define DEFAULT_PALETTE_HEIGHT 5.0

template<class T>
const T& clamp(const T& x, const T& lower, const T& upper) {
	if (x < lower) return lower;
	if (x > upper) return upper;
	return x;
}

VisualPalette::VisualPalette(QWidget *parent) : QWidget(parent)
{
	layout = new QGridLayout(this);
	this->setLayout(layout);

	paletteWidth = 7;
	paletteHeight = 5;

	resetSwatches();

	setMouseTracking(true);
	installEventFilter(this);
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

	QPixmap pm = QPixmap(":/main/graphics/PaintSwatch.png");
	QPixmap pxr = QPixmap(pm.size());
	pxr.fill(fillColor);
	pxr.setMask(pm.createMaskFromColor(Qt::transparent));
	swatch->setPixmap(pxr);

	swatch->setScaledContents(true);
}

void VisualPalette::resetSwatches()
{
	if (layout->count() == 0)
	{
		for (int y = 0; y < DEFAULT_PALETTE_HEIGHT; y++)
		{
			for (int x = 0; x < DEFAULT_PALETTE_WIDTH; x++)
			{
				auto swatch = new QLabel(this);

				swatch->setMouseTracking(true);

				layout->addWidget(swatch, y, x);
				layout->setSpacing(0);
			}
		}
	}

	for (int y = 0; y < DEFAULT_PALETTE_HEIGHT; y++)
	{
		for (int x = 0; x < DEFAULT_PALETTE_WIDTH; x++)
		{
			setColorAt(x, y, QColor(0.0, 0.0, 0.0, 0.0));
		}
	}
}

void VisualPalette::_setColor(int column, int row, QColor &unmodifiedColor, qreal light_darkMultiplier, qreal ambientColorAlpha, bool enableLighting, QColor &in_ambientColor, qreal ambientColorBrightness, bool interpolate, bool go_dark)
{
	QColor newColor;
	QColor ambientColor = in_ambientColor;
	qreal r, g, b, light_r, light_g, light_b, litOriginal_r, litOriginal_g, litOriginal_b;

	r = unmodifiedColor.redF();
	g = unmodifiedColor.greenF();
	b = unmodifiedColor.blueF();

	/* used to calculate the interpolated color */
	litOriginal_r = r;
	litOriginal_g = g;
	litOriginal_b = b;

	if (light_darkMultiplier != 0)
	{
		if (go_dark ==false)
		{
			QColor lighter = QColor::fromRgbF(clamp(r, 0.0, 1.0), clamp(g, 0.0, 1.0), clamp(b, 0.0, 1.0));

			/*if (column == 2)
			{
				if (row == 0)
				{
					qInfo() << "start";
					qInfo() << "h: " << lighter.hsvHueF() << " s:" << lighter.hsvSaturationF() << " l:" << lighter.valueF();
					qInfo() << "(1.0 - lighter.valueF(): " << (1.0 - lighter.valueF()) << " ((1.0 - lighter.valueF()) * light_darkMultiplier):" << ((1.0 - lighter.valueF()) * light_darkMultiplier) << " ((1.0 - lighter.valueF()) * light_darkMultiplier) + lighter.valueF():" << (((1.0 - lighter.valueF()) * light_darkMultiplier) + lighter.valueF());
					qInfo() << "(1.0 - lighter.valueF(): " << 255 * (1.0 - lighter.valueF()) << " ((1.0 - lighter.valueF()) * light_darkMultiplier):" << 255 * ((1.0 - lighter.valueF()) * light_darkMultiplier) << " ((1.0 - lighter.valueF()) * light_darkMultiplier) + lighter.valueF():" << 255 * (((1.0 - lighter.valueF()) * light_darkMultiplier) + lighter.valueF());
				}
			}*/

			// get closer to zero
			qreal newSaturation = (1.0 - light_darkMultiplier) * lighter.hsvSaturationF();

			// get closer to 1.0
			qreal newLuminosity = ((1.0 - lighter.valueF()) * light_darkMultiplier) + lighter.valueF();

			lighter = QColor::fromHsvF(lighter.hsvHueF(), clamp(newSaturation, 0.0, 1.0), clamp(newLuminosity, 0.0, 1.0));
			r = lighter.redF();
			g = lighter.greenF();
			b = lighter.blueF();

			/*if (column == 2)
			{
				if (row == 0)
				{
					qInfo() << "h: " << lighter.hsvHueF() << " s:" << lighter.hsvSaturationF() << " l:" << lighter.valueF();
					qInfo() << "r: " << lighter.redF() << " g:" << lighter.greenF() << " b:" << lighter.blueF();
					qInfo() << "r: " << r << " g:" << g << " b:" << b;
					qInfo() << "end";
				}
			}*/
		}
		else
		{
			r = r * light_darkMultiplier;
			g = g * light_darkMultiplier;
			b = b * light_darkMultiplier;
		}
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

	/* light it LAST */
	if (enableLighting)
	{
		/*
		 * Figure out the light's color
		 */

		// get closer to zero
		qreal newLightSaturation = (1.0 - ambientColorBrightness) * ambientColor.hsvSaturationF();

		// get closer to 1.0
		qreal newLightLuminosity = ((1.0 - ambientColor.valueF()) * ambientColorBrightness) + ambientColor.valueF();

		// create new light color using new saturation and value
		ambientColor = QColor::fromHsvF(ambientColor.hsvHueF(), clamp(newLightSaturation, 0.0, 1.0), clamp(newLightLuminosity, 0.0, 1.0));

		// now multiply color blend
		light_r = r * ambientColor.redF();
		light_g = g * ambientColor.greenF();
		light_b = b * ambientColor.blueF();

		/* last, alpha blend the color over the original  */
		r = ambientColorAlpha * light_r + (1.0f - ambientColorAlpha) * r;
		g = ambientColorAlpha * light_g + (1.0f - ambientColorAlpha) * g;
		b = ambientColorAlpha * light_b + (1.0f - ambientColorAlpha) * b;
	}

	newColor = QColor::fromRgbF(clamp(r, 0.0, 1.0), clamp(g, 0.0, 1.0), clamp(b, 0.0, 1.0));

	setColorAt(column, row, newColor);
}

void VisualPalette::Formulate(QVector<QColor> combinedColors, QVector<QColor> primaryColors, QVector<QColor> secondaryColors,
			      QColor neutral, int paletteHeight, qreal stringLight, qreal stringDark,
			      bool enableLighting, QColor ambientColor, qreal ambientColorBrightness,
			      qreal ambientColorAlpha)
{
	// top line moves closer to white
	// second line linear interpolates between middle and top
	// third line is un-modified
	// fourth line is linear interpolated between middle and bottom
	// bottom line moves closer to black

	int paletteWidth = combinedColors.length();

	int midLine = 2;

	this->paletteHeight = paletteHeight;
	this->paletteWidth = paletteWidth;
	resetSwatches();

	int startingColumn = clamp(((DEFAULT_PALETTE_WIDTH - paletteWidth) / 2.0), 0.0, (double)paletteWidth + 1);
	int startingRow = clamp(((DEFAULT_PALETTE_HEIGHT - paletteHeight) / 2.0), 0.0, (double)paletteHeight);

	// set the midline first
	for (int i = 0; i < paletteWidth; i++)
	{
		_setColor(i + startingColumn, midLine, combinedColors[i], 0.0, ambientColorAlpha, enableLighting, ambientColor, ambientColorBrightness, false, false);
	}

	// first and last lines
	if (paletteHeight > 1)
	{
		for (int i = 0; i < paletteWidth; i++)
		{
			_setColor(i + startingColumn, startingRow, combinedColors[i], stringLight, ambientColorAlpha, enableLighting, ambientColor, ambientColorBrightness, false, false);
		}

		for (int i = 0; i < paletteWidth; i++)
		{
			_setColor(i + startingColumn, midLine + (midLine - startingRow), combinedColors[i], 1.0f - stringDark, ambientColorAlpha, enableLighting, ambientColor, ambientColorBrightness, false, true);
		}
	}

	// 2nd and 4th lines
	if (paletteHeight == 5)
	{
		for (int i = 0; i < paletteWidth; i++)
		{
			_setColor(i + startingColumn, startingRow + 1, combinedColors[i], stringLight, ambientColorAlpha, enableLighting, ambientColor, ambientColorBrightness, true, false);
		}

		for (int i = 0; i < paletteWidth; i++)
		{
			_setColor(i + startingColumn, midLine + 1, combinedColors[i], 1.0f - stringDark, ambientColorAlpha, enableLighting, ambientColor, ambientColorBrightness, true, true);
		}
	}
}

bool VisualPalette::eventFilter(QObject* watched, QEvent* event)
{
	if (event->type() == QEvent::MouseMove)
	{
		const QMouseEvent* me = static_cast<const QMouseEvent*>(event);

		QPoint p = this->mapFromGlobal(QCursor::pos());
		int swatchWidth = this->width() / DEFAULT_PALETTE_WIDTH;
		int swatchHeight = this->height() / DEFAULT_PALETTE_HEIGHT;

		int row, column;
		row = p.y() / swatchHeight;
		column = p.x() / swatchWidth;

		QLabel *swatch;
		auto cell = this->layout->itemAtPosition(row, column);
		if (cell == NULL)
		{
			return false;
		}

		swatch = (QLabel *)(cell->widget());

		QColor color = swatch->pixmap()->toImage().pixelColor(50, 50);
		emit hoverColor(color);
	}

	return false;
}
