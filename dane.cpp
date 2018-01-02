#include "dane.h"
#include <QDebug>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

//zamiana long double na QString bez ucinania cyfr
QString LdToQstr(double myLongDouble) {

    std::stringstream str;
    str << std::setprecision(15) << myLongDouble;
    QString qstr = QString::fromStdString(str.str());
    return qstr;
}

//zamiana QStrina na long double
double QstrToLd(QString qstr)
{

    std::string str = qstr.toLocal8Bit().constData();
    double ld = std::stold(str.c_str(), 0);
    return ld;
}



Dane::Dane(QWidget *parent) : QWidget(parent)
{
    //this->setSizePolicy(QSizePolicy::Expanding);
    //setGeometry(0,0,500,500);
    //sizePolicy(Expanding);
    tabs = new QTabWidget(this);
    emg = new EMG();
    mmg = new MMG();
    sensGlove = new SensGlove();
    plotLayout = new QHBoxLayout();
    QHBoxLayout *layout = new QHBoxLayout(this);
    QWidget *bio = new QWidget;
   // QTabBar::tab " background-color : yellow;"
    //tabs->setStyleSheet(    QTabBar::tab {" background-color : yellow;"});
    emg->autoFillBackground();




    plotLayout->addWidget(emg);
    plotLayout->addWidget(mmg);
    bio->setLayout(plotLayout);

    qDebug() << "dane utworzone\n";
    //readData("1.txt"); // 7.txt - plik z samymi EMG MMG

    layout->addWidget(tabs);

    tabs->addTab(bio, tr("Biosygnały"));
    tabs->addTab(sensGlove, tr("Rękawiczka Sensoryczna"));
    tabs->autoFillBackground();

    //tabs->addTab(emg,"EMG");
    //tabs->setLayout(plotLayout);


    QObject::connect(this,      SIGNAL(sendEMG(QVector<QVector<double> >)),
                     emg,       SLOT(setVector(QVector<QVector<double> >)));
    QObject::connect(this,      SIGNAL(sendMMG(QVector<QVector<double> >)),
                     mmg,       SLOT(setVector(QVector<QVector<double> >)));
    QObject::connect(this,      SIGNAL(sendSensGlove(QVector<QVector<double> >)),
                     sensGlove, SLOT(setVector(QVector<QVector<double> >)));
    QObject::connect(this,      SIGNAL(startPlot()),
                     emg,       SLOT(plot()));
    QObject::connect(this,      SIGNAL(startPlot()),
                     mmg,       SLOT(plot()));
    QObject::connect(this,      SIGNAL(startPlot()),
                     sensGlove, SLOT(set()));



    readData("./6.txt");

    //setLayout(plotLayout);
    show();


}

void Dane::readData(QString nazwa)
{
    ilosc_linii = 0;
    EMGvector.clear();
    MMGvector.clear();
    SensGlovevector.clear();
    //
    //######
    //##dorobic sprawdzanie poprawnosci
    //######
    //
    qDebug() << "wczytuje dane";
    QVector < QVector <double> > tablica;
    //tworzymy 40 qvectorow typu double dla 40 kanalow
    for (int i = 0 ; i < 40 ; i++){
       tablica.append(QVector<double>());
    }

    //otweramy plik z pomiarem
    QFile plik(nazwa);
    if (plik.open(QIODevice::ReadOnly))
    {
       QTextStream in(&plik);
       //powtarzamy az do konca pliku
       while (!in.atEnd())
       {
          double dane[40];
          //skanujemy linia po linii pomijajac linie przerwy miedzy samplami
          QString line = in.readLine();

          if (line != ""){
              ilosc_linii++;
              //dzielimy po spacjach
              QStringList sample = line.split(" ");
              for (int i = 0 ; i < sample.size() ; i++)
              {
                  //konwertujemy do dobula (jednak nie long) z precyzja (15)
                dane[i] = QstrToLd(sample.at(i));
                //i dodajemy po jednej probce na kazdy kanal
                tablica[i].append(dane[i]);
              }
          }
       }
       plik.close();
    }
    //dzielimy vector na EMG, MMG i SensGlove i emitujemy
    for(int i = 0 ; i < 8 ; i++)
    {
        this->MMGvector.append(tablica.takeFirst());
        this->EMGvector.append(tablica.takeFirst());
    }
    qDebug() << "ILOSC LINII: " << ilosc_linii;
    emg->czasPomiaru = ilosc_linii;
    mmg->czasPomiaru = ilosc_linii;
    sensGlove->czasPomiaru = ilosc_linii;

    tablica.swap(this->SensGlovevector);
    emit sendEMG(this->EMGvector);
    emit sendMMG(this->MMGvector);
    emit sendSensGlove(this->SensGlovevector);
    emit startPlot();
    qDebug() << "dane wczytane";
}

void Dane::changeFileSlot(QString sciezka)
{
    readData(sciezka);
}

