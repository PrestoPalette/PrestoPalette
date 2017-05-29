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
    void pressed();
protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
};

#endif // CLICKABLELABEL_H
