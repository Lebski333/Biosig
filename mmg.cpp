#include "mmg.h"



MMG::MMG(QWidget *parent) : QWidget(parent)
{
    qDebug() << "tworze mmg\n";
    //setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    kolumna = new QVBoxLayout();
    //pole = new QRect(0,0,100,80); //rozmiar pojedynczego wykresu
    pomiary = new QVector <QVector <double>>;
    QLabel *label = new QLabel;
    label->setAlignment(Qt::AlignCenter);
    label->setMaximumHeight(20);
    label->setTextFormat(Qt::RichText);
    label->setText("<b>MMG</b>");
    kolumna->addWidget(label);
    for(int i = 0 ; i < 8 ; i++)
    {
        wykresy[i] = new QCustomPlot();
        wykresy[i]->addGraph();
        //wykresy[i]->setGeometry(*pole);
        wykresy[i]->yAxis->setRange(-6, 6);
        kolumna->addWidget(wykresy[i]);
    }
    setLayout(kolumna);

    qDebug() << "mmg utworzone\n";

}

void MMG::plot()
{
    czas.clear();
    for(int i = 0 ; i < czasPomiaru ; i++)
    {
        czas.append(i);
    }
    for(int i = 0 ; i < 8 ; i++)
    {
        //wykresy[i]->graph(0)->
        wykresy[i]->xAxis->setRange(0, czasPomiaru);
        wykresy[i]->graph(0)->setData(czas, pomiary->at(i));
        wykresy[i]->replot();
        //iloscWykresow++;
    }


}

void MMG::setVector(QVector < QVector <double> > vek)
{
    delete pomiary;
    pomiary = new QVector <QVector <double>>;
    vek.swap(*pomiary);
}

void MMG::wypisz()
{
    for(int i = 0 ; i < pomiary->size() ; i++)
    {
        qDebug() << "rozmiar " << i << ": " << QString::number(pomiary->size()) << "  : " << QString::number(pomiary[i].size());
        for(int j = 0 ; j < pomiary[i].size() ; j++)
        {
            //qDebug() << j << ": " << QString::number(pomiary[i].at(j));
        }
    }

}

