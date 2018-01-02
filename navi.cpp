#include "navi.h"
#include <QVBoxLayout>
#include <QDebug>

Navi::Navi(QWidget *parent) : QWidget(parent)
{
    //setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);

    QVBoxLayout *layout = new QVBoxLayout();
    //setMinimumSize(300,600);
    //layout->setSizeConstraint(QLayout::SetMinimumSize);
    //setGeometry(*pole);
    QString rootPath = QDir::currentPath()+"/pomiary";   //zmienic poxniej /testy2 na /pomiary
    tree = new QTreeView(this);
    model = new QFileSystemModel(tree);
    //tree->setFixedWidth(200);

    layout->addWidget(tree);
//    tree->adjustSize();
//    tree->setMinimumHeight(500);
    //tree->setMinimumSize(200,800);
    tree->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    //tree->setGeometry(*pole);
    tree->setModel(model);  //ustawiamy model dla widoku
    model->setRootPath(rootPath);   //ustawiamy sciezke modelu
    tree->setRootIndex(model->index(rootPath)); //ustawiamy widok na sciezke
    tree->hideColumn(1);    //chowamy zbedne kolumny (size itp)
    tree->hideColumn(2);
    tree->hideColumn(3);
    //layout->addWidget(tree);
    setLayout(layout);
    QItemSelectionModel *selection = tree->selectionModel();

    connect(selection, SIGNAL(selectionChanged (const QItemSelection &, const QItemSelection &)),
                this, SLOT(selectionChangedSlot(const QItemSelection &, const QItemSelection &)));

    //show();
}

void Navi::selectionChangedSlot(const QItemSelection & /*newSelection*/, const QItemSelection & /*oldSelection*/)
{
    const QModelIndex index = tree->selectionModel()->currentIndex();
    QString sciezka = model->filePath(index);
    if(QFileInfo(sciezka).isFile()){
        qDebug() << sciezka;

        emit sendPath(sciezka);
    }
    else qDebug() << "halooooo";

}

//const QSize Navi::sizeHint()
//{
//    return QSize(300,550);
//}
