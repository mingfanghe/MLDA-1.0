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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include"Gui-colorswatch.h"
#include"BLL-ProjectsManagerTree.h"
#include"BLL-MesgManager.h"
#include "BLL-ParameterTab.h"
#include "BLL-CentralShowTabWgt.h"
#include "BLL-ProgressWgt.h"

#include "Common.h"
#include<QFileSystemModel>
#include <QTreeWidget>
#include <QLabel>
#include <QIcon>
#include <QList>

#include "svm/AiSvm.h"
#include "svm/BLL_SVM_UI.h"

class ToolBar;
QT_FORWARD_DECLARE_CLASS(QMenu)
QT_FORWARD_DECLARE_CLASS(QSignalMapper)

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QTextEdit *center;
    QList<ToolBar*> toolBars;
    QMenu *dockWidgetMenu;
    QMenu *mainWindowMenu;
    QSignalMapper *mapper;
    QList<QDockWidget*> extraDockWidgets;
    QAction *createDockWidgetAction;
    QMenu *destroyDockWidgetMenu;

    QAction *Run,*Check;
    ///////////////////////////////////////////////////////////////////////////
    // 项目管理树
    ColorSwatch * ProjectDockWidget;
    BLLProjectsManagerTree * ProjectTreeViewer;
  // 消息显示窗口
    ColorSwatch * MessagesDockWidget;
    BLLMesgManager *messagesManager;
   //
    ColorSwatch * ParameterListDockWidget;

    // 进度条管理窗口
    ColorSwatch * ProgressDockWidget;
    BLLProgressWgt *progressWgtManager;

    // central window
    QDockWidget * CentralDockWidget;
    CentralShowTabWgt *CentralTabWidget;

    QList<LearnerUI* >  *LearnerList;   //用以管理学习器,使用链表管理


public:
    MainWindow(const QMap<QString, QSize> &customSizeHints,
                QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~MainWindow();
protected:
    void showEvent(QShowEvent *event);

public slots:
    void ActionNewClicked();
    void actionTriggered(QAction *action);
    void saveLayout();
    void loadLayout();
    void setCorner(int id);
    void switchLayoutDirection();
    void setDockOptions();
    void createDockWidget();
    void destroyDockWidget(QAction *action);

    void currrntTabChanged(int currentTabIndex);
    void setupDefaultLayout() ;
    void NewProjectCommand();
    void CheckModel()  ;
   void  RunModel();
       void setupASvmInstance();
private:
    void setupToolBar();
    void setupMenuBar();

    void setMenuBarDataPreProcess();
    void setMenuBarMachineLearning();
    void setMenuBarFeaturesEnginering();

    void setupDockWidgets(const QMap<QString, QSize> &customSizeHints);
    //////////////////////////////////////////////////////////

    void CreateCentralDockWidget();
    void CreateProjectDockWidget();
     void CreateMessagesDockWidget();
     void CreateParameterListDockWidget();
     void CreateProgressDockWidget();
     void DefaultLayout();
     ////////////////////////////////////////////////////////////


};


#endif
