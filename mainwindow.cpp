#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dane.h"
#include "emg.h"
#include "sensglove.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QVBoxLayout *plot = new QVBoxLayout;
//    Navi *nav = new Navi();
//    Dane *test = new Dane();


    connect(ui->widget, SIGNAL(sendPath(QString)), ui->widget_2, SLOT(changeFileSlot(QString)));


//    nav->show();
//    test->show();
//    ui->treeLayout->addWidget(nav);
//    ui->plotLayout->addWidget(test);
//    ui->centralwidget->setLayout(plot);
}

MainWindow::~MainWindow()
{
    delete ui;
}
