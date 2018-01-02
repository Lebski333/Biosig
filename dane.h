#ifndef DANE_H
#define DANE_H
#include <QFile>
#include <QVector>
#include "emg.h"
#include "mmg.h"
#include "sensglove.h"

//wczytuje i przerabia dane z jednego pliku
class Dane : public QWidget
{
    Q_OBJECT
public:
    Dane(QWidget *parent = 0);
    //~dane();
    void readData(QString nazwa);
    EMG *emg;
    MMG *mmg;
    SensGlove *sensGlove;
private:
    //QFile *plik;
    QTabWidget *tabs;
    QHBoxLayout *plotLayout;
    QVector < QVector <double> > EMGvector;
    QVector < QVector <double> > MMGvector;
    QVector < QVector <double> > SensGlovevector;
    QString plik;
    int ilosc_linii = 0;


signals:    //dorobic w mainie connect dla EMG i MMG
    void sendEMG(QVector < QVector <double> > vek);
    void sendMMG(QVector < QVector <double> > vek);
    void sendSensGlove(QVector < QVector <double> > vek);
    void startPlot();
    void startClean();
    void cleanEMG();
    void clearSensGlove();

public slots:
    void changeFileSlot(QString sciezka);
    //void cleanSlot();
};

double QstrToLd(QString qstr);
QString LdToQstr(double myLongDouble);


#endif // DANE_H
