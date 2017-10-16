#ifndef LEARNER_H
#define LEARNER_H
#include <QThread>
#include <QMainWindow>
#include "baseWgt/BASE-Type.hpp"
#include "baseWgt/BASE-DataTableWgt.h"
#include "ModelEvalution/BLL-ModelEvaluator_UI.h"
#include "baseWgt/BASE-AiQComboBox.h"
#include "QTreeWidgetItem"
#include "QTreeWidget"


/*
   此文件提供两个基类
   学习器类 Learner：
                      继承自QThread，主要为各类学习器提供一个统一的接口
                      各个学习其算法作为后端，只提供一个最原始的算法实现，不涉及相关的界面 ，这一层作为 Algorithm 层
                      将算法进一步封装，得到算法业务层，主要封装算法的使用，命名 Ai_Algorithm，继承自Learner

       学习器界面类GuiLearner：
                     继承自QMainWindow，主要负责算法调用交互，完成参数设置的功能


*/

class Learner:public  QThread  //学习器基类
{
    Q_OBJECT
signals:
    void ShowMsgRequest(AiMsg msg);

protected:
    int trainningAble;

public:
    virtual void startUp(){}
    virtual  void  train(){}     // training
    virtual  void  predict(){}   // predtion
    virtual void   evaluate(){}  //evaluate

    virtual void  setTrainingData(){ }
    void setrainningAble(int flag=0){trainningAble=flag;}
};

class GuiLearner :public QMainWindow{

    Q_OBJECT

 signals:

    void getActivateProjectTreeLeafRequest(int id);
    void ShowMsgRequest(AiMsg msg);

public slots:
    // void  SendEvalutionData(vector<vector<double>> testData,vector<double> y_prediction);
    void  receive_trainingData(QString dir, QStringList path);


public:
    DataTableWgt * paramsTable,*TrainingDataTable ,*TestDataTable, *EvalutionTable;
    ModelEvaluator_UI  * evalWgt;
    AiQComboBox * trainingDataItem,*TestDataItems;
    Learner *learner;

    GuiLearner();
    GuiLearner(QWidget*parent):QMainWindow(parent){
        initVar();
    }
    void addTableRow(DataTableWgt * table,int row,QTableWidgetItem*var,QTableWidgetItem*val,QTableWidgetItem*comment );
    void addTableRow( DataTableWgt * table ,  int row,QTableWidgetItem*var,QWidget *val,QTableWidgetItem*comment );
    void  initVar();
    void init();
    void initDatasetItems(int row);
    void initTestDataTable();
    void initTrainDataTable();
    void setTableAttributes( DataTableWgt * Table);

    //
    virtual void   updateParamFromUI(){}
protected :
    QFont  * cellfont;

    QString modelName, ActivateProjectDir ;
    void setActivateProjectDir(QString &dir){ ActivateProjectDir =dir;}


};


struct LearnerUI
{

    GuiLearner *Ui;
    LearnerUI(QMainWindow *ui=nullptr )
    {
        Ui=(GuiLearner * )ui;          // C++  类型不安全
    }

};




#endif
