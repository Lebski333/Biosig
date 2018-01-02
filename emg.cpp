#include "emg.h"
#include <QLayout>
#include <QVBoxLayout>

EMG::EMG(QWidget *parent) : QWidget(parent)
{
    qDebug() << "tworze emg\n";
    //setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    kolumna = new QVBoxLayout(this);

    //pole = new QRect(0,0,100,60); //rozmiar pojedynczego wykresu
    pomiary = new QVector <QVector <double>>;
    QLabel *label = new QLabel;
    label->setAlignment(Qt::AlignCenter);
    label->setMaximumHeight(20);
    label->setTextFormat(Qt::RichText);
    label->setText("<b>EMG</b>");
    kolumna->addWidget(label);
    for(int i = 0 ; i < 8 ; i++)
    {
        wykresy[i] = new QCustomPlot();
        //wykresy[i]->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
        //wykresy[i]->setGeometry(*pole);
        wykresy[i]->yAxis->setRange(-6, 6);
        kolumna->addWidget(wykresy[i]);
    }
    setLayout(kolumna);

    qDebug() << "emg utworzone\n";

}

void EMG::plot()
{
    czas.clear();

    for(int i = 0 ; i < czasPomiaru ; i++)
    {
        czas.append(i);
    }
    for(int i = 0 ; i < 8 ; i++)
    {
        wykresy[i]->xAxis->setRange(0, czasPomiaru);
        wykresy[i]->addGraph();
        wykresy[i]->graph(0)->setData(czas, pomiary->at(i));
        wykresy[i]->replot();
    }
}

void EMG::setVector(QVector < QVector <double> > vek)
{
    delete pomiary;
    pomiary = new QVector <QVector <double>>;
    vek.swap(*pomiary);
}

void EMG::wypisz()
{
    for(int i = 0 ; i < pomiary->size() ; i++)
    {
        qDebug() << "rozmiar " << i << ": " << QString::number(pomiary->size()) << "  : " << QString::number(pomiary[i].size());
        for(int j = 0 ; j < pomiary[i].size() ; j++)
        {
            //qDebug() << j << ": " << QString::number(*pomiary[i].at(j));
        }
    }

}

