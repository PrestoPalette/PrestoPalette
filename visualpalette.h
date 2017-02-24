#ifndef VISUALPALETTE_H
#define VISUALPALETTE_H

#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

#define TOTAL_SWATCHES 25

class VisualPalette : public QWidget
{
	Q_OBJECT
public:
	explicit VisualPalette(QWidget *parent = 0);
	void setColorAt(int row, int column, const QColor &fillColor);

signals:

public slots:

private:
	QGridLayout *layout;
	std::vector<QLabel*> swatches;
};

#endif // VISUALPALETTE_H
