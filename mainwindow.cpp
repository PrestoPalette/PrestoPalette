#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMouseEvent>
#include <QMessageBox>
#include <QtDebug>

#include <QPainter>

const qreal circleWidth = 14.0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	ui->colorWheel->installEventFilter(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_actionExit_triggered()
{
	::exit(0);
}

void MainWindow::on_backgroundSlider_sliderMoved(int position)
{
	int rgb = ((100.0 - (double)position) / 100.0) * 255.0;
	QPalette Pal(palette());
	Pal.setColor(QPalette::Background, QColor::fromRgb(rgb,rgb,rgb));
	ui->backgroundArea->setAutoFillBackground(true);
	ui->backgroundArea->setPalette(Pal);
}

bool MainWindow::eventFilter( QObject* watched, QEvent* event )
{
	if (watched == ui->colorWheel && event->type() == QEvent::MouseButtonPress)
	{
		const QMouseEvent* me = static_cast<const QMouseEvent*>(event);
		//might want to check the buttons here
		const QPoint p = me->pos(); //...or ->globalPos();

		QImage img = ui->colorWheel->pixmap()->toImage();
		//QRgb rgb = img.pixel(p.x(), p.y());
		QColor color = img.pixelColor(p.x(), p.y());

		QString rgbText = QString::number(color.red()) + ", " + QString::number(color.green()) + ", " + QString::number(color.blue());
		QString hexText = "#" + QString::number(color.red(), 16) + QString::number(color.green(), 16) + QString::number(color.blue(), 16);

		ui->lblColorName->setText(rgbText + '\n' + hexText);
	}

	if (watched == ui->colorWheel && event->type() == QEvent::Paint)
	{
		QPainter painter(ui->colorWheel);

		/* draw circle */
		QPen circlePen(Qt::red);
		circlePen.setWidth(2);
		painter.setPen(circlePen);
		painter.drawEllipse(10.0, 10.0, circleWidth, circleWidth);

		/* draw line */
		QPen linePen(Qt::white);
		linePen.setWidth(1);
		painter.setPen(linePen);
		painter.drawLine(50, 50, 150, 100);
	}

	return false;
}

