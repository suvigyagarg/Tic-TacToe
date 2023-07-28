#include <iostream>
#include <vector>

#define COMPUTER 1
#define HUMAN 2
#define SIDE 3
#define COMPUTERMOVE 'O'
#define HUMANMOVE 'X'

using namespace std;

void showBoard(char board[][SIDE]);
void showInstructions();
void initialise(char board[][SIDE]);
void declareWinner(int whoseTurn);
bool rowCrossed(char board[][SIDE]);
bool columnCrossed(char board[][SIDE]);
bool diagonalCrossed(char board[][SIDE]);
bool gameOver(char board[][SIDE]);
int minimax(char board[][SIDE], int depth, bool isAI);
int bestMove(char board[][SIDE], int moveIndex);
void playTicTacToe(int whoseTurn);

void showBoard(char board[][SIDE])
{
    cout << "\t\t\t" << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
    cout << "\t\t\t-----------\n";
    cout << "\t\t\t" << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
    cout << "\t\t\t-----------\n";
    cout << "\t\t\t" << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
}

void showInstructions()
{
    cout << "\nChoose a cell numbered from 1 to 9 in the Matrix Board shown below :- \n\n";

    cout << "\t\t\t\t\t 1 | 2 | 3 \n";
    cout << "\t\t\t\t\t-----------\n";
    cout << "\t\t\t\t\t 4 | 5 | 6 \n";
    cout << "\t\t\t\t\t-----------\n";
    cout << "\t\t\t\t\t 7 | 8 | 9 \n";

    cout << endl;
}

void initialise(char board[][SIDE])
{
    for (int i = 0; i < SIDE; i++)
    {
        for (int j = 0; j < SIDE; j++)
        {
            board[i][j] = '*';
        }
    }
}

void declareWinner(int whoseTurn)
{
    if (whoseTurn == COMPUTER)
        cout << "COMPUTER has won the GAME\n";
    else
        cout << "You have won the GAME\n";
}

bool rowCrossed(char board[][SIDE])
{
    for (int i = 0; i < SIDE; i++)
    {
        if (board[i][0] == board[i][1] &&
            board[i][1] == board[i][2] &&
            board[i][0] != '*')
            return true;
    }
    return false;
}

bool columnCrossed(char board[][SIDE])
{
    for (int i = 0; i < SIDE; i++)
    {
        if (board[0][i] == board[1][i] &&
            board[1][i] == board[2][i] &&
            board[0][i] != '*')
            return true;
    }
    return false;
}

bool diagonalCrossed(char board[][SIDE])
{
    // checking for Diagonal from Top-left corner to Bottom right corner
    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2] &&
        board[0][0] != '*')
    {
        return true;
    }

    // checking for Diagonal from Top-Right corner to Bottom left corner
    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0] &&
        board[0][2] != '*')
    {
        return true;
    }

    return false;
}

bool gameOver(char board[][SIDE])
{
    return rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board);
}

int minimax(char board[][SIDE], int depth, bool isAI)
{
    int score = 0;
    int bestScore = 0;
    if (gameOver(board) == true)
    {
        if (isAI == true)
            return -10;
        if (isAI == false)
            return +10;
    }
    else
    {
        if (depth < 9)
        {
            if (isAI == true)
            {
                bestScore = -1000;
                for (int i = 0; i < SIDE; i++)
                {
                    for (int j = 0; j < SIDE; j++)
                    {
                        if (board[i][j] == '*')
                        {
                            board[i][j] = COMPUTERMOVE;
                            score = minimax(board, depth + 1, false);
                            board[i][j] = '*';
                            if (score > bestScore)
                            {
                                bestScore = score;
                            }
                        }
                    }
                }
                return bestScore;
            }
            else
            {
                bestScore = 1000;
                for (int i = 0; i < SIDE; i++)
                {
                    for (int j = 0; j < SIDE; j++)
                    {
                        if (board[i][j] == '*')
                        {
                            board[i][j] = HUMANMOVE;
                            score = minimax(board, depth + 1, true);
                            board[i][j] = '*';
                            if (score < bestScore)
                            {
                                bestScore = score;
                            }
                        }
                    }
                }
                return bestScore;
            }
        }
        else
        {
            return 0;
        }
    }
    return 0;
}

int bestMove(char board[][SIDE], int moveIndex)
{
    int x = -1, y = -1;
    int score = 0, bestScore = -1000;
    for (int i = 0; i < SIDE; i++)
    {
        for (int j = 0; j < SIDE; j++)
        {
            if (board[i][j] == '*')
            {
                board[i][j] = COMPUTERMOVE;
                score = minimax(board, moveIndex + 1, false);
                board[i][j] = '*';
                if (score > bestScore)
                {
                    bestScore = score;
                    x = i;
                    y = j;
                }
            }
        }
    }
    return x * 3 + y;
}

void playTicTacToe(int whoseTurn)
{
    system("cls");
    char board[SIDE][SIDE];
    int moveIndex = 0, x = 0, y = 0;

    initialise(board);
    showInstructions();

    while (gameOver(board) == false && moveIndex != SIDE * SIDE)
    {
        int n;
        if (whoseTurn == COMPUTER)
        {
            n = bestMove(board, moveIndex);
            x = n / SIDE;
            y = n % SIDE;
            board[x][y] = COMPUTERMOVE;
            cout << endl;

            cout << "COMPUTER has put a " << COMPUTERMOVE << " in cell : " << n + 1 << endl
                                 << endl;
            showBoard(board);
            moveIndex++;
            whoseTurn = HUMAN;
        }

        else if (whoseTurn == HUMAN)
        {
            cout << endl;
            cout << "Choose from following available positions : ";

            for (int i = 0; i < SIDE; i++)
                for (int j = 0; j < SIDE; j++)
                    if (board[i][j] == '*')
                        cout << (i * 3 + j) + 1 << "  ";

            cout << "\n\nEnter the position = ";
            cin >> n;
            n--;
            x = n / SIDE;
            y = n % SIDE;

            if (board[x][y] == '*' && n < 9 && n >= 0)
            {
                board[x][y] = HUMANMOVE;
                system("cls");
                cout << "\nPLAYER has put a " << HUMANMOVE << " in cell : " << n + 1 << endl
                     << endl;
                showBoard(board);
                moveIndex++;
                whoseTurn = COMPUTER;
            }
            else if (board[x][y] != '*' && n < 9 && n >= 0)
            {
                cout << "\nPosition is occupied, select any one place from the available places\n\n";
            }
            else if (n < 0 || n > 8)
            {
                cout << "Invalid position\n";
            }
        }
    }

    if (gameOver(board) == false && moveIndex == SIDE * SIDE)
        cout << "It's a draw\n";
    else
    {
        if (whoseTurn == COMPUTER)
            whoseTurn = HUMAN;
        else if (whoseTurn == HUMAN)
            whoseTurn = COMPUTER;

        declareWinner(whoseTurn);
    }
}

int main()
{
    playTicTacToe(HUMAN);
    return 0;
}
