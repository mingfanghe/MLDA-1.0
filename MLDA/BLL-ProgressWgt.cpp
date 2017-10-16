#include "BLL-ProgressWgt.h"

BLLProgressWgt::BLLProgressWgt(QWidget *parent):QTreeWidget(parent)
{
    setColumnCount(1);
    setHeaderHidden(true);
    activatedProjectTree=new RuningProgress(this,"Project1" );
    activatedProjectRoot=activatedProjectTree->activatedProject;

    setItemWidget(activatedProjectTree->progressItem,0,activatedProjectTree->progressBar );

    activatedProjectRoot=activatedProjectTree->activatedProject;

    activatedProjectRoot->setExpanded(false);

}
void  BLLProgressWgt::RecvAMessage(QString type, QString message){
      if(type=="Progress")
      {
             activatedProjectTree->progressBar->setValue(message.toInt() );
      }
}
void BLLProgressWgt:: RecvAMessage(AiMsg msg )
{
      if(msg.Type==MSG_TYPE_NUM)
      {
             activatedProjectRoot-> setExpanded(true);
             activatedProjectTree->progressBar->setValue(msg.Num);
             if(msg.Num ==100 ){
                  activatedProjectTree->MessageItem->setText(0,"Finished");
             }

      }
}

