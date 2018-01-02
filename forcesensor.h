#ifndef FORCESENSOR_H
#define FORCESENSOR_H
#include <QWidget>
#include <QGraphicsItem>
#include <QPainter>
#include <QVector>

class ForceSensor : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    ForceSensor(QGraphicsItem *parent = 0);
    ForceSensor(QGraphicsItem *parent, double x, double y, double width, double height, double kat, int index);
    void wypisz();
    double getWidth();
    double getHeight();
    int czasPomiaru;

public slots:
    void rotate(int kat);   //do przycisku w sensglove
    void advance(int step);
    void setVector(QVector <double> pomiar);

private:
    QColor *kolor;
    int it = 0;
    QRectF *rect;
    int index;
    QGraphicsSimpleTextItem *numer;
    QVector <double> pomiar;


protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event);

};

#endif // FORCESENSOR_H
