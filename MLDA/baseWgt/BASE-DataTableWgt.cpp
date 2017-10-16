#include "BASE-DataTableWgt.h"

DataTableWgt::DataTableWgt(int row,int col)
{

       setWindowFlags(Qt::FramelessWindowHint);

       setRowCount(row);
       setColumnCount(col);




}
  void DataTableWgt::setCellContent(int row,int col,QString content)
  {
          QTableWidgetItem *item=new QTableWidgetItem(content) ;
          item->setFont(QFont("Times New Roman"));
          setItem(row,col,item);

   }
