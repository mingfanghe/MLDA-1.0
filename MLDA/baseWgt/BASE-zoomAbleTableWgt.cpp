#include "BASE-zoomAbleTableWgt.h"

zoomAbleTableWgt::zoomAbleTableWgt(QWidget *parent=nullptr):QGraphicsView(parent)
{
    sence=new QGraphicsScene(this);

    sence->setSceneRect(this->rect());
    //setViewportMargins(100,0,0,100);

    scale(2,2);

    Table=new QTableWidget();

    Table->setRowCount(20);
    Table->setColumnCount(30);

    Table->setSizeAdjustPolicy(SizeAdjustPolicy::AdjustToContents);
     proxyWgt= sence->addWidget(Table) ;


    proxyWgt->moveBy(-300,-100 ) ;

    this->setScene(sence);



}
 void zoomAbleTableWgt:: wheelEvent(QWheelEvent* event)
 {
     setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
         // QPoint p=pos();
         // cout<<p.x()<<","<<p.y()<<endl;

         // Scale the view / do the zoom
         double scaleFactor = 1.15;
         if(event->delta() > 0) {
             // Zoom in
             scale(scaleFactor, scaleFactor);
         } else {
             // Zooming out
             scale(1.0 / scaleFactor, 1.0 / scaleFactor);
         }
          // if (proxyWgt) proxyWgt->moveBy(-20,-100 ) ;

         // Don't call superclass handler here
         // as wheel is normally used for moving scrollbars

 }
