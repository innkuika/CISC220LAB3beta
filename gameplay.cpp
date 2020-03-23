#include "gameplay.h"
#include <QLayout>
#include <QFormLayout>
#include <QFileDialog>
#include <QObject>


gameplay::gameplay(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gameplay)
{
    ui->setupUi(this);
    ui->horizontalLayout->setSizeConstraint(QLayout::SizeConstraint(3));
    ui->horizontalLayout_2->setSizeConstraint(QLayout::SizeConstraint(3));
    ui->horizontalLayout_3->setSizeConstraint(QLayout::SizeConstraint(3));
    ui->horizontalLayout_4->setSizeConstraint(QLayout::SizeConstraint(3));
    ui->horizontalLayout_5->setSizeConstraint(QLayout::SizeConstraint(3));
    ui->horizontalLayout_6->setSizeConstraint(QLayout::SizeConstraint(3));
    ui->horizontalLayout_7->setSizeConstraint(QLayout::SizeConstraint(3));
    ui->horizontalLayout_8->setSizeConstraint(QLayout::SizeConstraint(3));


}

gameplay::~gameplay()
{
    delete ui;
}


void gameplay::deleteIntro()
{
    delete ui->intro_lb1;
    delete ui->intro_lb2;
    delete ui->bt;
    delete ui->bt_2;
    delete ui->bt_3;
}


void gameplay::emptyOneBox(QLayout* layout, bool deleteWidgets = true)
{
    while (QLayoutItem* item = layout->takeAt(0))
    {
        if (deleteWidgets)
        {
            if (QWidget* widget = item->widget())
                widget->deleteLater();
        }
        if (QLayout* childLayout = item->layout())
            emptyOneBox(childLayout, deleteWidgets);
        delete item;
    }
}
void gameplay::emptyAllBox(){
    emptyOneBox(ui->horizontalLayout);
    emptyOneBox(ui->horizontalLayout_2);
    emptyOneBox(ui->horizontalLayout_3);
    emptyOneBox(ui->horizontalLayout_4);
    emptyOneBox(ui->horizontalLayout_5);
    emptyOneBox(ui->horizontalLayout_6);
    emptyOneBox(ui->horizontalLayout_7);
    emptyOneBox(ui->horizontalLayout_8);

}
void delay()
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 1);
}

void gameplay::labelclicked(){
    CClickableLabel* ccl = qobject_cast<CClickableLabel*>(sender());
    this->personx = ccl->x;
    this->persony = ccl->y;
    this->personMouseClicked = true;

}

void gameplay::on_bt_clicked()
{
    QMessageBox :: information(this, "title", "0 player");
    deleteIntro();

    this->gb->playerNum = 0;
    this->play(this->gb);
}


void gameplay::on_bt_2_clicked()
{
    QMessageBox :: information(this, "title", "1 player");
    deleteIntro();

    this->gb->playerNum = 1;
    this->play(this->gb);
}

void gameplay::printBoard2(char arr[], int ct, int size, int row) {
    if (ct == size) {
        return;
    } else {
       QString filename;
        if(arr[ct] == '-')filename = ":/bgb/bgb.png";
        else if(arr[ct] == 'O')filename =  ":/bgo/bgo.png";
        else if(arr[ct] == 'X') filename =  ":/bgx/bgx.png";

        CClickableLabel *ccl =  new CClickableLabel(filename,row,ct,this);
        connect(ccl , SIGNAL(clicked()), this, SLOT(labelclicked()));
        QImage image;
        image.load(filename);
        if(ct == 0)
        ui->horizontalLayout->addWidget(ccl);
        if(ct == 1)
        ui->horizontalLayout_2->addWidget(ccl);
        if(ct == 2)
        ui->horizontalLayout_3->addWidget(ccl);
        if(ct == 3)
        ui->horizontalLayout_4->addWidget(ccl);
        if(ct == 4)
        ui->horizontalLayout_5->addWidget(ccl);
        if(ct == 5)
        ui->horizontalLayout_6->addWidget(ccl);
        if(ct == 6)
        ui->horizontalLayout_7->addWidget(ccl);
        if(ct == 7)
        ui->horizontalLayout_8->addWidget(ccl);

        ccl->setPixmap(QPixmap::fromImage(image));
        ccl->show();
        return printBoard2(arr, ct += 1, size, row);
    }

}

void gameplay::printBoard(GameBoard *game, int ct) {
    if (ct == game->size) {
        return;
    } else {
        printBoard2(game->board[ct], 0, game->size, ct);
        return printBoard(game, ct += 1);
    }
}


bool gameplay::placepieceperson(GameBoard *game) {
    int dash = countSquare(game, '-', game->size, 0, 0);
    if (dash == 0) {
        return false;
    }
    int x = 0;
    int y = 0;
    delay();

    while(!this->personMouseClicked){
        QApplication::processEvents();

    }

    x = this->personx;
    y = this->persony;

    //reset temp var to initial condition
    this->personMouseClicked = false;
    this->personx = 0;
    this->persony = 0;



//    cout << game->p << " Enter the x coordinate: " << endl;
//    cin >> x;
//    cout << game->p << " Enter the y coordinate: " << endl;
//    cin >> y;

    if (x < 0 || x >= game->size || y < 0 || y >= game->size
            || game->board[x][y] != '-') {
        cout << game->p << " forfeits turn" << endl;
        return false;
    }
    int num = flipPieceNum(game, x, y, true);

    if (num == 0) {
        cout << game->p << " forfeits turn" << endl;
        return false;
    } else {

        return true;
    }

}

int gameplay::play(GameBoard *game) {

    srand(time(NULL));
    int size = 0;
    getSize(size); // gets the size for the game board.  Note we only do this once for this game.
    game->size = size;  //sets the gameboard's size
    game->totalct = 4;  // the 4 middle squares are taken
    cout << "Size is " << game->size << endl;
    makeBoard(game, 0, true);
    this->printBoard(game, 0);
    startGame(game);
    return 0;
}

void gameplay::startGame(GameBoard *game) {

    int numplayers = game->playerNum;
    if (numplayers == 0) {
        playGame(false, false, game, true);

    } else if (numplayers == 1) {
        bool whoplaysfirstflag;
        rand() % 2 == 0 ? whoplaysfirstflag = true : whoplaysfirstflag = false;
        playGame(true, false, game, whoplaysfirstflag);
    } else
        playGame(true, true, game, true);
    char w = ckwin(game);
    if (w != 'T') {

         if(w == 'O')
         QMessageBox :: information(this, "result", "WHITE WON!!!!  ");

         if(w == 'X' )
         QMessageBox :: information(this, "result", "BLACK WON!!!!  ");


    } else {
        QMessageBox :: information(this, "result", "Tie game. ");
    }
    string s;
    cout << "Play again? (Y or N)" << endl;
    cin >> s;
    if (s == "Y") {
        game->totalct = 4;
        makeBoard(game, 0, false);
        cout << "STARTING OVER" << endl;
        this->emptyAllBox();
        this->printBoard(game, 0);
        startGame(game);
    } else {
        cout << "THANKS FOR PLAYING!" << endl;
    }
}

void gameplay::playGame(bool fp1, bool fp2, GameBoard *game, bool whoplaysfirstflag) {
    bool s1 = true;
    bool s2 = true;
    if (fp1 && fp2 && (s1 || s2)) {
        if (whoplaysfirstflag) {
            game->p = 'X';
            delay();
            s1 = placepieceperson(game);
            this->emptyAllBox();
            this->printBoard(game, 0);
            game->p = 'O';
            delay();
            s2 = placepieceperson(game);
            this->emptyAllBox();
            this->printBoard(game, 0);
        } else {
            game->p = 'O';
            delay();
            s1 = placepieceperson(game);
            this->emptyAllBox();
            this->printBoard(game, 0);
            game->p = 'X';
            delay();
            s2 = placepieceperson(game);
            this->emptyAllBox();
            this->printBoard(game, 0);
        }
    } else if (fp1 == false && fp2 == false && (s1 || s2)) {
        game->p = 'X';
        delay();
        s1 = compplacepiece(game);
        this->emptyAllBox();
        this->printBoard(game, 0);
        game->p = 'O';
        delay();
        s2 = compplacepiece(game);
        this->emptyAllBox();
        this->printBoard(game, 0);
    } else {
        if (whoplaysfirstflag) {
            game->p = 'X';
            delay();
            s1 = placepieceperson(game);
            this->emptyAllBox();
            this->printBoard(game, 0);
            game->p = 'O';
            delay();
            s2 = compplacepiece(game);
            this->emptyAllBox();
            this->printBoard(game, 0);
        } else {
            game->p = 'X';
            delay();
            s1 = compplacepiece(game);
            this->emptyAllBox();
            this->printBoard(game, 0);
            game->p = 'O';
            delay();
            s2 = placepieceperson(game);
            this->emptyAllBox();
            this->printBoard(game, 0);
        }
    }
    if ((s1 == false && s2 == false)
            || game->totalct == game->size * game->size) {
        cout << "Game over" << endl;
        this->emptyAllBox();
        this->printBoard(game, 0);
        return;
    }
    playGame(fp1, fp2, game, whoplaysfirstflag);

}



