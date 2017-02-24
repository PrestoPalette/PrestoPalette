#include "circlepalette.h"

#include <QEvent>
#include <QPainter>

const qreal circleWidth = 14.0;

CirclePalette::CirclePalette(QLabel *parent) : QLabel(parent)
{
	/* add three points to list */
	points.push_back(new QPoint());
	points.push_back(new QPoint());
	points.push_back(new QPoint());
}

bool CirclePalette::eventFilter( QObject* watched, QEvent* event )
{
	if (watched == this && event->type() == QEvent::Paint)
	{
		QPainter painter(this);

		for (auto p : this->points)
		{
			/* draw circle */
			QPen circlePen(Qt::blue);
			circlePen.setWidth(2);
			painter.setPen(circlePen);
			painter.drawEllipse(p->x()+50, p->y(), circleWidth, circleWidth);
		}

		/* draw line */
		QPen linePen(Qt::white);
		linePen.setWidth(1);
		painter.setPen(linePen);
		painter.drawLine(50, 50, 150, 100);
	}

	return false;
}
