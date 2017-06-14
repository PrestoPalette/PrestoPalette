#ifndef CIRCLEPALETTE_H
#define CIRCLEPALETTE_H

#include <QLabel>
#include <QPoint>
#include <QSoundEffect>

namespace PrestoPalette
{
enum GlobalGamutShape
{
	GamutShapeNone,
	GamutShapeLine,
	GamutShapeTriangle,
	GamutShapeSquare
};

enum GlobalWheelShape
{
	WheelShapeCourse,
	WheelShapeFine,
};
}

class ColorPoint
{
public:
	QColor color;
	QPoint point;
	qreal angle; // in radians
	bool secondaryOn;

	ColorPoint(QPoint p)
	{
		this->point = p;
		this->angle = 0;
		this->secondaryOn = false; // secondaries are off by default
		this->color = QColor();
	}
};

class CirclePalette : public QWidget
{
	Q_OBJECT
public:
	explicit CirclePalette(QWidget *parent = 0);

	QWidget *drawnElements;
	QLabel *colorWheel;
	QLabel *backgroundWheel;
	QVector<QColor> selectedColors;
	QColor lightingColor;
	PrestoPalette::GlobalGamutShape gamutShape;
	PrestoPalette::GlobalWheelShape wheelShape;
	QSoundEffect controlOffClick;
	QSoundEffect controlOnClick;

	bool enableLighting;

	void ChangeGamutShape(PrestoPalette::GlobalGamutShape shape);
	void ChangeWheelShape(PrestoPalette::GlobalWheelShape shape);

	void CalculateCentroid(int circleRadius);

signals:
	void selectedColorsChanged();
	void hoverColor(const QColor &color);
	void lightingColorChanged(const QColor &color);

private slots:


private:
	bool eventFilter(QObject* watched, QEvent* event);
	void mousePressEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;

private:
	int primaryRadius = 15;
	int secondaryRadius = 6;
	int centroidRadius = 5;

	std::vector<ColorPoint*> pointsLine;
	std::vector<ColorPoint*> pointsTriangle;
	std::vector<ColorPoint*> pointsQuad;

	//std::vector<QPoint*> seconardariesLine;
	//std::vector<QPoint*> seconardariesTriangle;
	//std::vector<QPoint*> seconardariesQuad;

	/*bool secondaryTriangle1On;
	bool secondaryTriangle2On;
	bool secondaryTriangle3On;

	bool secondaryQuad1On;
	bool secondaryQuad2On;
	bool secondaryQuad3On;
	bool secondaryQuad4On;*/

	QPoint centroidTriangle;
	QPoint centroidQuad;

	//bool centroidLineOn;
	bool centroidTriangleOn;
	bool centroidQuadOn;

	std::vector<ColorPoint*> *points;
	//std::vector<QPoint*> *secondaries;

	QPoint *lighting;
	QPoint *centroid;

	QPoint dragStartPosition;
	bool isDragging;
	QPoint *dragPoint;
	QPoint relativeDistance;
	QPixmap circlePic;

	QPixmap lightingPic;

	void create_gamut_line();
        void create_gamut_triangle();
	void create_gamut_square();
	void destroy_gamut();

	QPointF FindIntersectionWithCircle(const QPoint &p1, const QPoint &p2, const qreal radius);
	void _draw_primary_imp(QPainter &painter, const QPoint &p, int circleRadius, bool isCentroid);
	void _draw_line_imp(QPainter &painter, const QPoint &p1, const QPoint &p2, int circleRadius, bool secondaryOn);
	void _draw_centroid(QPainter &painter, int circleRadius, bool secondaryOn);
	bool _is_collision(const QPoint &circle, int circleRadius, const QPoint &hitTest);

public:
	struct Less {
	       Less(CirclePalette& c) : circlePalette(c) {}
	       bool operator () ( const ColorPoint & i1, const ColorPoint & i2 ) {return circlePalette.sort_angles(i1, i2);}
	       CirclePalette& circlePalette;
	   };

	bool sort_angles(const ColorPoint i, const ColorPoint j);
	QColor getColorAt(const QPoint &p);
	QColor getMidPointColor(QPoint p1, QPoint p2);
	QPoint getMidPoint(QPoint &p1, QPoint &p2);
};

#endif // CIRCLEPALETTE_H
