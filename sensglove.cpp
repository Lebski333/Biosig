#include "sensglove.h"
#include <QHBoxLayout>
#include <QDebug>
#include <QFile>
#include <QSpinBox>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include "dane.h"
#include <QTimer>

SensGlove::SensGlove(QWidget *parent)
{
    iloscSensorow = ILOSC_SENSOROW;
    layout = new QHBoxLayout();
    layout2 = new QVBoxLayout();
    layout3 = new QHBoxLayout();
    pole = new QRect(50,50,500,500);
    layout->setGeometry(*pole);
    pomiary = new QVector <QVector <double>>;


    //EDYCJA***************************************
    indexEnter = new QSpinBox();
    button_minus = new QPushButton("-");
    button_plus = new QPushButton("+");
    button_zapisz = new QPushButton("zapisz");
    button_wczytaj = new QPushButton("wczytaj");
    button_start = new QPushButton("start");
    //*********************************************

    graphView = new QGraphicsView();
    scena = new QGraphicsScene(this);
    reka = new QGraphicsPixmapItem(QPixmap("hand2.png"));
    timer = new QTimer(this);

    graphView->setRenderHint(QPainter::Antialiasing);
    timer->setInterval(1);

    QObject::connect(button_minus,SIGNAL(clicked(bool)),this,SLOT(on_button_minus_clicked()));
    QObject::connect(button_plus,SIGNAL(clicked(bool)),this,SLOT(on_button_plus_clicked()));
    QObject::connect(button_zapisz,SIGNAL(clicked(bool)),this,SLOT(zapiszSensoryDoPliku()));
    QObject::connect(button_wczytaj,SIGNAL(clicked(bool)),this,SLOT(wczytajSensoryZPliku()));
    QObject::connect(indexEnter, SIGNAL(valueChanged(int)),this,SLOT(setIndex(int)));
    QObject::connect(button_start,SIGNAL(clicked(bool)),timer,SLOT(start()));
    QObject::connect(timer,SIGNAL(timeout()),scena,SLOT(advance()));
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(timer_stop()));


    //WERSJA Z PLIKIEM
    //ustawianie wektorow  *************************************************
    wczytajSensoryZPliku();
    for(int i = 0 ; i < iloscSensorow ; i++){
        sensory[i] = new ForceSensor(reka, 0, 0, sensorData[i][3], sensorData[i][4], 0, i);
        sensory[i]->setPos(sensorData[i][1],sensorData[i][2]);
        sensory[i]->setRotation(sensorData[i][5]);
        //qDebug() << "SYGNAL wyslijPomiar nr:    " << i << " NADANY";

    }
    //**********************************************************************
    //DODAWANIE ITEMOW DO SCENY**********************
    scena->addItem(reka);
    for(int i = 0 ; i < iloscSensorow ; i++)
    {
        scena->addItem(sensory[i]);
    }
    //***********************************************
    layout3->addWidget(button_plus);
    layout3->addWidget(button_minus);
    graphView->setScene(scena);
    layout->addWidget(graphView);
   // layout2->addWidget(QLabel("Wybór czujnika"));
    layout2->addWidget(indexEnter);
   // layout2->addWidget(QLabel("Obrór czujnika"));
    layout2->addLayout(layout3);
    layout2->addWidget(button_zapisz);
    layout2->addWidget(button_wczytaj);
    layout2->addWidget(button_start);
    layout->addLayout(layout2);
    setLayout(layout);
}
void SensGlove::set()
{

    for(int i = 0 ; i < iloscSensorow ; i++){
        sensory[i]->czasPomiaru = czasPomiaru;
        QObject::connect(this, SIGNAL(wyslijPomiar(QVector<double>)),sensory[i],SLOT(setVector(QVector<double>)));
        emit(wyslijPomiar(pomiary->at(i)));
        QObject::disconnect(this, SIGNAL(wyslijPomiar(QVector<double>)),sensory[i],SLOT(setVector(QVector<double>)));
    }


        scena->update();
        show();
}



void SensGlove::setVector(QVector < QVector <double> > vek)
{
    delete pomiary;
    pomiary = new QVector <QVector <double>>;
    vek.swap(*pomiary);
}

void SensGlove::setIndex(int index)
{
    aktualnyIndex = index;
}

void SensGlove::zapiszSensoryDoPliku()
{
    QString filename="sensory.txt";
    QFile file( filename );
    if ( file.open(QIODevice::WriteOnly) )
    {
        QTextStream stream( &file );

        for(int i = 0 ; i < iloscSensorow ; i++){

            QString index = QString::number(i);
            QString width = QString::number(sensory[i]->getWidth());
            QString height = QString::number(sensory[i]->getHeight());
            QString x = QString::number(sensory[i]->pos().x());
            QString y = QString::number(sensory[i]->pos().y());
            QString kat = QString::number(sensory[i]->rotation());

            QString linia = index + " "  + x  + " " + y + " " + width + " " + height +  " " + kat;

            stream << linia << endl;
        }
    }
}

void SensGlove::wczytajSensoryZPliku()
{
    QFile plik("sensory.txt");
    int i = 0;
    if (plik.open(QIODevice::ReadOnly))
    {
       QTextStream in(&plik);
        while (!in.atEnd())
        {
           //skanujemy linia po linii pomijajac linie przerwy miedzy samplami
           QString line = in.readLine();
           if (line != ""){
               //dzielimy po spacjach
               QStringList sample = line.split(" ");
               for (int j = 0; j < 6 ; j++)
               {
                sensorData[i][j] = QstrToLd(sample.at(j));
               }
           }
           i++;
        }
    plik.close();
    }
}




void SensGlove::wypisz()
{
    for(int i = 0 ; i < pomiary->size() ; i++)
    {
        qDebug() << "rozmiar " << i << ": " << QString::number(pomiary->size()) << "  : " << QString::number(pomiary[i].size());
        for(int j = 0 ; j < pomiary[i].size() ; j++)
        {
         //   qDebug() << j << ": " << QString::number(&pomiary[i][j]);
        }
    }

}

void SensGlove::wypiszSensory()
{
    for(int i = 0 ; i < ILOSC_SENSOROW; i++)
    {
        qDebug() << "Sensor " << i << ": " << QString::number(sensory[i]->x()) << "  : " << QString::number(sensory[i]->y());
    }
}



void SensGlove::on_button_plus_clicked()
{
    QObject::connect(this,SIGNAL(wyslijKat(int)),sensory[aktualnyIndex],SLOT(rotate(int)));
    emit(wyslijKat(1));
    disconnect(this, SIGNAL(wyslijKat(int)),sensory[aktualnyIndex],SLOT(rotate(int)));
}


void SensGlove::on_button_minus_clicked()
{
    QObject::connect(this,SIGNAL(wyslijKat(int)),sensory[aktualnyIndex],SLOT(rotate(int)));
    emit(wyslijKat(-1));
    disconnect(this, SIGNAL(wyslijKat(int)),sensory[aktualnyIndex],SLOT(rotate(int)));

}

void SensGlove::timer_stop()
{
    timer_time++;
    if(timer_time>=czasPomiaru){
        timer->stop();
        timer_time = 0;
    }
    //qDebug() << timer_time;
}
