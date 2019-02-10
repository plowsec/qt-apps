#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>

class View : public QGraphicsView
{
    Q_OBJECT
public:
    View(QWidget *parent = 0);

public slots:
    void setStr(QString str);
    QString getStr();
    QString getMap();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    QGraphicsItem *carte[12][12];
    QGraphicsScene *scene;
    QString file;
    QChar map[12][12];
};

#endif // VIEW_H
