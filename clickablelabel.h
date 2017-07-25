#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>

class ClickableLabel : public QLabel
{
	Q_OBJECT
      public:
	explicit ClickableLabel(QWidget *parent = Q_NULLPTR);
	~ClickableLabel();

      signals:
	void clicked();
	void pressed();
	void hoverEnter(QHoverEvent *e);
	void hoverLeave(QHoverEvent *e);
	void hoverMove(QHoverEvent *e);

      protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	bool event(QEvent *e);
};

#endif // CLICKABLELABEL_H
