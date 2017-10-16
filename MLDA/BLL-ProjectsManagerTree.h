#ifndef BLLPROJECTSMANAGERTREE_H
#define BLLPROJECTSMANAGERTREE_H

#include <QTreeWidget>
#include <QVector>
#include<QMessageBox>
#include<QMenu>
#include <QtEvents>
#include "Common.h"
#include<QThread>

enum  myItemType {Node,Leaf} ;


//****************redefined item type og the tree ****************************
class TreeItem : public QTreeWidgetItem
{

public:
    myItemType NodeType;
    TreeItem(QTreeWidgetItem *parent, const QStringList &strings,myItemType type):   QTreeWidgetItem(parent,strings)
    {
         NodeType=type;

    }
    TreeItem(QTreeWidget *parent, const QStringList &strings,myItemType type):QTreeWidgetItem(parent,strings)
    {
         NodeType=type;
    }

};


//**********************************************


class BLLProjectsManagerTree : public QTreeWidget
{
    Q_OBJECT
private:
    QMenu * menu;
    QString myProjectDir;
    QAction * addafolder_action,*addCsvFile_action,*addaExistingFile_action,*Rename_action ;
    QAction * Delete_action,*ShowAsTable_action;

public:
    explicit BLLProjectsManagerTree(QWidget *parent);
     void  addProject(QString ProjectName);

    TreeItem * addChild(QTreeWidgetItem *parent,QString name,QIcon icon,myItemType type);
     void getAllLeaf(TreeItem * activeProject,QStringList &path ,QStringList &Leaf);

signals:
    void ShowDataRequest(QString fullpath,QString type) ;
    void UpdateTabRequest(QString,TabData tabData);
    void ShowMsgRequest(QString Type,QString Msg );

    void  respondActivateProjectTreeLeaf(QString dir,QStringList allLeaf);


public slots:
   void transpondMsg(QString Type,QString message);
    void ItemClicked(QTreeWidgetItem*,int);
    void ItemDoubleClicked(QTreeWidgetItem*,int);
    void ItemExpanded(QTreeWidgetItem*Item ) ;
    void ItemCollapsed(QTreeWidgetItem*Item)  ;

    void AddaFolder();
    void AddCsv();
    void Rename();
    void deleteItem();
    void DataShowAsTable();
    void  getActivateProjectTreeLeaf(int id);
    void  freshProjectManagerTree();
protected :
     void run();
     virtual void contextMenuEvent(QContextMenuEvent *);
     void  closeEditor(QWidget *editor, QAbstractItemDelegate::EndEditHint hint);

private:
             void FreshTreeByFileSys(TreeItem *root,QString PathRoot);

             QTreeWidgetItem*  openProject(QString RootPath);
             void    WalkPath(QString PathRoot,TreeItem *TreeRoot );
              QVector<QTreeWidgetItem*>  Projects;

              TreeItem * RightKeyClickedItem;

              QTreeWidgetItem* ActivateProject;

              QString oldNodeName;  //重命名时暂时备份旧的节点名
              QString PathCur2Root(QTreeWidgetItem *cur);


};
///////////////////////////////////////////////////
// QString BLLProjectsManagerTree::myProjectDir("./");

#endif // BLLPROJECTSMANAGERTREE_H
