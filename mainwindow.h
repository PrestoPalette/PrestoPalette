#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "gui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	
	void refreshPalette();
	void SetCurrentColor(const QColor &fillColor);
	
private:
	qreal stringLight;
	qreal stringDark;
	bool enableLighting;
	qreal ambientColorBrightness;
	qreal power;
	int mixString;

private slots:
	void on_backgroundSlider_sliderMoved(int position);
	void on_rdoGamutShapeTriangle_clicked(bool checked = false);
	void on_rdoGamutShapeLine_clicked(bool checked = false);
	void on_rdoGamutShapeSquare_clicked(bool checked = false);
	void on_btnSaveJPG_clicked();
	void on_btnClipboard_clicked();
	void on_colorWheel_selectedColorsChanged();
	void on_lightSlider_sliderMoved(int position);
	void on_darkSlider_sliderMoved(int position);
	void on_brightnessSlider_sliderMoved(int position);
	void on_powerSlider_sliderMoved(int position);
	void on_colorWheel_hoverColor(const QColor &color);

	void on_rdoMixString1_clicked(bool checked = false);
	void on_rdoMixString3_clicked(bool checked = false);
	void on_rdoMixString5_clicked(bool checked = false);

private:
	//bool eventFilter( QObject* watched, QEvent* event );

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
