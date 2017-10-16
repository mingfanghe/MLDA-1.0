#include "BASE-Plot.h"
#include <math.h>

#include <iostream>
using namespace std;
Plot::Plot(QWidget *parent) :
    QCustomPlot(parent)
{


}

 void Plot:: run(){

     QVector<double> x(100), y(100); // initialize with entries 0..100
     double dx= 10.0/100;
     for (int i=0; i<100; ++i)
     {
       x[i] =-5.0 + (double)(i*dx)  ; // x goes from -1 to 1

       y[i] = sin (x[i]); // let's plot a quadratic function
     }
     plot(x,y,"x","sin(x)");


 }
void Plot:: plot(const QVector<double> &x,const QVector<double> &y,
                 QString xlabel,
                 QString ylabel){

    // 添加数据曲线（一个图像可以有多个数据曲线）
    addGraph();
    // graph(0);可以获取某个数据曲线（按添加先后排序）
    // setData();为数据曲线关联数据
    graph(0)->setData(x, y);
    // 为坐标轴添加标签
    xAxis->setLabel("x");
    yAxis->setLabel("y");
    // 设置坐标轴的范围，以看到所有数据
    xAxis->setRange(-1, 1);
    yAxis->setRange(0, 1);

    setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    replot();

}


