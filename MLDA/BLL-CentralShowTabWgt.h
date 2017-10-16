#ifndef BLLCENTRALSHOWTABWGT_H
#define BLLCENTRALSHOWTABWGT_H
#include <QTabWidget>
#include <QList>

#include "Common.h"
#include "BLL-ProjectsManagerTree.h"
#include "baseWgt/BASE-zoomAbleTableWgt.h"
extern svmReportor *svm_Reportor;

class CentralShowTabWgt : public QTabWidget
{
    //这个类的对象放到主框架的中心DockWidget 中
    Q_OBJECT

public:
    CentralShowTabWgt();
    ~CentralShowTabWgt(){}
    void add2TabList(const TabData& tabData);
    TAB_TYPE  getCurTabType() ;

protected:
signals:
      void ShowMsgRequest(QString Type,QString message);

public slots:
    void  ShowData(QString fullpath,QString type);
    void  UpdateTab(QString oldID,TabData tabData);
    void  CloseTab(int index);
    void transpondMsg(QString Type,QString message);//转发消息


private:
     UtilReadTextFile *reader; //new 出一个对象作为这个类读取文本文件的工具，程序运行期间一直保持这个对象，避免每次重新new

      ///////////////////////////////////////////////////////////////////////////
      QList <TabData> TabList;

      TabData *findTabWithID(QString id);
      void deleteTab(QWidget *delWgt);



};

#endif // BLLCENTRALSHOWTABWGT_H
