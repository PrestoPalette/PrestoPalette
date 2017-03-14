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

//#define APP_WIDTH 1090
//#define APP_HEIGHT 989

#define APP_WIDTH 1090
#define APP_HEIGHT 989

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionExit;
    QWidget *centralWidget;
    CirclePalette *colorWheel;
    QGroupBox *groupBox;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QGroupBox *groupBoxGamutShape;
    QRadioButton *rdoGamutShapeLine;
    QRadioButton *rdoGamutShapeTriangle;
    QRadioButton *rdoGamutShapeSquare;
    //QRadioButton *radioButton_10;
    QGroupBox *groupBox_3;
    QRadioButton *rdoMixString1;
    QRadioButton *rdoMixString3;
    QRadioButton *rdoMixString4;
    QRadioButton *rdoMixString5;
    QGroupBox *groupBox_4;
    QSlider *backgroundSlider;
    QSlider *lightSlider;
    QSlider *darkSlider;
    QSlider *brightnessSlider;
    QSlider *powerSlider;
    QFrame *line_5;
    ClickableLabel *btnClipboard;
    QWidget *backgroundArea;
    QLabel *ppLogo;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    VisualPalette *visualPalette;
    QLabel *swatchSample;
    QLabel *lblColorName;
    ClickableLabel *btnSaveJPG;
    //QLabel *label_4;
    QLabel *label;
    QLabel *label_9;
    QLabel *label_8;
    QLabel *label_10;
    QFrame *line;
    QFrame *line_2;
    QFrame *line_3;
    QFrame *line_4;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
	if (MainWindow->objectName().isEmpty())
	    MainWindow->setObjectName(QStringLiteral("MainWindow"));
	MainWindow->resize(QSize(APP_WIDTH, APP_HEIGHT));

	actionNew = new QAction(MainWindow);
	actionNew->setObjectName(QStringLiteral("actionNew"));
	actionExit = new QAction(MainWindow);
	actionExit->setObjectName(QStringLiteral("actionExit"));
	centralWidget = new QWidget(MainWindow);
	centralWidget->setObjectName(QStringLiteral("centralWidget"));
	colorWheel = new CirclePalette(centralWidget);
	colorWheel->setObjectName(QStringLiteral("colorWheel"));
	colorWheel->setGeometry(QRect(30, 50, 600, 600));
	//colorWheel->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/YWheel_Course.png")));
	//colorWheel->setScaledContents(true);
	visualPalette = new VisualPalette(centralWidget);
	visualPalette->setObjectName(QStringLiteral("visualPalette"));
	visualPalette->setGeometry(QRect(640, 60, 391, 551));
	groupBox = new QGroupBox(centralWidget);
	groupBox->setObjectName(QStringLiteral("groupBox"));
	groupBox->setGeometry(QRect(190, 780, 101, 111));
	QFont font;
	font.setFamily(QStringLiteral("MuseJazz"));
	font.setBold(true);
	font.setWeight(75);
	groupBox->setFont(font);
	groupBox->setStyleSheet(QLatin1String("QGroupBox { \n"
"	border: 0px solid gray; \n"
" } \n"
"\n"
"QGroupBox::title {\n"
"	font-weight: bold;\n"
"}"));
	groupBox->setAlignment(Qt::AlignCenter);
	radioButton = new QRadioButton(groupBox);
	radioButton->setObjectName(QStringLiteral("radioButton"));
	radioButton->setGeometry(QRect(10, 30, 104, 25));
	radioButton_2 = new QRadioButton(groupBox);
	radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
	radioButton_2->setGeometry(QRect(10, 50, 104, 25));
	groupBoxGamutShape = new QGroupBox(centralWidget);
	groupBoxGamutShape->setObjectName(QStringLiteral("groupBoxGamutShape"));
	groupBoxGamutShape->setGeometry(QRect(330, 780, 151, 151));
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
	/*radioButton_10 = new QRadioButton(groupBoxGamutShape);
	radioButton_10->setObjectName(QStringLiteral("radioButton_10"));
	radioButton_10->setGeometry(QRect(10, 90, 104, 25));*/
	groupBox_3 = new QGroupBox(centralWidget);
	groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
	groupBox_3->setGeometry(QRect(500, 780, 101, 111));
	groupBox_3->setFont(font);
	groupBox_3->setStyleSheet(QLatin1String("QGroupBox { \n"
"	border: 0px solid gray; \n"
" } \n"
"\n"
"QGroupBox::title {\n"
"	font-weight: bold;\n"
"}"));
	groupBox_3->setAlignment(Qt::AlignCenter);
	rdoMixString1 = new QRadioButton(groupBox_3);
	rdoMixString1->setObjectName(QStringLiteral("rdoMixString1"));
	rdoMixString1->setGeometry(QRect(10, 30, 104, 25));
	rdoMixString3 = new QRadioButton(groupBox_3);
	rdoMixString3->setObjectName(QStringLiteral("rdoMixString3"));
	rdoMixString3->setGeometry(QRect(50, 30, 104, 25));
	rdoMixString4 = new QRadioButton(groupBox_3);
	rdoMixString4->setObjectName(QStringLiteral("rdoMixString4"));
	rdoMixString4->setGeometry(QRect(10, 70, 104, 25));
	rdoMixString5 = new QRadioButton(groupBox_3);
	rdoMixString5->setObjectName(QStringLiteral("rdoMixString5"));
	rdoMixString5->setGeometry(QRect(50, 70, 104, 25));
	groupBox_4 = new QGroupBox(centralWidget);
	groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
	groupBox_4->setGeometry(QRect(620, 780, 221, 111));
	groupBox_4->setFont(font);
	groupBox_4->setStyleSheet(QLatin1String("QGroupBox { \n"
"	border: 0px solid gray; \n"
" } \n"
"\n"
"QGroupBox::title {\n"
"	font-weight: bold;\n"
"}"));
	groupBox_4->setAlignment(Qt::AlignCenter);
	backgroundSlider = new QSlider(groupBox_4);
	backgroundSlider->setObjectName(QStringLiteral("backgroundSlider"));
	backgroundSlider->setGeometry(QRect(10, 40, 160, 20));
	backgroundSlider->setOrientation(Qt::Horizontal);

	lightSlider = new QSlider(groupBox_4);
	lightSlider->setObjectName(QStringLiteral("lightSlider"));
	lightSlider->setGeometry(QRect(10, 60, 160, 20));
	lightSlider->setOrientation(Qt::Horizontal);

	darkSlider = new QSlider(groupBox_4);
	darkSlider->setObjectName(QStringLiteral("darkSlider"));
	darkSlider->setGeometry(QRect(10, 80, 160, 20));
	darkSlider->setOrientation(Qt::Horizontal);

	brightnessSlider = new QSlider(groupBox_4);
	brightnessSlider->setObjectName(QStringLiteral("brightnessSlider"));
	brightnessSlider->setGeometry(QRect(10, 100, 160, 20));
	brightnessSlider->setOrientation(Qt::Horizontal);

	powerSlider = new QSlider(groupBox_4);
	powerSlider->setObjectName(QStringLiteral("powerSlider"));
	powerSlider->setGeometry(QRect(10, 120, 160, 20));
	powerSlider->setOrientation(Qt::Horizontal);

	line_5 = new QFrame(groupBox_4);
	line_5->setObjectName(QStringLiteral("line_5"));
	line_5->setGeometry(QRect(200, 0, 20, 101));
	line_5->setFrameShadow(QFrame::Plain);
	line_5->setFrameShape(QFrame::VLine);
	btnClipboard = new ClickableLabel(centralWidget);
	btnClipboard->setObjectName(QStringLiteral("btnClipboard"));
	btnClipboard->setGeometry(QRect(870, 770, 71, 71));
	btnClipboard->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/ClipboardIcon.png")));
	btnClipboard->setScaledContents(true);
	backgroundArea = new QWidget(centralWidget);
	backgroundArea->setObjectName(QStringLiteral("backgroundArea"));
	backgroundArea->setGeometry(QRect(0, -10, 1091, 771));
	ppLogo = new QLabel(backgroundArea);
	ppLogo->setObjectName(QStringLiteral("label_6"));
	//auto logoPos = QRect(visualPalette->width() - (458/2), visualPalette->rect().bottom()+ 20 + 49 , 458, 49);
	ppLogo->setGeometry(QRect(619, 650, 458, 49));
	ppLogo->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/PPLogo.png")));
	ppLogo->setScaledContents(true);
	label_6 = new QLabel(backgroundArea);
	label_6->setObjectName(QStringLiteral("label_6"));
	label_6->setGeometry(QRect(1030, 10, 61, 61));
	label_6->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/TopRightCorner.png")));
	label_6->setScaledContents(true);
	label_7 = new QLabel(backgroundArea);
	label_7->setObjectName(QStringLiteral("label_7"));
	label_7->setGeometry(QRect(0, 10, 61, 61));
	label_7->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/TopLeftCorner.png")));
	label_7->setScaledContents(true);
	label_11 = new QLabel(backgroundArea);
	label_11->setObjectName(QStringLiteral("label_11"));
	label_11->setGeometry(QRect(60, 10, 971, 21));
	label_11->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/TopBorder.png")));
	label_11->setScaledContents(true);
	label_12 = new QLabel(backgroundArea);
	label_12->setObjectName(QStringLiteral("label_12"));
	label_12->setGeometry(QRect(1070, 70, 21, 801));
	label_12->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/RightBorder.png")));
	label_12->setScaledContents(true);
	label_13 = new QLabel(backgroundArea);
	label_13->setObjectName(QStringLiteral("label_13"));
	label_13->setGeometry(QRect(0, 70, 21, 801));
	label_13->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/LeftBorder.png")));
	label_13->setScaledContents(true);
	swatchSample = new QLabel(centralWidget);
	swatchSample->setObjectName(QStringLiteral("swatchSample"));
	swatchSample->setGeometry(QRect(40, 800, 101, 101));
	swatchSample->setPixmap(QPixmap(QString::fromUtf8(":/main/PaintSwatch.png")));
	swatchSample->setScaledContents(false);
	lblColorName = new QLabel(centralWidget);
	lblColorName->setObjectName(QStringLiteral("lblColorName"));
	lblColorName->setGeometry(QRect(20, 880, 131, 61));
	QFont font1;
	font1.setFamily(QStringLiteral("MuseJazz"));
	lblColorName->setFont(font1);
	lblColorName->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
	btnSaveJPG = new ClickableLabel(centralWidget);
	btnSaveJPG->setObjectName(QStringLiteral("btnSaveJPG"));
	btnSaveJPG->setGeometry(QRect(970, 770, 71, 71));
	btnSaveJPG->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/JPGIcon.png")));
	btnSaveJPG->setScaledContents(true);
	/*label_4 = new QLabel(centralWidget);
	label_4->setObjectName(QStringLiteral("label_4"));
	label_4->setGeometry(QRect(870, 840, 71, 71));
	label_4->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/PSIcon.png")));
	label_4->setScaledContents(true);*/
	label = new QLabel(centralWidget);
	label->setObjectName(QStringLiteral("label"));
	label->setGeometry(QRect(20, 769, 161, 41));
	label->setFont(font);
	label->setAlignment(Qt::AlignCenter);
	label_9 = new QLabel(centralWidget);
	label_9->setObjectName(QStringLiteral("label_9"));
	label_9->setGeometry(QRect(0, 860, 71, 71));
	label_9->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/BottomLeftCorner.png")));
	label_9->setScaledContents(true);
	label_8 = new QLabel(centralWidget);
	label_8->setObjectName(QStringLiteral("label_8"));
	label_8->setGeometry(QRect(1020, 860, 71, 71));
	label_8->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/BottomRightCorner.png")));
	label_8->setScaledContents(true);
	label_10 = new QLabel(centralWidget);
	label_10->setObjectName(QStringLiteral("label_10"));
	label_10->setGeometry(QRect(70, 910, 951, 21));
	label_10->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/BottomBorder.png")));
	label_10->setScaledContents(true);
	line = new QFrame(centralWidget);
	line->setObjectName(QStringLiteral("line"));
	line->setGeometry(QRect(170, 790, 20, 101));
	line->setFrameShadow(QFrame::Plain);
	line->setFrameShape(QFrame::VLine);
	line_2 = new QFrame(centralWidget);
	line_2->setObjectName(QStringLiteral("line_2"));
	line_2->setGeometry(QRect(300, 790, 20, 101));
	line_2->setFrameShadow(QFrame::Plain);
	line_2->setFrameShape(QFrame::VLine);
	line_3 = new QFrame(centralWidget);
	line_3->setObjectName(QStringLiteral("line_3"));
	line_3->setGeometry(QRect(470, 790, 20, 101));
	line_3->setFrameShadow(QFrame::Plain);
	line_3->setFrameShape(QFrame::VLine);
	line_4 = new QFrame(centralWidget);
	line_4->setObjectName(QStringLiteral("line_4"));
	line_4->setGeometry(QRect(600, 790, 20, 101));
	line_4->setFrameShadow(QFrame::Plain);
	line_4->setFrameShape(QFrame::VLine);
	MainWindow->setCentralWidget(centralWidget);
	backgroundArea->lower();
	colorWheel->raise();
	groupBox->raise();
	groupBoxGamutShape->raise();
	groupBox_3->raise();
	groupBox_4->raise();
	btnClipboard->raise();
	swatchSample->raise();
	lblColorName->raise();
	btnSaveJPG->raise();
	//label_4->raise();
	label->raise();
	label_9->raise();
	label_8->raise();
	label_10->raise();
	line->raise();
	line_2->raise();
	line_3->raise();
	line_4->raise();
	menuBar = new QMenuBar(MainWindow);
	menuBar->setObjectName(QStringLiteral("menuBar"));
	menuBar->setGeometry(QRect(0, 0, 1090, 28));
	menuFile = new QMenu(menuBar);
	menuFile->setObjectName(QStringLiteral("menuFile"));
	MainWindow->setMenuBar(menuBar);
	mainToolBar = new QToolBar(MainWindow);
	mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
	MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
	statusBar = new QStatusBar(MainWindow);
	statusBar->setObjectName(QStringLiteral("statusBar"));
	MainWindow->setStatusBar(statusBar);

	menuBar->addAction(menuFile->menuAction());
	menuFile->addAction(actionNew);
	menuFile->addSeparator();
	menuFile->addAction(actionExit);

	/*
	 * block window resize
	 */
	//MainWindow->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	this->statusBar->setSizeGripEnabled(false);
	MainWindow->setFixedSize(QSize(APP_WIDTH, APP_HEIGHT));

	retranslateUi(MainWindow);

	QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
	MainWindow->setWindowTitle(QApplication::translate("PrestoPalette", "PrestoPalette", 0));
	actionNew->setText(QApplication::translate("MainWindow", "&New", 0));
	actionExit->setText(QApplication::translate("MainWindow", "E&xit", 0));
	//colorWheel->setText(QString());
	groupBox->setTitle(QApplication::translate("MainWindow", "WHEEL", 0));
	radioButton->setText(QApplication::translate("MainWindow", "Fi&ne", 0));
	radioButton_2->setText(QApplication::translate("MainWindow", "Course", 0));
	groupBoxGamutShape->setTitle(QApplication::translate("MainWindow", "GAMUT SHAPE", 0));
	rdoGamutShapeLine->setText(QApplication::translate("MainWindow", "&2 Point", 0));
	rdoGamutShapeTriangle->setText(QApplication::translate("MainWindow", "T&riad", 0));
	rdoGamutShapeSquare->setText(QApplication::translate("MainWindow", "&Quad", 0));
	//radioButton_10->setText(QApplication::translate("MainWindow", "Accent", 0));
	groupBox_3->setTitle(QApplication::translate("MainWindow", "MIX STRING", 0));
	rdoMixString1->setText(QApplication::translate("MainWindow", "&1", 0));
	rdoMixString3->setText(QApplication::translate("MainWindow", "&3", 0));
	rdoMixString4->setText(QApplication::translate("MainWindow", "&4", 0));
	rdoMixString5->setText(QApplication::translate("MainWindow", "&5", 0));
	groupBox_4->setTitle(QApplication::translate("MainWindow", "BACKGROUND", 0));
	btnClipboard->setText(QString());
	label_6->setText(QString());
	label_7->setText(QString());
	label_11->setText(QString());
	label_12->setText(QString());
	label_13->setText(QString());
	swatchSample->setText(QString());
	lblColorName->setText(QApplication::translate("MainWindow", "No Color Selected", 0));
	btnSaveJPG->setText(QString());
	//label_4->setText(QString());
	label->setText(QApplication::translate("MainWindow", "CURRENT COLOR", 0));
	label_9->setText(QString());
	label_8->setText(QString());
	label_10->setText(QString());
	menuFile->setTitle(QApplication::translate("MainWindow", "Fi&le", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOWX_H
