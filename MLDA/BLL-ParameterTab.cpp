#include "BLL-ParameterTab.h"

BLLParameterTab::BLLParameterTab(int row,int col)
{

    setRowCount(row);
    setColumnCount(col);
    setHorizontalHeaderLabels(QStringList()<<"Name"<<"Expression"<<"Value"<<"Description"<<"Type");

}
