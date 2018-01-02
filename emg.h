#ifndef EMG_H
#define EMG_H

#include <QObject>
#include <QWidget>
#include <QVector>
#include <QDebug>
#include "qcustomplot.h"


//wczytuja dane dotyczace sygnalo EMG z klasy dane i przygotowuje layout ze wszystkimi wykresami
class EMG : public QWidget
{
    Q_OBJECT
public:
    EMG(QWidget *parent = 0);
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

#endif // EMG_H
