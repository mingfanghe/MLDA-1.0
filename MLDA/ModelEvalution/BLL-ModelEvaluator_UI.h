#ifndef BLLMODELEVALUATOR_UI_H
#define BLLMODELEVALUATOR_UI_H
#include<QTabWidget>
#include "alg-modelevaluate.h"
#include <QTableWidget>
#include "baseWgt/BASE-DataTableWgt.h"
#include "Common.h"
/*
 主要的区别是QTableView可以使用自定义的数据模型来显示内容
(也就是先要通过setModel来绑定数据源)，而QTableWidget则只能使
用标准的数据模型，并且其单元格数据是QTableWidgetItem的对
象来实现的(也就是不需要数据源，将逐个单元格内的信息填好即可)。
这主要体现在QTableView类中有setModel成员函数，而到了QTableWidget类中，
该成员函数变成了私有。使用QTableWidget就离不开QTableWidgetItem。
QTableWidgetItem用来表示表格中的一个单元格，正个表格都需要用逐
个单元格构建起来。


  */
class ModelEvaluator_UI : public QTabWidget,ModelEvaluator
{
    Q_OBJECT

public:
       ModelEvaluator_UI();
       ~ModelEvaluator_UI(){}

       void  showEvalResults();


public slots:
        void receive_evalData(vector<vector<double>> testData,vector<double> y_prediction);
        void  receive_evalData(int);
        void  CloseTab(int index);

protected:
        DataTableWgt * ConfusionMatrixTable;
private:

};

#endif // BLLMODELEVALUATOR_UI_H
