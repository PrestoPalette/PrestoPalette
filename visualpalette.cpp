#include "visualpalette.h"
#include <math.h>

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
