#include "visualpalette.h"
#include <math.h>
#include <QDebug>
#include <QBitmap>

VisualPalette::VisualPalette(QWidget *parent) : QWidget(parent)
{
	layout = new QGridLayout(this);
	this->setLayout(layout);

	swatches.reserve(TOTAL_SWATCHES);

	int row_width = sqrt(TOTAL_SWATCHES);
	int col_height = row_width;

	for (int y = 0; y < col_height; y++)
	{
		for (int x = 0; x < row_width; x++)
		{
			auto swatch = new QLabel(this);

			swatch->setStyleSheet("\
			QLabel {\
			border: 0; \
			margin: 1px 1px 1px 1px; \
			}");

			layout->addWidget(swatch, x, y);
			layout->setSpacing(0);
		}
	}

	for (int y = 0; y < col_height; y++)
	{
		for (int x = 0; x < row_width; x++)
		{
			setColorAt(x, y, Qt::gray);
		}
	}
}

void VisualPalette::setColorAt(int row, int column, const QColor &fillColor)
{
	QLabel *swatch;
	swatch = (QLabel *)this->layout->itemAtPosition(row, column)->widget();

	auto pm = new QPixmap(":/main/graphics/PaintSwatch.png");
	auto pxr = new QPixmap(pm->size());
	pxr->fill(fillColor);
	pxr->setMask(pm->createMaskFromColor(Qt::transparent));
	swatch->setPixmap(*pxr);

	swatch->setScaledContents(true);
}

void VisualPalette::Formulate(QVector<QColor> seedColors)
{
	int row_width = sqrt(TOTAL_SWATCHES);
	int col_height = row_width;

	QColor color = Qt::black;

	for (int y = 0; y < col_height; y++)
	{
		color.setBlue(color.blue() + 10);

		for (int x = 0; x < row_width; x++)
		{
			int r, g, b;

			r = color.red();
			g = color.green();
			b = color.blue();

			r += 23;

			if (r > 255)
			{
				g += r - 255;
				r = 255;
			}

			if (g > 255)
			{
				b += g - 255;
				g = 255;
			}

			if (b > 255)
			{
				b = 255;
			}

			color.setRgb(r, g, b);
			setColorAt(x, y, color);
		}
	}
}
