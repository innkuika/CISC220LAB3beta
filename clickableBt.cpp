#include "clickableBt.h"


 CClickableLabel::CClickableLabel(QString text, int x, int y, QWidget *parent): QLabel(text, parent)
 {
     this->text = text;
     this->x = x;
     this->y = y;
 }
