#include "BLL-CentralShowTabWgt.h"
#include "Common.h"
#include "GlobalVars.h"

CentralShowTabWgt::CentralShowTabWgt()
{

    extern int jinjiego;

    Plot* plot= new Plot();
    TabList.append(TabData(plot,"Sin","figure"));
    plot->start();
    int  plotIndex=addTab(plot," figure ");
    setTabIcon(plotIndex,QIcon(":/res/Images/Figure.png"));
    setTabsClosable(true);

    //addTab(new zoomAbleTableWgt(this),"zoomAbleTableWgt");

    QMainWindow * aTab=new QMainWindow(this);

    TabList.append( TabData(aTab,"DataTableTest","Data Table ") );
    aTab->setCentralWidget(new TextDataWgt());
    addTab(aTab ,"Text");

    connect(this,SIGNAL(tabCloseRequested(int)),SLOT(CloseTab(int) ) );

    reader=new UtilReadTextFile() ; //线程文本读取器
    connect(reader,SIGNAL( ShowMsgRequest(QString,QString)) ,this,SLOT( transpondMsg(QString ,QString )  )     );//SLOT中的槽函数不要写形参

}
  void CentralShowTabWgt::add2TabList(const TabData& tabData){
      this-> TabList.append(tabData);
      this->addTab(  tabData.wgt,tabData.Label  );
      this->setCurrentWidget(tabData.wgt);

  }

TAB_TYPE CentralShowTabWgt :: getCurTabType() {
           int tabIndex =currentIndex();
           for(auto iter=TabList.begin();iter!=TabList.end();++iter)
           {
                 int curIndex= this->indexOf(iter->wgt);
                 if(curIndex == tabIndex ) return iter->tabType;
           }
            return TAB_OTHERS;
}

void CentralShowTabWgt:: CloseTab(int index)
{
      //deleteTab(  );
   //   removeTab(index);
      deleteTab( widget(index)  );


}
void CentralShowTabWgt:: transpondMsg(QString Type,QString message)
{
           emit ShowMsgRequest(Type,message);
}

void CentralShowTabWgt:: UpdateTab(QString oldID,TabData tabData){
    TabData * tab=     findTabWithID(oldID);
    if(tab)  //是否存在对应的tab
    {
        tab->ID=tabData.ID;
        tab->Label=tabData.Label;
        int index=indexOf(tab->wgt);
        setTabText(index,tab->Label);
    }

}
void CentralShowTabWgt::ShowData(QString fullpath,QString type){
    if("Text"==type)
    {
        TabData *tab=findTabWithID(fullpath);//检查是否已经打开
        if (tab==NULL )
        {
            QMainWindow * aTab=new QMainWindow(this);

            TextDataWgt * TextTab= new TextDataWgt();
            reader->ReadTextFileFrom(fullpath,TextTab);//线程读文本，防止界面卡顿，线程不能在这个函数结束后生命周期停止，否则文本可能读不完
            TextTab->setUtf8(true);
            aTab->setCentralWidget(TextTab);

            QString label=fullpath.mid(1+fullpath.lastIndexOf("\\"));
            addTab(aTab ,label);

            TabList.append(TabData (  aTab ,fullpath,label ));

            setCurrentWidget(aTab);
        }else {

            addTab(tab->wgt,tab->Label);
            setCurrentWidget(tab->wgt);
        }
    }else if("Table"==type){

                DataTableWgt * tableTab=new DataTableWgt();

                reader->ReadTextAsTable(fullpath, tableTab);
                QString label=fullpath.mid(1+fullpath.lastIndexOf("\\"));

                int tableTabIndex=  addTab(tableTab ,label);

                setTabIcon(tableTabIndex,QIcon(":/res/Images/table.png"));
                TabList.append(TabData (  tableTab ,fullpath,label ));
                setCurrentWidget(tableTab);
    }

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TabData * CentralShowTabWgt::   findTabWithID(QString id ){

    for ( auto iter = TabList.begin();iter!=TabList.end(); ++iter){
        if(id==iter->ID){
            return  &(*iter);
        }
    }
    return NULL;
}
void CentralShowTabWgt:: deleteTab(QWidget *delWgt)
{
    int i=0;
     for ( auto iter = TabList.begin();iter!=TabList.end(); ++iter,++i){
          if(delWgt==iter->wgt)
          {
                 iter->freeWgt();
                 TabList.removeAt(i);
                 break;
          }
     }

}








