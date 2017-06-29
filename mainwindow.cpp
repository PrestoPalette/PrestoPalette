#include <QMouseEvent>
#include <QMessageBox>
#include <QtDebug>
#include <QFileDialog>
#include <QPainter>
#include <QSizeGrip>
#include <QStandardPaths>
#include <QClipboard>
#include <QBitmap>
#include <QSoundEffect>
#include <QInputDialog>
#include <QJsonDocument>
#include <QJsonObject>

#include "mainwindow.h"
#include "gui_mainwindow.h"
#include "aboutdialog.h"

const qreal circleWidth = 14.0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	stringLight = 0;
	stringDark = 0;
	enableLighting = false;
	ambientColor = QColor::fromRgb(0);
	ambientColorBrightness = 0;
	alpha = 0;
	mixString = 0;

	ui->setupUi(this);

	this->SetCurrentColor(QColor::fromRgb(0, 0, 0));

	/***************************
	 * BEGIN PRESETS
	 ***************************/
	this->ui->rdoGamutShapeSquare->clicked();
	this->ui->rdoCoarseWheel->clicked();
	this->ui->rdoMixString1->clicked();
	this->ui->btnLightingOff->clicked();
	this->ui->backgroundSlider->setValue(92);
	this->ui->alphaSlider->setValue(50);
	this->ui->brightnessSlider->setValue(0);
	this->ui->darkSlider->setValue(70);
	this->ui->lightSlider->setValue(70);

	/***************************
	 * END PRESETS
	 ***************************/

	refresh_sliders();

	this->controlClick.setSource(QUrl::fromLocalFile(":/main/audio/Select.wav"));
	this->controlClick.setVolume(0.25f);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::refresh_lighting_buttons()
{
	this->ui->colorWheel->enableLighting = this->enableLighting;

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

	refresh_palette();
}

void MainWindow::on_btnLightingOn_clicked(bool checked)
{
	this->enableLighting = true;
	controlClick.play();

	refresh_lighting_buttons();
}

void MainWindow::on_btnLightingOff_clicked(bool checked)
{
	this->enableLighting = false;
	controlClick.play();

	refresh_lighting_buttons();
}

void MainWindow::on_backgroundSlider_valueChanged(int position)
{
	int rgb = ((100.0 - (double)position) / 100.0) * 255.0;
	QPalette Pal(palette());
	Pal.setColor(QPalette::Background, QColor::fromRgb(rgb,rgb,rgb));
	ui->backgroundArea->setAutoFillBackground(true);
	ui->backgroundArea->setPalette(Pal);
}

void MainWindow::on_lightSlider_valueChanged(int position)
{
	qreal v = (((double)position) / 100.0);

	this->stringLight = v;

	refresh_palette();

	ui->lblLightPct->setText(QApplication::translate("MainWindow", "LIGHT", 0) + QString(" ") + QString::number(v * 100.0) + QString("%"));
	ui->lblLightPct->adjustSize();
}

void MainWindow::on_darkSlider_valueChanged(int position)
{
	qreal v = (((double)position) / 100.0);

	this->stringDark = v;

	refresh_palette();

	ui->lblDarkPct->setText(QApplication::translate("MainWindow", "DARK", 0) + QString(" ") + QString::number(v * 100.0) + QString("%"));
	ui->lblDarkPct->adjustSize();
}

void MainWindow::on_brightnessSlider_valueChanged(int position)
{
	qreal v = (((double)position) / 100.0);

	this->ambientColorBrightness = v;

	refresh_palette();

	ui->lblBrightnessPct->setText(QApplication::translate("MainWindow", "BRIGHTNESS", 0) + QString(" ") + QString::number(v * 100.0) + QString("%"));
	ui->lblBrightnessPct->adjustSize();
}

void MainWindow::on_alphaSlider_valueChanged(int position)
{
	qreal v = (((double)position) / 100.0);

	this->alpha = v;

	refresh_palette();

	ui->lblAlphaPct->setText(QApplication::translate("MainWindow", "ALPHA", 0) + QString(" ") + QString::number(v * 100.0) + QString("%"));
	ui->lblAlphaPct->adjustSize();
}

void MainWindow::on_rdoCoarseWheel_clicked(bool checked)
{
	ui->colorWheel->ChangeWheelShape(PrestoPalette::WheelShapeCoarse);
	controlClick.play();
	refresh_wheel_buttons();
}

void MainWindow::on_rdoFineWheel_clicked(bool checked)
{
	ui->colorWheel->ChangeWheelShape(PrestoPalette::WheelShapeFine);
	controlClick.play();
	refresh_wheel_buttons();
}

void MainWindow::refresh_wheel_buttons(void)
{
	switch(this->ui->colorWheel->wheelShape)
	{
	case PrestoPalette::GlobalWheelShape::WheelShapeCoarse:
		this->ui->rdoCoarseWheel->setPixmap(QPixmap(":/main/graphics/Button_Course_Selected.png"));
		this->ui->rdoFineWheel->setPixmap(QPixmap(":/main/graphics/Button_Fine_Off.png"));
		break;
	case PrestoPalette::GlobalWheelShape::WheelShapeFine:
		this->ui->rdoCoarseWheel->setPixmap(QPixmap(":/main/graphics/Button_Course_Off.png"));
		this->ui->rdoFineWheel->setPixmap(QPixmap(":/main/graphics/Button_Fine_Selected.png"));
		break;
	default:
		// not sure what to do here
		break;
	}

	this->ui->rdoCoarseWheel->setScaledContents(true);
	this->ui->rdoFineWheel->setScaledContents(true);

	refresh_palette();
}

void MainWindow::on_rdoGamutShapeLine_clicked(bool checked)
{
	ui->colorWheel->ChangeGamutShape(PrestoPalette::GamutShapeLine);
	controlClick.play();
	refresh_gamutShape_buttons();
}

void MainWindow::on_rdoGamutShapeTriangle_clicked(bool checked)
{
	ui->colorWheel->ChangeGamutShape(PrestoPalette::GamutShapeTriangle);
	controlClick.play();
	refresh_gamutShape_buttons();
}

void MainWindow::on_rdoGamutShapeSquare_clicked(bool checked)
{
	ui->colorWheel->ChangeGamutShape(PrestoPalette::GamutShapeSquare);
	controlClick.play();
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
	refresh_palette();
	refresh_mixString_buttons();
	controlClick.play();
}

void MainWindow::on_rdoMixString3_clicked(bool checked)
{
	this->mixString = 3;
	controlClick.play();
	refresh_mixString_buttons();
}

void MainWindow::on_rdoMixString5_clicked(bool checked)
{
	this->mixString = 5;
	controlClick.play();
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

	refresh_palette();
}

void MainWindow::on_btnSaveJPG_hoverEnter(QHoverEvent* e)
{
	this->ui->btnSaveJPG->setPixmap(QPixmap(":/main/graphics/PNGIcon_Hover.png"));
}

void MainWindow::on_btnSaveJPG_hoverLeave(QHoverEvent* e)
{
	this->ui->btnSaveJPG->setPixmap(QPixmap(":/main/graphics/PNGIcon.png"));
}

void MainWindow::on_btnSave_hoverEnter(QHoverEvent* e)
{
	this->ui->btnSave->setPixmap(QPixmap(":/main/graphics/SaveIcon_Hover.png"));
}

void MainWindow::on_btnSave_hoverLeave(QHoverEvent* e)
{
	this->ui->btnSave->setPixmap(QPixmap(":/main/graphics/SaveIcon.png"));
}

void MainWindow::on_btnLoad_hoverEnter(QHoverEvent* e)
{
	this->ui->btnLoad->setPixmap(QPixmap(":/main/graphics/LoadIcon_Hover.png"));
}

void MainWindow::on_btnLoad_hoverLeave(QHoverEvent* e)
{
	this->ui->btnLoad->setPixmap(QPixmap(":/main/graphics/LoadIcon.png"));
}

void MainWindow::on_btnAbout_hoverEnter(QHoverEvent* e)
{
	this->ui->btnAbout->setPixmap(QPixmap(":/main/graphics/AboutIcon_Hover.png"));
}

void MainWindow::on_btnAbout_hoverLeave(QHoverEvent* e)
{
	this->ui->btnAbout->setPixmap(QPixmap(":/main/graphics/AboutIcon.png"));
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

	this->ui->btnSaveJPG->setPixmap(QPixmap(":/main/graphics/PNGIcon.png"));
}

void MainWindow::on_btnSave_clicked()
{
	auto docPath = QStandardPaths::locate(QStandardPaths::DocumentsLocation, QString(), QStandardPaths::LocateDirectory);
	auto docDir = QDir(docPath);
	auto fullPath = docDir.filePath("palette.json");
	auto fileName = QFileDialog::getSaveFileName(this,
						     tr("Save Palette"),
						     fullPath,
						     tr("JSON Files (*.json)"));

	QFile saveFile(fileName);
	if (!saveFile.open(QIODevice::WriteOnly))
	{
		qWarning("Couldn't open file for writing.");
		return;
	}

	QJsonObject saveState;

	// write the state here
	saveState["gamutShape"] = this->ui->colorWheel->gamutShape;
	saveState["wheelShape"] = this->ui->colorWheel->wheelShape;
	saveState["mixString"] = this->mixString;
	saveState["enableLighting"] = this->enableLighting;
	saveState["backgroundSlider"] = this->ui->backgroundSlider->value();
	saveState["alphaSlider"] = this->ui->alphaSlider->value();
	saveState["brightnessSlider"] = this->ui->brightnessSlider->value();
	saveState["darkSlider"] = this->ui->darkSlider->value();
	saveState["lightSlider"] = this->ui->lightSlider->value();

	this->ui->colorWheel->SaveState(saveState);

	QJsonDocument saveDoc(saveState);
	saveFile.write(saveDoc.toJson());
}

void MainWindow::on_btnLoad_clicked()
{
	auto docPath = QStandardPaths::locate(QStandardPaths::DocumentsLocation, QString(), QStandardPaths::LocateDirectory);
	auto docDir = QDir(docPath);
	auto fullPath = docDir.filePath("palette.json");
	auto fileName = QFileDialog::getOpenFileName(this,
						     tr("Load Palette"),
						     fullPath,
						     tr("JSON Files (*.json)"));

	QFile loadFile(fileName);
	if (!loadFile.open(QIODevice::ReadOnly))
	{
		qWarning("Couldn't open file.");
		return;
	}

	QByteArray saveData = loadFile.readAll();

	QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

	QJsonObject saveState = loadDoc.object();

	// load the state here
	this->ui->colorWheel->ChangeGamutShape((PrestoPalette::GlobalGamutShape)saveState["gamutShape"].toInt());
	this->ui->colorWheel->ChangeWheelShape((PrestoPalette::GlobalWheelShape)saveState["wheelShape"].toInt());
	this->mixString = saveState["mixString"].toInt();
	this->enableLighting = saveState["enableLighting"].toBool();
	this->ui->backgroundSlider->setValue(saveState["backgroundSlider"].toInt());
	this->ui->alphaSlider->setValue(saveState["alphaSlider"].toInt());
	this->ui->brightnessSlider->setValue(saveState["brightnessSlider"].toInt());
	this->ui->darkSlider->setValue(saveState["darkSlider"].toInt());
	this->ui->lightSlider->setValue(saveState["lightSlider"].toInt());

	this->ui->colorWheel->LoadState(saveState);

	refresh_lighting_buttons();
	refresh_mixString_buttons();
	refresh_gamutShape_buttons();
	refresh_wheel_buttons();
	refresh_palette();
}

void MainWindow::on_btnAbout_clicked()
{
	auto about = new AboutDialog(this);
	about->exec();
}

void MainWindow::on_btnClipboard_clicked()
{
	QApplication::clipboard()->setPixmap(this->ui->visualPalette->grab());

	this->ui->btnClipboard->setPixmap(QPixmap(":/main/graphics/ClipboardIcon.png"));
}

void MainWindow::on_btnClipboard_hoverEnter(QHoverEvent* e)
{
	this->ui->btnClipboard->setPixmap(QPixmap(":/main/graphics/ClipboardIcon_Hover.png"));
}

void MainWindow::on_btnClipboard_hoverLeave(QHoverEvent* e)
{
	this->ui->btnClipboard->setPixmap(QPixmap(":/main/graphics/ClipboardIcon.png"));
}

void MainWindow::refresh_sliders()
{
	this->on_backgroundSlider_valueChanged(this->ui->backgroundSlider->value());
	this->on_alphaSlider_valueChanged(this->ui->alphaSlider->value());
	this->on_brightnessSlider_valueChanged(this->ui->brightnessSlider->value());
	this->on_darkSlider_valueChanged(this->ui->darkSlider->value());
	this->on_lightSlider_valueChanged(this->ui->lightSlider->value());
}

void MainWindow::refresh_palette()
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
	refresh_palette();
}

void MainWindow::on_colorWheel_hoverColor(const QColor &color)
{
	SetCurrentColor(color);
}

void MainWindow::on_colorWheel_lightingColorChanged(const QColor &color)
{
	this->ambientColor = color;

	this->ui->alphaSliderStyle->setColor(this->ambientColor);
	this->ui->brightnessSliderStyle->setColor(this->ambientColor);

	refresh_palette();

	this->ui->alphaSlider->update();
	this->ui->brightnessSlider->update();
}

void MainWindow::on_visualPalette_hoverColor(const QColor &color)
{
	SetCurrentColor(color);
}

void MainWindow::SetCurrentColor(const QColor &color)
{
	QPixmap pm = QPixmap(":/main/graphics/CurrentColorSwatch.png");
	QPixmap pxr = QPixmap(pm.size());
	pxr.fill(color);
	pxr.setMask(pm.createMaskFromColor(Qt::transparent));
	this->ui->currentColorSwatch->setPixmap(pxr);

	QString rgbText = QString::number(color.red()) + ", " + QString::number(color.green()) + ", " + QString::number(color.blue());
	//QString hexText = "#" + QString::number(color.red(), 16) + QString::number(color.green(), 16) + QString::number(color.blue(), 16);

	//this->ui->currentColorSwatchCaption->setText(QString("RGB:" + rgbText + "\r\nHEX: " + hexText));
	this->ui->currentColorSwatchCaption->setText(QString(rgbText));
	//this->ui->currentColorSwatchCaption->adjustSize();
}
