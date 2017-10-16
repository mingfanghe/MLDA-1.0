#ifndef BASEDATATABLEWGT_H
#define BASEDATATABLEWGT_H

#include <QTableWidget>
#include<QTextBrowser>
#include<QTextCodec>
#include <QStyle>
class DataTableWgt : public QTableWidget
{
    //提供一个显示数据的表格类，其对象可放在主框架的 CentralShowTabWgt 中显示
    Q_OBJECT

public:
     DataTableWgt(){}
     DataTableWgt(int row,int col);
    void setCellContent(int row,int col,QString content);
    void setBorderVisiable(bool visiable=true)
    {
             if(!visiable) this->setStyleSheet("border:none;");
    }

};

#endif // BASEDATATABLEWGT_H
