#include "Solvers/Learner.h"

 GuiLearner::GuiLearner()
 {
     initVar();
 }
void GuiLearner:: initVar()
{
     this->setStyleSheet("border:none;");
     cellfont =new QFont("Times New Roman",12);

     TestDataTable=new DataTableWgt(1,3);

     TrainingDataTable=new DataTableWgt(1,3);

     evalWgt= new  ModelEvaluator_UI();

     trainingDataItem=new AiQComboBox();


     TestDataItems = new   AiQComboBox();

     initTrainDataTable();
     initTestDataTable();

}

void GuiLearner::init()
{
    cout<< " The current object of type BLL_SVM_UI is at " <<QThread::currentThreadId()<<endl;
    //*********create model tree****************
    QTreeWidget  * centralWidget= new QTreeWidget(this);
    centralWidget->setHeaderHidden(true);

    QTreeWidgetItem *  svmModel =new QTreeWidgetItem(centralWidget,QStringList()<<modelName+ " Model");
    svmModel->setFont(0,QFont("Times New Roman",13) );
    QTreeWidgetItem *  TrainDataPar =new QTreeWidgetItem(svmModel,QStringList()<<"training Data set");
    TrainDataPar->setFont(0,QFont("Times New Roman",13)  );
    QTreeWidgetItem *  TrainDataNode =new QTreeWidgetItem(TrainDataPar);

    QTreeWidgetItem *  TestDataParent =new QTreeWidgetItem(svmModel,QStringList()<<"Test Data");
      TestDataParent->setFont(0,QFont("Times New Roman",13)  );
    QTreeWidgetItem *  TestDataNode  =new  QTreeWidgetItem(TestDataParent);
    QTreeWidgetItem *  paraTbParent =new QTreeWidgetItem(svmModel,QStringList()<< "Parameters");
    paraTbParent->setFont(0,QFont("Times New Roman",13)  );
    QTreeWidgetItem *  paraTbNode =new QTreeWidgetItem(paraTbParent);

    QTreeWidgetItem *  evalWgtPar =new QTreeWidgetItem(svmModel,QStringList()<<"Model Evalution");
     evalWgtPar->setFont(0,QFont("Times New Roman",13)  );
    QTreeWidgetItem *  evalWgtNode =new QTreeWidgetItem(evalWgtPar);

     svmModel->setExpanded(true);


    //*********set model tree****************
    centralWidget->setItemWidget(TrainDataNode,0,trainingDataItem);
    centralWidget->setItemWidget(paraTbNode,0,paramsTable   );
    centralWidget->setItemWidget(TestDataNode, 0 ,TestDataItems );

    centralWidget->setItemWidget(evalWgtNode,0,evalWgt);
      //*********add model tree into the window****************

    setCentralWidget(centralWidget);

    //********** 显示模型的评测结果************************

}

void GuiLearner:: initDatasetItems(int row)
{
       emit getActivateProjectTreeLeafRequest( 0 );

}
void GuiLearner:: initTestDataTable()
{

    TestDataTable->setColumnWidth(0,200);
    TestDataTable->setColumnWidth(1,300);
    TestDataTable->setColumnWidth(2,600);
    TestDataTable->setMaximumHeight(100);
    TestDataTable->setHorizontalHeaderLabels(QStringList()<<"Parameters Name"<<"Values"<<"Comment" );

    QTableWidgetItem * var =new QTableWidgetItem("Test data");
    QTableWidgetItem * Comment =new QTableWidgetItem("Test Data set");
    addTableRow(TestDataTable, 0,var,TestDataItems,Comment);
    setTableAttributes(TestDataTable);

    TestDataTable->setStyleSheet("border:none;");
    TestDataTable->horizontalHeader()->setVisible(false);
    TestDataTable->verticalHeader()->setVisible(false);
}
void GuiLearner:: initTrainDataTable()
{

    TrainingDataTable->setColumnWidth(0,200);
    TrainingDataTable->setColumnWidth(1,300);
    TrainingDataTable->setColumnWidth(2,600);
    TrainingDataTable->setMaximumHeight(100);
      TrainingDataTable->setHorizontalHeaderLabels(QStringList()<<"Parameters Name"<<"Values"<<"Comment" );
    QTableWidgetItem * var =new QTableWidgetItem("Training data");
    QTableWidgetItem * Comment =new QTableWidgetItem("Training Data set");
    addTableRow(TrainingDataTable, 0,var,trainingDataItem,Comment);

    setTableAttributes(TrainingDataTable);
    TrainingDataTable->setStyleSheet("border:none;");
    TrainingDataTable->horizontalHeader()->setVisible(false);
    TrainingDataTable->verticalHeader()->setVisible(false);

}

void GuiLearner:: receive_trainingData(QString dir, QStringList path)
{

        setActivateProjectDir(dir);
        trainingDataItem->addItems(path);
        int maxW=0;
        for(auto item:path) {
              if(item.length()>maxW ) maxW =item.length();
        }
        maxW *=7;
        trainingDataItem->setMaximumWidth(maxW);

        TestDataItems->addItems(path);
        TestDataItems->setMaximumWidth(maxW);


}
void GuiLearner::addTableRow(DataTableWgt * table,int row,QTableWidgetItem*var,QTableWidgetItem*val,QTableWidgetItem*comment )
{
      table->setItem(row,0,var);
      table->setItem(row,1,val);
      table->setItem(row,2,comment);

}
void GuiLearner::addTableRow(DataTableWgt * table,int row,QTableWidgetItem*var,QWidget *val,QTableWidgetItem*comment )
{
      table->setItem(row,0,var);
      table->setCellWidget(row,1,val);
      table->setItem(row,2,comment);

}
void GuiLearner::setTableAttributes( DataTableWgt * Table){

    if(!cellfont)
        cellfont =new QFont("Times New Roman",12);
     int m= Table->rowCount();
     int n=Table->columnCount();

    for(int i=0;i<m;++i)
        for(int j=0;j<n;++j){
             QTableWidgetItem *itemWgt= Table->item(i,j);

             if(itemWgt){
                      itemWgt->setTextAlignment(Qt::AlignLeft);
                      itemWgt->setFont(*cellfont);
             }
        }

    int  H=15;
    if (m>0)   H=Table->rowHeight(0);
    Table->setMinimumHeight(  (m+1) * H);

    Table->horizontalHeaderItem(0)->setTextAlignment(Qt::AlignLeft);
    Table->horizontalHeaderItem(0)->setFont(*cellfont);
    Table->horizontalHeaderItem(1)->setTextAlignment(Qt::AlignLeft);
    Table->horizontalHeaderItem(1)->setFont(*cellfont);
    Table->horizontalHeaderItem(2)->setTextAlignment(Qt::AlignLeft);
    Table->horizontalHeaderItem(2)->setFont(*cellfont);

}
