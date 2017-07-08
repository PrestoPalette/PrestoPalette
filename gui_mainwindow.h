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
#include <QFontDatabase>
#include <QSizePolicy>
#include <QScreen>
#include "circlepalette.h"
#include "visualpalette.h"
#include "clickablelabel.h"
#include "lightingsliderstyle.h"

#define APP_WIDTH 1250
#define APP_HEIGHT 800
#define APP_FRAMETOP 10
#define BORDER_SIZE 15
#define TOOLBAR_TEXT_HEIGHT 635

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    CirclePalette *colorWheel;
    QLabel *lblResolution;
    ClickableLabel *rdoFineWheel;
    ClickableLabel *rdoCoarseWheel;
    QLabel *lblGamutShape;
    ClickableLabel *rdoGamutShapeLine;
    ClickableLabel *rdoGamutShapeTriangle;
    ClickableLabel *rdoGamutShapeSquare;
    QLabel *lblMixString;
    ClickableLabel *rdoMixString1;
    ClickableLabel *rdoMixString3;
    ClickableLabel *rdoMixString5;
    QLabel *lblBackground;
    QSlider *backgroundSlider;
    QLabel *lblSave;
    QLabel *lblLightIntensity;
    QLabel *lblLightPct;
    QLabel *lblDarkPct;
    QSlider *lightSlider;
    QSlider *darkSlider;
    QLabel *lblLightColor;
    QLabel *lblBrightnessPct;
    QSlider *brightnessSlider;
    QLabel *lblAlphaPct;
    QSlider *alphaSlider;
    QLabel *alphaSliderTransparency;
    LightingSliderStyle *alphaSliderStyle;
    LightingSliderStyle *brightnessSliderStyle;
    ClickableLabel *btnClipboard;
    QWidget *backgroundArea;
    QLabel *ppLogo;
    QLabel *cornerTopRight;
    QLabel *cornerTopLeft;
    QLabel *borderTop;
    QLabel *borderRight;
    QLabel *borderLeft;
    VisualPalette *visualPalette;
    ClickableLabel *btnSaveJPG;
    QLabel *lblCurrentColor;
    QLabel *currentColorSwatch;
    QLabel *currentColorSwatchCaption;

    ClickableLabel *btnSave;
    ClickableLabel *btnLoad;

    ClickableLabel *btnAbout;

    QLabel *cornerBottomLeft;
    QLabel *cornerBottomRight;
    QLabel *borderBottom;
    QLabel *toolbarBackground;

    ClickableLabel *btnLightingOn;
    ClickableLabel *btnLightingOff;

    QLabel *line1;
    QLabel *line2;
    QLabel *line3;
    QLabel *line4;
    QLabel *line5;
    QLabel *line6;    QLabel *line7;

    QString maroonedOnMars;
    QString calibri;

    // sadly this has to be marked this way -- else there is a memory leak and segfault on app close
    //static LightingSliderStyle *alphaStyle = nullptr;

    void positionDividingLine(QLabel *line, const QRect &position)
    {
	    line->setGeometry(position);
	    line->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/Divider.png")));
	    line->setScaledContents(true);
    }

    void setupUi(QMainWindow *MainWindow)
    {
	MainWindow->setWindowIcon(QIcon(":/main/graphics/favicon.ico"));

	maroonedOnMars = QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/main/fonts/MaroonedOnMarsBB.ttf")).at(0);
	calibri = QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/main/fonts/calibrib.ttf")).at(0);

	//qreal screenDPI  = QApplication::primaryScreen()->physicalDotsPerInch();

	/*#ifdef WINDOWS
	qreal RENDER_DPI = 96;
	#else
	qreal RENDER_DPI = 72;
	#endif*/

	QFont fontTitle;
	fontTitle.setFamily(this->maroonedOnMars);
	//fontTitle.setPixelSize((int)((qreal)14 * screenDPI / RENDER_DPI));
	fontTitle.setPointSize(19);
	//fontTitle.setLetterSpacing(QFont::AbsoluteSpacing, 1.0);

	QFont fontSubTitle;
	fontSubTitle.setFamily(this->calibri);
	//fontSubTitle.setPixelSize((int)((qreal)7 * screenDPI / RENDER_DPI));
	fontSubTitle.setPointSize(9);

	QFont fontDetail;
	fontDetail.setFamily(this->maroonedOnMars);
	//fontDetail.setPixelSize((int)((qreal)10 * screenDPI / RENDER_DPI));
	fontDetail.setPointSize(15);

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
	lblResolution = new QLabel(centralWidget);
	lblResolution->setObjectName(QStringLiteral("lblResolution"));
	lblResolution->setGeometry(QRect(202, TOOLBAR_TEXT_HEIGHT, 1, 1));
	lblResolution->setFont(fontTitle);
	lblResolution->setAlignment(Qt::AlignLeft);
	lblResolution->setStyleSheet(QLatin1String("QLabel { color : #808073;}"));
	/*groupBoxResolution = new QGroupBox(centralWidget);
	groupBoxResolution->setObjectName(QStringLiteral("groupBoxResolution"));
	groupBoxResolution->setGeometry(QRect(202, 660, 100, 100));
	groupBoxResolution->setAlignment(Qt::AlignLeft);
	groupBoxResolution->setStyleSheet(QLatin1String("QGroupBox { \n"
"	border: 0px solid gray; \n"
" } \n"
"\n"
"QGroupBox::title {\n"
"	color: #808073;\n"
"}"));
	groupBoxResolution->setAlignment(Qt::AlignCenter);*/
	rdoFineWheel = new ClickableLabel(centralWidget);
	rdoFineWheel->setObjectName(QStringLiteral("rdoFineWheel"));
	rdoFineWheel->setGeometry(QRect(203, 692, 76, 38));
	rdoCoarseWheel = new ClickableLabel(centralWidget);
	rdoCoarseWheel->setObjectName(QStringLiteral("rdoCoarseWheel"));
	rdoCoarseWheel->setGeometry(QRect(203, 660, 76, 38));
	lblGamutShape = new QLabel(centralWidget);
	lblGamutShape->setObjectName(QStringLiteral("lblGamutShape"));
	lblGamutShape->setGeometry(QRect(350, TOOLBAR_TEXT_HEIGHT, 1, 1));
	lblGamutShape->setFont(fontTitle);
	lblGamutShape->setAlignment(Qt::AlignLeft);
	lblGamutShape->setStyleSheet(QLatin1String("QLabel { color : #808073;}"));
	/*groupBoxGamutShape = new QGroupBox(centralWidget);
	groupBoxGamutShape->setObjectName(QStringLiteral("groupBoxGamutShape"));
	groupBoxGamutShape->setGeometry(QRect(330, 675, 151, 151));
	groupBoxGamutShape->setFont(fontTitle);
	groupBoxGamutShape->setStyleSheet(QLatin1String("QGroupBox { \n"
"	border: 0px solid gray; \n"
" } \n"
"\n"
"QGroupBox::title {\n"
"	color: #808073;\n"
"}"));
	groupBoxGamutShape->setAlignment(Qt::AlignCenter);*/
	rdoGamutShapeLine = new ClickableLabel(centralWidget);
	rdoGamutShapeLine->setObjectName(QStringLiteral("rdoGamutShapeLine"));
	rdoGamutShapeLine->setGeometry(QRect(353, 660, 76, 38));
	rdoGamutShapeTriangle = new ClickableLabel(centralWidget);
	rdoGamutShapeTriangle->setObjectName(QStringLiteral("rdoGamutShapeTriangle"));
	rdoGamutShapeTriangle->setGeometry(QRect(353, 692, 76, 38));
	rdoGamutShapeSquare = new ClickableLabel(centralWidget);
	rdoGamutShapeSquare->setObjectName(QStringLiteral("rdoGamutShapeSquare"));
	rdoGamutShapeSquare->setGeometry(QRect(353, 724, 76, 38));
	lblMixString = new QLabel(centralWidget);
	lblMixString->setObjectName(QStringLiteral("lblMixString"));
	lblMixString->setGeometry(QRect(500, TOOLBAR_TEXT_HEIGHT, 1, 1));
	lblMixString->setFont(fontTitle);
	lblMixString->setAlignment(Qt::AlignHCenter);
	lblMixString->setStyleSheet(QLatin1String("QLabel { color : #808073;}"));
	//groupBoxMixString = new QGroupBox(centralWidget);
	//groupBoxMixString->setObjectName(QStringLiteral("groupBoxMixString"));
	//groupBoxMixString->setGeometry(QRect(500, 670, 101, 111));
	//groupBoxMixString->setGeometry(QRect(0, 0, 500, 500));
	//groupBoxMixString->setFont(fontTitle);
	/*groupBoxMixString->setStyleSheet(QLatin1String("QGroupBox { \n"
"	border: 0px solid gray; \n"
" } \n"
"\n"
"QGroupBox::title {\n"
"	color: #808073;\n"
"}"));
	groupBoxMixString->setAlignment(Qt::AlignCenter);*/
	rdoMixString1 = new ClickableLabel(centralWidget);
	rdoMixString1->setObjectName(QStringLiteral("rdoMixString1"));
	rdoMixString1->setGeometry(QRect(529, 665, 36, 32));
	rdoMixString3 = new ClickableLabel(centralWidget);
	rdoMixString3->setObjectName(QStringLiteral("rdoMixString3"));
	rdoMixString3->setGeometry(QRect(529, 697, 36, 32));
	rdoMixString5 = new ClickableLabel(centralWidget);
	rdoMixString5->setObjectName(QStringLiteral("rdoMixString5"));
	rdoMixString5->setGeometry(QRect(529, 729, 36, 32));

	lblBackground = new QLabel(centralWidget);
	lblBackground->setObjectName(QStringLiteral("lblBackground"));
	lblBackground->setGeometry(QRect(960, TOOLBAR_TEXT_HEIGHT, 1, 1));
	lblBackground->setFont(fontTitle);
	lblBackground->setAlignment(Qt::AlignLeft);
	lblBackground->setStyleSheet(QLatin1String("QLabel { color : #808073;}"));
	backgroundSlider = new QSlider(centralWidget);
	backgroundSlider->setObjectName(QStringLiteral("backgroundSlider"));
	backgroundSlider->setGeometry(QRect(948, 678, 110, 21));
	backgroundSlider->setOrientation(Qt::Horizontal);
	backgroundSlider->setStyleSheet("QSlider::groove:horizontal {background-image:url(:/main/graphics/BackgroundSliderBG.png);}"
					"QSlider::handle:horizontal {background-image:url(:/main/graphics/SliderHandle.png); height:21px; width: 21px;}");

	lblSave = new QLabel(centralWidget);
	lblSave->setObjectName(QStringLiteral("lblSave"));
	lblSave->setGeometry(QRect(1139, TOOLBAR_TEXT_HEIGHT, 1, 1));
	lblSave->setFont(fontTitle);
	lblSave->setAlignment(Qt::AlignLeft);
	lblSave->setStyleSheet(QLatin1String("QLabel { color : #808073;}"));

	lblLightIntensity = new QLabel(centralWidget);
	lblLightIntensity->setObjectName(QStringLiteral("lblLightIntensity"));
	lblLightIntensity->setGeometry(QRect(650, TOOLBAR_TEXT_HEIGHT, 1, 1));
	lblLightIntensity->setFont(fontTitle);
	lblLightIntensity->setAlignment(Qt::AlignLeft);
	lblLightIntensity->setStyleSheet(QLatin1String("QLabel { color : #808073;}"));

	lightSlider = new QSlider(centralWidget);
	lightSlider->setObjectName(QStringLiteral("lightSlider"));
	lightSlider->setGeometry(QRect(645, 678, 110, 21));
	lightSlider->setOrientation(Qt::Horizontal);
	lightSlider->setStyleSheet("QSlider::groove:horizontal {background-image:url(:/main/graphics/LightnessSliderBG.png);}"
					"QSlider::handle:horizontal {background-image:url(:/main/graphics/SliderHandle.png); height:21px; width: 21px;}");

	darkSlider = new QSlider(centralWidget);
	darkSlider->setObjectName(QStringLiteral("darkSlider"));
	darkSlider->setGeometry(QRect(645, 718, 110, 21));
	darkSlider->setOrientation(Qt::Horizontal);
	darkSlider->setStyleSheet("QSlider::groove:horizontal {background-image:url(:/main/graphics/DarknessSliderBG.png);}"
					"QSlider::handle:horizontal {background-image:url(:/main/graphics/SliderHandle.png); height:21px; width: 21px;}");

	lblLightColor = new QLabel(centralWidget);
	lblLightColor->setObjectName(QStringLiteral("lblLightColor"));
	lblLightColor->setGeometry(QRect(822, TOOLBAR_TEXT_HEIGHT, 1, 1));
	lblLightColor->setFont(fontTitle);
	lblLightColor->setAlignment(Qt::AlignLeft);
	lblLightColor->setStyleSheet(QLatin1String("QLabel { color : #808073;}"));
	brightnessSlider = new QSlider(centralWidget);
	brightnessSlider->setObjectName(QStringLiteral("brightnessSlider"));
	brightnessSlider->setGeometry(QRect(796, TOOLBAR_TEXT_HEIGHT + 42, 110, 21));
	brightnessSlider->setOrientation(Qt::Horizontal);

	brightnessSliderStyle = new LightingSliderStyle(brightnessSlider->style(), QString::fromUtf8(":/main/graphics/SliderHandle_Brightness.png"), QString::fromUtf8(":/main/graphics/SliderOverlay.png"), true);
	brightnessSlider->setStyle(brightnessSliderStyle);

	alphaSlider = new QSlider(centralWidget);
	alphaSlider->setObjectName(QStringLiteral("alphaSlider"));
	alphaSlider->setGeometry(QRect(796, 718, 110, 21));
	alphaSlider->setOrientation(Qt::Horizontal);

	alphaSliderStyle = new LightingSliderStyle(alphaSlider->style(), QString::fromUtf8(":/main/graphics/SliderHandle.png"), QString::fromUtf8(":/main/graphics/SliderOverlay.png"));
	alphaSlider->setStyle(alphaSliderStyle);

	alphaSliderTransparency = new QLabel(centralWidget);
	alphaSliderTransparency->setObjectName(QStringLiteral("alphaSliderTransparency"));
	alphaSliderTransparency->setGeometry(QRect(alphaSlider->geometry()));
	alphaSliderTransparency->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/AlphaSliderBG.png")));

	alphaSliderTransparency->lower();
	alphaSlider->raise();

	lblLightPct = new QLabel(centralWidget);
	lblLightPct->setObjectName(QStringLiteral("lblLightPct"));
	lblLightPct->setGeometry(QRect(653, 662, 1, 1));
	lblLightPct->setFont(fontSubTitle);
	lblLightPct->setAlignment(Qt::AlignLeft);
	lblLightPct->setStyleSheet(QLatin1String("QLabel { margin-top:0px; padding-top:0px; color : #808073;}"));

	lblDarkPct = new QLabel(centralWidget);
	lblDarkPct->setObjectName(QStringLiteral("lblDarkPct"));
	lblDarkPct->setGeometry(QRect(653, 702, 1, 1));
	lblDarkPct->setFont(fontSubTitle);
	lblDarkPct->setAlignment(Qt::AlignLeft);
	lblDarkPct->setStyleSheet(QLatin1String("QLabel { color : #808073;}"));

	lblBrightnessPct = new QLabel(centralWidget);
	lblBrightnessPct->setObjectName(QStringLiteral("lblBrightnessPct"));
	lblBrightnessPct->setGeometry(QRect(807, 662, 1, 1));
	lblBrightnessPct->setFont(fontSubTitle);
	lblBrightnessPct->setAlignment(Qt::AlignLeft);
	lblBrightnessPct->setStyleSheet(QLatin1String("QLabel { color : #808073;}"));

	lblAlphaPct = new QLabel(centralWidget);
	lblAlphaPct->setObjectName(QStringLiteral("lblAlphaPct"));
	lblAlphaPct->setGeometry(QRect(807, 702, 1, 1));
	lblAlphaPct->setFont(fontSubTitle);
	lblAlphaPct->setAlignment(Qt::AlignLeft);
	lblAlphaPct->setStyleSheet(QLatin1String("QLabel { color : #808073;}"));

	btnClipboard = new ClickableLabel(centralWidget);
	btnClipboard->setObjectName(QStringLiteral("btnClipboard"));
	btnClipboard->setGeometry(QRect(1112, 722, 33, 44));
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
	btnSaveJPG = new ClickableLabel(centralWidget);
	btnSaveJPG->setObjectName(QStringLiteral("btnSaveJPG"));
	btnSaveJPG->setGeometry(QRect(1172, 723, 33, 42));
	btnSaveJPG->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/PNGIcon.png")));
	btnSaveJPG->setScaledContents(true);
	lblCurrentColor = new QLabel(centralWidget);
	lblCurrentColor->setObjectName(QStringLiteral("lblCurrentColor"));
	lblCurrentColor->setGeometry(QRect(36, TOOLBAR_TEXT_HEIGHT, 1, 1));
	lblCurrentColor->setFont(fontTitle);
	lblCurrentColor->setAlignment(Qt::AlignLeft);
	lblCurrentColor->setStyleSheet(QLatin1String("QLabel { color : #808073;}"));
	currentColorSwatch = new QLabel(centralWidget);
	currentColorSwatch->setObjectName(QStringLiteral("currentColorSwatch"));
	currentColorSwatch->setGeometry(QRect(61, 669, 60, 60));
	currentColorSwatch->setAlignment(Qt::AlignCenter);
	currentColorSwatchCaption = new QLabel(centralWidget);
	currentColorSwatchCaption->setObjectName(QStringLiteral("currentColorSwatchCaption"));
	currentColorSwatchCaption->setGeometry(QRect(0, 743, 178, 15));
	currentColorSwatchCaption->setFont(fontDetail);
	currentColorSwatchCaption->setAlignment(Qt::AlignCenter);
	currentColorSwatchCaption->setStyleSheet(QLatin1String("QLabel { color : #808073;}"));
	cornerBottomLeft = new QLabel(centralWidget);
	cornerBottomLeft->setObjectName(QStringLiteral("cornerBottomLeft"));
	cornerBottomLeft->setGeometry(QRect(0, APP_HEIGHT - 52, 52, 52));
	cornerBottomLeft->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/BottomLeftCorner.png")));
	cornerBottomRight = new QLabel(centralWidget);
	cornerBottomRight->setObjectName(QStringLiteral("cornerBottomRight"));
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

	btnSave = new ClickableLabel(centralWidget);
	btnSave->setObjectName(QStringLiteral("btnSave"));
	btnSave->setGeometry(QRect(1106, 660, 43, 46));
	btnSave->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/SaveIcon.png")));
	btnSave->setScaledContents(true);

	btnLoad = new ClickableLabel(centralWidget);
	btnLoad->setObjectName(QStringLiteral("btnLoad"));
	btnLoad->setGeometry(QRect(1166, 660, 43, 46));
	btnLoad->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/LoadIcon.png")));
	btnLoad->setScaledContents(true);

	btnAbout = new ClickableLabel(centralWidget);
	btnAbout->setObjectName(QStringLiteral("btnAbout"));
	btnAbout->setGeometry(QRect(24, 24, 36, 32));
	btnAbout->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/AboutIcon.png")));
	btnAbout->setScaledContents(true);

	btnLightingOn = new ClickableLabel(centralWidget);
	btnLightingOn->setObjectName(QStringLiteral("btnLightingOn"));
	btnLightingOn->setGeometry(QRect(809, 744, 35, 31));
	btnLightingOn->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/Button_On_Off.png")));
	btnLightingOn->setScaledContents(true);

	btnLightingOff = new ClickableLabel(centralWidget);
	btnLightingOff->setObjectName(QStringLiteral("btnLightingOff"));
	btnLightingOff->setGeometry(QRect(861, 744, 35, 31));
	btnLightingOff->setPixmap(QPixmap(QString::fromUtf8(":/main/graphics/Button_Off_Off.png")));
	btnLightingOff->setScaledContents(true);

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
	//groupBoxResolution->raise();
	//groupBoxGamutShape->raise();
	//groupBoxMixString->raise();
	btnClipboard->raise();
	lblCurrentColor->raise();
	btnSaveJPG->raise();
	btnSave->raise();
	btnLoad->raise();
	btnAbout->raise();
	toolbarBackground->lower();
	toolbarBackground->stackUnder(borderLeft);
	backgroundArea->lower();

	rdoMixString1->raise();
	rdoMixString3->raise();
	rdoMixString5->raise();

	rdoGamutShapeLine->raise();
	rdoGamutShapeTriangle->raise();
	rdoGamutShapeSquare->raise();

	rdoCoarseWheel->raise();
	rdoFineWheel->raise();

	/*toolbarBackground->hide();
	backgroundArea->hide();
	colorWheel->hide();
	visualPalette->hide();*/

	retranslateUi(MainWindow);

	QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
	MainWindow->setWindowTitle(QApplication::translate("PrestoPalette", "PrestoPalette", 0));
	lblResolution->setText(QApplication::translate("MainWindow", "RESOLUTION", 0));
	lblResolution->adjustSize();
	rdoFineWheel->setText(QApplication::translate("MainWindow", "Fi&ne", 0));
	lblGamutShape->setText(QApplication::translate("MainWindow", "GAMUT SHAPE", 0));
	lblGamutShape->adjustSize();
	rdoGamutShapeLine->setText(QApplication::translate("MainWindow", "&2 Point", 0));
	rdoGamutShapeTriangle->setText(QApplication::translate("MainWindow", "T&riad", 0));
	rdoGamutShapeSquare->setText(QApplication::translate("MainWindow", "&Quad", 0));
	lblMixString->setText(QApplication::translate("MainWindow", "MIX STRING", 0));
	lblMixString->adjustSize();
	//rdoMixString1->setText(QApplication::translate("MainWindow", "&1", 0));
	//rdoMixString3->setText(QApplication::translate("MainWindow", "&3", 0));
	//rdoMixString5->setText(QApplication::translate("MainWindow", "&5", 0));
	btnClipboard->setText(QString());
	cornerTopRight->setText(QString());
	cornerTopLeft->setText(QString());
	borderTop->setText(QString());
	borderRight->setText(QString());
	borderLeft->setText(QString());
	btnSaveJPG->setText(QString());
	btnSave->setText(QString());
	btnLoad->setText(QString());
	btnAbout->setText(QString());
	lblCurrentColor->setText(QApplication::translate("MainWindow", "CURRENT COLOR", 0));
	lblCurrentColor->adjustSize();
	cornerBottomLeft->setText(QString());
	cornerBottomRight->setText(QString());
	borderBottom->setText(QString());

	rdoMixString1->setText(QString());
	rdoMixString3->setText(QString());
	rdoMixString5->setText(QString());

	rdoGamutShapeLine->setText(QString());
	rdoGamutShapeTriangle->setText(QString());
	rdoGamutShapeSquare->setText(QString());

	rdoCoarseWheel->setText(QString());
	rdoFineWheel->setText(QString());

	lblBackground->setText(QApplication::translate("MainWindow", "BACKGROUND", 0));
	lblBackground->adjustSize();

	lblLightColor->setText(QApplication::translate("MainWindow", "LIGHTING", 0));
	lblLightColor->adjustSize();

	lblLightIntensity->setText(QApplication::translate("MainWindow", "STRING VALUES", 0));
	lblLightIntensity->adjustSize();

	lblSave->setText(QApplication::translate("MainWindow", "SAVE", 0));
	lblSave->adjustSize();
    } // retranslateUi

    /*
    ~Ui_MainWindow(void)
    {
	delete this->alphaSlider;
	delete this->alphaSliderStyle;
	delete this->backgroundArea;
	delete this->backgroundSlider;
	delete this->borderBottom;
	delete this->borderLeft;
	delete this->borderRight;
	delete this->borderTop;
	delete this->brightnessSlider;
	delete this->btnAbout;
	delete this->btnClipboard;
	delete this->btnLightingOff;
	delete this->btnLightingOn;
	delete this->btnLoad;
	delete this->btnSave;
	delete this->btnSaveJPG;
    }
    */

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOWX_H
