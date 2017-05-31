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
#include <QBitmap>

const qreal circleWidth = 14.0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	this->SetCurrentColor(QColor::fromRgb(0, 0, 0));

	/***************************
	 * BEGIN PRESETS
	 ***************************/
	// select the triangle by default
	this->ui->rdoGamutShapeTriangle->clicked();

	// select the course wheel by default
	this->ui->rdoCourseWheel->clicked();

	this->mixString = 3;
	this->ui->rdoMixString5->clicked();

	this->ui->btnLightingOff->clicked();
	
	this->ui->backgroundSlider->setSliderPosition(100);
	this->ui->alphaSlider->setSliderPosition(50);
	this->ui->brightnessSlider->setSliderPosition(0);
	this->ui->darkSlider->setSliderPosition(70);
	this->ui->lightSlider->setSliderPosition(70);

	/***************************
	 * END PRESETS
	 ***************************/

	this->on_backgroundSlider_sliderMoved(this->ui->backgroundSlider->value());
	this->on_alphaSlider_sliderMoved(this->ui->alphaSlider->value());
	this->on_brightnessSlider_sliderMoved(this->ui->brightnessSlider->value());
	this->on_darkSlider_sliderMoved(this->ui->darkSlider->value());
	this->on_lightSlider_sliderMoved(this->ui->lightSlider->value());
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::refresh_lighting_buttons()
{
	if (enableLighting)
	{
		this->ui->btnLightingOn->setPixmap(QPixmap(":/main/graphics/Button_On_Selected.png"));
		this->ui->btnLightingOff->setPixmap(QPixmap(":/main/graphics/Button_Off_Off.png"));
	}
	else
	{
		this->ui->btnLightingOn->setPixmap(QPixmap(":/main/graphics/Button_On_Off.png"));
		this->ui->btnLightingOff->setPixmap(QPixmap(":/main/graphics/Button_Off_Selected.png"));
	}

	this->ui->colorWheel->repaint();

	refreshPalette();
}

void MainWindow::on_btnLightingOn_clicked(bool checked)
{
	this->enableLighting = true;
	this->ui->colorWheel->enableLighting = true;

	refresh_lighting_buttons();
}

void MainWindow::on_btnLightingOff_clicked(bool checked)
{
	this->enableLighting = false;
	this->ui->colorWheel->enableLighting = false;

	refresh_lighting_buttons();
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

	ui->lblLightPct->setText(QApplication::translate("MainWindow", "LIGHT", 0) + QString(" ") + QString::number(v * 100.0) + QString("%"));
	ui->lblLightPct->adjustSize();
}

void MainWindow::on_darkSlider_sliderMoved(int position)
{
	qreal v = (((double)position) / 100.0);

	this->stringDark = v;

	refreshPalette();

	ui->lblDarkPct->setText(QApplication::translate("MainWindow", "DARK", 0) + QString(" ") + QString::number(v * 100.0) + QString("%"));
	ui->lblDarkPct->adjustSize();
}

void MainWindow::on_brightnessSlider_sliderMoved(int position)
{
	qreal v = (((double)position) / 100.0);

	this->ambientColorBrightness = v;

	refreshPalette();

	ui->lblBrightnessPct->setText(QApplication::translate("MainWindow", "BRIGHTNESS", 0) + QString(" ") + QString::number(v * 100.0) + QString("%"));
	ui->lblBrightnessPct->adjustSize();
}

void MainWindow::on_alphaSlider_sliderMoved(int position)
{
	qreal v = (((double)position) / 100.0);

	this->alpha = v;

	refreshPalette();

	ui->lblAlphaPct->setText(QApplication::translate("MainWindow", "ALPHA", 0) + QString(" ") + QString::number(v * 100.0) + QString("%"));
	ui->lblAlphaPct->adjustSize();
}

void MainWindow::on_rdoCourseWheel_clicked(bool checked)
{
	ui->colorWheel->ChangeWheelShape(PrestoPalette::WheelShapeCourse);
	refresh_wheel_buttons();
	refreshPalette();
}

void MainWindow::on_rdoFineWheel_clicked(bool checked)
{
	ui->colorWheel->ChangeWheelShape(PrestoPalette::WheelShapeFine);
	refresh_wheel_buttons();
	refreshPalette();
}

void MainWindow::refresh_wheel_buttons(void)
{
	switch(this->ui->colorWheel->wheelShape)
	{
	case PrestoPalette::GlobalWheelShape::WheelShapeCourse:
		this->ui->rdoCourseWheel->setPixmap(QPixmap(":/main/graphics/Button_Course_Selected.png"));
		this->ui->rdoFineWheel->setPixmap(QPixmap(":/main/graphics/Button_Fine_Off.png"));
		break;
	case PrestoPalette::GlobalWheelShape::WheelShapeFine:
		this->ui->rdoCourseWheel->setPixmap(QPixmap(":/main/graphics/Button_Course_Off.png"));
		this->ui->rdoFineWheel->setPixmap(QPixmap(":/main/graphics/Button_Fine_Selected.png"));
		break;
	default:
		// not sure what to do here
		break;
	}

	this->ui->rdoCourseWheel->setScaledContents(true);
	this->ui->rdoFineWheel->setScaledContents(true);
}

void MainWindow::on_rdoGamutShapeLine_clicked(bool checked)
{
	ui->colorWheel->ChangeGamutShape(PrestoPalette::GamutShapeLine);
	refresh_gamutShape_buttons();
}

void MainWindow::on_rdoGamutShapeTriangle_clicked(bool checked)
{
	ui->colorWheel->ChangeGamutShape(PrestoPalette::GamutShapeTriangle);
	refresh_gamutShape_buttons();
}

void MainWindow::on_rdoGamutShapeSquare_clicked(bool checked)
{
	ui->colorWheel->ChangeGamutShape(PrestoPalette::GamutShapeSquare);
	refresh_gamutShape_buttons();
}

void MainWindow::refresh_gamutShape_buttons(void)
{
	switch(this->ui->colorWheel->gamutShape)
	{
	case PrestoPalette::GlobalGamutShape::GamutShapeLine:
		this->ui->rdoGamutShapeLine->setPixmap(QPixmap(":/main/graphics/Button_2point_Selected.png"));
		this->ui->rdoGamutShapeTriangle->setPixmap(QPixmap(":/main/graphics/Button_Triad_Off.png"));
		this->ui->rdoGamutShapeSquare->setPixmap(QPixmap(":/main/graphics/Button_Quad_Off.png"));
		break;
	case PrestoPalette::GlobalGamutShape::GamutShapeTriangle:
		this->ui->rdoGamutShapeLine->setPixmap(QPixmap(":/main/graphics/button_2point_Off.png"));
		this->ui->rdoGamutShapeTriangle->setPixmap(QPixmap(":/main/graphics/Button_Triad_Selected.png"));
		this->ui->rdoGamutShapeSquare->setPixmap(QPixmap(":/main/graphics/Button_Quad_Off.png"));
		break;
	case PrestoPalette::GlobalGamutShape::GamutShapeSquare:
		this->ui->rdoGamutShapeLine->setPixmap(QPixmap(":/main/graphics/button_2point_Off.png"));
		this->ui->rdoGamutShapeTriangle->setPixmap(QPixmap(":/main/graphics/Button_Triad_Off.png"));
		this->ui->rdoGamutShapeSquare->setPixmap(QPixmap(":/main/graphics/Button_Quad_Selected.png"));
		break;
	default:
		// not sure what to do here
		break;
	}

	this->ui->rdoGamutShapeLine->setScaledContents(true);
	this->ui->rdoGamutShapeTriangle->setScaledContents(true);
	this->ui->rdoGamutShapeSquare->setScaledContents(true);
}

void MainWindow::on_rdoMixString1_clicked(bool checked)
{
	this->mixString = 1;
	refreshPalette();
	refresh_mixString_buttons();
}

void MainWindow::on_rdoMixString3_clicked(bool checked)
{
	this->mixString = 3;
	refreshPalette();
	refresh_mixString_buttons();
}

void MainWindow::on_rdoMixString5_clicked(bool checked)
{
	this->mixString = 5;
	refreshPalette();
	refresh_mixString_buttons();
}

void MainWindow::refresh_mixString_buttons(void)
{
	switch(this->mixString)
	{
	case 1:
		this->ui->rdoMixString1->setPixmap(QPixmap(":/main/graphics/Button_1_Selected.png"));
		this->ui->rdoMixString3->setPixmap(QPixmap(":/main/graphics/Button_3_Off.png"));
		this->ui->rdoMixString5->setPixmap(QPixmap(":/main/graphics/Button_5_Off.png"));
		break;
	case 3:
		this->ui->rdoMixString1->setPixmap(QPixmap(":/main/graphics/Button_1_Off.png"));
		this->ui->rdoMixString3->setPixmap(QPixmap(":/main/graphics/Button_3_Selected.png"));
		this->ui->rdoMixString5->setPixmap(QPixmap(":/main/graphics/Button_5_Off.png"));
		break;
	case 5:
		this->ui->rdoMixString1->setPixmap(QPixmap(":/main/graphics/Button_1_Off.png"));
		this->ui->rdoMixString3->setPixmap(QPixmap(":/main/graphics/Button_3_Off.png"));
		this->ui->rdoMixString5->setPixmap(QPixmap(":/main/graphics/Button_5_Selected.png"));
		break;
	default:
		this->mixString = 5;
		refresh_mixString_buttons();
		break;
	}

	this->ui->rdoMixString1->setScaledContents(true);
	this->ui->rdoMixString3->setScaledContents(true);
	this->ui->rdoMixString5->setScaledContents(true);
}

void MainWindow::on_btnSaveJPG_pressed()
{
	this->ui->btnSaveJPG->setPixmap(QPixmap(":/main/graphics/JPGIcon_Down.png"));
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

	this->ui->btnSaveJPG->setPixmap(QPixmap(":/main/graphics/JPGIcon.png"));
}

void MainWindow::on_btnClipboard_clicked()
{
	QApplication::clipboard()->setPixmap(this->ui->visualPalette->grab());

	this->ui->btnClipboard->setPixmap(QPixmap(":/main/graphics/ClipboardIcon.png"));
}

void MainWindow::on_btnClipboard_pressed()
{
	this->ui->btnClipboard->setPixmap(QPixmap(":/main/graphics/ClipboardIcon_Down.png"));
}

void MainWindow::refreshPalette()
{
	this->ui->visualPalette->Formulate(this->ui->colorWheel->selectedColors,
					   QVector<QColor>(), // don't need this
					   QVector<QColor>(), // don't need this
					   QColor(), // don't need this
					   this->mixString,
					   this->stringLight,
					   this->stringDark,
					   this->enableLighting,
					   this->ambientColor,
					   this->ambientColorBrightness,
					   this->alpha);
}

void MainWindow::on_colorWheel_selectedColorsChanged()
{
	refreshPalette();
}

void MainWindow::on_colorWheel_hoverColor(const QColor &color)
{
	SetCurrentColor(color);
}

void MainWindow::on_colorWheel_lightingColorChanged(const QColor &color)
{
	// TODO -- change the slider color

	this->ambientColor = color;

	refreshPalette();

	/*this->ui->alphaSlider->setStyleSheet("QSlider::groove:horizontal {background-color: yellow; background-image:url(:/main/graphics/AlphaSliderOverlay.png);}"
					"QSlider::handle:horizontal {background-image:url(:/main/graphics/SliderHandle.png); height:21px; width: 21px;}");*/

	/*this->ui->alphaSlider->setStyleSheet("QSlider::groove:horizontal {color: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 rgba(75, 150, 202, 0), stop:1 rgba(75, 150, 202, 255));}"
						"QSlider::handle:horizontal {background-image:url(:/main/graphics/SliderHandle.png); height:21px; width: 21px;}");
*/
}

void MainWindow::SetCurrentColor(const QColor &color)
{
	auto pm = new QPixmap(":/main/graphics/CurrentColorSwatch.png");
	auto pxr = new QPixmap(pm->size());
	pxr->fill(color);
	pxr->setMask(pm->createMaskFromColor(Qt::transparent));
	this->ui->currentColorSwatch->setPixmap(*pxr);

	QString rgbText = QString::number(color.red()) + ", " + QString::number(color.green()) + ", " + QString::number(color.blue());
	//QString hexText = "#" + QString::number(color.red(), 16) + QString::number(color.green(), 16) + QString::number(color.blue(), 16);

	//this->ui->currentColorSwatchCaption->setText(QString("RGB:" + rgbText + "\r\nHEX: " + hexText));
	this->ui->currentColorSwatchCaption->setText(QString(rgbText));
	//this->ui->currentColorSwatchCaption->adjustSize();
}
