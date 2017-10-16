#include "BLL-mesgmanager.h"

BLLMesgManager::BLLMesgManager(QWidget *parent,QString initMessage) :
    QListWidget(parent)
{
      MessageItem=new QListWidgetItem(initMessage,this);
      insertItem(1,MessageItem);
}
void BLLMesgManager::RecvAMessage(QString type,QString message)
{
     addItem(getItemWith(AiMsg(Ok,MSG_TYPE_TEXT, 0, message ) ));
}
QListWidgetItem* BLLMesgManager::getItemWith(const AiMsg & msg)
{
    //generate an item with given message
    QString msgCont;
    for( auto c:msg.Content)
        msgCont.append(c);
     QListWidgetItem* MessageItem=new QListWidgetItem(msgCont,this);
     switch(msg.Status)
     {
        case Error:
        case Fail:
               MessageItem->setIcon(QIcon(":res/Images/ErrorMsg.png"));
               MessageItem->setForeground(QBrush(QColor(  Qt::red   )));
              break;
         case Warning:
                 MessageItem->setIcon(QIcon(":res/Images/WarningMsg.png"));
                 break;
        default:
                 MessageItem->setIcon(QIcon(":res/Images/NormalMsg.png"));
                 break;
         }
      return  MessageItem;
}
 void BLLMesgManager::RecvAMessage(AiMsg msg)
 {
         if(msg.Type==MSG_TYPE_TEXT) //接受一个文本消息
         {
                addItem(getItemWith(msg));
         }
 }
