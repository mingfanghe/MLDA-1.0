#ifndef BASEPLOT_H
#define BASEPLOT_H

#include "BASE-QCustomPlot.h"
#include<QThread>


class Plot : public QCustomPlot,public QThread
{
    //该类对象是一个widget，可放在主框架的 CentralShowTabWgt 中显示
    //封装一系列画图指令
    Q_OBJECT
public:
    explicit Plot(QWidget *parent = 0);
    void plot(const QVector<double> &x,const QVector<double> &y,
           QString xlabel,
           QString ylabel);
protected:

    void run();
signals:

public slots:

};



#endif // BASEPLOT_H
