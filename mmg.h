#ifndef MMG_H
#define MMG_H
#include <QObject>
#include <QWidget>
#include <QVector>
#include <QDebug>
#include "qcustomplot.h"



class MMG : public QWidget
{
    Q_OBJECT
public:
    MMG(QWidget *parent = 0);
    void wypisz();
    QVBoxLayout *kolumna;
    int czasPomiaru;

private:
    QVector < QVector <double> > *pomiary;
    QCustomPlot *wykresy[8];
    QRect *pole; //rozmiar pojedynczego wykresu
    QVector <double> czas;



private slots:
    void setVector(QVector < QVector <double> > vek);
    void plot();

};

#endif // MMG_H
