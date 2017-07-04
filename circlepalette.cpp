#include "circlepalette.h"

#include <QEvent>
#include <QPainter>
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
#include <QtMath>
#include <QFileDialog>
#include <QJsonArray>

#include <algorithm>

#define LIGHTING_ICON_MIDDLE_TO_TOP 7
#define LEFT_SHIFT 60
#define TOP_SHIFT 57

QPoint operator *(const QPoint& x, const QPointF& y) {
    return QPoint((qreal)x.x() * y.x(), (qreal)x.y() * y.y());
}

CirclePalette::CirclePalette(QWidget *parent) : QWidget(parent)
{
	isDragging = false;

	lightingPic = QPixmap(QString::fromUtf8(":/main/graphics/LightingIcon.png"));

	circlePic = QPixmap(QString::fromUtf8(":/main/graphics/PrimaryHandle.png"));
	primaryRadius = (double)circlePic.width() / 2.0;

	gamutShape = PrestoPalette::GamutShapeNone;
	wheelShape = PrestoPalette::WheelShapeCoarse;

	backgroundWheel = new QLabel(parent);
	backgroundWheel->setGeometry(QRect(44, 37, 549, 549));
	backgroundWheel->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/Wheel_BG.png")));

	colorWheel = new QLabel(parent);
	colorWheel->setGeometry(QRect(70, 62, 499, 499));
	colorWheel->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/YWheel_Course.png")));
	colorWheel->raise();

	lighting = new QPoint(325, 40);

	drawnElements = new QWidget(parent);
	drawnElements->setGeometry(colorWheel->geometry());
	drawnElements->raise();
	drawnElements->installEventFilter(this);

	setMouseTracking(true);

	installEventFilter(this);

	create_gamut_line();
	create_gamut_triangle();
	create_gamut_square();

	centroidTriangleOn = false; // centroids are off by default
	centroidQuadOn = false; // centroids are off by default

	this->controlOffClick.setSource(QUrl::fromLocalFile(":/main/audio/Click_Off_Short.wav"));
	this->controlOffClick.setVolume(0.25f);

	this->controlOnClick.setSource(QUrl::fromLocalFile(":/main/audio/Click_On_Short.wav"));
	this->controlOnClick.setVolume(0.25f);
}

CirclePalette::~CirclePalette(void)
{
	for(auto p: pointsLine)
	{
		delete p;
	}
	pointsLine.clear();

	for(auto p: pointsTriangle)
	{
		delete p;
	}
	pointsTriangle.clear();

	for (auto p: pointsQuad)
	{
		delete p;
	}
	pointsQuad.clear();

	if (lighting)
	{
		delete lighting;
		lighting = NULL;
	}
}

QPointF CirclePalette::FindIntersectionWithCircle(const QPoint &p1, const QPoint &p2, const qreal radius)
{
	qreal theta = atan2(p2.y() - p1.y(), p2.x() - p1.x());
	return QPointF(p1.x() + radius * cos(theta), p1.y() + radius * sin(theta));
}

void CirclePalette::_draw_primary_imp(QPainter &painter, const QPoint &p, int circleRadius, bool isCentroid)
{
	QPoint p_center(p.x() - circleRadius, p.y() - circleRadius);

	painter.drawPixmap(p_center, circlePic);
}

void CirclePalette::_draw_line_imp(QPainter &painter, const QPoint &p1, const QPoint &p2, int circleRadius, bool secondaryOn)
{
	// TODO Trim the lines, so they don't go into the circle

	QPen linePen(Qt::white);
	linePen.setWidth(3);
	painter.setPen(linePen);

	//trim the lines by adjusting the points
	painter.drawLine(FindIntersectionWithCircle(p1, p2, circleRadius * 2), FindIntersectionWithCircle(p2, p1, circleRadius * 2));
	//painter.drawLine(p1, p2);

	QPoint midpoint((p1.x() + p2.x()) / 2, (p1.y() + p2.y()) / 2);

	painter.setPen(QPen(Qt::transparent, 1));
	if (secondaryOn == true)
	{
		painter.setBrush(QBrush(Qt::white)); //on color
	}
	else
	{
		painter.setBrush(QBrush(QColor(64,64,57))); //off color
	}
	painter.drawEllipse(midpoint, circleRadius, circleRadius);
}

void CirclePalette::CalculateCentroid(int circleRadius)
{
	QPoint c;

	for (ColorPoint *cp : *this->points)
	{
		c += cp->point;
	}
	c /= this->points->size();

	// shift over the centroid (because the above is using top-left)
	centroid->setX(c.x() - circleRadius);
	centroid->setY(c.y() - circleRadius);
}

void CirclePalette::_draw_centroid(QPainter &painter, int circleRadius, bool secondaryOn)
{
	CalculateCentroid(circleRadius);

	painter.setPen(QPen(Qt::transparent, 1));
	if (secondaryOn == true)
	{
		painter.setBrush(QBrush(Qt::white)); //on color
	}
	else
	{
		painter.setBrush(QBrush(QColor(64,64,57))); //off color
	}
	painter.drawEllipse(*centroid, secondaryRadius, secondaryRadius);
}

bool CirclePalette::sort_angles(const ColorPoint i, const ColorPoint j)
{
	/*if (j.is_centroid)
	{
		return -1;
	}*/

	QPoint a, b;
	a = i.point;
	b = j.point;

	QPoint center = *centroid;

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

bool sort_angles1 (ColorPoint *i, ColorPoint *j)
{
	return (i->angle <= j->angle);
}

QColor CirclePalette::getColorAt(const QPoint &p)
{
	QColor color = colorWheel->pixmap()->toImage().pixelColor(p.x(), p.y());
	/*ColorPoint cp;
	cp.color = color;
	cp.point = p;

	return cp;*/
	return color;
}

QColor CirclePalette::getMidPointColor(QPoint p1, QPoint p2)
{
	return getColorAt(QPoint((p1.x() + p2.x()) / 2, (p1.y() + p2.y()) / 2));
}

QPoint CirclePalette::getMidPoint(QPoint &p1, QPoint &p2)
{
	return QPoint((p1.x() + p2.x()) / 2, (p1.y() + p2.y()) / 2);
}

// https://stackoverflow.com/questions/1311049/how-to-map-atan2-to-degrees-0-360
float PointPairToBearingDegrees(QPoint startingPoint, QPoint point)
{
	QPoint endingPoint;
	endingPoint = point;
	QPoint originPoint = QPoint(endingPoint.x() - startingPoint.x(), endingPoint.y() - startingPoint.y()); // get origin point to origin by subtracting end from start

	float bearingRadians = atan2f(originPoint.y(), originPoint.x()); // get bearing in radians
	float bearingDegrees = bearingRadians * (180.0 / M_PI); // convert to degrees

	// this is for PrestoPalette
	bearingDegrees += 105.0; // to shift over to the yellow (90 degrees plus 360/24)

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

		//QVector<ColorPoint> colors;

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
			_draw_primary_imp(painter, (*(*this->points)[0]).point, primaryRadius, false);
			_draw_primary_imp(painter, (*(*this->points)[1]).point, primaryRadius, false);
			_draw_line_imp(painter, (*(*this->points)[0]).point, (*(*this->points)[1]).point, secondaryRadius, (*(*this->points)[0]).secondaryOn);
		}

		if (gamutShape == PrestoPalette::GamutShapeTriangle)
		{
			_draw_primary_imp(painter, (*(*this->points)[0]).point, primaryRadius, false);
			_draw_line_imp(painter, (*(*this->points)[0]).point, (*(*this->points)[1]).point, secondaryRadius, (*(*this->points)[0]).secondaryOn);
			_draw_primary_imp(painter, (*(*this->points)[1]).point, primaryRadius, false);
			_draw_line_imp(painter, (*(*this->points)[1]).point, (*(*this->points)[2]).point, secondaryRadius, (*(*this->points)[1]).secondaryOn);
			_draw_primary_imp(painter, (*(*this->points)[2]).point, primaryRadius, false);
			_draw_line_imp(painter, (*(*this->points)[2]).point, (*(*this->points)[0]).point, secondaryRadius, (*(*this->points)[2]).secondaryOn);

			_draw_centroid(painter, centroidRadius, centroidTriangleOn);
		}

		if (gamutShape == PrestoPalette::GamutShapeSquare)
		{
			_draw_primary_imp(painter, (*(*this->points)[0]).point, primaryRadius, false);
			_draw_line_imp(painter, (*(*this->points)[0]).point, (*(*this->points)[1]).point, secondaryRadius, (*(*this->points)[0]).secondaryOn);
			_draw_primary_imp(painter, (*(*this->points)[1]).point, primaryRadius, false);
			_draw_line_imp(painter, (*(*this->points)[1]).point, (*(*this->points)[2]).point, secondaryRadius, (*(*this->points)[1]).secondaryOn);
			_draw_primary_imp(painter, (*(*this->points)[2]).point, primaryRadius, false);
			_draw_line_imp(painter, (*(*this->points)[2]).point, (*(*this->points)[3]).point, secondaryRadius, (*(*this->points)[2]).secondaryOn);
			_draw_primary_imp(painter, (*(*this->points)[3]).point, primaryRadius, false);
			_draw_line_imp(painter, (*(*this->points)[3]).point, (*(*this->points)[0]).point, secondaryRadius, (*(*this->points)[3]).secondaryOn);

			_draw_centroid(painter, centroidRadius, centroidQuadOn);
		}

		// make sure that this is empty
		//colors.clear();

		// populate the angles for each point
		for (auto n : *points)
		{
			n->angle = PointPairToBearingDegrees(center, n->point);
		};

		std::sort(points->begin(), points->end(), sort_angles1);

		QVector<QColor> sortedColors;
		if (gamutShape == PrestoPalette::GamutShapeLine)
		{
			sortedColors.append(getColorAt((*points)[0]->point));
			if ((*(*this->points)[0]).secondaryOn)
			{
				sortedColors.append(getMidPointColor((*points)[0]->point, (*points)[1]->point));
			}
			sortedColors.append(getColorAt((*points)[1]->point));
		}

		if (gamutShape == PrestoPalette::GamutShapeTriangle)
		{
			sortedColors.append(getColorAt((*points)[0]->point));
			if ((*points)[0]->secondaryOn)
			{
				sortedColors.append(getMidPointColor((*points)[0]->point, (*points)[1]->point));
			}
			sortedColors.append(getColorAt((*points)[1]->point));
			if ((*points)[1]->secondaryOn)
			{
				sortedColors.append(getMidPointColor((*points)[1]->point, (*points)[2]->point));
			}
			sortedColors.append(getColorAt((*points)[2]->point));
			if ((*points)[2]->secondaryOn)
			{
				sortedColors.append(getMidPointColor((*points)[2]->point, (*points)[0]->point));
			}

			if (centroidTriangleOn)
			{
				sortedColors.append(getColorAt(*this->centroid));
			}
		}

		if (gamutShape == PrestoPalette::GamutShapeSquare)
		{
			sortedColors.append(getColorAt((*points)[0]->point));
			if ((*points)[0]->secondaryOn)
			{
				sortedColors.append(getMidPointColor((*points)[0]->point, (*points)[1]->point));
			}
			sortedColors.append(getColorAt((*points)[1]->point));
			if ((*points)[1]->secondaryOn)
			{
				sortedColors.append(getMidPointColor((*points)[1]->point, (*points)[2]->point));
			}
			sortedColors.append(getColorAt((*points)[2]->point));
			if ((*points)[2]->secondaryOn)
			{
				sortedColors.append(getMidPointColor((*points)[2]->point, (*points)[3]->point));
			}
			sortedColors.append(getColorAt((*points)[3]->point));
			if ((*points)[3]->secondaryOn)
			{
				sortedColors.append(getMidPointColor((*points)[3]->point, (*points)[0]->point));
			}

			if (centroidQuadOn)
			{
				sortedColors.append(getColorAt(*this->centroid));
			}
		}

		QVector<QColor> newColors;
		for(auto cc : sortedColors)
		{
			newColors.append(cc);
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
	return (qPow(circleCenter.x() - hitTest.x(), 2.0) + qPow(circleCenter.y() - hitTest.y(), 2.0)) <= qPow(circleRadius, 2.0);
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
			for (auto cp : *this->points)
			{
				QPoint *p = &cp->point;
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
				if (_is_collision(*lighting, lightingPic.height(), mousePos))
				{
					this->dragStartPosition = event->pos();
					this->isDragging = true;
					this->dragPoint = lighting;
					this->relativeDistance = dragStartPosition - *lighting;
					//qInfo() << "CLICK: " << event->pos() << " LIGHTING: " << *lighting;
					return;
				}
			}

			if (gamutShape == PrestoPalette::GamutShapeLine)
			{
				if (_is_collision(getMidPoint((this->pointsLine[0])->point, (this->pointsLine[1])->point), secondaryRadius, mousePos))
				{
					(this->pointsLine[0])->secondaryOn = !(this->pointsLine[0])->secondaryOn;
					if ((this->pointsLine[0])->secondaryOn)
					{
						this->controlOnClick.play();
					}
					else
					{
						this->controlOffClick.play();
					}
				}
			}

			if (gamutShape == PrestoPalette::GamutShapeTriangle)
			{
				if (_is_collision(getMidPoint((this->pointsTriangle[0])->point, (this->pointsTriangle[1])->point), secondaryRadius, mousePos))
				{
					(this->pointsTriangle[0])->secondaryOn = !(this->pointsTriangle[0])->secondaryOn;
					if ((this->pointsTriangle[0])->secondaryOn)
					{
						this->controlOnClick.play();
					}
					else
					{
						this->controlOffClick.play();
					}
				}
				if (_is_collision(getMidPoint((this->pointsTriangle[1])->point, (this->pointsTriangle[2])->point), secondaryRadius, mousePos))
				{
					(this->pointsTriangle[1])->secondaryOn = !(this->pointsTriangle[1])->secondaryOn;
					if ((this->pointsTriangle[1])->secondaryOn)
					{
						this->controlOnClick.play();
					}
					else
					{
						this->controlOffClick.play();
					}
				}
				if (_is_collision(getMidPoint((this->pointsTriangle[2])->point, (this->pointsTriangle[0])->point), secondaryRadius, mousePos))
				{
					(this->pointsTriangle[2])->secondaryOn = !(this->pointsTriangle[2])->secondaryOn;
					if ((this->pointsTriangle[2])->secondaryOn)
					{
						this->controlOnClick.play();
					}
					else
					{
						this->controlOffClick.play();
					}
				}

				if (_is_collision(this->centroidTriangle, centroidRadius, mousePos))
				{
					this->centroidTriangleOn = !this->centroidTriangleOn;
					if (centroidTriangleOn)
					{
						this->controlOnClick.play();
					}
					else
					{
						this->controlOffClick.play();
					}
				}
			}

			if (gamutShape == PrestoPalette::GamutShapeSquare)
			{
				if (_is_collision(getMidPoint((this->pointsQuad[0])->point, (this->pointsQuad[1])->point), secondaryRadius, mousePos))
				{
					(this->pointsQuad[0])->secondaryOn = !(this->pointsQuad[0])->secondaryOn;
					if ((this->pointsQuad[0])->secondaryOn)
					{
						this->controlOnClick.play();
					}
					else
					{
						this->controlOffClick.play();
					}
				}
				if (_is_collision(getMidPoint((this->pointsQuad[1])->point, (this->pointsQuad[2])->point), secondaryRadius, mousePos))
				{
					(this->pointsQuad[1])->secondaryOn = !(this->pointsQuad[1])->secondaryOn;
					if ((this->pointsQuad[1])->secondaryOn)
					{
						this->controlOnClick.play();
					}
					else
					{
						this->controlOffClick.play();
					}
				}
				if (_is_collision(getMidPoint((this->pointsQuad[2])->point, (this->pointsQuad[3])->point), secondaryRadius, mousePos))
				{
					(this->pointsQuad[2])->secondaryOn = !(this->pointsQuad[2])->secondaryOn;
					if ((this->pointsQuad[2])->secondaryOn)
					{
						this->controlOnClick.play();
					}
					else
					{
						this->controlOffClick.play();
					}
				}
				if (_is_collision(getMidPoint((this->pointsQuad[3])->point, (this->pointsQuad[0])->point), secondaryRadius, mousePos))
				{
					(this->pointsQuad[3])->secondaryOn = !(this->pointsQuad[3])->secondaryOn;
					if ((this->pointsQuad[3])->secondaryOn)
					{
						this->controlOnClick.play();
					}
					else
					{
						this->controlOffClick.play();
					}
				}

				if (_is_collision(this->centroidQuad, centroidRadius, mousePos))
				{
					this->centroidQuadOn = !this->centroidQuadOn;
					if (centroidQuadOn)
					{
						this->controlOnClick.play();
					}
					else
					{
						this->controlOffClick.play();
					}
				}
			}
		}

		this->drawnElements->repaint();
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
	ColorPoint *pFirst = new ColorPoint(QPoint(411 - this->geometry().left() - LEFT_SHIFT, 172 - this->geometry().top() - TOP_SHIFT));
	ColorPoint *pSecond = new ColorPoint(QPoint(120 - this->geometry().left() - LEFT_SHIFT, 407 - this->geometry().top() - TOP_SHIFT));

	pointsLine.push_back(pFirst);
	pointsLine.push_back(pSecond);
}

void CirclePalette::create_gamut_triangle()
{
	ColorPoint *pBottom = new ColorPoint(QPoint(269 - this->geometry().left() - LEFT_SHIFT, 519 - this->geometry().top() - TOP_SHIFT));
	ColorPoint *pTopLeft = new ColorPoint(QPoint(423 - this->geometry().left() - LEFT_SHIFT, 253 - this->geometry().top() - TOP_SHIFT));
	ColorPoint *pTopRight = new ColorPoint(QPoint(295 - this->geometry().left() - LEFT_SHIFT, 184 - this->geometry().top() - TOP_SHIFT));

	pointsTriangle.push_back(pBottom);
	pointsTriangle.push_back(pTopLeft);
	pointsTriangle.push_back(pTopRight);
}

void CirclePalette::create_gamut_square()
{
	ColorPoint *pFirst = new ColorPoint(QPoint(204 - this->geometry().left(), 40 - this->geometry().top()));
	ColorPoint *pSecond = new ColorPoint(QPoint(410 - this->geometry().left(), 194 - this->geometry().top()));
	ColorPoint *pThird = new ColorPoint(QPoint(380 - this->geometry().left(), 318 - this->geometry().top()));
	ColorPoint *pFourth = new ColorPoint(QPoint(116 - this->geometry().left(), 355 - this->geometry().top()));

	pointsQuad.push_back(pFirst);
	pointsQuad.push_back(pSecond);
	pointsQuad.push_back(pThird);
	pointsQuad.push_back(pFourth);
}

void CirclePalette::destroy_gamut()
{
	mouseReleaseEvent(NULL);

	gamutShape = PrestoPalette::GamutShapeNone;
	this->points = NULL;
	//this->secondaries = NULL;
	this->centroid = NULL;
}

void CirclePalette::ChangeGamutShape(PrestoPalette::GlobalGamutShape shape)
{
	if (shape != gamutShape)
	{
		destroy_gamut();
	}

	// boundary check
	if (shape >= PrestoPalette::GamutShapeLast)
	{
		gamutShape = PrestoPalette::GamutShapeTriangle;
	}
	else
	{
		gamutShape = shape;
	}

	if (gamutShape == PrestoPalette::GamutShapeLine)
	{
		this->points = &this->pointsLine;
		//this->secondaries = &this->seconardariesLine;
		this->centroid = NULL;
	}

	if (gamutShape == PrestoPalette::GamutShapeTriangle)
	{
		this->points = &this->pointsTriangle;
		//this->secondaries = &this->seconardariesTriangle;
		this->centroid = &this->centroidTriangle;
	}

	if (gamutShape == PrestoPalette::GamutShapeSquare)
	{
		this->points = &this->pointsQuad;
		//this->secondaries = &this->seconardariesQuad;
		this->centroid = &this->centroidQuad;
	}

	this->drawnElements->repaint();
}

void CirclePalette::SaveState(QJsonObject &saveState)
{
	saveState["centroidTriangleOn"] = this->centroidTriangleOn;
	saveState["centroidQuadOn"] = this->centroidQuadOn;

	{
		QJsonArray pointsLineArray;
		foreach (ColorPoint* point, pointsLine)
		{
			QJsonObject s;
			point->SaveState(s);
			pointsLineArray.append(s);
		}
		saveState["pointsLine"] = pointsLineArray;
	}

	{
		QJsonArray pointsTriangleArray;
		foreach (ColorPoint* point, pointsTriangle)
		{
			QJsonObject s;
			point->SaveState(s);
			pointsTriangleArray.append(s);
		}
		saveState["pointsTriangle"] = pointsTriangleArray;
	}

	{
		QJsonArray pointsQuadArray;
		foreach (ColorPoint* point, pointsQuad)
		{
			QJsonObject s;
			point->SaveState(s);
			pointsQuadArray.append(s);
		}
		saveState["pointsQuad"] = pointsQuadArray;
	}
}

void CirclePalette::LoadState(QJsonObject &loadState)
{
	this->centroidTriangleOn = loadState["centroidTriangleOn"].toBool();
	this->centroidQuadOn = loadState["centroidQuadOn"].toBool();

	{
		QJsonArray array = loadState["pointsLine"].toArray();
		for (int i = 0; i < array.size(); i++)
		{
			QJsonObject s = array[i].toObject();
			if(pointsLine.size() >= i)
			{
				pointsLine[i]->LoadState(s);
			}
		}
	}

	{
		QJsonArray array = loadState["pointsTriangle"].toArray();
		for (int i = 0; i < array.size(); i++)
		{
			QJsonObject s = array[i].toObject();
			if(pointsTriangle.size() >= i)
			{
				pointsTriangle[i]->LoadState(s);
			}
		}
	}

	{
		QJsonArray array = loadState["pointsQuad"].toArray();
		for (int i = 0; i < array.size(); i++)
		{
			QJsonObject s = array[i].toObject();
			if(pointsQuad.size() >= i)
			{
				pointsQuad[i]->LoadState(s);
			}
		}
	}
}

void CirclePalette::ChangeWheelShape(PrestoPalette::GlobalWheelShape shape)
{
	// boundary check
	if (shape >= PrestoPalette::WheelShapeLast)
	{
		this->wheelShape = PrestoPalette::WheelShapeCoarse;
	}
	else
	{
		this->wheelShape = shape;
	}

	switch(this->wheelShape)
	{
	case PrestoPalette::GlobalWheelShape::WheelShapeCoarse:
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
