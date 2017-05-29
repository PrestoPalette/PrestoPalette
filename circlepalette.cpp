#include "circlepalette.h"

#include <QEvent>
#include <QPainter>
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
#include <QtMath>
#include <QFileDialog>

#include <algorithm>

CirclePalette::CirclePalette(QWidget *parent) : QWidget(parent)
{
	lightingPic = QPixmap(QString::fromUtf8(":/main/graphics/LightingIcon.png"));

	circlePic = QPixmap(QString::fromUtf8(":/main/graphics/PrimaryHandle.png"));
	primaryRadius = (double)circlePic.width() / 2.0;

	gamutShape = PrestoPalette::GamutShapeNone;
	wheelShape = PrestoPalette::WheelShapeCourse;

	backgroundWheel = new QLabel(parent);
	backgroundWheel->setGeometry(QRect(44, 37, 549, 549));
	backgroundWheel->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/Wheel_BG.png")));
	backgroundWheel->setScaledContents(true);

	QRect wheelPostion = QRect(70, 62, 499, 499);

	colorWheel = new QLabel(parent);
	colorWheel->setGeometry(wheelPostion);
	colorWheel->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/YWheel_Course.png")));
	colorWheel->setScaledContents(true);
	colorWheel->raise();

	int radius = colorWheel->width() / 2;
	radius = (float)radius * 0.70;
	lighting = new QPoint(radius * 2.0, 40);

	drawnElements = new QWidget(parent);
	drawnElements->setGeometry(wheelPostion);
	drawnElements->raise();
	drawnElements->installEventFilter(this);

	setMouseTracking(true);

	this->installEventFilter(this);

	QMetaObject::connectSlotsByName(this);
}

void CirclePalette::_draw_primary_imp(QPainter &painter, QVector<QColor> *colors, QLabel *colorWheel, const QPoint &p, int circleRadius)
{
	QPoint p_center(p.x() - circleRadius, p.y() - circleRadius);

	painter.drawPixmap(p_center, circlePic);

	QColor color = colorWheel->pixmap()->toImage().pixelColor(p.x(), p.y());
	colors->append(color);
}

void CirclePalette::_draw_line_imp(QPainter &painter, QVector<QColor> *colors, QLabel *colorWheel, const QPoint &p1, const QPoint &p2, int circleRadius)
{
	// TODO Trim the lines, so they don't go into the circle

	QPen linePen(Qt::white);
	linePen.setWidth(3);
	painter.setPen(linePen);

	//TODO use the radius (9px) of the circles, then compute

	painter.drawLine(p1, p2);

	QPoint midpoint((p1.x() + p2.x()) / 2, (p1.y() + p2.y()) / 2);

	/* TODO use the image for these... */
	painter.setPen(QPen(Qt::white, 3));
	painter.drawEllipse(midpoint, circleRadius, circleRadius);

	QColor color = colorWheel->pixmap()->toImage().pixelColor(midpoint.x(), midpoint.y());
	colors->append(color);
}

void CirclePalette::_draw_centroid(QPainter &painter, QVector<QColor> *colors, QLabel *colorWheel, std::vector<QPoint*> &points, int circleRadius)
{
	QPoint centroid;

	for (auto p : points)
	{
		centroid += *p;
	}
	centroid /= points.size();

	// shift over the centroid (because the above is using top-left)
	centroid = QPoint(centroid.x() - circleRadius, centroid.y() - circleRadius);
	_draw_primary_imp(painter, colors, colorWheel, centroid, circleRadius);
}

struct tup
{
	QPoint *point;
	double angle; // in radians
};

bool sort_angles (struct tup i, struct tup j) { return (i.angle <= j.angle); }

bool CirclePalette::eventFilter(QObject* watched, QEvent* event)
{
	if (event->type() == QEvent::MouseMove)
	{
		const QMouseEvent* me = static_cast<const QMouseEvent*>(event);
		//might want to check the buttons here
		const QPoint p = me->pos(); //...or ->globalPos();

		if (_is_collision(colorWheel->pos(), colorWheel->width() / 2, p))
		{
			// TODO save off this image at the start -- not in this event
			QImage img = colorWheel->pixmap()->toImage();
			QColor color = img.pixelColor(p.x(), p.y());

			emit hoverColor(color);
		}
	}

	if (watched == drawnElements && event->type() == QEvent::Paint)
	{
		QPainter painter(drawnElements);

		QVector<QColor> colors;

		std::vector<QPoint*> sortedPoints;

		QPoint center = QPoint(drawnElements->width() / 2.0, drawnElements->height() / 2.0);

		/* draw the lighting icon */
		if(enableLighting)
		{
			painter.drawPixmap(*lighting, lightingPic);

			QColor lightingColor = colorWheel->pixmap()->toImage().pixelColor(lighting->x(), lighting->y());

			if (this->lightingColor != lightingColor)
			{
				this->lightingColor = lightingColor;

				// notify that colors changed
				emit lightingColorChanged(lightingColor);
			}
		}

		std::list<struct tup> intermediaryPoints;

		for (auto p : this->points)
		{
			auto t = QPoint(p->x(), p->y());
			t = t - center;

			p->setX(t.x());
			p->setY(t.y());

			struct tup r;
			if (p->x() == 0)
			{
				r.angle = -3.14159265;
			}
			else if (p->x() < 0)
			{
				r.angle -= M_PI_4;
			}
			else
			{
				r.angle = atan(p->y() / p->x());
			}

			r.angle += M_PI;

			// go back a bit for the sections being not aligned to top
			// this is 1/2 a section
			r.angle += 15.0 * M_PI / 180.0;

			// rotate backwards by pi/2 radians
			//r.angle -= M_PI_2;

			r.point = p;
			intermediaryPoints.push_back(r);

		};

		//std::sort(intermediaryPoints.begin(), intermediaryPoints.end(), sort_angles);
		intermediaryPoints.sort(sort_angles);

		// rotate by 1
		//intermediaryPoints.push_back(*intermediaryPoints.begin());
		//intermediaryPoints.pop_front();

		int index = 0;
		for (auto i : intermediaryPoints)
		{
			//qInfo() << "hi " << index << *i.point << " angle " << i.angle;
			index++;

			auto t = QPoint(i.point->x(), i.point->y());
			t = t + center;

			i.point->setX(t.x());
			i.point->setY(t.y());

			sortedPoints.push_back(i.point);
		};

		if (gamutShape == PrestoPalette::GamutShapeLine)
		{
			_draw_primary_imp(painter, &colors, colorWheel, *sortedPoints[0], primaryRadius);
			_draw_primary_imp(painter, &colors, colorWheel, *sortedPoints[1], primaryRadius);
			_draw_line_imp(painter, &colors, colorWheel, *sortedPoints[0], *this->points[1], secondaryRadius);
		}

		if (gamutShape == PrestoPalette::GamutShapeTriangle)
		{
			_draw_primary_imp(painter, &colors, colorWheel, *sortedPoints[0], primaryRadius);
			_draw_line_imp(painter, &colors, colorWheel, *sortedPoints[0], *sortedPoints[1], secondaryRadius);
			_draw_primary_imp(painter, &colors, colorWheel, *sortedPoints[1], primaryRadius);
			_draw_line_imp(painter, &colors, colorWheel, *sortedPoints[1], *sortedPoints[2], secondaryRadius);
			_draw_primary_imp(painter, &colors, colorWheel, *sortedPoints[2], primaryRadius);
			_draw_line_imp(painter, &colors, colorWheel, *sortedPoints[2], *sortedPoints[0], secondaryRadius);
			_draw_centroid(painter, &colors, colorWheel, sortedPoints, centroidRadius);
		}

		if (gamutShape == PrestoPalette::GamutShapeSquare)
		{
			_draw_primary_imp(painter, &colors, colorWheel, *sortedPoints[0], primaryRadius);
			_draw_line_imp(painter, &colors, colorWheel, *sortedPoints[0], *sortedPoints[1], secondaryRadius);
			_draw_primary_imp(painter, &colors, colorWheel, *sortedPoints[1], primaryRadius);
			_draw_line_imp(painter, &colors, colorWheel, *sortedPoints[1], *sortedPoints[3], secondaryRadius);
			_draw_primary_imp(painter, &colors, colorWheel, *sortedPoints[2], primaryRadius);
			_draw_line_imp(painter, &colors, colorWheel, *sortedPoints[2], *sortedPoints[3], secondaryRadius);
			_draw_primary_imp(painter, &colors, colorWheel, *sortedPoints[3], primaryRadius);
			_draw_line_imp(painter, &colors, colorWheel, *sortedPoints[0], *sortedPoints[2], secondaryRadius);

			_draw_centroid(painter, &colors, colorWheel, sortedPoints, centroidRadius);
		}

		if (this->selectedColors != colors)
		{
			this->selectedColors = colors;

			// notify that colors changed
			emit selectedColorsChanged();
		}
	}

	return false;
}

bool CirclePalette::_is_collision(const QPoint &circle, int circleRadius, const QPoint &hitTest)
{
	QPoint circleCenter = QPoint(circle.x() + circleRadius, circle.y() + circleRadius);
	int r2 = circleRadius * circleRadius;
	int d2 = (hitTest.x() - circleCenter.x()) * (hitTest.x() - circleCenter.x())
			+
	(hitTest.y() - circleCenter.y()) * (hitTest.y() - circleCenter.y());

	if (d2 <= r2)
	{
		//qInfo() << "pos: " << hitTest << " center: " << circleCenter << " radius: " << circleRadius;
		return true;
	}
	else
	{
		//qInfo() << "NO: pos: " << hitTest << " center: " << circleCenter << " radius: " << circleRadius;
		return false;
	}
}

void CirclePalette::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		if (this->isDragging == false)
		{
			// check for collisions with the points
			// http://math.stackexchange.com/questions/198764/how-to-know-if-a-point-is-inside-a-circle
			for (auto p : this->points)
			{
				if (_is_collision(*p, primaryRadius * 3.0, event->pos()))
				{
					this->dragStartPosition = event->pos();
					this->isDragging = true;
					this->dragPoint = p;
					this->relativeDistance = dragStartPosition - *p;
					//qInfo() << "CLICK: " << event->pos() << " CIRCLE: " << *p;
					return;
				}
			}

			if (enableLighting)
			{
				if (_is_collision(*lighting, primaryRadius * 3.0, event->pos()))
				{
					this->dragStartPosition = event->pos();
					this->isDragging = true;
					this->dragPoint = lighting;
					this->relativeDistance = dragStartPosition - *lighting;
					//qInfo() << "CLICK: " << event->pos() << " LIGHTING: " << *lighting;
					return;
				}
			}
		}
	}
}

void CirclePalette::mouseReleaseEvent(QMouseEvent *event)
{
	if (isDragging)
	{
		this->isDragging = false;
		this->dragStartPosition = QPoint();
		this->dragPoint = NULL;
	}
}

void CirclePalette::mouseMoveEvent(QMouseEvent *event)
{
	if (isDragging)
	{
		//qInfo() << event->pos();
		//qInfo() << this->relativeDistance;
		*this->dragPoint = (event->pos() - this->relativeDistance);
		this->drawnElements->repaint();
	}
}

void CirclePalette::create_gamut_line()
{
	int radius = colorWheel->width() / 2;
	radius = (float)radius * 0.80; //not using whole radius
	auto center = QPoint(colorWheel->width() / 2, colorWheel->height() / 2);
	auto ang60 = qDegreesToRadians(60.0);

	auto pFirst = new QPoint(qCos(ang60) * radius, qSin(ang60) * radius);
	auto pSecond = new QPoint(*pFirst + QPoint(radius, radius));

	points.push_back(pFirst);
	points.push_back(pSecond);
}

void CirclePalette::create_gamut_triangle()
{
	int radius = colorWheel->width() / 2;
	radius = radius * 0.80; //not using whole radius
	auto center = QPoint(colorWheel->width() / 2, colorWheel->height() / 2);
	auto ang60 = qDegreesToRadians(60.0);

	/* add three points to list */

	/* bottom */
	auto pBottom = new QPoint(center + QPoint(0, radius));
	auto pTopLeft = new QPoint(qCos(ang60) * radius, qSin(ang60) * radius);

	auto line = QLineF(pTopLeft->x(), pTopLeft->y(), pBottom->x(), pBottom->y());

	auto l = line.length();

	auto pTopRight = new QPoint(pTopLeft->x() + l, pTopLeft->y());

	points.push_back(pBottom);
	points.push_back(pTopLeft);
	points.push_back(pTopRight);
}

void CirclePalette::create_gamut_square()
{
	int radius = colorWheel->width() / 2;
	radius = radius * 0.80; //not using whole radius
	auto center = QPoint(colorWheel->width() / 2, colorWheel->height() / 2);
	auto ang60 = qDegreesToRadians(60.0);

	auto pFirst = new QPoint(qCos(ang60) * radius, qSin(ang60) * radius);
	auto pSecond = new QPoint(*pFirst + QPoint(radius, 0));
	auto pThird = new QPoint(*pFirst + QPoint(0, radius));
	auto pFourth = new QPoint(*pFirst + QPoint(radius, radius));

	points.push_back(pFirst);
	points.push_back(pSecond);
	points.push_back(pThird);
	points.push_back(pFourth);
}

void CirclePalette::destroy_gamut()
{
	for (auto p : this->points)
	{
		delete p;
	}
	this->points.clear();

	mouseReleaseEvent(NULL);

	gamutShape = PrestoPalette::GamutShapeNone;
}

void CirclePalette::ChangeGamutShape(PrestoPalette::GlobalGamutShape shape)
{
	if (shape != gamutShape)
	{
		destroy_gamut();
	}

	gamutShape = shape;

	if (gamutShape == PrestoPalette::GamutShapeLine)
	{
		create_gamut_line();
	}

	if (gamutShape == PrestoPalette::GamutShapeTriangle)
	{
		create_gamut_triangle();
	}

	if (gamutShape == PrestoPalette::GamutShapeSquare)
	{
		create_gamut_square();
	}

	this->drawnElements->repaint();
}

void CirclePalette::ChangeWheelShape(PrestoPalette::GlobalWheelShape shape)
{
	wheelShape = shape;

	switch(wheelShape)
	{
	case PrestoPalette::GlobalWheelShape::WheelShapeCourse:
		colorWheel->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/YWheel_Course.png")));
		break;
	case PrestoPalette::GlobalWheelShape::WheelShapeFine:
		colorWheel->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/YWheel_Fine.png")));
		break;
	default:
		// not sure what to do here
		break;
	}
}
