#include "circlepalette.h"

#include <QEvent>
#include <QPainter>
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
#include <QtMath>
#include <QFileDialog>

const int circleRadius = 25;

CirclePalette::CirclePalette(QWidget *parent) : QWidget(parent)
{
	gamutShape = PrestoPalette::GamutShapeNone;

	QRect position = QRect(30, 50, 600, 600);

	backgroundWheel = new QLabel(parent);
	backgroundWheel->setGeometry(position);
	backgroundWheel->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/Wheel_BG.png")));
	backgroundWheel->setScaledContents(true);

	colorWheel = new QLabel(parent);
	colorWheel->setGeometry(position);
	colorWheel->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/YWheel_Course.png")));
	colorWheel->setScaledContents(true);
	colorWheel->raise();

	drawnElements = new QWidget(parent);
	drawnElements->setGeometry(position);
	drawnElements->raise();
	drawnElements->installEventFilter(this);

	this->installEventFilter(this);

	QMetaObject::connectSlotsByName(this);
}

static void _draw_line_imp(QPainter &painter,const QPoint &p1, const QPoint &p2)
{
	QPen linePen(Qt::red);
	linePen.setWidth(1);
	painter.setPen(linePen);
	painter.drawLine(p1, p2);
}

bool CirclePalette::eventFilter( QObject* watched, QEvent* event )
{
	if (watched == drawnElements && event->type() == QEvent::Paint)
	{
		QPainter painter(drawnElements);

		QVector<QColor> colors;

		if (gamutShape == PrestoPalette::GamutShapeLine)
		{
			// draw the circles
			for (auto p : this->points)
			{
				painter.setPen(QPen(Qt::blue, 3));
				//painter.setBrush(Qt::BrushStyle::SolidPattern);
				painter.drawEllipse(*p, circleRadius, circleRadius);

				QColor color = colorWheel->pixmap()->toImage().pixelColor(p->x(), p->y());
				colors.append(color);
			}

			// draw the line
			_draw_line_imp(painter, *this->points[0], *this->points[1]);
		}


		if (gamutShape == PrestoPalette::GamutShapeTriangle)
		{
			// draw the circles
			for (auto p : this->points)
			{
				painter.setPen(QPen(Qt::blue, 3));
				//painter.setBrush(Qt::BrushStyle::SolidPattern);
				painter.drawEllipse(*p, circleRadius, circleRadius);

				QColor color = colorWheel->pixmap()->toImage().pixelColor(p->x(), p->y());
				colors.append(color);
			}

			// draw the lines
			_draw_line_imp(painter, *this->points[0], *this->points[1]);
			_draw_line_imp(painter, *this->points[1], *this->points[2]);
			_draw_line_imp(painter, *this->points[2], *this->points[0]);
		}

		if (gamutShape == PrestoPalette::GamutShapeSquare)
		{
			// draw the circles
			for (auto p : this->points)
			{
				painter.setPen(QPen(Qt::blue, 3));
				//painter.setBrush(Qt::BrushStyle::SolidPattern);
				painter.drawEllipse(*p, circleRadius, circleRadius);

				QColor color = colorWheel->pixmap()->toImage().pixelColor(p->x(), p->y());
				colors.append(color);
			}

			// draw the lines
			_draw_line_imp(painter, *this->points[0], *this->points[1]);
			_draw_line_imp(painter, *this->points[1], *this->points[3]);
			_draw_line_imp(painter, *this->points[2], *this->points[3]);
			_draw_line_imp(painter, *this->points[0], *this->points[2]);
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

static bool _is_collision(const QPoint &circle, const QPoint &hitTest)
{
	int r2 = circleRadius * circleRadius;
	int d2 = (hitTest.x() - circle.x()) * (hitTest.x() - circle.x())
			+
	(hitTest.y() - circle.y()) * (hitTest.y() - circle.y());

	if (d2 <= r2)
	{
		return true;
	}
	else
	{
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
				if (_is_collision(*p, event->pos()))
				{
					this->dragStartPosition = event->pos();
					this->isDragging = true;
					this->dragPoint = p;
					this->relativeDistance = *p - dragStartPosition;
					qInfo() << "CLICK: " << event->pos() << " CIRCLE: " << *p;
					break;
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
		qInfo() << event->pos();
		qInfo() << this->relativeDistance;
		*this->dragPoint = (event->pos() - this->relativeDistance);
		this->drawnElements->repaint();
	}
}

void CirclePalette::create_gamut_line()
{
	int radius = colorWheel->width() / 2;
	radius = radius * 0.80; //not using whole radius
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

