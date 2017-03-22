#ifndef UI_MAINWINDOWX_H
#define UI_MAINWINDOWX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "circlepalette.h"
#include "visualpalette.h"
#include "clickablelabel.h"

#define APP_WIDTH 1250
#define APP_HEIGHT 800
#define APP_FRAMETOP 10
#define BORDER_SIZE 15

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    CirclePalette *colorWheel;
    QGroupBox *groupBoxWheel;
    QRadioButton *rdoFineWheel;
    QRadioButton *rdoCourseWheel;
    QGroupBox *groupBoxGamutShape;
    QRadioButton *rdoGamutShapeLine;
    QRadioButton *rdoGamutShapeTriangle;
    QRadioButton *rdoGamutShapeSquare;
    QGroupBox *groupBoxMixString;
    QRadioButton *rdoMixString1;
    QRadioButton *rdoMixString3;
    QRadioButton *rdoMixString4;
    QRadioButton *rdoMixString5;
    QGroupBox *groupBoxBackgroundSlider;
    QSlider *backgroundSlider;
    QSlider *lightSlider;
    QSlider *darkSlider;
    QSlider *brightnessSlider;
    QSlider *powerSlider;
    ClickableLabel *btnClipboard;
    QWidget *backgroundArea;
    QLabel *ppLogo;
    QLabel *cornerTopRight;
    QLabel *cornerTopLeft;
    QLabel *borderTop;
    QLabel *borderRight;
    QLabel *borderLeft;
    VisualPalette *visualPalette;
    QLabel *lblColorName;
    ClickableLabel *btnSaveJPG;
    QLabel *lblCurrentColor;
    QLabel *cornerBottomLeft;
    QLabel *cornerBottomRight;
    QLabel *borderBottom;
    QLabel *toolbarBackground;

    QLabel *line1;
    QLabel *line2;
    QLabel *line3;
    QLabel *line4;
    QLabel *line5;
    QLabel *line6;
    QLabel *line7;

    void positionDividingLine(QLabel *line, const QRect &position)
    {
	    line->setGeometry(position);
	    line->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/Divider.png")));
	    line->setScaledContents(true);
    }

    void setupUi(QMainWindow *MainWindow)
    {
	if (MainWindow->objectName().isEmpty())
	    MainWindow->setObjectName(QStringLiteral("MainWindow"));

	MainWindow->resize(QSize(APP_WIDTH, APP_HEIGHT));

	/*
	 * block window resize
	 */
	MainWindow->setFixedSize(QSize(APP_WIDTH, APP_HEIGHT));

	centralWidget = new QWidget(MainWindow);
	centralWidget->setObjectName(QStringLiteral("centralWidget"));
	colorWheel = new CirclePalette(centralWidget);
	colorWheel->setObjectName(QStringLiteral("colorWheel"));
	colorWheel->setGeometry(QRect(44, 37, 549, 549)); // TODO this should match the sizes inside this control
	visualPalette = new VisualPalette(centralWidget);
	visualPalette->setObjectName(QStringLiteral("visualPalette"));
	visualPalette->setGeometry(QRect(643, 74, 540, 390));
	groupBoxWheel = new QGroupBox(centralWidget);
	groupBoxWheel->setObjectName(QStringLiteral("groupBoxWheel"));
	groupBoxWheel->setGeometry(QRect(190, 580, 101, 111));
	QFont font;
	font.setFamily(QStringLiteral("MuseJazz"));
	font.setBold(true);
	font.setWeight(75);
	groupBoxWheel->setFont(font);
	groupBoxWheel->setStyleSheet(QLatin1String("QGroupBox { \n"
"	border: 0px solid gray; \n"
" } \n"
"\n"
"QGroupBox::title {\n"
"	font-weight: bold;\n"
"}"));
	groupBoxWheel->setAlignment(Qt::AlignCenter);
	rdoFineWheel = new QRadioButton(groupBoxWheel);
	rdoFineWheel->setObjectName(QStringLiteral("rdoFineWheel"));
	rdoFineWheel->setGeometry(QRect(10, 30, 104, 25));
	rdoCourseWheel = new QRadioButton(groupBoxWheel);
	rdoCourseWheel->setObjectName(QStringLiteral("rdoCourseWheel"));
	rdoCourseWheel->setGeometry(QRect(10, 50, 104, 25));
	groupBoxGamutShape = new QGroupBox(centralWidget);
	groupBoxGamutShape->setObjectName(QStringLiteral("groupBoxGamutShape"));
	groupBoxGamutShape->setGeometry(QRect(330, 580, 151, 151));
	groupBoxGamutShape->setFont(font);
	groupBoxGamutShape->setStyleSheet(QLatin1String("QGroupBox { \n"
"	border: 0px solid gray; \n"
" } \n"
"\n"
"QGroupBox::title {\n"
"	font-weight: bold;\n"
"}"));
	groupBoxGamutShape->setAlignment(Qt::AlignCenter);
	rdoGamutShapeLine = new QRadioButton(groupBoxGamutShape);
	rdoGamutShapeLine->setObjectName(QStringLiteral("rdoGamutShapeLine"));
	rdoGamutShapeLine->setGeometry(QRect(10, 30, 104, 25));
	rdoGamutShapeTriangle = new QRadioButton(groupBoxGamutShape);
	rdoGamutShapeTriangle->setObjectName(QStringLiteral("rdoGamutShapeTriangle"));
	rdoGamutShapeTriangle->setGeometry(QRect(10, 50, 104, 25));
	rdoGamutShapeSquare = new QRadioButton(groupBoxGamutShape);
	rdoGamutShapeSquare->setObjectName(QStringLiteral("rdoGamutShapeSquare"));
	rdoGamutShapeSquare->setGeometry(QRect(10, 70, 104, 25));
	groupBoxMixString = new QGroupBox(centralWidget);
	groupBoxMixString->setObjectName(QStringLiteral("groupBoxMixString"));
	groupBoxMixString->setGeometry(QRect(500, 580, 101, 111));
	groupBoxMixString->setFont(font);
	groupBoxMixString->setStyleSheet(QLatin1String("QGroupBox { \n"
"	border: 0px solid gray; \n"
" } \n"
"\n"
"QGroupBox::title {\n"
"	font-weight: bold;\n"
"}"));
	groupBoxMixString->setAlignment(Qt::AlignCenter);
	rdoMixString1 = new QRadioButton(groupBoxMixString);
	rdoMixString1->setObjectName(QStringLiteral("rdoMixString1"));
	rdoMixString1->setGeometry(QRect(10, 30, 104, 25));
	rdoMixString3 = new QRadioButton(groupBoxMixString);
	rdoMixString3->setObjectName(QStringLiteral("rdoMixString3"));
	rdoMixString3->setGeometry(QRect(50, 30, 104, 25));
	rdoMixString4 = new QRadioButton(groupBoxMixString);
	rdoMixString4->setObjectName(QStringLiteral("rdoMixString4"));
	rdoMixString4->setGeometry(QRect(10, 70, 104, 25));
	rdoMixString5 = new QRadioButton(groupBoxMixString);
	rdoMixString5->setObjectName(QStringLiteral("rdoMixString5"));
	rdoMixString5->setGeometry(QRect(50, 70, 104, 25));
	groupBoxBackgroundSlider = new QGroupBox(centralWidget);
	groupBoxBackgroundSlider->setObjectName(QStringLiteral("groupBoxBackgroundSlider"));
	groupBoxBackgroundSlider->setGeometry(QRect(620, 580, 221, 111));
	groupBoxBackgroundSlider->setFont(font);
	groupBoxBackgroundSlider->setStyleSheet(QLatin1String("QGroupBox { \n"
"	border: 0px solid gray; \n"
" } \n"
"\n"
"QGroupBox::title {\n"
"	font-weight: bold;\n"
"}"));
	groupBoxBackgroundSlider->setAlignment(Qt::AlignCenter);
	backgroundSlider = new QSlider(groupBoxBackgroundSlider);
	backgroundSlider->setObjectName(QStringLiteral("backgroundSlider"));
	backgroundSlider->setGeometry(QRect(10, 40, 160, 20));
	backgroundSlider->setOrientation(Qt::Horizontal);

	lightSlider = new QSlider(groupBoxBackgroundSlider);
	lightSlider->setObjectName(QStringLiteral("lightSlider"));
	lightSlider->setGeometry(QRect(10, 60, 160, 20));
	lightSlider->setOrientation(Qt::Horizontal);

	darkSlider = new QSlider(groupBoxBackgroundSlider);
	darkSlider->setObjectName(QStringLiteral("darkSlider"));
	darkSlider->setGeometry(QRect(10, 80, 160, 20));
	darkSlider->setOrientation(Qt::Horizontal);

	brightnessSlider = new QSlider(groupBoxBackgroundSlider);
	brightnessSlider->setObjectName(QStringLiteral("brightnessSlider"));
	brightnessSlider->setGeometry(QRect(10, 100, 160, 20));
	brightnessSlider->setOrientation(Qt::Horizontal);

	powerSlider = new QSlider(groupBoxBackgroundSlider);
	powerSlider->setObjectName(QStringLiteral("powerSlider"));
	powerSlider->setGeometry(QRect(10, 120, 160, 20));
	powerSlider->setOrientation(Qt::Horizontal);

	btnClipboard = new ClickableLabel(centralWidget);
	btnClipboard->setObjectName(QStringLiteral("btnClipboard"));
	btnClipboard->setGeometry(QRect(1103, 679, 41, 55));
	btnClipboard->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/ClipboardIcon.png")));
	btnClipboard->setScaledContents(true);
	backgroundArea = new QWidget(centralWidget);
	backgroundArea->setObjectName(QStringLiteral("backgroundArea"));
	backgroundArea->setGeometry(QRect(0, -10, APP_WIDTH, APP_HEIGHT + 10));
	QPalette Pal;
	Pal.setColor(QPalette::Background, QColor::fromRgb(0,0,0));
	backgroundArea->setAutoFillBackground(true);
	backgroundArea->setPalette(Pal);
	ppLogo = new QLabel(backgroundArea);
	ppLogo->setObjectName(QStringLiteral("ppLogo"));
	ppLogo->setGeometry(QRect(644, 502, 539, 79));
	ppLogo->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/PPLogo.png")));
	cornerTopRight = new QLabel(backgroundArea);
	cornerTopRight->setObjectName(QStringLiteral("cornerTopRight"));
	cornerTopRight->setGeometry(QRect(APP_WIDTH - 52, APP_FRAMETOP, 52, 52));
	cornerTopRight->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/TopRightCorner.png")));
	cornerTopLeft = new QLabel(backgroundArea);
	cornerTopLeft->setObjectName(QStringLiteral("cornerTopLeft"));
	cornerTopLeft->setGeometry(QRect(0, APP_FRAMETOP, 52, 52));
	cornerTopLeft->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/TopLeftCorner.png")));
	borderTop = new QLabel(backgroundArea);
	borderTop->setObjectName(QStringLiteral("borderTop"));
	borderTop->setGeometry(QRect(52, APP_FRAMETOP, APP_WIDTH - 52 - 52, 15));
	borderTop->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/TopBorder.png")));
	borderTop->setScaledContents(true);
	borderRight = new QLabel(backgroundArea);
	borderRight->setObjectName(QStringLiteral("borderRight"));
	borderRight->setGeometry(QRect(APP_WIDTH - BORDER_SIZE, APP_FRAMETOP + 52, BORDER_SIZE, APP_HEIGHT - 52 - 52));
	borderRight->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/RightBorder.png")));
	borderRight->setScaledContents(true);
	borderLeft = new QLabel(backgroundArea);
	borderLeft->setObjectName(QStringLiteral("borderLeft"));
	borderLeft->setGeometry(QRect(0, APP_FRAMETOP + 52, BORDER_SIZE, APP_HEIGHT - 52 - 52));
	borderLeft->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/LeftBorder.png")));
	borderLeft->setScaledContents(true);
	lblColorName = new QLabel(centralWidget);
	lblColorName->setObjectName(QStringLiteral("lblColorName"));
	lblColorName->setGeometry(QRect(20, 680, 131, 61));
	QFont font1;
	font1.setFamily(QStringLiteral("MuseJazz"));
	lblColorName->setFont(font1);
	lblColorName->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
	btnSaveJPG = new ClickableLabel(centralWidget);
	btnSaveJPG->setObjectName(QStringLiteral("btnSaveJPG"));
	btnSaveJPG->setGeometry(QRect(1171, 682, 41, 52));
	btnSaveJPG->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/JPGIcon.png")));
	btnSaveJPG->setScaledContents(true);
	lblCurrentColor = new QLabel(centralWidget);
	lblCurrentColor->setObjectName(QStringLiteral("lblCurrentColor"));
	lblCurrentColor->setGeometry(QRect(20, 569, 161, 41));
	lblCurrentColor->setFont(font);
	lblCurrentColor->setAlignment(Qt::AlignCenter);
	cornerBottomLeft = new QLabel(centralWidget);
	cornerBottomLeft->setObjectName(QStringLiteral("label_9"));
	cornerBottomLeft->setGeometry(QRect(0, APP_HEIGHT - 52, 52, 52));
	cornerBottomLeft->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/BottomLeftCorner.png")));
	cornerBottomRight = new QLabel(centralWidget);
	cornerBottomRight->setObjectName(QStringLiteral("label_8"));
	cornerBottomRight->setGeometry(QRect(APP_WIDTH - 52, APP_HEIGHT - 52, 52, 52));
	cornerBottomRight->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/BottomRightCorner.png")));
	borderBottom = new QLabel(centralWidget);
	borderBottom->setObjectName(QStringLiteral("borderBottom"));
	borderBottom->setGeometry(QRect(52, APP_HEIGHT - BORDER_SIZE, APP_WIDTH - 52 - 52, BORDER_SIZE));
	borderBottom->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/BottomBorder.png")));
	borderBottom->setScaledContents(true);

	toolbarBackground = new QLabel(centralWidget);
	toolbarBackground->setObjectName(QStringLiteral("toolbarBackground"));
	toolbarBackground->setGeometry(QRect(15, 619, APP_WIDTH - 15 - 15, 165));
	toolbarBackground->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/OptionBG.png")));
	toolbarBackground->setScaledContents(true);

	line1 = new QLabel(centralWidget);
	line1->setObjectName(QStringLiteral("line1"));
	positionDividingLine(line1, QRect(165, 632, 2, 139));

	line2 = new QLabel(centralWidget);
	line2->setObjectName(QStringLiteral("line2"));
	positionDividingLine(line2, QRect(317, 632, 2, 139));

	line3 = new QLabel(centralWidget);
	line3->setObjectName(QStringLiteral("line3"));
	positionDividingLine(line3, QRect(470, 632, 2, 139));

	line4 = new QLabel(centralWidget);
	line4->setObjectName(QStringLiteral("line4"));
	positionDividingLine(line4, QRect(622, 632, 2, 139));

	line5 = new QLabel(centralWidget);
	line5->setObjectName(QStringLiteral("line5"));
	positionDividingLine(line5, QRect(774, 632, 2, 139));

	line6 = new QLabel(centralWidget);
	line6->setObjectName(QStringLiteral("line6"));
	positionDividingLine(line6, QRect(927, 632, 2, 139));

	line7 = new QLabel(centralWidget);
	line7->setObjectName(QStringLiteral("line7"));
	positionDividingLine(line7, QRect(1080, 632, 2, 139));

	MainWindow->setCentralWidget(centralWidget);
	borderLeft->lower();
	borderRight->lower();
	borderBottom->lower();
	borderTop->lower();
	cornerBottomLeft->lower();
	cornerBottomRight->lower();
	cornerTopLeft->lower();
	cornerTopRight->lower();
	colorWheel->raise();
	groupBoxWheel->raise();
	groupBoxGamutShape->raise();
	groupBoxMixString->raise();
	groupBoxBackgroundSlider->raise();
	btnClipboard->raise();
	lblColorName->raise();
	lblCurrentColor->raise();
	btnSaveJPG->raise();
	toolbarBackground->lower();
	toolbarBackground->stackUnder(borderLeft);
	backgroundArea->lower();

	retranslateUi(MainWindow);

	QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
	MainWindow->setWindowTitle(QApplication::translate("PrestoPalette", "PrestoPalette", 0));
	groupBoxWheel->setTitle(QApplication::translate("MainWindow", "WHEEL", 0));
	rdoFineWheel->setText(QApplication::translate("MainWindow", "Fi&ne", 0));
	rdoCourseWheel->setText(QApplication::translate("MainWindow", "Course", 0));
	groupBoxGamutShape->setTitle(QApplication::translate("MainWindow", "GAMUT SHAPE", 0));
	rdoGamutShapeLine->setText(QApplication::translate("MainWindow", "&2 Point", 0));
	rdoGamutShapeTriangle->setText(QApplication::translate("MainWindow", "T&riad", 0));
	rdoGamutShapeSquare->setText(QApplication::translate("MainWindow", "&Quad", 0));
	groupBoxMixString->setTitle(QApplication::translate("MainWindow", "MIX STRING", 0));
	rdoMixString1->setText(QApplication::translate("MainWindow", "&1", 0));
	rdoMixString3->setText(QApplication::translate("MainWindow", "&3", 0));
	rdoMixString4->setText(QApplication::translate("MainWindow", "&4", 0));
	rdoMixString5->setText(QApplication::translate("MainWindow", "&5", 0));
	groupBoxBackgroundSlider->setTitle(QApplication::translate("MainWindow", "BACKGROUND", 0));
	btnClipboard->setText(QString());
	cornerTopRight->setText(QString());
	cornerTopLeft->setText(QString());
	borderTop->setText(QString());
	borderRight->setText(QString());
	borderLeft->setText(QString());
	//swatchSample->setText(QString());
	lblColorName->setText(QApplication::translate("MainWindow", "No Color Selected", 0));
	btnSaveJPG->setText(QString());
	lblCurrentColor->setText(QApplication::translate("MainWindow", "CURRENT COLOR", 0));
	cornerBottomLeft->setText(QString());
	cornerBottomRight->setText(QString());
	borderBottom->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOWX_H
