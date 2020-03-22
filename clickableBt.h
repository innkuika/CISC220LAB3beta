#include <QLabel>


class CClickableLabel : public QLabel
{
   Q_OBJECT
public:
    CClickableLabel(QString text, QWidget *parent = 0);
   ~CClickableLabel() {}

signals:
   void clicked();

public:
   QString text;
public:
   void printBoard2();

protected:
   void mousePressEvent(QMouseEvent *event) { emit clicked(); }
};

