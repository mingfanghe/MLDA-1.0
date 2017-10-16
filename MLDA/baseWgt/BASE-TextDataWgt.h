#ifndef BASETEXTDATAWGT_H
#define BASETEXTDATAWGT_H

#include <QMainWindow>
#include "QSci/qsciscintilla.h"
#include "QSci/qscilexer.h"
#include <QThread>
#include <iostream>
using namespace std;

class TextDataWgt : public QsciScintilla,QThread
{
public:
    explicit TextDataWgt();

    void  wheelEvent(QWheelEvent *event);
    void  keyPressEvent(QKeyEvent *event);
    void  keyReleaseEvent(QKeyEvent *event);
signals:
public slots:

private:
     int PressdKey;
};

#endif // BASETEXTDATAWGT_H
