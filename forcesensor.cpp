#include "forcesensor.h"
#include <QLabel>
#include "dane.h"
#include <QDebug>
ForceSensor::ForceSensor(QGraphicsItem *parent)
{
    setFlag(ItemIsMovable);
    setAcceptHoverEvents(true);
    numer = new QGraphicsSimpleTextItem("0",this);
    rect = new QRectF(0,0,30,50);
    kolor = new QColor(200,200,200);

}

ForceSensor::ForceSensor(QGraphicsItem *parent,  double x, double y, double width, double height, double kat, int index)
{
    setFlag(ItemIsMovable);
    setAcceptHoverEvents(true);
    rect = new QRectF(x,y,width,height);

    numer = new QGraphicsSimpleTextItem(QString::number(index),this);
    numer->setPos(x-5+(height/2),y-5+(width/2));
    //numer->mapToParent(0,0);
    setRotation(kat);
    kolor = new QColor(200,200,200);

    }

QRectF ForceSensor::boundingRect() const
{
    return QRectF(*rect);
}

void ForceSensor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF ksztalt = boundingRect();
    QBrush brush(Qt::green);
    brush.setColor(*kolor);
    //QPen pen1 = QPen(Qt::black);
    mapFromParent(0,0);
    //pen1.setWidth(2);
    //painter->setBrush(*kolor);
    painter->fillRect(ksztalt,brush);
    painter->drawRect(ksztalt);
}

void ForceSensor::rotate(int kat)
{
    setRotation(rotation()+kat);
}

void ForceSensor::advance(int step)
{
    if(!step){
        if(pomiar.at(it)<0){
            //ciemno zielone
            int g = pomiar.at(it)*255;
            kolor->setRgb(0,255+g,0);
        }
        if(pomiar.at(it)>0 && pomiar.at(it)<1){
            //zielone
            int g = pomiar.at(it)*155;
            kolor->setRgb(0,g+100,0);
        }
        if(pomiar.at(it)>1 && pomiar.at(it)<2){
            //zolte
            int r = (pomiar.at(it)*255/2);
            kolor->setRgb(r,255,0);
        }
        if(pomiar.at(it)>2 && pomiar.at(it)<3){
            //pomaranczowe
            int g = (pomiar.at(it)*255/3);
            kolor->setRgb(255,255-g,0);
        }
        if(pomiar.at(it)>3){
            int r = (pomiar.at(it)*255/4);
            kolor->setRgb(r-150,0,0);
        }
    }

    if(step){
        if(it < czasPomiaru-1){  //zmienia zaleznie od czasu trwania pomiaru
        //numer->setText(LdToQstr(pomiar.at(it)));
        update();
        it++;
        }
        else it = 0;
    }
}

void ForceSensor::setVector(QVector<double> wek)
{
    pomiar.clear();
    pomiar.append(wek);
}

void ForceSensor::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QString info;
    QLabel etykieta;
    info = "Pozycja: " + QString::number(pos().x()) + ", " + QString::number(pos().y()) + "| Orientacja: " + QString::number(rotation());
    qDebug() << info;
    etykieta.setText(info);
    etykieta.show();
}


double ForceSensor::getWidth()
{
    return boundingRect().width();
}

double ForceSensor::getHeight()
{
    return boundingRect().height();
}
