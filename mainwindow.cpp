#include "mainwindow.h"
#include "gui_mainwindow.h"

#include <QMouseEvent>
#include <QMessageBox>
#include <QtDebug>
#include <QFileDialog>
#include <QPainter>
#include <QSizeGrip>
#include <QStandardPaths>
#include <QClipboard>

const qreal circleWidth = 14.0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	this->installEventFilter(this);

	// select the triangle by default
	this->ui->rdoGamutShapeTriangle->click();

	this->mixString = 5;
	this->ui->rdoMixString5->click();
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

void MainWindow::on_lightSlider_sliderMoved(int position)
{
	qreal v = (((double)position) / 100.0);

	this->stringLight = v;

	refreshPalette();
}

void MainWindow::on_darkSlider_sliderMoved(int position)
{
	qreal v = (((double)position) / 100.0);

	this->stringDark = v;

	refreshPalette();
}

void MainWindow::on_brightnessSlider_sliderMoved(int position)
{
	qreal v = ((100.0 - (double)position) / 100.0);

	this->ambientColorBrightness = v;

	refreshPalette();
}

void MainWindow::on_powerSlider_sliderMoved(int position)
{
	qreal v = ((100.0 - (double)position) / 100.0);

	this->power = v;

	refreshPalette();
}

void MainWindow::on_rdoGamutShapeLine_clicked(bool checked)
{
	ui->colorWheel->ChangeGamutShape(PrestoPalette::GamutShapeLine);
}

void MainWindow::on_rdoGamutShapeTriangle_clicked(bool checked)
{
	ui->colorWheel->ChangeGamutShape(PrestoPalette::GamutShapeTriangle);
}

void MainWindow::on_rdoGamutShapeSquare_clicked(bool checked)
{
	ui->colorWheel->ChangeGamutShape(PrestoPalette::GamutShapeSquare);
}

void MainWindow::on_rdoMixString1_clicked(bool checked)
{
	this->mixString = 1;
	refreshPalette();
}

void MainWindow::on_rdoMixString3_clicked(bool checked)
{
	this->mixString = 3;
	refreshPalette();
}

void MainWindow::on_rdoMixString5_clicked(bool checked)
{
	this->mixString = 5;
	refreshPalette();
}

void MainWindow::on_btnSaveJPG_clicked()
{
	auto docPath = QStandardPaths::locate(QStandardPaths::DocumentsLocation, QString(), QStandardPaths::LocateDirectory);
	auto docDir = QDir(docPath);
	auto fullPath = docDir.filePath("palette.png");
	auto fileName = QFileDialog::getSaveFileName(this,
						     tr("Save Palette"),
						     fullPath,
						     tr("PNG Files (*.png)"));

	this->ui->visualPalette->grab().save(fileName);
}

void MainWindow::on_btnClipboard_clicked()
{
	QApplication::clipboard()->setPixmap(this->ui->visualPalette->grab());
}

void MainWindow::refreshPalette()
{
	this->ui->visualPalette->Formulate(this->ui->colorWheel->selectedColors,
					   this->ui->colorWheel->selectedColors, // don't need this
					   QVector<QColor>(), // don't need this
					   QColor(128, 128, 128),
					   this->mixString,
					   this->stringLight,
					   this->stringDark,
					   this->enableLighting,
					   QColor(232, 128, 23),
					   this->ambientColorBrightness,
					   this->power);
}

void MainWindow::on_colorWheel_selectedColorsChanged()
{
	refreshPalette();
}

bool MainWindow::eventFilter(QObject* watched, QEvent* event)
{
	/*
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
	*/

	return false;
}

