
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include <signal.h>
#include <float.h>
using namespace std;
struct GameBoard {
    char **board; // the othello board
    int size; //for the size of the board (it's a square, so size is one dimension)
    char p; //for current player ('X' or 'O')
    int totalct; // for number of used squares (so that when the board is full, the game stops)
    int playerNum;//Num of players
};

struct Square {
    char p;
    int x; //x coordinate
    int y; //y coordinate
    int xs; //x step
    int ys; //y step
    bool flip; //T if can flip
    int rank; //for AI to determine priority
    int num; //how many chess can be flipped if placed here, -1 if this spot has already been taken
};

void getSize(int &size);
/* Parameter: int. This int will take the input from the players.
 *
 * Return: None.
 *
 * This function is used to take a number to be the size of the board, and it is only accept the even number
 * If it receives a odd number, it will round it to the next even number.
 */
void makeBoard(GameBoard *game, int ct, bool flag);
/* Parameter:  a pointer to the game, the current count (int), and a flag indicating whether
 * this board was already allocated or needs to be allocated for the first time(boolean).
 *
 * Return: None.
 *
 * This function is used to makes the board by recursively calling the makeBoard2 function
 * for each row being created.
 */
void makeBoard2(char arr[], int ct, int size);
/* Parameter:  a pointer to the game, the current count (int), and a flag indicating whether
 * this board was already allocated or needs to be allocated for the first time(boolean).
 *
 * Return: None.
 *
 * This function is used to fill the rest space of board where does not have 'O' or 'X' with '-'.
 */
void printBoard(GameBoard *game, int ct);
/* Parameter: a pointer to the current game piece and the count(int).
 *
 * Return: None.
 *
 * This function is used to indicate which row is being printed out. It
 * prints out the board, as seen in the output.
 */
void printBoard2(char arr[], int ct, int size);
/* Parameter: an array, count(int), size(int).
 *
 * Return: None.
 *
 * It should print out the board for the player's view.
 */
char ckwin(GameBoard *game);
/* Parameter: a pointer to the current game piece and the count(int).
 *
 * Return: char.
 *
 * This function is used to check the number of pieces, compare the result and
 * print who is the winner.
 */
int countRow(char arr[], char c, int ct, int size, int num);
/* Parameter: a pointer to the current game piece(char), a character(char), the count(int), the size(int), num(int).
 *
 * Return: int.
 *
 * This function is used to count how many pieces('O' and 'X') the board has for each row.
 */
int countSquare(GameBoard *game, char c, int size, int ct, int num);
/* Parameter: a pointer to the current game piece(char), a character(char), the count(int), the size(int), num(int).
 *
 * Return: int.
 *
 * This function is used to count how many pieces('O' and 'X') the board has for the whole board.
 */
bool compplacepiece(GameBoard *game);
/* Parameter: a pointer to the current game piece.
 *
 * Return: Boolean.
 *
 * This function is used for when the computer is playing as one (or both) of the players. It determines
 * the location on the board where, if it places its piece, the most other pieces will be fixed.
 */

bool placepieceperson(GameBoard *game);
/* Parameter: a pointer to the current game piece.
 *
 * Return: Boolean.
 *
 * This function is for a human placing a piece on the board. If the human chooses a square that is not located on the
 * board, it alerts the human that they forfeited a turn and returns false. If the human chooses a square that does not
 * result in any flipping, it alerts the human that they forfeited a turn and returns false. Otherwise it places the piece and
 * flips all possible pieces in all possible directions
 */
int flipPieceNum(GameBoard *game, int x, int y, bool flipflag);
/* Parameter: a pointer to the current game piece, a num(int), a num(int), a element to show if this space was allocated.
 *
 * Return: int.
 *
 * This function is count the total number which was flipped.
 */
void checkRankandFlipNum(GameBoard *game, Square *s);
/* Parameter: a pointer to the current game piece, a pointer to the square.
 *
 * Return: None.
 *
 * This function is used to check the rank of the square and if all parts of the new chart was filled
 * with '-',
 */
Square* findSpot2(GameBoard *game, Square *bestSpot, int row, int ct);
/* Parameter: a pointer to the game piece, a pointer to the square, row number(int), count(int).
 *
 * Return: a pointer.
 *
 * It is used to find the spot which has higher possibility to win.
 */


