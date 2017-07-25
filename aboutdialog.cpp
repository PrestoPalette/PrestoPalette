#include "aboutdialog.h"
#include "gui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent, Qt::FramelessWindowHint | Qt::Dialog),
      ui(new Ui::AboutDialog)
{
	ui->setupUi(this);

	setAttribute(Qt::WA_TranslucentBackground);
}

AboutDialog::~AboutDialog()
{
	delete ui;
}

void AboutDialog::on_closeButton_clicked()
{
	this->accept();
}

void AboutDialog::on_closeButton_hoverEnter(QHoverEvent *e)
{
	this->ui->closeButton->setPixmap(QPixmap(":/main/graphics/Close_Hover.png"));
}

void AboutDialog::on_closeButton_hoverLeave(QHoverEvent *e)
{
	this->ui->closeButton->setPixmap(QPixmap(":/main/graphics/Close.png"));
}
