#ifndef UI_ABOUTDIALOG_H
#define UI_ABOUTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QFontDatabase>
#include <QScreen>
#include "clickablelabel.h"

#define ABOUT_DIALOG_WIDTH 750
#define ABOUT_DIALOG_HEIGHT 520

QT_BEGIN_NAMESPACE

class Ui_AboutDialog
{
      public:
	QWidget *backgroundArea;
	ClickableLabel *closeButton;

	QLabel *cornerTopRight;
	QLabel *cornerTopLeft;
	QLabel *cornerBottomLeft;
	QLabel *cornerBottomRight;
	QLabel *borderTop;
	QLabel *borderRight;
	QLabel *borderLeft;
	QLabel *borderBottom;

	QLabel *ppLogo;

	QLabel *copyrightText;
	QLabel *webLink;
	QLabel *licenseText;

	QLabel *qtLogo;
	QLabel *builtWith;

	QString calibri;

	void setupUi(QDialog *AboutDialog)
	{
		calibri = QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/main/fonts/calibrib.ttf")).at(0);

		qreal screenDPI = QApplication::primaryScreen()->physicalDotsPerInch() / 96.0;

		QFont fontSubTitle;
		fontSubTitle.setFamily(this->calibri);
		fontSubTitle.setPixelSize(15.0 * screenDPI);
		//fontSubTitle.setPointSize(15);

		QFont fontWebLink;
		fontWebLink.setFamily(this->calibri);
		fontWebLink.setPixelSize(18.0 * screenDPI);
		//fontWebLink.setPointSize(18);

		QFont fontLicenseText;
		fontLicenseText.setFamily(this->calibri);
		fontLicenseText.setPixelSize(11.0 * screenDPI);
		//fontLicenseText.setPointSizeF(11.0f);

		QFont fontBuiltWith;
		fontBuiltWith.setFamily(this->calibri);
		fontBuiltWith.setPixelSize(12.0 * screenDPI);
		//fontBuiltWith.setPointSizeF(12.0f);

		if (AboutDialog->objectName().isEmpty())
			AboutDialog->setObjectName(QStringLiteral("AboutDialog"));

		AboutDialog->resize(ABOUT_DIALOG_WIDTH, ABOUT_DIALOG_HEIGHT);

		/*
	 * block window resize
	 */
		AboutDialog->setFixedSize(QSize(ABOUT_DIALOG_WIDTH, ABOUT_DIALOG_HEIGHT));

		backgroundArea = new QWidget(AboutDialog);
		backgroundArea->setObjectName(QStringLiteral("backgroundArea"));
		//backgroundArea->setGeometry(QRect(0, 0, ABOUT_DIALOG_WIDTH, ABOUT_DIALOG_HEIGHT));
		backgroundArea->setGeometry(QRect(32, 32, ABOUT_DIALOG_WIDTH - 64, ABOUT_DIALOG_HEIGHT - 32));
		int rgb = 18;
		QPalette Pal;
		Pal.setColor(QPalette::Background, QColor::fromRgb(rgb, rgb, rgb));
		backgroundArea->setAutoFillBackground(true);
		backgroundArea->setPalette(Pal);

		closeButton = new ClickableLabel(AboutDialog);
		closeButton->setObjectName(QStringLiteral("closeButton"));
		closeButton->setGeometry(QRect(704, 13, 31, 31));
		closeButton->setPixmap(QPixmap(":/main/graphics/Close.png"));
		closeButton->setScaledContents(true);

		cornerTopRight = new QLabel(AboutDialog);
		cornerTopRight->setObjectName(QStringLiteral("cornerTopRight"));
		cornerTopRight->setGeometry(QRect(718, 0, 32, 32));
		cornerTopRight->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/PopUp_TopRight.png")));
		cornerTopLeft = new QLabel(AboutDialog);
		cornerTopLeft->setObjectName(QStringLiteral("cornerTopLeft"));
		cornerTopLeft->setGeometry(QRect(0, 0, 32, 32));
		cornerTopLeft->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/PopUp_TopLeft.png")));
		borderTop = new QLabel(AboutDialog);
		borderTop->setObjectName(QStringLiteral("borderTop"));
		borderTop->setGeometry(QRect(32, 0, 686, 32));
		borderTop->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/PopUp_Top.png")));
		borderTop->setScaledContents(true);
		borderRight = new QLabel(AboutDialog);
		borderRight->setObjectName(QStringLiteral("borderRight"));
		borderRight->setGeometry(QRect(718, 32, 32, 456));
		borderRight->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/PopUp_Right.png")));
		borderRight->setScaledContents(true);
		borderLeft = new QLabel(AboutDialog);
		borderLeft->setObjectName(QStringLiteral("borderLeft"));
		borderLeft->setGeometry(QRect(0, 32, 32, 456));
		borderLeft->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/PopUp_Left.png")));
		borderLeft->setScaledContents(true);
		cornerBottomLeft = new QLabel(AboutDialog);
		cornerBottomLeft->setObjectName(QStringLiteral("cornerBottomLeft"));
		cornerBottomLeft->setGeometry(QRect(0, 488, 32, 32));
		cornerBottomLeft->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/PopUp_BottomLeft.png")));
		cornerBottomRight = new QLabel(AboutDialog);
		cornerBottomRight->setObjectName(QStringLiteral("cornerBottomRight"));
		cornerBottomRight->setGeometry(QRect(718, 488, 32, 32));
		cornerBottomRight->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/PopUp_BottomRight.png")));
		borderBottom = new QLabel(AboutDialog);
		borderBottom->setObjectName(QStringLiteral("borderBottom"));
		borderBottom->setGeometry(QRect(32, 488, 686, 32));
		borderBottom->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/PopUp_Bottom.png")));
		borderBottom->setScaledContents(true);

		ppLogo = new QLabel(AboutDialog);
		ppLogo->setObjectName(QStringLiteral("ppLogo"));
		ppLogo->setGeometry(QRect(108, 32, 539, 79));
		ppLogo->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/PPLogo.png")));

		copyrightText = new QLabel(AboutDialog);
		copyrightText->setObjectName(QStringLiteral("copyrightText"));
		copyrightText->setGeometry(QRect(105, 145, 539, 79));
		copyrightText->setText("© 2017 by John Cboins and Darryl T. Agostinelli. All Rights Reserved.");
		copyrightText->setFont(fontSubTitle);
		copyrightText->setStyleSheet(QLatin1String("QLabel { color : #C3C3C3;}"));
		copyrightText->adjustSize();

		webLink = new QLabel(AboutDialog);
		webLink->setObjectName(QStringLiteral("webLink"));
		webLink->setGeometry(QRect(235, 190, 258, 79));
		webLink->setText("www.prestopalette.com");
		webLink->setFont(fontWebLink);
		webLink->setStyleSheet(QLatin1String("QLabel { color : #E9E995;}"));
		webLink->adjustSize();

		licenseText = new QLabel(AboutDialog);
		licenseText->setObjectName(QStringLiteral("licenseText"));
		licenseText->setGeometry(QRect(50, 240, 672, 235));
		licenseText->setText("Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the \"Software\"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:\nThe above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.\nTHE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.");
		licenseText->setFont(fontLicenseText);
		licenseText->setStyleSheet(QLatin1String("QLabel { color : #C3C3C3;}"));
		licenseText->setWordWrap(true);
		licenseText->adjustSize();

		qtLogo = new QLabel(AboutDialog);
		qtLogo->setObjectName(QStringLiteral("qtLogo"));
		qtLogo->setGeometry(QRect(702, 488, 25, 18));
		qtLogo->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/QtIcon.png")));

		builtWith = new QLabel(AboutDialog);
		builtWith->setObjectName(QStringLiteral("builtWith"));
		builtWith->setGeometry(QRect(630, 490, 50, 10));
		builtWith->setText("Built with");
		builtWith->setFont(fontBuiltWith);
		builtWith->setStyleSheet(QLatin1String("QLabel { color : #363636;}"));
		builtWith->adjustSize();

		retranslateUi(AboutDialog);

		QMetaObject::connectSlotsByName(AboutDialog);

		backgroundArea->lower();
		borderLeft->lower();
		borderRight->lower();
		borderBottom->lower();
		borderTop->lower();
		cornerBottomLeft->lower();
		cornerBottomRight->lower();
		cornerTopLeft->lower();
		cornerTopRight->lower();
		backgroundArea->lower();
		closeButton->raise();
	} // setupUi

	void retranslateUi(QDialog *AboutDialog)
	{
		// blank out the title of the dialog box
		AboutDialog->setWindowTitle(QApplication::translate("AboutDialog", "", Q_NULLPTR));
	}
};

namespace Ui
{
class AboutDialog : public Ui_AboutDialog
{
};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTDIALOG_H
