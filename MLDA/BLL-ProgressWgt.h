#ifndef BLLPROGRESSWGT_H
#define BLLPROGRESSWGT_H
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QProgressBar>
#include "Common.h"
//typedef  void (QTreeWidget::*setItemWidget)(QTreeWidgetItem*,int,QWidget*);

class RuningProgress:public QObject
{
public:

    RuningProgress(QTreeWidget*parent, QString activatedProjectName) //,setItemWidget fun )
    {
        activatedProject=new QTreeWidgetItem(parent, QStringList(activatedProjectName));
        activatedProject->setIcon(0,QIcon(":/res/Images/logo.png"));
        MessageItem=new QTreeWidgetItem(QStringList("Runing ..."));

        progressItem=new QTreeWidgetItem();
        progressBar=new QProgressBar();
        progressBar->setMaximumWidth(300);
        progressBar->setMaximumHeight(20);
        //(*fun)(progressItem,0,progressBar);
        ShowStatus();

    }
    ~RuningProgress(){
        delete activatedProject;
        delete MessageItem;
        delete  progressItem;
        delete  progressBar;
    }

    void ShowStatus()
    {
         activatedProject->addChild(MessageItem);
         activatedProject->addChild(progressItem);

    }
    void ClearStatus()
    {

    }
    void UapdateStatus(QString message,int progress)
    {
           MessageItem->setText(0,message);
           progressBar->setValue(progress);
    }
public:
       QTreeWidgetItem* activatedProject;
       QTreeWidgetItem *MessageItem;
       QTreeWidgetItem *progressItem;
       QProgressBar *progressBar;

};



class BLLProgressWgt : public  QTreeWidget
{

    Q_OBJECT
public:
     BLLProgressWgt(QWidget *parent=nullptr);


signals:
public slots:
     void RecvAMessage(QString type, QString message);
     void RecvAMessage(AiMsg msg );

private :
     QTreeWidgetItem * activatedProjectRoot;
     RuningProgress * activatedProjectTree;
};

#endif // BLLPROGRESSWGT_H
