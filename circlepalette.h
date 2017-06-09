#ifndef CIRCLEPALETTE_H
#define CIRCLEPALETTE_H

#include <QLabel>
#include <QPoint>

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
	bool is_centroid;
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

	bool enableLighting;

	void ChangeGamutShape(PrestoPalette::GlobalGamutShape shape);
	void ChangeWheelShape(PrestoPalette::GlobalWheelShape shape);

	QPoint CalculateCentroid(int circleRadius);

signals:
	void selectedColorsChanged();
	void hoverColor(const QColor &color);
	void lightingColorChanged(const QColor &color);

private slots:


private:
	bool eventFilter( QObject* watched, QEvent* event );
	void mousePressEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;

private:
	int primaryRadius = 15;
	int secondaryRadius = 5;
	int centroidRadius = 5;

	std::vector<QPoint*> points;
	std::vector<QLabel*> lines;
	QPoint *lighting;
	QPoint centroid;

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

	QPointF FindIntersectionWithCircle(const QPoint &p1, const QPoint &p2);
	void _draw_primary_imp(QPainter &painter, QVector<ColorPoint> *colors, QLabel *colorWheel, const QPoint &p, int circleRadius, bool isCentroid);
	void _draw_line_imp(QPainter &painter, QVector<ColorPoint> *colors, QLabel *colorWheel, const QPoint &p1, const QPoint &p2, int circleRadius);
	void _draw_centroid(QPainter &painter, QVector<ColorPoint> *colors, QLabel *colorWheel, int circleRadius);
	bool _is_collision(const QPoint &circle, int circleRadius, const QPoint &hitTest);

public:
	struct Less {
	       Less(CirclePalette& c) : circlePalette(c) {}
	       bool operator () ( const ColorPoint & i1, const ColorPoint & i2 ) {return circlePalette.sort_angles(i1, i2);}
	       CirclePalette& circlePalette;
	   };

	bool sort_angles(const ColorPoint i, const ColorPoint j);
};

#endif // CIRCLEPALETTE_H
