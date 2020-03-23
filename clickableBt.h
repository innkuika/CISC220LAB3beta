#include <QLabel>
#include "QMessageBox"

class CClickableLabel : public QLabel
{
   Q_OBJECT
public:
    CClickableLabel(QString text, int x, int y, QWidget *parent = 0);
   ~CClickableLabel() {}

public:
    int x;

public:
    int y;

signals:
   void clicked();

public:
   QString text;
public:
   void printBoard2();

protected:
   void mousePressEvent(QMouseEvent *event) { emit clicked();}
};

