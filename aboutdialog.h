#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>

namespace Ui
{
class AboutDialog;
}

class AboutDialog : public QDialog
{
	Q_OBJECT

      public:
	explicit AboutDialog(QWidget *parent = 0);
	~AboutDialog();

      private:
	Ui::AboutDialog *ui;

      private slots:
	void on_closeButton_hoverLeave(QHoverEvent *e);
	void on_closeButton_hoverEnter(QHoverEvent *e);
	void on_closeButton_clicked();
};

#endif // ABOUTDIALOG_H
