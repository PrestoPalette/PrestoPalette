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

QPoint operator *(const QPoint& x, const QPointF& y) {
    return QPoint((qreal)x.x() * y.x(), (qreal)x.y() * y.y());
}

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

QPointF CirclePalette::FindIntersectionWithCircle(const QPoint &p1, const QPoint &p2)
{
	QLine line(p1, p2);
	QVector2D slope(line.dx(), line.dy());
	slope.normalize();
	qreal angle = slope.y() / slope.length();
	return QPointF(qCos(angle), qSin(angle));

}

void CirclePalette::_draw_primary_imp(QPainter &painter, QVector<ColorPoint> *colors, QLabel *colorWheel, const QPoint &p, int circleRadius, bool isCentroid)
{
	QPoint p_center(p.x() - circleRadius, p.y() - circleRadius);

	painter.drawPixmap(p_center, circlePic);

	/*QColor color = colorWheel->pixmap()->toImage().pixelColor(p.x(), p.y());
	ColorPoint cp;
	cp.color = color;
	cp.point = p;
	cp.is_centroid = isCentroid;
	colors->append(cp);*/
}

void CirclePalette::_draw_line_imp(QPainter &painter, QVector<ColorPoint> *colors, QLabel *colorWheel, const QPoint &p1, const QPoint &p2, int circleRadius)
{
	// TODO Trim the lines, so they don't go into the circle

	QPen linePen(Qt::white);
	linePen.setWidth(3);
	painter.setPen(linePen);

	//trim the lines by adjusting the points
	//qInfo() << "p1: " << p1 << " intersection: " << FindIntersectionWithCircle(p1, p2);
	//painter.drawLine(p1 * FindIntersectionWithCircle(p1, p2), p2 * FindIntersectionWithCircle(p2, p1));

	painter.drawLine(p1, p2);

	QPoint midpoint((p1.x() + p2.x()) / 2, (p1.y() + p2.y()) / 2);

	/* TODO use the image for these... */
	painter.setPen(QPen(Qt::white, 3));
	painter.drawEllipse(midpoint, circleRadius, circleRadius);

	/*QColor color = colorWheel->pixmap()->toImage().pixelColor(midpoint.x(), midpoint.y());
	ColorPoint cp;
	cp.color = color;
	cp.point = midpoint;
	colors->append(cp);*/
}

void CirclePalette::CalculateCentroid(int circleRadius)
{
	centroid = QPoint();
	for (QPoint *p : this->points)
	{
		centroid += *p;
	}
	centroid /= this->points.size();

	// shift over the centroid (because the above is using top-left)
	centroid = QPoint(centroid.x() - circleRadius, centroid.y() - circleRadius);
}

void CirclePalette::_draw_centroid(QPainter &painter, QVector<ColorPoint> *colors, QLabel *colorWheel, int circleRadius)
{
	CalculateCentroid(circleRadius);
	_draw_primary_imp(painter, colors, colorWheel, centroid, circleRadius, true);
}

bool CirclePalette::sort_angles(const ColorPoint i, const ColorPoint j)
{
	if (j.is_centroid)
	{
		return -1;
	}

	QPoint a, b;
	a = i.point;
	b = j.point;

	QPoint center = centroid;

    if (a.x() - center.x() >= 0 && b.x() - center.x() < 0)
	return true;
    if (a.x() - center.x() < 0 && b.x() - center.x() >= 0)
	return false;
    if (a.x() - center.x() == 0 && b.x() - center.x() == 0) {
	if (a.y() - center.y() >= 0 || b.y() - center.y() >= 0)
	    return a.y() > b.y();
	return b.y() > a.y();
    }

    // compute the cross product of vectors (center -> a) x (center -> b)
    int det = (a.x() - center.x()) * (b.y() - center.y()) - (b.x() - center.x()) * (a.y() - center.y());
    if (det < 0)
	return true;
    if (det > 0)
	return false;

    // points a and b are on the same line from the center
    // check which point is closer to the center
    int d1 = (a.x() - center.x()) * (a.x() - center.x()) + (a.y() - center.y()) * (a.y() - center.y());
    int d2 = (b.x() - center.x()) * (b.x() - center.x()) + (b.y() - center.y()) * (b.y() - center.y());
    return d1 > d2;
}

bool sort_angles1 (ColorPoint i, ColorPoint j)
{
	/*if (j.is_centroid)
	{
		return -1;
	}*/

	return (i.angle <= j.angle);
}

ColorPoint CirclePalette::getColorAt(const QPoint &p)
{
	QColor color = colorWheel->pixmap()->toImage().pixelColor(p.x(), p.y());
	ColorPoint cp;
	cp.color = color;
	cp.point = p;
	//cp.is_centroid = isCentroid;

	return cp;
}

ColorPoint CirclePalette::getMidPointColor(QPoint p1, QPoint p2)
{
	return getColorAt(QPoint((p1.x() + p2.x()) / 2, (p1.y() + p2.y()) / 2));
}

float PointPairToBearingDegrees(QPoint startingPoint, QPoint point)
{
	QPoint endingPoint;
	//endingPoint.setX((cos(qDegreesToRadians(-90.0)) * (float)point.x()) + (-sin(qDegreesToRadians(-90.0)) * (float)point.y()));
	//endingPoint.setY((sin(qDegreesToRadians(-90.0)) * (float)point.x()) + (cos(qDegreesToRadians(-90.0)) * (float)point.y()));

	endingPoint = point;

    QPoint originPoint = QPoint(endingPoint.x() - startingPoint.x(), endingPoint.y() - startingPoint.y()); // get origin point to origin by subtracting end from start
    float bearingRadians = atan2f(originPoint.y(), originPoint.x()); // get bearing in radians
    float bearingDegrees = bearingRadians * (180.0 / M_PI); // convert to degrees
    bearingDegrees = (bearingDegrees > 0.0 ? bearingDegrees : (360.0 + bearingDegrees)); // correct discontinuity
    return qDegreesToRadians(bearingDegrees);
}

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
		painter.setRenderHint(QPainter::HighQualityAntialiasing, true);

		QVector<ColorPoint> colors;

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

		if (gamutShape == PrestoPalette::GamutShapeLine)
		{
			_draw_primary_imp(painter, &colors, colorWheel, *this->points[0], primaryRadius, false);
			_draw_primary_imp(painter, &colors, colorWheel, *this->points[1], primaryRadius, false);
			_draw_line_imp(painter, &colors, colorWheel, *this->points[0], *this->points[1], secondaryRadius);
		}

		if (gamutShape == PrestoPalette::GamutShapeTriangle)
		{
			_draw_primary_imp(painter, &colors, colorWheel, *this->points[0], primaryRadius, false);
			_draw_line_imp(painter, &colors, colorWheel, *this->points[0], *this->points[1], secondaryRadius);
			_draw_primary_imp(painter, &colors, colorWheel, *this->points[1], primaryRadius, false);
			_draw_line_imp(painter, &colors, colorWheel, *this->points[1], *this->points[2], secondaryRadius);
			_draw_primary_imp(painter, &colors, colorWheel, *this->points[2], primaryRadius, false);
			_draw_line_imp(painter, &colors, colorWheel, *this->points[2], *this->points[0], secondaryRadius);

			_draw_centroid(painter, &colors, colorWheel, centroidRadius);
		}

		if (gamutShape == PrestoPalette::GamutShapeSquare)
		{
			_draw_primary_imp(painter, &colors, colorWheel, *this->points[0], primaryRadius, false);
			_draw_line_imp(painter, &colors, colorWheel, *this->points[0], *this->points[1], secondaryRadius);
			_draw_primary_imp(painter, &colors, colorWheel, *this->points[1], primaryRadius, false);
			_draw_line_imp(painter, &colors, colorWheel, *this->points[1], *this->points[2], secondaryRadius);
			_draw_primary_imp(painter, &colors, colorWheel, *this->points[2], primaryRadius, false);
			_draw_line_imp(painter, &colors, colorWheel, *this->points[2], *this->points[3], secondaryRadius);
			_draw_primary_imp(painter, &colors, colorWheel, *this->points[3], primaryRadius, false);
			_draw_line_imp(painter, &colors, colorWheel, *this->points[3], *this->points[0], secondaryRadius);

			_draw_centroid(painter, &colors, colorWheel, centroidRadius);
		}

		// make sure that this is empty
		colors.clear();

		qInfo() << "start";

		// populate the angles for each point
		for (auto n : points)
		{
			ColorPoint p;

			/*auto t = QPoint(n->x(), n->y());


			// TODO make sure center is true
			t = t - center;
			t.setY(-t.y()); // invert y so up is positive

			if (t.x() == 0)
			{
				if (t.y() == 0)
				{
					p.angle = 0;
				}
				else if (t.y() > 0)
					p.angle = qDegreesToRadians(90.0);
				else
					p.angle = qDegreesToRadians(270.0);
			}
			else if (t.y() == 0)
			{
				if (t.x() < 0)
				{
					p.angle = qDegreesToRadians(180.0);
				}
				else
				{
					p.angle = 0.0f;
				}
			}
			else
			{
				p.angle = atan((double)t.y() / (double)t.x());
			}*/

			p.angle = PointPairToBearingDegrees(center, QPoint(n->x(), n->y()));

			//qInfo() << QPoint(n->x(), n->y()) << " " << t << " " << center << " " << qRadiansToDegrees(p.angle);
			qInfo() << QPoint(n->x(), n->y()) << " " << " " << center << " " << qRadiansToDegrees(p.angle);

			p.point = QPoint(n->x(), n->y());

			// rotate backwards by pi/2 radians
			//p.angle -= M_PI_2;

			colors.append(p);
		};

		qInfo() << "end";

		//std::sort(colors.begin(), colors.end(), Less(*this));
		std::sort(colors.begin(), colors.end(), sort_angles1);

		QVector<ColorPoint> sortedColors;
		if (gamutShape == PrestoPalette::GamutShapeLine)
		{
			sortedColors.append(getColorAt(colors[0].point));
			sortedColors.append(getColorAt(colors[1].point));
			sortedColors.append(getMidPointColor(colors[0].point, colors[1].point));
		}

		if (gamutShape == PrestoPalette::GamutShapeTriangle)
		{
			sortedColors.append(getColorAt(colors[0].point));
			sortedColors.append(getMidPointColor(colors[0].point, colors[1].point));
			sortedColors.append(getColorAt(colors[1].point));
			sortedColors.append(getMidPointColor(colors[1].point, colors[2].point));
			sortedColors.append(getColorAt(colors[2].point));
			sortedColors.append(getMidPointColor(colors[2].point, colors[0].point));

			sortedColors.append(getColorAt(this->centroid));
		}

		if (gamutShape == PrestoPalette::GamutShapeSquare)
		{
			sortedColors.append(getColorAt(colors[0].point));
			sortedColors.append(getMidPointColor(colors[0].point, colors[1].point));
			sortedColors.append(getColorAt(colors[1].point));
			sortedColors.append(getMidPointColor(colors[1].point, colors[2].point));
			sortedColors.append(getColorAt(colors[2].point));
			sortedColors.append(getMidPointColor(colors[2].point, colors[3].point));
			sortedColors.append(getColorAt(colors[3].point));
			sortedColors.append(getMidPointColor(colors[3].point, colors[0].point));

			sortedColors.append(getColorAt(this->centroid));
		}

		QVector<QColor> newColors;
		for(auto cc : sortedColors)
		{
			newColors.append(cc.color);
		}

		if (this->selectedColors != newColors)
		{
			this->selectedColors = newColors;

			// notify that colors changed
			emit selectedColorsChanged();
		}
	}

	return false;
}

bool CirclePalette::_is_collision(const QPoint &circleCenter, int circleRadius, const QPoint &hitTest)
{
	bool a = (qPow(circleCenter.x() - hitTest.x(), 2.0) + qPow(circleCenter.y() - hitTest.y(), 2.0)) <= qPow(circleRadius, 2.0);
	//qInfo() << a;
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

	//auto pFirst = new QPoint(center.x() - (qCos(angle) * radius), center.y() - (qSin(angle) * radius));
	//auto pSecond = new QPoint(center.x() + (qCos(angle) * radius), center.y() + (qSin(angle) * radius));
	QPoint *pFirst = new QPoint(411 - this->geometry().left(), 172 - this->geometry().top());
	QPoint *pSecond = new QPoint(120 - this->geometry().left(), 407 - this->geometry().top());

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
	//auto pBottom = new QPoint(center + QPoint(0, radius));
	//auto pTopLeft = new QPoint((-qCos(angle) * radius) + center.x(), center.y() - (qSin(angle) * radius));
	//auto pTopRight = new QPoint((qCos(angle) * radius) + center.x(), center.y() - (qSin(angle) * radius));
	QPoint *pBottom = new QPoint(269 - this->geometry().left(), 519 - this->geometry().top());
	QPoint *pTopLeft = new QPoint(423 - this->geometry().left(), 253 - this->geometry().top());
	QPoint *pTopRight = new QPoint(295 - this->geometry().left(), 184 - this->geometry().top());

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

	//auto pFirst = new QPoint((qCos(angle) * radius) + center.x(), (qSin(angle) * radius) + center.y());
	//auto pSecond = new QPoint((-qCos(angle) * radius)+ center.x(), (qSin(angle) * radius) + center.y());
	//auto pThird = new QPoint((qCos(angle) * radius)+ center.x(), (-qSin(angle) * radius) + center.y());
	//auto pFourth = new QPoint((-qCos(angle) * radius)+ center.x(), (-qSin(angle) * radius) + center.y());
	QPoint *pFirst = new QPoint(122 - this->geometry().left(), 411 - this->geometry().top());
	QPoint *pSecond = new QPoint(188 - this->geometry().left(), 287 - this->geometry().top());
	QPoint *pThird = new QPoint(362 - this->geometry().left(), 220 - this->geometry().top());
	QPoint *pFourth = new QPoint(495 - this->geometry().left(), 419 - this->geometry().top());

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
