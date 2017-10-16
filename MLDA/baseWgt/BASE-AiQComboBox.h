#ifndef BASEAIQCOMBOBOX_H
#define BASEAIQCOMBOBOX_H

#include<QWidget>
#include<QComboBox>
#include <QEvent>
#include "Common.h"


class AiQComboBox : public QComboBox
{

    Q_OBJECT
public:
    AiQComboBox();
    void wheelEvent(QWheelEvent *e);



};

#endif // BASEAIQCOMBOBOX_H
