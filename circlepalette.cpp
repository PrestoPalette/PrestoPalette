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

#define LIGHTING_ICON_MIDDLE_TO_TOP 7

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

	colorWheel = new QLabel(parent);
	colorWheel->setGeometry(QRect(70, 62, 499, 499));
	colorWheel->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/YWheel_Course.png")));
	colorWheel->raise();
	//colorWheel->installEventFilter(this);
	//colorWheel->setMouseTracking(true);

	lighting = new QPoint(325, 40);

	drawnElements = new QWidget(parent);
	drawnElements->setGeometry(colorWheel->geometry());
	drawnElements->raise();
	drawnElements->installEventFilter(this);

	//drawnElements->setMouseTracking(true);

	setMouseTracking(true);

	installEventFilter(this);

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
	if (event->type() == QEvent::MouseMove && (watched == this))
	{
		const QMouseEvent* me = static_cast<const QMouseEvent*>(event);

		QPoint p = colorWheel->mapFromGlobal(QCursor::pos());
		QPoint wheelCenter = QPoint(colorWheel->width() / 2, colorWheel->height() / 2);
		int radius = colorWheel->width() / 2;

		// prevent it from going off the edge of the whole circle palette
		if (isDragging)
		{
			if (_is_collision(wheelCenter, radius - primaryRadius, p) == false)
			{
				// end it
				return true;
			}
		}

		if (_is_collision(wheelCenter, radius, p))
		{
			QColor color = colorWheel->pixmap()->toImage().pixelColor(p.x(), p.y());

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
			painter.drawPixmap(QPoint(lighting->x() - (lightingPic.width() / 2),
						  lighting->y() - (lightingPic.height() / 2) + LIGHTING_ICON_MIDDLE_TO_TOP),
						  lightingPic);

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
			_draw_primary_imp(painter, &colors, colorWheel, *this->points[0], primaryRadius);
			_draw_primary_imp(painter, &colors, colorWheel, *this->points[1], primaryRadius);
			_draw_line_imp(painter, &colors, colorWheel, *this->points[0], *this->points[1], secondaryRadius);
		}

		if (gamutShape == PrestoPalette::GamutShapeTriangle)
		{
			_draw_primary_imp(painter, &colors, colorWheel, *this->points[0], primaryRadius);
			_draw_line_imp(painter, &colors, colorWheel, *this->points[0], *this->points[1], secondaryRadius);
			_draw_primary_imp(painter, &colors, colorWheel, *this->points[1], primaryRadius);
			_draw_line_imp(painter, &colors, colorWheel, *this->points[1], *this->points[2], secondaryRadius);
			_draw_primary_imp(painter, &colors, colorWheel, *this->points[2], primaryRadius);
			_draw_line_imp(painter, &colors, colorWheel, *this->points[2], *this->points[0], secondaryRadius);
			_draw_centroid(painter, &colors, colorWheel, sortedPoints, centroidRadius);
		}

		if (gamutShape == PrestoPalette::GamutShapeSquare)
		{
			_draw_primary_imp(painter, &colors, colorWheel, *this->points[0], primaryRadius);
			_draw_line_imp(painter, &colors, colorWheel, *this->points[0], *this->points[1], secondaryRadius);
			_draw_primary_imp(painter, &colors, colorWheel, *this->points[1], primaryRadius);
			_draw_line_imp(painter, &colors, colorWheel, *this->points[1], *this->points[3], secondaryRadius);
			_draw_primary_imp(painter, &colors, colorWheel, *this->points[2], primaryRadius);
			_draw_line_imp(painter, &colors, colorWheel, *this->points[2], *this->points[3], secondaryRadius);
			_draw_primary_imp(painter, &colors, colorWheel, *this->points[3], primaryRadius);
			_draw_line_imp(painter, &colors, colorWheel, *this->points[0], *this->points[2], secondaryRadius);

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

bool CirclePalette::_is_collision(const QPoint &circleCenter, int circleRadius, const QPoint &hitTest)
{
	bool a = (qPow(circleCenter.x() - hitTest.x(), 2.0) + qPow(circleCenter.y() - hitTest.y(), 2.0)) <= qPow(circleRadius, 2.0);
	qInfo() << a;
	return a;

/*	auto right = circleCenter.x() + circleRadius;
	auto left = circleCenter.x() - circleRadius;
	auto top = circleCenter.y() - circleRadius;
	auto bottom = circleCenter.y() + circleRadius;

	if (hitTest.x() < right && hitTest.x() > left)
	{
		if (hitTest.y() > top && hitTest.y() < bottom)
		{
			return true;
		}
	}

	return false;*/
}

void CirclePalette::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		if (this->isDragging == false)
		{
			QPoint mousePos = colorWheel->mapFromGlobal(QCursor::pos());

			// check for collisions with the points
			// http://math.stackexchange.com/questions/198764/how-to-know-if-a-point-is-inside-a-circle
			for (auto p : this->points)
			{
				if (_is_collision(*p, primaryRadius, mousePos))
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
				if (_is_collision(*lighting, primaryRadius, mousePos))
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

	/* important, so the event filter catches it */
	//event->ignore();
}

void CirclePalette::mouseReleaseEvent(QMouseEvent *event)
{
	if (isDragging)
	{
		this->isDragging = false;
		this->dragStartPosition = QPoint();
		this->dragPoint = NULL;
	}

	/* important, so the event filter catches it */
	//event->ignore();
}

void CirclePalette::mouseMoveEvent(QMouseEvent *event)
{
	if (isDragging)
	{
		*this->dragPoint = (event->pos() - this->relativeDistance);
		this->drawnElements->repaint();
	}

	/* important, so the event filter catches it */
	event->ignore();
}

void CirclePalette::create_gamut_line()
{
	int radius = colorWheel->width() / 2;
	radius = (float)radius * 0.80; //not using whole radius
	auto center = QPoint(colorWheel->width() / 2, colorWheel->height() / 2);
	auto angle = qDegreesToRadians(30.0);

	auto pFirst = new QPoint(center.x() - (qCos(angle) * radius), center.y() - (qSin(angle) * radius));
	auto pSecond = new QPoint(center.x() + (qCos(angle) * radius), center.y() + (qSin(angle) * radius));

	points.push_back(pFirst);
	points.push_back(pSecond);
}

void CirclePalette::create_gamut_triangle()
{
	int radius = colorWheel->width() / 2;
	radius = radius * 0.80; //not using whole radius
	auto center = QPoint(colorWheel->width() / 2, colorWheel->width() / 2);
	auto angle = qDegreesToRadians(30.0);

	/* add three points to list */
	auto pBottom = new QPoint(center + QPoint(0, radius));
	auto pTopLeft = new QPoint((-qCos(angle) * radius) + center.x(), center.y() - (qSin(angle) * radius));
	auto pTopRight = new QPoint((qCos(angle) * radius) + center.x(), center.y() - (qSin(angle) * radius));

	points.push_back(pBottom);
	points.push_back(pTopLeft);
	points.push_back(pTopRight);
}

void CirclePalette::create_gamut_square()
{
	int radius = colorWheel->width() / 2;
	radius = radius * 0.60; //not using whole radius
	auto center = QPoint(colorWheel->width() / 2, colorWheel->height() / 2);
	auto angle = qDegreesToRadians(45.0);

	auto pFirst = new QPoint((qCos(angle) * radius) + center.x(), (qSin(angle) * radius) + center.y());
	auto pSecond = new QPoint((-qCos(angle) * radius)+ center.x(), (qSin(angle) * radius) + center.y());
	auto pThird = new QPoint((qCos(angle) * radius)+ center.x(), (-qSin(angle) * radius) + center.y());
	auto pFourth = new QPoint((-qCos(angle) * radius)+ center.x(), (-qSin(angle) * radius) + center.y());

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
