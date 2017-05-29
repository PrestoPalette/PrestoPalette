#include "clickablelabel.h"

ClickableLabel::ClickableLabel(QWidget* parent)
    : QLabel(parent)
{
	setMouseTracking(true);
}

ClickableLabel::~ClickableLabel()
{
}

void ClickableLabel::mouseReleaseEvent(QMouseEvent* event)
{
	emit clicked();
}

void ClickableLabel::mousePressEvent(QMouseEvent* event)
{
	emit pressed();
}

