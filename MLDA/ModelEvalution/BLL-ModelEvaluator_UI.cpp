#include "BLL-ModelEvaluator_UI.h"

ModelEvaluator_UI::ModelEvaluator_UI()
{
       this->setTabsClosable(true);
        connect(this,SIGNAL(tabCloseRequested(int)),SLOT(CloseTab(int) ) );
        setWindowFlags(Qt::FramelessWindowHint);



}
void ModelEvaluator_UI::receive_evalData(int data ){

    cout<<data<<endl;
}

void ModelEvaluator_UI::receive_evalData(vector<vector<double>> testData,vector<double> y_prediction)
{
//  testData 为测试集数据
   // y_prediction 为模型输出


    TestDataMatrix=testData;
     sampleNums=TestDataMatrix.size();
     if(sampleNums>0) {
            FeatureNums=TestDataMatrix[0].size()-1;
     }else{
           cout<< "Test Data is empty!"<<endl;
     }
     y_Prediction=y_prediction;
     Evaluate();
     showEvalResults();

}
void ModelEvaluator_UI:: showEvalResults()
{
     int LabesNums=    Labels.size();

    ConfusionMatrixTable=new  DataTableWgt( LabesNums+2, LabesNums+2 );
    ConfusionMatrixTable->horizontalHeader()->setVisible(false);
    ConfusionMatrixTable->verticalHeader()->setVisible(false);

    for(auto l: Labels)
    {
        QTableWidgetItem *ei=new QTableWidgetItem();
        ei->setText( QString::number( l.first )  );
        ei->setBackgroundColor(QColor("green") );
        ConfusionMatrixTable->setItem(l.second+2,  1  ,ei);

        QTableWidgetItem *ej= new QTableWidgetItem();
        ej->setText( QString::number( l.first  )  );
        ej->setBackgroundColor(QColor("yellow") );
        ConfusionMatrixTable->setItem(1,  l.second+2    ,ej);

    }
       for(int i=2;i<= LabesNums+1;++i )
           for(int  j=2;j<=LabesNums+1;++j)
           {
                   QTableWidgetItem *e= new QTableWidgetItem();
                   e->setText( QString::number(ConfusionMatrix[i-2][ j-2])  );
                   ConfusionMatrixTable->setItem(i,  j ,e);

           }

       ConfusionMatrixTable->setSpan(0,2,1,LabesNums);
       ConfusionMatrixTable->setSpan(2,0,LabesNums,1);
       ConfusionMatrixTable->setSpan(0,0,2,2);
       QTableWidgetItem *pred= new QTableWidgetItem();
       pred->setText("Predicted");
       ConfusionMatrixTable->setItem(0,2,pred);
       QTableWidgetItem *truth = new QTableWidgetItem();
       truth->setText("Actual");
       ConfusionMatrixTable->setItem(2,0,truth);
       ConfusionMatrixTable->setBorderVisiable(false);

       this->addTab(ConfusionMatrixTable,QIcon(),"Confusion Matrix");
       setCurrentWidget(ConfusionMatrixTable);



}
void ModelEvaluator_UI::  CloseTab(int index)
{
        removeTab(index);
}

