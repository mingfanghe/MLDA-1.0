#ifndef BASEZOOMABLETABLEWGT_H
#define BASEZOOMABLETABLEWGT_H
#include <QGraphicsScene>
#include<QTableWidget>
#include<QGraphicsView>
#include <QGraphicsProxyWidget>
#include <QWheelEvent>
#include <iostream>
using namespace std;
class zoomAbleTableWgt:public QGraphicsView
{
    Q_OBJECT
public:
    zoomAbleTableWgt(){}
    zoomAbleTableWgt(QWidget *parent);
    ~zoomAbleTableWgt(){ }

protected:
    void wheelEvent(QWheelEvent* event);

private :
      QGraphicsScene *sence;
     QGraphicsProxyWidget *proxyWgt;
      QTableWidget *Table;

};

#endif // BASEZOOMABLETABLEWGT_H
