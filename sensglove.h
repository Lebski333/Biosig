#ifndef SENSGLOVE_H
#define SENSGLOVE_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVector>
#include "forcesensor.h"
#include <QGraphicsPixmapItem>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRect>
#include <QSpinBox>

#define ILOSC_SENSOROW 24

class SensGlove : public QWidget
{
    Q_OBJECT
public:
    explicit SensGlove(QWidget *parent = 0);

    void wypisz();
    void wypiszSensory();
    double sensorData[ILOSC_SENSOROW][6];   //informacje o sensorach (z pliku)
    int czasPomiaru;

private:
    QVector < QVector <double> > *pomiary;
    QGraphicsView *graphView;
    QGraphicsScene *scena;
    QGraphicsPixmapItem *reka;
    ForceSensor *sensory[ILOSC_SENSOROW];   //pomiary z sensorow nacisku i zgiecia !!!wykminic ktore to zgiecia!!!
    ForceSensor *sensor;                    //pojedynczy sensor do testow
    int iloscSensorow;

    //WIDGETY DO OBSLUGI SENSOROW NA SCENIE
    QPushButton *button_minus;
    QPushButton *button_plus;
    QPushButton *button_zapisz;
    QPushButton *button_wczytaj;
    QPushButton *button_start;
    QTimer *timer;
    QSpinBox *indexEnter;
    int aktualnyIndex;  //do ustawiania sensorow na scenie
    int timer_time = 0;

    QHBoxLayout *layout;
    QVBoxLayout *layout2;
    QHBoxLayout *layout3;

    QRect *pole;        //do ustawiania geometrii glownego layoutu


signals:
    void wyslijKat(int kat); //wysyla 1 albo -1 po nacisnieciu odpowiedniego przycisku
    void wyslijPomiar(QVector <double> wek);


public slots:
    void on_button_minus_clicked();
    void on_button_plus_clicked();
    void zapiszSensoryDoPliku();
    void wczytajSensoryZPliku();
    void setVector(QVector < QVector <double> > vek);
    void setIndex(int index);
    void set();
    void timer_stop();


};

#endif // SENSGLOVE_H
