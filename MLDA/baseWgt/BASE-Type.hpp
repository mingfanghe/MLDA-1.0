#ifndef BASETYPE_H
#define BASETYPE_H
#include<QWidget>
#include<qnamespace.h>
#include <Qt>
#include <QtCore/qobject.h>


//这个文件要注意重复包含的问题
enum STATUS{Ok,Error,Warning,Fail};
enum TAB_TYPE{TAB_TEXT,TAB_FIGURE,TAB_GUI_LEARNER,TAB_OTHERS};

class TabData
{
public:
    QWidget *wgt;             //windows
    QString ID;                  // 标识符 ID
    QString Label;             //标签
    TAB_TYPE tabType;   // 类型

    TabData(QWidget* w=0,QString id="",QString label=""):wgt(w),ID(id),Label(label){}
    TabData(QWidget* w=0,TAB_TYPE type=TAB_OTHERS,QString id="",QString label=""):
        wgt(w),ID(id),Label(label),tabType(type) {}
    void freeWgt(){delete wgt;}

};

//////////////////////////////////////////////////////////////////////////////////////////
/// \brief  自定义类型作为
/// 信号槽的参数时必须使用 qRegisterMetaType<AiMsg> ("AiMsg");
/// 注册
/// 如果定义的槽函数未触发，检查一下emit,connect 等是否在对象
/// 生成之前被执行了
///
//////////////////////////////////////////////////////////////////////////////////////////
enum MsgType{MSG_TYPE_TEXT,MSG_TYPE_NUM,};
class AiMsg
{
public:
    AiMsg(){}
    AiMsg(STATUS s,MsgType t,int digit,QString text)
    {
        Status=s;
        Type=t;
        Num=digit;
        Content.append(text);
    }
    void appendText(QString text)
    {
        Content.append(text);
    }
    Qt::HANDLE senderId;
    MsgType Type;
    STATUS Status;
    int Num;
    QStringList Content;

};

#endif // BASETYPE_H
