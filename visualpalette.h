#ifndef VISUALPALETTE_H
#define VISUALPALETTE_H

#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

//#define TOTAL_SWATCHES 25
#define TOTAL_SWATCHES 45

class VisualPalette : public QWidget
{
	Q_OBJECT
      public:
	explicit VisualPalette(QWidget *parent = 0);
	void setColorAt(int row, int column, const QColor &fillColor);
	void Formulate(QVector<QColor> combinedColors,
		       QVector<QColor> primaryColors, QVector<QColor> secondaryColors,
		       QColor neutral, int paletteWidth, qreal stringLight, qreal stringDark,
		       bool enableLighting, QColor ambientColor, qreal ambientColorBrightness,
		       qreal power);

      private:
	int paletteHeight;
	int paletteWidth;

	void resetSwatches();
	void _setColor(int column, int row, QColor &combinedColor, qreal componentMultiplier, qreal ambientColorAlpha, bool enableLighting, QColor &ambientColor, qreal ambientColorBrightness, bool interpolate, bool go_dark);
	bool eventFilter(QObject *watched, QEvent *event);

	bool _is_collision(const QPoint &circleCenter, int circleRadius, const QPoint &hitTest);
      signals:
	void hoverColor(const QColor &color);

      public slots:

      private:
	QGridLayout *layout;
};

#endif // VISUALPALETTE_H
