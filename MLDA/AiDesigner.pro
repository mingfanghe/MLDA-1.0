TEMPLATE = app
QT += widgets printsupport
DEFINES += QT_DEPRECATED_WARNINGS
###############################################################
ROOT =I:/Projects/Qt/AiDesigner

###################   配置XGBoost  ###############################
#LIBS += -L$${ROOT}/XGBoost/Libs -lxgboost
#LIBS += -L$${ROOT}/XGBoost/Libs -lrabit
#LIBS += -L$${ROOT}/XGBoost/Libs -ldmlccore
#INCLUDEPATH += $${ROOT}/XGBoost/includes/xgboost
#QMAKE_CXXFLAGS += /openmp

####################配置QScintilla  #####################################

LIBS += -L$${ROOT}/GuiLibs/QScintilla -lqscintilla2_qt5d
INCLUDEPATH += $${ROOT}/GuiLibs/QScintilla

#############################################################

HEADERS += \
    Gui-colorswatch.h \
    Gui-mainwindow.h \
    Gui-toolbar.h \
    BLL-ParameterTab.h \
    BLL-MesgManager.h \
    BLL-ProjectsManagerTree.h \
    BLL-CentralShowTabWgt.h \
    BLL-CentralShowTabWgt.h \
    BLL-MesgManager.h \
    BLL-ParameterTab.h \
    BLL-ProjectsManagerTree.h \
    Gui-colorswatch.h \
    Gui-mainwindow.h \
    Gui-toolbar.h \
    baseWgt/BASE-DataTableWgt.h \
    baseWgt/BASE-Plot.h \
    baseWgt/BASE-QCustomPlot.h \
    baseWgt/BASE-TextDataWgt.h \
    baseWgt/BASE-Type.hpp \
    baseWgt/BASE-Util.hpp\
    CplusHeader.h \
    Common.h \
    GlobalVars.h \
    BLL-ProgressWgt.h \
    svm/AiSvm.h \
    svm/BLL_SVM_UI.h \
    baseWgt/BASE-zoomAbleTableWgt.h \
    svm/alg_svm.h \
    baseWgt/BASE-Gadget.h \
    baseWgt/BASE-AiQComboBox.h \
    baseWgt/BASE-AiQComboBox.h \
    baseWgt/BASE-DataTableWgt.h \
    baseWgt/BASE-Gadget.h \
    baseWgt/BASE-Plot.h \
    baseWgt/BASE-QCustomPlot.h \
    baseWgt/BASE-TextDataWgt.h \
    baseWgt/BASE-Type.hpp \
    baseWgt/BASE-Util.hpp \
    baseWgt/BASE-zoomAbleTableWgt.h \
    svm/AiSvm.h \
    svm/alg_svm.h \
    svm/BLL_SVM_UI.h \
    BLL-CentralShowTabWgt.h \
    BLL-MesgManager.h \
    BLL-ParameterTab.h \
    BLL-ProgressWgt.h \
    BLL-ProjectsManagerTree.h \
    Common.h \
    cplusheader.h \
    GlobalVars.h \
    Gui-colorswatch.h \
    Gui-mainwindow.h \
    Gui-toolbar.h \
    ModelEvalution/ModelEvaluate1.h \
    ModelEvalution/alg-modelevaluate.h \
    ModelEvalution/BLL-ModelEvaluator_UI.h \
    Solvers/Learner.h \
    #XGBoost/xgboosttest.h

SOURCES += \
    main.cpp \
    Gui-colorswatch.cpp \
    Gui-mainwindow.cpp \
    Gui-toolbar.cpp \
    BLL-ParameterTab.cpp \
    BLL-MesgManager.cpp \
    BLL-ProjectsManagerTree.cpp \
    BLL-CentralShowTabWgt.cpp \
    BLL-CentralShowTabWgt.cpp \
    BLL-MesgManager.cpp \
    BLL-ParameterTab.cpp \
    BLL-ProjectsManagerTree.cpp \
    Gui-colorswatch.cpp \
    Gui-mainwindow.cpp \
    Gui-toolbar.cpp \
    main.cpp \
    baseWgt/BASE-DataTableWgt.cpp \
    baseWgt/BASE-Plot.cpp \
    baseWgt/BASE-QCustomPlot.cpp \
    baseWgt/BASE-TextDataWgt.cpp \
    Common.cpp \
    GlobalVars.cpp \
    BLL-ProgressWgt.cpp \
    svm/AiSvm.cpp \
    svm/BLL_SVM_UI.cpp \
    baseWgt/BASE-zoomAbleTableWgt.cpp \
    svm/alg_svm.cpp \
    baseWgt/BASE-Gadget.cpp \
    baseWgt/BASE-AiQComboBox.cpp \
    baseWgt/BASE-AiQComboBox.cpp \
    baseWgt/BASE-DataTableWgt.cpp \
    baseWgt/BASE-Gadget.cpp \
    baseWgt/BASE-Plot.cpp \
    baseWgt/BASE-QCustomPlot.cpp \
    baseWgt/BASE-TextDataWgt.cpp \
    baseWgt/BASE-zoomAbleTableWgt.cpp \
    svm/aisvm.cpp \
    svm/alg_svm.cpp \
    svm/BLL_SVM_UI.cpp \
    BLL-CentralShowTabWgt.cpp \
    BLL-MesgManager.cpp \
    BLL-ParameterTab.cpp \
    BLL-ProgressWgt.cpp \
    BLL-ProjectsManagerTree.cpp \
    common.cpp \
    GlobalVars.cpp \
    Gui-colorswatch.cpp \
    Gui-mainwindow.cpp \
    Gui-toolbar.cpp \
    main.cpp \
    ModelEvalution/alg-modelevaluate.cpp \
    ModelEvalution/BLL-ModelEvaluator_UI.cpp \
    Solvers/LearnerUI.cpp \
   # XGBoost/xgboostTest.cpp

build_all:!build_pass {
    CONFIG -= build_all
    CONFIG += release
}

RESOURCES += mainwindow.qrc

# install
#target.path = $$[QT_INSTALL_EXAMPLES]/widgets/mainwindows/mainwindow

target.path =$$[ProjectDir]/mainwindows
INSTALLS += target

FORMS +=


