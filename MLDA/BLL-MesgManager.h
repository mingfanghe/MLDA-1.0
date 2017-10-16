#ifndef BLLMESGMANAGER_H
#define BLLMESGMANAGER_H

#include <QListWidget>
#include "Common.h"


class BLLMesgManager : public QListWidget
{
    Q_OBJECT
public:
         explicit BLLMesgManager(QWidget *parent = 0,QString initMessage="");

signals:

public slots:
     void RecvAMessage(QString type,QString message);
     void RecvAMessage(AiMsg msg);

private:
     QListWidgetItem* getItemWith(const AiMsg & msg);
     QListWidgetItem*MessageItem;

};

#endif // BLLMESGMANAGER_H
