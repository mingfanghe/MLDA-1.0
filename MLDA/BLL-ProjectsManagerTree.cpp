#include "BLL-projectsmanagertree.h"

BLLProjectsManagerTree::BLLProjectsManagerTree(QWidget *parent) :
    QTreeWidget(parent)
{

    myProjectDir= "I:\\Projects\\Qt\\AiProjects";
    ActivateProject=  openProject(myProjectDir+"\\Project1");

    setColumnCount(1);
    setHeaderHidden(true);
    //////////////////////////////////////////////////////////////////////////////////////////////////
    addafolder_action= new QAction(tr("Add a folder"),this);
    addafolder_action->setIcon(QIcon(":/res/Images/AddFolder.png"));
    connect(addafolder_action,SIGNAL(triggered(bool)),SLOT(AddaFolder()  ));

    addCsvFile_action=new QAction(tr("Add a csv file"),this);
    addCsvFile_action->setIcon(QIcon(":/res/Images/NewFile.png"));
    connect(addCsvFile_action,SIGNAL(triggered(bool)) , SLOT(AddCsv() ));

    addaExistingFile_action =new QAction(tr("Add an existing file"),this);
    addaExistingFile_action->setIcon(QIcon(":/res/Images/Add_file.png"));

    Rename_action =new QAction(tr("Rename"),this);
    connect(Rename_action,SIGNAL(triggered(bool)),SLOT( Rename() ) );

    Delete_action= new QAction(tr("Delete"),this);
    Delete_action->setIcon(QIcon(":/res/Images/delete.png") );
    connect(Delete_action,SIGNAL(triggered(bool)),SLOT( deleteItem()  ));

    ShowAsTable_action=new QAction(tr("Show as Table") );
    connect(ShowAsTable_action,SIGNAL(triggered(bool)) ,SLOT( DataShowAsTable()    )   );

    //////////////////////////////////////////////////////////////////////////////////////////////////

    menu= new QMenu();

    menu->addAction(new QAction(tr("close"),this));

    connect(this,SIGNAL(itemClicked(QTreeWidgetItem*,int)),SLOT(ItemClicked(QTreeWidgetItem *,int)  ));
    connect(this,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),SLOT(ItemDoubleClicked(QTreeWidgetItem*,int) )  );

    connect(this,SIGNAL(itemExpanded(QTreeWidgetItem*)),SLOT(ItemExpanded(QTreeWidgetItem* )    ));
    connect(this,SIGNAL(itemCollapsed(QTreeWidgetItem*)),SLOT(ItemCollapsed(QTreeWidgetItem*)      ));

    //////start();

}
void BLLProjectsManagerTree::ItemExpanded(QTreeWidgetItem*Item ) {
       if(Item->parent()!=NULL)
           Item->setIcon(0,QIcon(":/res/Images/FolderOpen.png"));
}
void BLLProjectsManagerTree::ItemCollapsed(QTreeWidgetItem*Item)  {
     if(Item->parent() !=NULL )
            Item->setIcon(0,QIcon(":/res/Images/FolderClose.png"));
}
QTreeWidgetItem* BLLProjectsManagerTree:: openProject(QString RootPath){

    emit ShowMsgRequest("","Open "+RootPath);//或许messageManager 对象尚未初始化完成

    TreeItem *Project=new  TreeItem(this,  QStringList(RootPath.mid(1+ RootPath.lastIndexOf("\\")  )),Node );
    Project->setIcon(0,QIcon(":/res/Images/logo.png"));

    WalkPath(RootPath,Project);
    Project->setExpanded(true);
    Projects.append(Project);
    return Project;

}
void  BLLProjectsManagerTree::  WalkPath(QString PathRoot,TreeItem *TreeRoot )
{//递归地遍历整个文件夹
     QDir dir(PathRoot);
     for(QFileInfo fileInfo:dir.entryInfoList())
     {
           if(fileInfo.isFile() ){
                addChild(TreeRoot,fileInfo.fileName(),QIcon(":/res/Images/TextFileLogo.png"),Leaf);

            }else{
              if(fileInfo.fileName()=="." || fileInfo.fileName()=="..") continue;
              TreeItem *cur= addChild(TreeRoot,fileInfo.baseName(),QIcon(":/res/Images/FolderClose.png"),Node);
               WalkPath(fileInfo.absoluteFilePath(), cur);
               if( cur->childCount() >0 ) cur->setIcon(0,QIcon(":/res/Images/FolderOpen.png") );

           }
      }//for
}

TreeItem * BLLProjectsManagerTree::addChild(QTreeWidgetItem *parent,QString name,QIcon icon,myItemType isLeaf){
       TreeItem * Child=new TreeItem(parent, QStringList(name),isLeaf);
       Child->setIcon(0,icon);
       Child->setExpanded(true);

       parent->addChild(Child);

       return Child;

}

void  BLLProjectsManagerTree:: addProject(  QString ProjectName){
    CreateDir(myProjectDir+"\\"+ProjectName);
    TreeItem *Project=new  TreeItem(this,  QStringList(ProjectName),Node );
    Projects.append(Project);

    addChild(Project,QString("Data"),QIcon(":/res/Images/FolderClose.png"),Node);
    addChild(Project,QString("Model"),QIcon(":/res/Images/FolderClose.png"),Node);
    addChild(Project,QString("Results"),QIcon(":/res/Images/FolderClose.png"),Node);
    CreateDir(myProjectDir+"\\"+ProjectName+"\\"+QString("Data"));
    CreateDir(myProjectDir+"\\"+ProjectName+"\\"+QString("Model"));
    CreateDir(myProjectDir+"\\"+ProjectName+"\\"+QString("Result"));
    Project->setExpanded(true);

}
void BLLProjectsManagerTree::transpondMsg(QString Type,QString message){

            ShowMsgRequest(Type,message);
}
void  BLLProjectsManagerTree:: ItemClicked(QTreeWidgetItem*Item,int index){

    TreeItem * item=(TreeItem*)Item;

    if( NULL==item->parent()  ){
        //
         cout<< QString(item->text(index) ).toStdString()<<"\n";
    }else if(item->NodeType==Leaf ){
        //QMessageBox::information(NULL, QString("click Promote"  ), QString(item->text(index)  ));

    }

}
void BLLProjectsManagerTree:: ItemDoubleClicked(QTreeWidgetItem*Item,int index){

    TreeItem * item=(TreeItem*)Item;
    if(item->NodeType==Leaf ){
         emit ShowMsgRequest("","Open file "+myProjectDir+PathCur2Root( Item ));//显示消息

         emit ShowDataRequest(myProjectDir+PathCur2Root( Item ),"Text" );//发送数据显示请求
    }

}

void BLLProjectsManagerTree::contextMenuEvent(QContextMenuEvent *event)
{
    //右键菜单
      QPoint p=  event->pos();
      RightKeyClickedItem= (TreeItem *)itemAt(p);

     if(RightKeyClickedItem){

        menu->clear();
        menu->addAction(Rename_action );
        menu->addAction(Delete_action);

        if( RightKeyClickedItem->parent() ==NULL){//if the selected item is Root

        }
        if (RightKeyClickedItem->NodeType==Node)  //右键节点
        {
            menu->addAction(addafolder_action);
            menu->addAction(addCsvFile_action );
            menu->addAction(addaExistingFile_action);

        }else{
            menu->addAction(ShowAsTable_action );
        }
        event->accept();
        menu->exec(QCursor::pos());
     }
}
  void BLLProjectsManagerTree::  getActivateProjectTreeLeaf(int id)
   {
       QStringList path(  "/"+ActivateProject->text(0) ), allLeaf;
       getAllLeaf((TreeItem*)ActivateProject, path,allLeaf);
       emit  respondActivateProjectTreeLeaf(myProjectDir, allLeaf );
    }
 void BLLProjectsManagerTree::freshProjectManagerTree()
 {
          cout<<"freshProjectManagerTree"<< endl;

 }
void BLLProjectsManagerTree::FreshTreeByFileSys(TreeItem *root,QString PathRoot)
{
    QDir dir(PathRoot);
   /*
    for(QFileInfo fileInfo:dir.entryInfoList())
    {
          if(fileInfo.isFile() ){
               addChild(TreeRoot,fileInfo.fileName(),QIcon(":/res/Images/TextFileLogo.png"),Leaf);

           }else{
             if(fileInfo.fileName()=="." || fileInfo.fileName()=="..") continue;
             TreeItem *cur= addChild(TreeRoot,fileInfo.baseName(),QIcon(":/res/Images/FolderClose.png"),Node);
              WalkPath(fileInfo.absoluteFilePath(), cur);
              if( cur->childCount() >0 ) cur->setIcon(0,QIcon(":/res/Images/FolderOpen.png") );

          }

     }//for

*/

}
void  BLLProjectsManagerTree:: DataShowAsTable()
{
                TreeItem * Item=(TreeItem *)currentItem();
                if(Item->NodeType==Leaf )
                {
                     emit ShowMsgRequest("","Open file "+myProjectDir+PathCur2Root( Item ));//显示消息
                     emit ShowDataRequest(myProjectDir+PathCur2Root( Item ),"Table" );//发送数据显示请求
                }

}
void BLLProjectsManagerTree:: deleteItem(){

      TreeItem * Item=(TreeItem *)currentItem();
       QString  path=myProjectDir+PathCur2Root( Item );
      QString Text="<"+path+"> and its subitems  will be deleted permanently！ ";
      QDir dir(path);
      if(Item->NodeType == Leaf)
      {
           if(QMessageBox::information(NULL,MLDA,Text,QMessageBox::Yes | QMessageBox::No , QMessageBox::No)==QMessageBox::Yes  )
                    dir.remove(path )  ;

      }else{
          if(QMessageBox::information(NULL,"Confirm",Text,QMessageBox::Yes | QMessageBox::No , QMessageBox::No)==QMessageBox::Yes  ) {
              if(dir.exists()){
                  //dir.remove(path);
                  DelDir(path);
              }else{
                  QMessageBox::information(NULL,"Warning","delete Error!",QMessageBox::Yes);
              }
          }
      }
      TreeItem * ParentOfItem=(TreeItem *)Item->parent();
      ParentOfItem->removeChild(Item);

}
void BLLProjectsManagerTree::AddaFolder(){

     RightKeyClickedItem->setExpanded(true);

     QString folderName="\\NewFolder";

     QDir dir(myProjectDir+PathCur2Root(RightKeyClickedItem)+folderName);

     if( dir.exists() ){ //检查重命名文件夹
         int i=1;
         dir.setPath(myProjectDir+PathCur2Root(RightKeyClickedItem)+folderName+QString::number(i) );
         while(dir.exists() ){
             ++i;
             dir.setPath(myProjectDir+PathCur2Root(RightKeyClickedItem)+folderName+QString::number(i) );
         }
         folderName=folderName+QString::number(i);
     }

     TreeItem * newNode= addChild(RightKeyClickedItem,folderName.mid(1),QIcon(":/res/Images/FolderClose.png"),Node);
     CreateDir(  myProjectDir+PathCur2Root(newNode) );
     emit ShowMsgRequest("","Create directory "+  myProjectDir+PathCur2Root(newNode)   );

     editItem(newNode);


}
void BLLProjectsManagerTree:: Rename(){

    QTreeWidgetItem * selected = currentItem();

    oldNodeName=selected->text(0);

    selected->setFlags(selected->flags() | Qt::ItemIsEditable );

    editItem( selected  );

}

void BLLProjectsManagerTree:: closeEditor(QWidget *editor, QAbstractItemDelegate::EndEditHint hint){


    TreeItem * changeedNode=(TreeItem * ) currentItem();

    QString cur2Root= PathCur2Root(changeedNode);

    QString oldName=myProjectDir +PathCur2Root(changeedNode->parent() )+"\\"+oldNodeName;
    QString newName=myProjectDir +cur2Root;
   // *********update the corresponding file system*****
     if(changeedNode->NodeType ==Leaf ){
         QFile ::rename(oldName,newName);
     }else{
             QDir dir;
                    dir.rename(oldName, newName );
     }
     //*******************************************
     if(changeedNode ->NodeType==Leaf){ //如果改变的是叶子结点，对应显示的tab 也要更新
                        emit UpdateTabRequest(oldName,TabData(0,newName,changeedNode->text(0))        );
     }

    QTreeWidget:: closeEditor(editor,hint);

}
 QString BLLProjectsManagerTree:: PathCur2Root(QTreeWidgetItem *cur)
 {
    if( !cur ) return "\\";

     QString path("\\"+cur->text(0) );
     for(QTreeWidgetItem *root=cur->parent();root;root=root->parent() ){
         path="\\"+root->text(0)+path;
     }
     return path;

 }
void  BLLProjectsManagerTree:: AddCsv(){

    TreeItem *seled= (TreeItem * )currentItem();

    TreeItem * file = addChild(seled,QString("NewTxt.csv"),QIcon(":/res/Images/TextFileLogo.png"),Leaf);

    QFile newTxt(myProjectDir+PathCur2Root(file ));

    cout<<"Create>>>" <<QString(myProjectDir+PathCur2Root(file ) ).toStdString()<<endl;

    newTxt.open(QFile::Append);

    newTxt.close();

}
void BLLProjectsManagerTree :: getAllLeaf(TreeItem * root,QStringList &path ,QStringList &allLeaf){
     if(!root) return ;

    if(root->child(0)==nullptr &&root->NodeType==Leaf ){  // leaf node
         QString t;
         for(auto p=path.begin();p!=path.end();++p){
               t.append(*p);
         }
         cout<<t.toStdString()<<endl;
         allLeaf.append(t);
    } else{
        for(int i=0;i<root->childCount();++i)
        {
                 TreeItem *child= (TreeItem*) root->child(i);
                  path.append("/"+child->text(0));
                   getAllLeaf(child,path,allLeaf);
                  path.pop_back();
         }
    }
}

