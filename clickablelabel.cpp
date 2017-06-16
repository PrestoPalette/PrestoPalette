#include <QHoverEvent>
#include <QEvent>
#include <QPushButton>
#include <QDebug>
#include <Qt>
#include <QWidget>

#include "clickablelabel.h"

ClickableLabel::ClickableLabel(QWidget* parent)
    : QLabel(parent)
{
	setMouseTracking(true);

	// https://stackoverflow.com/questions/411823/how-do-i-implement-qhoverevent-in-qt
	this->setAttribute(Qt::WA_Hover, true);
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

bool ClickableLabel::event(QEvent * e)
{
    switch(e->type())
    {
    case QEvent::HoverEnter:
	emit hoverEnter(static_cast<QHoverEvent*>(e));
	return true;
	break;
    case QEvent::HoverLeave:
	emit hoverLeave(static_cast<QHoverEvent*>(e));
	return true;
	break;
    case QEvent::HoverMove:
	emit hoverMove(static_cast<QHoverEvent*>(e));
	return true;
	break;
    default:
	break;
    }
    return QWidget::event(e);
}


