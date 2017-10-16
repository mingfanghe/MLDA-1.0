#include "BASE-AiQComboBox.h"

AiQComboBox::AiQComboBox()
{
           setStyleSheet("QComboBox {\
                         border: 1px solid gray;\
                         border-radius: 5px;\
                         padding: 1px 18px 1px 3px;\
                         min-width: 6em;\
                         height:20px\
                     }\
                     QComboBox:!editable:on, QComboBox::drop-down:editable:on {\
                         background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\
                                                     stop: 0 #D3D3D3, stop: 0.4 #D8D8D8,\
                                                     stop: 0.5 #DDDDDD, stop: 1.0 #E1E1E1);\
                     }\
                     QComboBox:on { /* shift the text when the popup opens */\
                         padding-top: 3px;\
                         padding-left: 4px;\
                     }\
                     QComboBox::drop-down {\
                         subcontrol-origin: padding;\
                         subcontrol-position: top right;\
                         width: 22px;\
                         border-left-width: 1px;\
                         border-left-color: darkgray;\
                         border-left-style: solid; /* just a single line */   \
                         border-top-right-radius: 3px; /* same radius as the QComboBox */  \
                         border-bottom-right-radius: 3px;\
                     }\
                     QComboBox::down-arrow {\
                         image: url(:/res/Images/DropArrow1.png);\
                         width:17px; \
                         height:17px;\
                     }\
                     QComboBox::down-arrow:on { /* shift the arrow when popup is open */ \
                         top: 1px;\
                         left: 1px;\
                     }");

}
void AiQComboBox:: wheelEvent(QWheelEvent *e){

}


/*
                     QComboBox:!editable, QComboBox::drop-down:editable {\
                          background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\
                                                      stop: 0 #E1E1E1, stop: 0.4 #DDDDDD,\
                                                      stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);\
                     }\

QComboBox{subcontrol-origin: padding;
                      subcontrol-position: top right;
                     border-radius: 5px;
                     height: 25px;
                     font-size:17;
                     border-left-width: 1px;
                     border-left-color: darkgray;
                     border-left-style: solid;
                     border-top-right-radius: 3px;
                     border-bottom-right-radius: 3px;
                     border: 1px solid gray;
                     drop-down{
                            image:url(:/res/Images/DropArrow1.png);
                            subcontrol-origin: padding;
                            subcontrol-position: top right;
                            border-left-width: 0px;
                            border-left-color: darkgray;
                            border-left-style: solid;
                             border-top-right-radius: 3px;
                             border-bottom-right-radius: 3px;
                             width:17px;
                             height:17px;
                             background:white ; }
                   }



















*/
