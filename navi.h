#ifndef NAVI_H
#define NAVI_H
#include <QFileSystemModel>
#include <QDir>
#include <QTreeView>

class Navi : public QWidget
{
    Q_OBJECT
public:
    explicit Navi(QWidget *parent = nullptr);
    QFileSystemModel *model;    //model dla QTreeView

private:
    QTreeView *tree;

signals:
    void sendPath(QString sciezka);

public slots:
    void selectionChangedSlot(const QItemSelection & /*newSelection*/, const QItemSelection & /*oldSelection*/);

protected:
    const QSize sizeHint();
};

#endif // NAVI_H
