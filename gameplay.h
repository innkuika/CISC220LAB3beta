#include "QMainWindow"
#include "logic.h"
#include <QPixmap>
#include "clickableBt.h"
#include "ui_gameplay.h"
#include "QtCore"
#include "QtGui"
#include "QMessageBox"

QT_BEGIN_NAMESPACE
namespace Ui { class gameplay; }
QT_END_NAMESPACE

class gameplay : public QMainWindow
{
    Q_OBJECT

public:
    GameBoard *gb;
public:
    bool getNum = false;



public:
    gameplay(QWidget *parent = nullptr);
    ~gameplay();

//public slots:
//    void on_pushButton_clicked();

public:
    void deleteIntro();

public:
    Ui::gameplay *ui;

public:
     CClickableLabel *ccl;

public:
    void setGameboard(GameBoard *gb);

public:
    void printBoard2(char arr[], int ct, int size);

public:
    void printBoard(GameBoard *game, int ct);

public:
    void setNumBt();

public:
    void emptyOneBox(QLayout* layout, bool deleteWidgets);

public:
    void emptyAllBox();

private slots:
    void on_bt_clicked();
    void on_bt_2_clicked();

public:
    void playGame(bool fp1, bool fp2, GameBoard *game, bool whoplaysfirstflag);

public:
    int play(GameBoard *game);

public:
    void startGame(GameBoard *game);

};


