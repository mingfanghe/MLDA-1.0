/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "Gui-mainwindow.h"
#include "Gui-colorswatch.h"
#include "Gui-toolbar.h"
#include "BLL-CentralShowTabWgt.h"

#include <QAction>
#include <QLayout>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QTextEdit>
#include <QFile>
#include <QDataStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QSignalMapper>
#include <QApplication>
#include <QPainter>
#include <QMouseEvent>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <qdebug.h>
#include <QTableWidget>
#include<QTreeWidget>
#include <QMetaType>
#include "svm/AiSvm.h"


static const char * const message =
    "<p><b>Qt Main Window Example</b></p>"

    "<p>This is a demonstration of the QMainWindow, QToolBar and "
    "QDockWidget classes.</p>"

    "<p>The tool bar and dock widgets can be dragged around and rearranged "
    "using the mouse or via the menu.</p>"

    "<p>Each dock widget contains a colored frame and a context "
    "(right-click) menu.</p>"

#ifdef Q_OS_MAC
    "<p>On Mac OS X, the \"Black\" dock widget has been created as a "
    "<em>Drawer</em>, which is a special kind of QDockWidget.</p>"
#endif
    ;

Q_DECLARE_METATYPE(QDockWidget::DockWidgetFeatures)

MainWindow::MainWindow(const QMap<QString, QSize> &customSizeHints,
                        QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{

     cout<< " The current object of type MainWindow is at " <<QThread::currentThreadId()<<endl;


    LearnerList=new QList<LearnerUI*> ();

    //★★★注册自定义类型,方可作为消息*****
    qRegisterMetaType<AiMsg> ("AiMsg"); // 注册自定义消息类型，否则信号槽不起作用

    setObjectName("MainWindow"); //
    setWindowTitle("MLDA");


    center = new QTextEdit(this);
    center->setReadOnly(true);
     center->setMinimumSize(1000, 700);
    setCentralWidget(center);

    showMaximized();

    setupToolBar();
    setupMenuBar();
    setupDockWidgets(customSizeHints);

    statusBar()->showMessage(tr("Ready"));

    // while project tree asked to open a csv file
    connect(ProjectTreeViewer,SIGNAL(ShowDataRequest(QString,QString) ),CentralTabWidget,SLOT( ShowData(QString,QString))  );
    connect(ProjectTreeViewer,SIGNAL( UpdateTabRequest(QString,TabData )) ,CentralTabWidget,SLOT(UpdateTab(QString,TabData)) );

    connect(ProjectTreeViewer,SIGNAL(  ShowMsgRequest(QString,QString)) ,messagesManager,SLOT(  RecvAMessage(QString,QString))          );

    connect(CentralTabWidget,SIGNAL(   ShowMsgRequest(QString,QString)) ,messagesManager,SLOT(RecvAMessage(QString,QString))    );
    connect(libsvm::svm_Reportor,SIGNAL(ShowMsgRequest(AiMsg)), messagesManager,SLOT(RecvAMessage( AiMsg )    ) );
    connect(libsvm::svm_Reportor,SIGNAL(ShowMsgRequest(AiMsg)), progressWgtManager,SLOT( RecvAMessage(AiMsg)  )   );


     setupASvmInstance();

}
MainWindow::~MainWindow(){
     delete ProjectTreeViewer;   delete ProjectDockWidget;
     delete messagesManager; delete MessagesDockWidget;
     delete progressWgtManager;delete ProgressDockWidget;



}
void MainWindow::setupASvmInstance()
{
         LearnerUI *svm=new LearnerUI;
        AiSVM *newSvm= new AiSVM;

        connect(newSvm,SIGNAL(ShowMsgRequest(AiMsg)),messagesManager,SLOT(  RecvAMessage(AiMsg)    ) ) ;
        connect(newSvm,SIGNAL(ShowMsgRequest(AiMsg)),  progressWgtManager ,SLOT(RecvAMessage(AiMsg))  );

        connect(libsvm::svm_Reportor,SIGNAL(ShowMsgRequest(AiMsg)), messagesManager,SLOT(RecvAMessage( AiMsg )    ) );
        connect(libsvm::svm_Reportor,SIGNAL(ShowMsgRequest(AiMsg)), progressWgtManager,SLOT( RecvAMessage(AiMsg)  )   );

        GuiLearner *bllsvmui=  new BLL_SVM_UI(nullptr,newSvm);


        connect(bllsvmui ,SIGNAL(ShowMsgRequest(AiMsg)),  messagesManager,SLOT(RecvAMessage( AiMsg )    )  );
        connect(bllsvmui , SIGNAL(getActivateProjectTreeLeafRequest(int) ) ,ProjectTreeViewer, SLOT( getActivateProjectTreeLeaf(int)  ));
        connect( ProjectTreeViewer,SIGNAL(respondActivateProjectTreeLeaf(QString ,QStringList)), bllsvmui ,SLOT(receive_trainingData(QString,  QStringList))   );

        connect(bllsvmui, SIGNAL(freshProjectManagerTreeRequest()),ProjectTreeViewer,SLOT(freshProjectManagerTree()) );

        svm->Ui=bllsvmui;

        bllsvmui->initDatasetItems(0);

        LearnerList->append(svm);


        CentralTabWidget->add2TabList(TabData(bllsvmui ,TAB_GUI_LEARNER,"dgjio","SVM setup") );


}


void MainWindow::actionTriggered(QAction *action)
{
    qDebug("action '%s' triggered", action->text().toLocal8Bit().data());
}
void MainWindow::ActionNewClicked()
{


}
void MainWindow:: RunModel()
{
    // run the model
   cout<<  typeid( BLL_SVM_UI ).name() <<endl;
   cout<<typeid ( CentralTabWidget->currentWidget() ).name() <<endl;

   if  ( CentralTabWidget->getCurTabType() ==TAB_GUI_LEARNER  )
   {
        cout<<"BLL_SVM_UI"<<endl;
        GuiLearner * lnr= dynamic_cast<GuiLearner*> (CentralTabWidget->currentWidget() ) ;
        if(lnr && lnr->learner)
        {
                lnr->learner->startUp();
        }
   }

}

void MainWindow::setupToolBar()
{

    QToolBar *myToolBar=new QToolBar("myToolBar",this);
    QAction *New= myToolBar->addAction(QIcon(":/res/Images/new.png"),"New");
    connect(New,SIGNAL(triggered(bool)),SLOT(ActionNewClicked() ));

    myToolBar->addAction(QIcon(":/res/Images/open.png"),"Open");
    myToolBar->addAction(QIcon(":res/Images/save.png"),"Save");
    addToolBar(myToolBar);

     myToolBar=new QToolBar("myToolBar1",this);
     QAction *Run=myToolBar->addAction(QIcon(":/res/Images/Run.png"),"Run");
     connect(Run,SIGNAL(triggered(bool)),SLOT( RunModel()  ) );

     QAction *Check=myToolBar->addAction(QIcon(":/res/Images/Check.png"),"Check");
     connect(Check,SIGNAL(triggered(bool)),SLOT(   CheckModel()  ));

     addToolBar(myToolBar);



    /*
    for (int i = 0; i < 3; ++i) {
        ToolBar *tb = new ToolBar(QString::fromLatin1("Tool Bar %1").arg(i + 1), this);
        toolBars.append(tb);
        addToolBar(tb);
    }*/

}

void MainWindow::setupMenuBar()
{
    //初始化菜单栏

    QMenu *menu = menuBar()->addMenu(tr("&File"));

    QAction *New =menu->addAction(tr("New Project"));


    connect(New,SIGNAL(triggered(bool)),this,SLOT( NewProjectCommand()));


    QAction *action = menu->addAction(tr("Save layout..."));
    connect(action, SIGNAL(triggered()), this, SLOT(saveLayout()));

    action = menu->addAction(tr("Load layout..."));
    connect(action, SIGNAL(triggered()), this, SLOT(loadLayout()));

    action = menu->addAction(tr("Switch layout direction"));
    connect(action, SIGNAL(triggered()), this, SLOT(switchLayoutDirection()));

    menu->addSeparator();

    menu->addAction(tr("&Quit"), this, SLOT(close()));

    mainWindowMenu = menuBar()->addMenu(tr("Main window"));

    action = mainWindowMenu->addAction(tr("Animated docks"));
    action->setCheckable(true);
    action->setChecked(dockOptions() & AnimatedDocks);
    connect(action, SIGNAL(toggled(bool)), this, SLOT(setDockOptions()));

    action = mainWindowMenu->addAction(tr("Allow nested docks"));
    action->setCheckable(true);
    action->setChecked(dockOptions() & AllowNestedDocks);
    connect(action, SIGNAL(toggled(bool)), this, SLOT(setDockOptions()));

    action = mainWindowMenu->addAction(tr("Allow tabbed docks"));
    action->setCheckable(true);
    action->setChecked(dockOptions() & AllowTabbedDocks);
    connect(action, SIGNAL(toggled(bool)), this, SLOT(setDockOptions()));

    action = mainWindowMenu->addAction(tr("Force tabbed docks"));
    action->setCheckable(true);
    action->setChecked(dockOptions() & ForceTabbedDocks);
    connect(action, SIGNAL(toggled(bool)), this, SLOT(setDockOptions()));

    action = mainWindowMenu->addAction(tr("Vertical tabs"));
    action->setCheckable(true);  //设置为可选中
    action->setChecked(dockOptions() & VerticalTabs);
    connect(action, SIGNAL(toggled(bool)), this, SLOT(setDockOptions()));

     mainWindowMenu->addAction(tr("Default layout"), this,SLOT(setupDefaultLayout()  )     );

    QMenu *toolBarMenu = menuBar()->addMenu(tr("Tool bars"));
    for (int i = 0; i < toolBars.count(); ++i)
        toolBarMenu->addMenu(toolBars.at(i)->menu);

    dockWidgetMenu = menuBar()->addMenu(tr("&View"));

    setMenuBarDataPreProcess();
    setMenuBarFeaturesEnginering();

    setMenuBarMachineLearning();
    QMenu *MenuHelp=menuBar()->addMenu(tr("Help(H)"));
    QAction * Action=MenuHelp->addAction(tr("About"));

}

void MainWindow::setMenuBarDataPreProcess(){

    QMenu *MenuDataPreProcess=menuBar()->addMenu(tr("Preprocess(P)"));
     QAction *Action= MenuDataPreProcess->addAction(tr("Sample and Filter"));
     Action= MenuDataPreProcess->addAction(tr("Type transformation"));
     Action= MenuDataPreProcess->addAction(tr("Split "));
     Action= MenuDataPreProcess->addAction(tr("Fill Missing value"));
     Action= MenuDataPreProcess->addAction(tr("Normalize"));
     Action= MenuDataPreProcess->addAction(tr("Standardize"));


}

void MainWindow::setMenuBarFeaturesEnginering()
{
      QMenu *MenuFeaturesEnginering=menuBar()->addMenu(tr("Features Enginering(F)"));
      QAction *Action =MenuFeaturesEnginering->addAction(tr("Feature Transformation"));
      Action =MenuFeaturesEnginering->addAction(tr("Feature Evaluation"));
      Action =MenuFeaturesEnginering->addAction(tr("Feature Selection"));
      Action =MenuFeaturesEnginering->addAction(tr("Feature Generation"));


}
void MainWindow::setMenuBarMachineLearning(){
    QMenu *MenuMachineLearning=menuBar()->addMenu(tr("Machine Learning(A)"));

    //********************************************

    QMenu *BinaryClass =MenuMachineLearning->addMenu(tr("Binary-class"));

    QAction *svmAct = BinaryClass->addAction(tr("Support Vector Machine"));
     connect(svmAct,SIGNAL(triggered(bool)),this,SLOT(setupASvmInstance() ) );

    QAction *LogisticRegAct = BinaryClass->addAction(tr("Logistic Regression"));

    //***************************************
    QAction * Action =MenuMachineLearning->addAction(tr("Multi-class"));

    Action =MenuMachineLearning->addAction(tr("Cluster"));

    Action =MenuMachineLearning->addAction(tr("Regression"));

    Action =MenuMachineLearning->addAction(tr("Relevant Recommendations"));

    Action =MenuMachineLearning->addAction(tr("Evaluation "));

     Action =MenuMachineLearning->addAction(tr("Prediction "));

}
void  MainWindow:: NewProjectCommand()
{
     ProjectTreeViewer->addProject("Test");

}
 void MainWindow:: CheckModel()
 {
     //得到当前活动的Tab
         QWidget * curWgt=   CentralTabWidget->currentWidget();

         for(auto  i= LearnerList->begin()   ;i !=LearnerList->end();++i   )
         {
                if(  (*i) ->Ui == curWgt   )
                {
                    GuiLearner *guilnr= (  (GuiLearner *) ( (*i) ->Ui)  );
                    Learner * lnr=guilnr->learner ;
                    if(lnr){

                            guilnr->updateParamFromUI();
                            lnr->setTrainingData();
                    }
                    break;
                }
         }

 }

void MainWindow::setDockOptions()
{
    DockOptions opts;
    QList<QAction*> actions = mainWindowMenu->actions();

    if (actions.at(0)->isChecked())
        opts |= AnimatedDocks;
    if (actions.at(1)->isChecked())
        opts |= AllowNestedDocks;
    if (actions.at(2)->isChecked())
        opts |= AllowTabbedDocks;
    if (actions.at(3)->isChecked())
        opts |= ForceTabbedDocks;
    if (actions.at(4)->isChecked())
        opts |= VerticalTabs;

    QMainWindow::setDockOptions(opts);
}

void MainWindow::saveLayout()
{
    QString fileName
        = QFileDialog::getSaveFileName(this, tr("Save layout"));
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly)) {
        QString msg = tr("Failed to open %1\n%2")
                        .arg(fileName)
                        .arg(file.errorString());
        QMessageBox::warning(this, tr("Error"), msg);
        return;
    }

    QByteArray geo_data = saveGeometry();
    QByteArray layout_data = saveState();

    bool ok = file.putChar((uchar)geo_data.size());
    if (ok)
        ok = file.write(geo_data) == geo_data.size();
    if (ok)
        ok = file.write(layout_data) == layout_data.size();

    if (!ok) {
        QString msg = tr("Error writing to %1\n%2")
                        .arg(fileName)
                        .arg(file.errorString());
        QMessageBox::warning(this, tr("Error"), msg);
        return;
    }
}

void MainWindow::loadLayout()
{
    QString fileName
        = QFileDialog::getOpenFileName(this, tr("Load layout"));
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
        QString msg = tr("Failed to open %1\n%2")
                        .arg(fileName)
                        .arg(file.errorString());
        QMessageBox::warning(this, tr("Error"), msg);
        return;
    }

    uchar geo_size;
    QByteArray geo_data;
    QByteArray layout_data;

    bool ok = file.getChar((char*)&geo_size);
    if (ok) {
        geo_data = file.read(geo_size);
        ok = geo_data.size() == geo_size;
    }
    if (ok) {
        layout_data = file.readAll();
        ok = layout_data.size() > 0;
    }

    if (ok)
        ok = restoreGeometry(geo_data);
    if (ok)
        ok = restoreState(layout_data);

    if (!ok) {
        QString msg = tr("Error reading %1")
                        .arg(fileName);
        QMessageBox::warning(this, tr("Error"), msg);
        return;
    }
}

QAction *addAction(QMenu *menu, const QString &text, QActionGroup *group, QSignalMapper *mapper,
                    int id)
{
    bool first = group->actions().isEmpty();
    QAction *result = menu->addAction(text);
    result->setCheckable(true);
    result->setChecked(first);
    group->addAction(result);
    QObject::connect(result, SIGNAL(triggered()), mapper, SLOT(map()));
    mapper->setMapping(result, id);
    return result;
}

void MainWindow::setupDockWidgets(const QMap<QString, QSize> &customSizeHints)
{
    qRegisterMetaType<QDockWidget::DockWidgetFeatures>();

    mapper = new QSignalMapper(this);
    connect(mapper, SIGNAL(mapped(int)), this, SLOT(setCorner(int)));

    QMenu *corner_menu = dockWidgetMenu->addMenu(tr("Top left corner"));
    QActionGroup *group = new QActionGroup(this);
    group->setExclusive(true);

    ::addAction(corner_menu, tr("Top dock area"), group, mapper, 0);
    ::addAction(corner_menu, tr("Left dock area"), group, mapper, 1);

    corner_menu = dockWidgetMenu->addMenu(tr("Top right corner"));
    group = new QActionGroup(this);
    group->setExclusive(true);
    ::addAction(corner_menu, tr("Top dock area"), group, mapper, 2);
    ::addAction(corner_menu, tr("Right dock area"), group, mapper, 3);

    corner_menu = dockWidgetMenu->addMenu(tr("Bottom left corner"));
    group = new QActionGroup(this);
    group->setExclusive(true);
    ::addAction(corner_menu, tr("Bottom dock area"), group, mapper, 4);
    ::addAction(corner_menu, tr("Left dock area"), group, mapper, 5);

    corner_menu = dockWidgetMenu->addMenu(tr("Bottom right corner"));
    group = new QActionGroup(this);
    group->setExclusive(true);
    ::addAction(corner_menu, tr("Bottom dock area"), group, mapper, 6);
    ::addAction(corner_menu, tr("Right dock area"), group, mapper, 7);

    dockWidgetMenu->addSeparator();

    static const struct Set {
        const char * name;
        uint flags;
        Qt::DockWidgetArea area;
    } sets [] = {
#ifndef Q_OS_MAC
         { "Black", Qt::Drawer, Qt::LeftDockWidgetArea }
#else
        { "Black", Qt::Drawer, Qt::LeftDockWidgetArea },
#endif
    };
    const int setCount = sizeof(sets) / sizeof(Set);

    for (int i = 0; i < 0; ++i) {
        ColorSwatch *swatch = new ColorSwatch(tr(sets[i].name), this, Qt::WindowFlags(sets[i].flags));
        QString name = QString::fromLatin1(sets[i].name);

         swatch->setWindowIcon(QIcon(QPixmap(":/res/qt.png")));
        if (qstrcmp(sets[i].name, sets[i].name) == 0) {

            BlueTitleBar *titlebar = new BlueTitleBar(swatch, name);
            swatch->setTitleBarWidget(titlebar);
            connect(swatch, SIGNAL(topLevelChanged(bool)), titlebar, SLOT(updateMask()));
            connect(swatch, SIGNAL(featuresChanged(QDockWidget::DockWidgetFeatures)), titlebar, SLOT(updateMask()), Qt::QueuedConnection);
        }

         if (customSizeHints.contains(name))
            swatch->setCustomSizeHint(customSizeHints.value(name));

         addDockWidget(sets[i].area, swatch);
         dockWidgetMenu->addMenu(swatch->menu);
    }
    QWidget *centralWin=  takeCentralWidget();
    if(centralWin) delete centralWin;//删掉中心widget
     CreateCentralDockWidget();

     CreateProjectDockWidget();
     CreateMessagesDockWidget();
      CreateParameterListDockWidget();
      CreateProgressDockWidget();

      setDockNestingEnabled(true);
      DefaultLayout();//设置默认布局

     createDockWidgetAction = new QAction(tr("Add dock widget..."), this);
     connect(createDockWidgetAction, SIGNAL(triggered()), this, SLOT(createDockWidget()));
     destroyDockWidgetMenu = new QMenu(tr("Destroy dock widget"), this);
     destroyDockWidgetMenu->setEnabled(false);
     connect(destroyDockWidgetMenu, SIGNAL(triggered(QAction*)), this, SLOT(destroyDockWidget(QAction*)));

    dockWidgetMenu->addSeparator();
    dockWidgetMenu->addAction(createDockWidgetAction);
    dockWidgetMenu->addMenu(destroyDockWidgetMenu);
}
void MainWindow::setupDefaultLayout() {
             DefaultLayout();
}

void MainWindow::DefaultLayout(){
     //设置DockWidget 的布局

     splitDockWidget(ProjectDockWidget,CentralDockWidget, Qt::Horizontal);
     splitDockWidget(CentralDockWidget,ParameterListDockWidget,Qt::Vertical);
     splitDockWidget(ParameterListDockWidget,MessagesDockWidget,Qt::Horizontal);
     splitDockWidget(ParameterListDockWidget,MessagesDockWidget,Qt::Horizontal);
     splitDockWidget(MessagesDockWidget,ProgressDockWidget,Qt::Horizontal);

}
void MainWindow::  currrntTabChanged(int currentTabIndex)
{



}
void MainWindow::CreateCentralDockWidget(){
    CentralTabWidget =new CentralShowTabWgt();//CentralTabWidget 中填内容由BLL 层控制

    connect(CentralTabWidget,SIGNAL(currentChanged(int)),this,SLOT( currrntTabChanged(int )   ) );
    CentralDockWidget=new ColorSwatch("",this,0);
    BlueTitleBar *titleBar=new BlueTitleBar(CentralDockWidget,false);


    CentralDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);

    CentralDockWidget->setTitleBarWidget(titleBar);




    CentralDockWidget->setWidget(CentralTabWidget);
    //CentralDockWidget->setFeatures( QDockWidget::NoDockWidgetFeatures);


    addDockWidget(Qt::LeftDockWidgetArea,CentralDockWidget);


}
void MainWindow:: CreateProjectDockWidget(){

     ProjectDockWidget=new ColorSwatch( "Project",this,0);
     //ProjectDockWidget->setStyleSheet(QString::fromUtf8("border:2px solid red"));

     BlueTitleBar *titleBar=new BlueTitleBar(ProjectDockWidget, QString("Project")  );//窗口头顶的样式

     ProjectDockWidget->setTitleBarWidget(titleBar );//设置到ProjectDockWidget头上
     //////给窗口头关联消息
     connect(ProjectDockWidget,SIGNAL(topLevelChanged(bool)) ,titleBar,SLOT(updateMask())    ); //当它的float属性改变时，信号发送，
     connect(ProjectDockWidget,SIGNAL(featuresChanged(QDockWidget::DockWidgetFeatures)),titleBar,SLOT( updateMask()) ,Qt::QueuedConnection);

     ///******初始化导航树**************
      ProjectTreeViewer  =new BLLProjectsManagerTree( ProjectDockWidget);

      ProjectDockWidget->setWidget(ProjectTreeViewer);



     //************把ProjectDockWidget添加到主窗口中**************
      addDockWidget(Qt::LeftDockWidgetArea,ProjectDockWidget);

      dockWidgetMenu->addMenu(ProjectDockWidget->menu );

}


 void MainWindow::CreateMessagesDockWidget(){
        MessagesDockWidget =new ColorSwatch("Messages",this,0);
        MessagesDockWidget->setMaximumHeight(300);
         MessagesDockWidget->adjustSize();

        BlueTitleBar *titleBar=new BlueTitleBar(MessagesDockWidget,QString("Messages") );

        MessagesDockWidget->setTitleBarWidget(titleBar);

        connect(MessagesDockWidget,
                          SIGNAL(topLevelChanged(bool)),
                          titleBar,
                         SLOT(updateMask())
                );
        connect(MessagesDockWidget,
                          SIGNAL(featuresChanged(QDockWidget::DockWidgetFeatures)),
                          titleBar,
                          SLOT(updateMask())
                );
        /////////////////////////////////////////////////////////////////////////////
         messagesManager = new BLLMesgManager(0,"start message");


         MessagesDockWidget->setWidget(messagesManager);

        ///////////////////////////////////////////////////////////////////////////////////
       addDockWidget(Qt::BottomDockWidgetArea,MessagesDockWidget);
        dockWidgetMenu->addMenu(MessagesDockWidget->menu);


 }
 void MainWindow::CreateParameterListDockWidget()
 {
          ParameterListDockWidget=new ColorSwatch("Parameter List",this,0);
          BlueTitleBar *titleBar=new BlueTitleBar( ParameterListDockWidget,QString("ParameterList")  );
          ParameterListDockWidget->setTitleBarWidget(titleBar);

          connect(ParameterListDockWidget,
                            SIGNAL(topLevelChanged(bool)),
                             titleBar,
                             SLOT(updateMask())
                  );
          connect(ParameterListDockWidget,  //sender
                      SIGNAL(featuresChanged(QDockWidget::DockWidgetFeatures)),//signal
                       titleBar, //recevier
                       SLOT(updateMask()) // handler
                  );


          //*********可删除（与主框架无关）**************
          BLLParameterTab *parameterTable=new BLLParameterTab(5,5);
          ParameterListDockWidget->setWidget(parameterTable);

          addDockWidget(Qt::BottomDockWidgetArea,ParameterListDockWidget);
          dockWidgetMenu->addMenu(ParameterListDockWidget->menu);
          //***********************


 }
 void MainWindow::CreateProgressDockWidget(){
                 ProgressDockWidget =new ColorSwatch("Progress",this,0);
                 BlueTitleBar *titleBar=new BlueTitleBar(ProgressDockWidget,QString("Progress"));
                 ProgressDockWidget->setTitleBarWidget(titleBar);

                 connect(ProgressDockWidget,
                                 SIGNAL(topLevelChanged(bool)),
                                 titleBar,
                                 SLOT(updateMask())
                         );
                 connect(ProgressDockWidget,
                                  SIGNAL(featuresChanged(QDockWidget::DockWidgetFeatures)),
                                  titleBar,
                                  SLOT(updateMask())
                                );
                 //*****************

                 BLLMesgManager  *curProjectLabel=new BLLMesgManager(0,"Project1");

                 progressWgtManager=new BLLProgressWgt();

                 ProgressDockWidget->setWidget(progressWgtManager);

                 //*******************
                 addDockWidget(Qt::BottomDockWidgetArea,ProgressDockWidget);
                 dockWidgetMenu->addMenu(ProgressDockWidget->menu);

 }

void MainWindow::setCorner(int id)
{
    switch (id) {
        case 0:
            QMainWindow::setCorner(Qt::TopLeftCorner, Qt::TopDockWidgetArea);
            break;
        case 1:
            QMainWindow::setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
            break;
        case 2:
            QMainWindow::setCorner(Qt::TopRightCorner, Qt::TopDockWidgetArea);
            break;
        case 3:
            QMainWindow::setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
            break;
        case 4:
            QMainWindow::setCorner(Qt::BottomLeftCorner, Qt::BottomDockWidgetArea);
            break;
        case 5:
            QMainWindow::setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
            break;
        case 6:
            QMainWindow::setCorner(Qt::BottomRightCorner, Qt::BottomDockWidgetArea);
            break;
        case 7:
            QMainWindow::setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);
            break;
    }
}

void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
}

void MainWindow::switchLayoutDirection()
{
    if (layoutDirection() == Qt::LeftToRight)
        qApp->setLayoutDirection(Qt::RightToLeft);
    else
        qApp->setLayoutDirection(Qt::LeftToRight);
}

class CreateDockWidgetDialog : public QDialog
{
public:
    CreateDockWidgetDialog(QWidget *parent = 0);

    QString objectName() const;
    Qt::DockWidgetArea location() const;

private:
    QLineEdit *m_objectName;
    QComboBox *m_location;
};

CreateDockWidgetDialog::CreateDockWidgetDialog(QWidget *parent)
    : QDialog(parent)
{
    QGridLayout *layout = new QGridLayout(this);

    layout->addWidget(new QLabel(tr("Object name:")), 0, 0);
    m_objectName = new QLineEdit;
    layout->addWidget(m_objectName, 0, 1);

    layout->addWidget(new QLabel(tr("Location:")), 1, 0);
    m_location = new QComboBox;
    m_location->setEditable(false);
    m_location->addItem(tr("Top"));
    m_location->addItem(tr("Left"));
    m_location->addItem(tr("Right"));
    m_location->addItem(tr("Bottom"));
    m_location->addItem(tr("Restore"));
    layout->addWidget(m_location, 1, 1);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    layout->addLayout(buttonLayout, 2, 0, 1, 2);
    buttonLayout->addStretch();

    QPushButton *cancelButton = new QPushButton(tr("Cancel"));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    buttonLayout->addWidget(cancelButton);
    QPushButton *okButton = new QPushButton(tr("Ok"));
    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    buttonLayout->addWidget(okButton);

    okButton->setDefault(true);
}

QString CreateDockWidgetDialog::objectName() const
{
    return m_objectName->text();
}

Qt::DockWidgetArea CreateDockWidgetDialog::location() const
{
    switch (m_location->currentIndex()) {
        case 0: return Qt::TopDockWidgetArea;
        case 1: return Qt::LeftDockWidgetArea;
        case 2: return Qt::RightDockWidgetArea;
        case 3: return Qt::BottomDockWidgetArea;
        default:
            break;
    }
    return Qt::NoDockWidgetArea;
}

void MainWindow::createDockWidget()
{
    CreateDockWidgetDialog dialog(this);
    int ret = dialog.exec();
    if (ret == QDialog::Rejected)
        return;

    QDockWidget *dw = new QDockWidget;
    dw->setObjectName(dialog.objectName());
    dw->setWindowTitle(dialog.objectName());
    dw->setWidget(new QTextEdit);

    Qt::DockWidgetArea area = dialog.location();
    switch (area) {
        case Qt::LeftDockWidgetArea:
        case Qt::RightDockWidgetArea:
        case Qt::TopDockWidgetArea:
        case Qt::BottomDockWidgetArea:
            addDockWidget(area, dw);
            break;
        default:
            if (!restoreDockWidget(dw)) {
                QMessageBox::warning(this, QString(), tr("Failed to restore dock widget"));
                delete dw;
                return;
            }
            break;
    }

    extraDockWidgets.append(dw);
    destroyDockWidgetMenu->setEnabled(true);
    destroyDockWidgetMenu->addAction(new QAction(dialog.objectName(), this));
}

void MainWindow::destroyDockWidget(QAction *action)
{
    int index = destroyDockWidgetMenu->actions().indexOf(action);
    delete extraDockWidgets.takeAt(index);
    destroyDockWidgetMenu->removeAction(action);
    action->deleteLater();

    if (destroyDockWidgetMenu->isEmpty())
        destroyDockWidgetMenu->setEnabled(false);
}


