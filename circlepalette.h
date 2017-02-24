#ifndef CIRCLEPALETTE_H
#define CIRCLEPALETTE_H

#include <QLabel>
#include <QPoint>

class CirclePalette : public QLabel
{
	Q_OBJECT
public:
	explicit CirclePalette(QLabel *parent = 0);

signals:

public slots:

private:
	bool eventFilter( QObject* watched, QEvent* event );

private:
	std::vector<QPoint*> points;
	std::vector<QLabel*> lines;
};

#endif // CIRCLEPALETTE_H
