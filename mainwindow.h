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
	
private slots:
	void on_actionExit_triggered();
	void on_backgroundSlider_sliderMoved(int position);
	void on_rdoGamutShapeTriangle_clicked(bool checked = false);
	void on_rdoGamutShapeLine_clicked(bool checked = false);
	void on_rdoGamutShapeSquare_clicked(bool checked = false);
	void on_btnSaveJPG_clicked();
	void on_btnClipboard_clicked();
	void on_colorWheel_selectedColorsChanged();

private:
	bool eventFilter( QObject* watched, QEvent* event );

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
