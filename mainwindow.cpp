#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);
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
	int rgb = ((double)position / 100.0) * 255.0;
	QPalette Pal(palette());
	Pal.setColor(QPalette::Background, QColor::fromRgb(rgb,rgb,rgb));
	this->ui->widget->setAutoFillBackground(true);
	this->ui->widget->setPalette(Pal);
}
