#include "logic.h"

void checkRankandFlipNum(GameBoard *game, Square *s) {

    int size = game->size;
    int x = s->x;
    int y = s->y;
    s->num = flipPieceNum(game, x, y, false);
    if ((game->board[x][y] != '-') || (s->num == 0)) {
        s->num = -1;
        s->rank = -1;
        return;
    }

    int emptNum = countSquare(game, '-', size, 0, 0);

    if ((x == 0 && (y == size - 1 || y == 0))
            || (x == size - 1 && (y == size - 1 || y == 0))) {
        s->rank = 40;
    } else if ((x % 2 == 0 && (y == size - 1 || y == 0))
            || (y % 2 == 0 && (x == size - 1 || x == 0))) {
        s->rank = 30;
    } else if (y == size - 1 || y == 0 || x == size - 1 || x == 0) {
        if (emptNum < size * size / 2) {
            s->rank = 20;
        } else {
            s->rank = 10;
        }
    } else if (x % 2 == 0 || y % 2 == 0) {
        if (emptNum < size * size / 2) {
            s->rank = 10;
        } else {
            s->rank = 20;
        }
    }

    if (((x == 0 || x == size - 1) && (y > 0 && y < size - 1))
            && (((game->board[x][y - 1] == '-')
                    &&(game->board[x][y + 1] != '-'
                            && game->board[x][y + 1] != game->p))
                    || ((game->board[x][y + 1] == '-')
                            &&(game->board[x][y - 1] != '-'
                                    && game->board[x][y - 1] != game->p)))) {
        s->rank = 1;
    }

    if ((y == 0 || y == size - 1) && (x > 0 && x < size - 1)
            && (((game->board[x - 1][y] == '-')
                    && (game->board[x + 1][y] != '-'
                            && game->board[x + 1][y] != game->p))
                    || ((game->board[x + 1][y] == '-')
                            && (game->board[x - 1][y] != '-'
                                    && game->board[x - 1][y] != game->p)))) {
        s->rank = 1;
    }

}

Square* findSpot2(GameBoard *game, Square *bestSpot, int row, int ct) {
    if (ct == game->size) {
        return bestSpot;
    } else {
        Square *temp = new Square;
        temp->x = row;
        temp->y = ct;

        checkRankandFlipNum(game, temp);

        if ((temp->rank > bestSpot->rank)
                || (temp->rank == bestSpot->rank && temp->num > bestSpot->num)) {
            bestSpot = temp;
        } /*else {
            delete temp;
        }*/
        return findSpot2(game, bestSpot, row, ct += 1);
    }
}

Square* findSpot(GameBoard *game, Square *bestSpot, int ct) {
    if (ct == game->size) {
        return bestSpot;
    } else {
        Square *temp = new Square;
        temp = findSpot2(game, bestSpot, ct, 0);

        if ((temp->rank > bestSpot->rank)
                || (temp->rank == bestSpot->rank && temp->num > bestSpot->num)) {
            bestSpot = temp;
        }
        return findSpot(game, bestSpot, ct += 1);
    }
}

bool compplacepiece(GameBoard *game) {
    int dash = countSquare(game, '-', game->size, 0, 0);
    if (dash == 0) {
        return false;
    }
    Square *bestSpot = new Square;
    bestSpot->rank = -1;
    bestSpot->num = -1;

    bestSpot = findSpot(game, bestSpot, 0);
    cout << "best spot: " << bestSpot->x << bestSpot->y << endl;

    if (bestSpot->num < 0 || bestSpot->rank < 0) {
        return false;
    } else {
        flipPieceNum(game, bestSpot->x, bestSpot->y, true);
        return true;
    }

}
void setArrToInitial(Square *start, Square arr[]) {
    arr[0].p = start->p;
    arr[0].x = start->x - 1;
    arr[0].y = start->y - 1;
    arr[0].xs = -1;
    arr[0].ys = -1;

    arr[1].p = start->p;
    arr[1].x = start->x - 1;
    arr[1].y = start->y;
    arr[1].xs = -1;
    arr[1].ys = 0;

    arr[2].p = start->p;
    arr[2].x = start->x - 1;
    arr[2].y = start->y + 1;
    arr[2].xs = -1;
    arr[2].ys = 1;

    arr[3].p = start->p;
    arr[3].x = start->x;
    arr[3].y = start->y - 1;
    arr[3].xs = 0;
    arr[3].ys = -1;

    arr[4].p = start->p;
    arr[4].x = start->x;
    arr[4].y = start->y + 1;
    arr[4].xs = 0;
    arr[4].ys = 1;

    arr[5].p = start->p;
    arr[5].x = start->x + 1;
    arr[5].y = start->y - 1;
    arr[5].xs = 1;
    arr[5].ys = -1;

    arr[6].p = start->p;
    arr[6].x = start->x + 1;
    arr[6].y = start->y;
    arr[6].xs = 1;
    arr[6].ys = 0;

    arr[7].p = start->p;
    arr[7].x = start->x + 1;
    arr[7].y = start->y + 1;
    arr[7].xs = 1;
    arr[7].ys = 1;

}

Square* buildArray(Square *start) {
    struct Square *arr = new Square[8];
    arr[0].p = start->p;
    arr[0].x = start->x - 1;
    arr[0].y = start->y - 1;
    arr[0].xs = -1;
    arr[0].ys = -1;

    arr[1].p = start->p;
    arr[1].x = start->x - 1;
    arr[1].y = start->y;
    arr[1].xs = -1;
    arr[1].ys = 0;

    arr[2].p = start->p;
    arr[2].x = start->x - 1;
    arr[2].y = start->y + 1;
    arr[2].xs = -1;
    arr[2].ys = 1;

    arr[3].p = start->p;
    arr[3].x = start->x;
    arr[3].y = start->y - 1;
    arr[3].xs = 0;
    arr[3].ys = -1;

    arr[4].p = start->p;
    arr[4].x = start->x;
    arr[4].y = start->y + 1;
    arr[4].xs = 0;
    arr[4].ys = 1;

    arr[5].p = start->p;
    arr[5].x = start->x + 1;
    arr[5].y = start->y - 1;
    arr[5].xs = 1;
    arr[5].ys = -1;

    arr[6].p = start->p;
    arr[6].x = start->x + 1;
    arr[6].y = start->y;
    arr[6].xs = 1;
    arr[6].ys = 0;

    arr[7].p = start->p;
    arr[7].x = start->x + 1;
    arr[7].y = start->y + 1;
    arr[7].xs = 1;
    arr[7].ys = 1;

    arr[0].flip = false;
    arr[1].flip = false;
    arr[2].flip = false;
    arr[3].flip = false;
    arr[4].flip = false;
    arr[5].flip = false;
    arr[6].flip = false;
    arr[7].flip = false;

    return arr;

}

void flipOneDirec(Square *first, GameBoard *game) {
    if (game->board[first->x][first->y] == first->p) {
        return;
    } else {
        game->board[first->x][first->y] = first->p;
        first->x += first->xs;
        first->y += +first->ys;

        return flipOneDirec(first, game);
    }
}

void flipAllDirec(Square *arr, GameBoard *game, int ct) {
    if (ct == 8) {
        return;
    } else {
        if (arr[ct].flip) {
            flipOneDirec(&arr[ct], game);
        }

        return flipAllDirec(arr, game, ct += 1);
    }

}
int getFlipNumOneDirec(Square *first, GameBoard *game, int num) {
    if (first->x < 0 || first->x >= game->size || first->y < 0
            || first->y >= game->size
            || first->p == game->board[first->x][first->y]
            || game->board[first->x][first->y] == '-') {

        if (first->x < 0 || first->x >= game->size || first->y < 0
                || first->y >= game->size
                || game->board[first->x][first->y] == '-') {
            num = 0;
        } else if (first->p == game->board[first->x][first->y]) {
            first->flip = true;
        }
        return num;
    } else {
        first->x += first->xs;
        first->y += +first->ys;
        num += 1;

        return getFlipNumOneDirec(first, game, num);
    }
}

int getFlipNum(Square arr[], GameBoard *game, int num, int ct) {
    if (ct == 8) {
        return num;
    } else {
        num += getFlipNumOneDirec(&arr[ct], game, 0);
        return getFlipNum(arr, game, num, ct += 1);
    }
}

int flipPieceNum(GameBoard *game, int x, int y, bool flipflag) {
    Square *start = new Square;
    start->p = game->p;
    start->x = x;
    start->y = y;
    Square *arr = buildArray(start);

    int num = getFlipNum(arr, game, 0, 0);

    if (flipflag && num != 0) {
        setArrToInitial(start, arr);
        game->board[x][y] = game->p;
        flipAllDirec(arr, game, 0);
    }
    delete[] arr;
    return num;
}


int countRow(char arr[], char c, int size, int ct, int num) {
    if (ct == size) {

        return num;
    } else {

        if (arr[ct] == c) {
            num++;
        }
        return countRow(arr, c, size, ct += 1, num);
    }

}
int countSquare(GameBoard *game, char c, int size, int ct, int num) {
    if (ct == size) {
        return num;
    } else {

        num += countRow(game->board[ct], c, game->size, 0, 0);
        return countSquare(game, c, size, ct += 1, num);
    }
}
char ckwin(GameBoard *game) {
    int x = countSquare(game, 'X', game->size, 0, 0);
    int o = countSquare(game, 'O', game->size, 0, 0);

    if (x == o)
        return 'T';
    if (x > o)
        return 'X';
    else
        return 'O';

}
void getSize(int &size) {
//	int tempSize = rand() % 5 + 5;
    int tempSize = 6;
    if (tempSize % 2 != 0) {
        tempSize++;
    }
    size = tempSize;

}

void printFirstRow(int size, int ct) {
    if (ct == 0) {
        cout << " \t";
    }
    if (ct == size) {
        cout << endl;
        return;
    } else {
        cout << ct << " \t";
        return printFirstRow(size, ct += 1);
    }
}

void printBoard(GameBoard *game, int ct) {
    if (ct == 0) {
        printFirstRow(game->size, ct);
    }
    if (ct == game->size) {
        cout << endl;
        cout << endl;
        return;
    } else {
        cout << ct << "\t";
        printBoard2(game->board[ct], 0, game->size);
        return printBoard(game, ct += 1);
    }
}

void printBoard2(char arr[], int ct, int size) {
    if (ct == size) {
        cout << endl;
        return;
    } else {
        cout << arr[ct] << "\t";
        return printBoard2(arr, ct += 1, size);
    }

}

void makeBoard(GameBoard *game, int ct, bool flag) {
    if (flag) {
        game->board = new char*[game->size];
        flag = false;
    }
    if (ct == game->size) {
        return;
    } else {
        game->board[ct] = new char[game->size];
        if (ct == game->size / 2) {
            game->board[ct][ct - 1] = 'O';
            game->board[ct][ct] = 'X';
        }
        if (ct == (game->size / 2) - 1) {
            game->board[ct][ct + 1] = 'O';
            game->board[ct][ct] = 'X';
        }
        makeBoard2(game->board[ct], 0, game->size);
        return makeBoard(game, ct += 1, flag);
    }
}

void makeBoard2(char arr[], int ct, int size) {
    if (ct == size) {
        return;
    } else {
        if (arr[ct] != 'X' && arr[ct] != 'O') {
            arr[ct] = '-';
        }
        return makeBoard2(arr, ct += 1, size);
    }

}

