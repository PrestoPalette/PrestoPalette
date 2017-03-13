#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>

class ClickableLabel : public QLabel
{
Q_OBJECT
public:
    explicit ClickableLabel(QWidget* parent=Q_NULLPTR);
    ~ClickableLabel();
signals:
    void clicked();
protected:
    void mouseReleaseEvent(QMouseEvent* event);
};

#endif // CLICKABLELABEL_H
