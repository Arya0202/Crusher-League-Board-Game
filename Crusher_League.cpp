//============================================================================
// Name        : League Crusher
// Author      : Ananya, Arya, Anshul
// Description : Follows candy crush rules
//============================================================================

#include <iostream>
#include <iomanip>
//#include <bits/stdc++.h>
using namespace std;

// Board elements
#define EDGE -1
int N; // global variable
// Table Size
int D; // maximum number of different tile types on the board

int S; // Seed for generating pseudo-random numbers

int **Board;
int line;
int column;
int point;
int pointTotal = 0;

// Class that defines the Movement
class movement
{
public:
    pair<int, int> source;
    pair<int, int> destination;
};

// Variable that stores the Movement

// USE BACKTRACKING TO CREATE BoardS
// NON ELIMINABLE STRUCTURES
//

/*
----------------------------------------------------------------------------------------------------
||||||||||||||||||||||||||||||||||||||||||||| Coin |||||||||||||||||||||||||||||||||||||||||||||
----------------------------------------------------------------------------------------------------
*/

// allocate one Board one NxN
void allocateBoard()
{

    // allocate memory space to the board
    Board = new int *[N + 2];
    for (int i = 0; i <= N + 1; i++)
    {
        Board[i] = new int[N + 2];
    }

    // define edge
    for (int i = 0; i <= N + 1; i++)
    {

        Board[0][i] = EDGE;
        Board[i][0] = EDGE;
        Board[N + 1][i] = EDGE;
        Board[i][N + 1] = EDGE;
    }

    // Resets all Board positions
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            Board[i][j] = 0;
        }
    }
}

// Search for empty cells
bool existcellempty(int &i, int &j)
{

    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= N; j++)
        {
            if (Board[i][j] == 0)
                return true;
        }
    }

    return false;
}

bool existpartsequalsAbove(int row, int col, int num)
{

    if (row > 2)
    {
        if ((num == Board[row - 1][col]) &&
            (num == Board[row - 2][col]))
            return true;
    }

    return false;
}

bool ThereexistspartsMiddle(int row, int col, int num)
{

    if (row > 1 & row < N)
    {
        if ((num == Board[row - 1][col]) &&
            (num == Board[row + 1][col]))
            return true;
    }

    return false;
}

bool existpartsBelow(int row, int col, int num)
{

    if (row <= N - 2)
    {
        if ((num == Board[row + 1][col]) &
            (num == Board[row + 2][col]))
            return true;
    }

    return false;
}

// Search for color equals in the same column
bool existpartsinthesamecolumn(int row, int col, int num)
{

    if (existpartsequalsAbove(row, col, num) ||
        ThereexistspartsMiddle(row, col, num) ||
        existpartsBelow(row, col, num))
        return true;

    return false;
}

// Search for parts equals to the left of the current part.
bool existpartsequalsLeft(int row, int col, int num)
{

    if (col > 2)
    {
        if ((num == Board[row][col - 1]) &
            (num == Board[row][col - 2]))
            return true;
    }

    return false;
}

// Search for parts equals to the left and right of the current part.
bool existpartsequalsrightLeft(int row, int col, int num)
{

    if (col > 1)
    {
        if ((num == Board[row][col - 1]) &
            (num == Board[row][col + 1]))
            return true;
    }

    return false;
}

// Search for parts equals to direct from the current part.
bool existpartsequalsRight(int row, int col, int num)
{

    if (col <= N - 2)
    {
        if ((num == Board[row][col + 1]) &
            (num == Board[row][col + 2]))
            return true;
    }

    return false;
}

// Search for parts equals on the same line.
bool existpartsequalsinthesameline(int row, int col, int num)
{

    if (existpartsequalsLeft(row, col, num) ||
        existpartsequalsrightLeft(row, col, num) ||
        existpartsequalsRight(row, col, num))
        return true;

    return false;
}

// Search for a pointable structure
bool Scoringstructurexists(int row, int col, int num)
{

    if (existpartsequalsinthesameline(row, col, num) ||
        existpartsinthesamecolumn(row, col, num))
        return true;

    return false;
}

// generates an NxN without scoring structure
// use backtracking
bool ConstructBoard()
{

    int i, j;

    if (!existcellempty(i, j))
    {
        return true;
    }

    Board[i][j] = rand() % D + 1;

    if (!Scoringstructurexists(i, j, Board[i][j]))
    {
        if (ConstructBoard())
            return true;
    }

    for (int num = 1; num <= D; num++)
    {

        Board[i][j] = num;

        if (!Scoringstructurexists(i, j, num))
        {
            if (ConstructBoard())
                return true;
        }
    }

    Board[i][j] = 0;

    // Triggers backtracking
    return false;
}

// Prints the Board with the EDGEs
void ImprimeBoard()
{
    for (int i = 0; i <= N + 1; i++)
    {
        for (int j = 0; j <= N + 1; j++)
        {
            cout << setw(3) << Board[i][j]; //
        }
        cout << endl;
    }
}

// Frees up memory space
void ApagaBoard()
{
    for (int i = 0; i <= N + 1; i++)
    {
        delete[] Board[i];
    }
    delete[] Board;
}

// Checks if there is a maximum - of - the - line structure above, between and below of the moved part, and marks them as empty.
void Marklikepartsonthesamecolumn(int row, int col, int num)
{

    if (existpartsequalsAbove(row, col, num))
    {
        for (int i = row; i >= 1; i--)
        {

            if (Board[i][col] == num && Board[i][col] != -1)
                Board[i][col] = 0;
            else if (Board[i][col] == 0)
                continue;
            else
                break;
        }
    }

    if (ThereexistspartsMiddle(row, col, num))
    {

        for (int i = row; i >= 1; i--)
        {

            if (Board[i][col] == num && Board[i][col] != -1)
                Board[i][col] = 0;
            else if (Board[i][col] == 0)
                continue;
            else
                break;
        }

        for (int i = row; i <= N; i++)
        {

            if (Board[i][col] == num && Board[i][col] != -1)
                Board[i][col] = 0;
            else if (Board[i][col] == 0)
                continue;
            else
                break;
        }
    }

    if (existpartsBelow(row, col, num))
    {

        for (int i = row; i <= N; i++)
        {

            if (Board[i][col] == num && Board[i][col] != -1)
                Board[i][col] = 0;
            else if (Board[i][col] == 0)
                continue;
            else
                break;
        }
    }
}

// Checks if there are structures to the right, between and left of the moved part, and marks them as empty.
void Marklikepartsonthesameline(int row, int col, int num)
{

    if (existpartsequalsRight(row, col, num))
    {

        for (int j = col; j <= N; j++)
        {

            if (Board[row][j] == num && Board[row][j] != -1)
                Board[row][j] = 0;
            else if (Board[row][j] == 0)
                continue;
            else
                break;
        }
    }

    if (existpartsequalsrightLeft(row, col, num))

    {

        for (int j = col; j <= N; j++)
        {

            if (Board[row][j] == num && Board[row][j] != -1)
                Board[row][j] = 0;
            else if (Board[row][j] == 0)
                continue;
            else
                break;
        }

        for (int j = col; j >= 1; j--)
        {

            if (Board[row][j] == num && Board[row][j] != -1)
                Board[row][j] = 0;
            else if (Board[row][j] == 0)
                continue;
            else
                break;
        }
    }

    if (existpartsequalsLeft(row, col, num))
    {

        for (int j = col; j >= 1; j--)
        {

            if (Board[row][j] == num && Board[row][j] != -1)
                Board[row][j] = 0;
            else if (Board[row][j] == 0)
                continue;
            else
                break;
        }
    }
}

// mark the scoring structures as empty.
void ExecuteMovement(int row, int col, int num)
{

    Marklikepartsonthesameline(row, col, num);
    Marklikepartsonthesamecolumn(row, col, num);
}

// It performs the Movement of the part.

void Movepart(movement move)
{

    int linesource = move.source.first;
    int columnsource = move.source.second;
    cout<<endl;

    int linedestination = move.destination.first;
    int columndestination = move.destination.second;

    int partsource = Board[linesource][columnsource];
    int partinstination = Board[linedestination][columndestination];

    if (Scoringstructurexists(linedestination, columndestination, partsource))
    {

        Board[linesource][columnsource] = partinstination;
        Board[linedestination][columndestination] = partsource;

        for (int row = 1; row <= N; row++)
        {
            for (int col = 1; col <= N; col++)
            {

                cout << Board[row][col] << " ";
            }
            cout << endl;
        }
        cout<<endl;

        ExecuteMovement(linedestination, columndestination, partsource);

        if (Scoringstructurexists(linesource, columnsource, partinstination))
        {

            ExecuteMovement(linesource, columnsource, partinstination);
        }
    }
}

// calculate a quantitiy in parts emptys Board and returns this number to be added the total score.
int calculatePunctuation()
{

    int qtdpartsChecked = 0;

    for (int row = 1; row <= N; row++)
    {
        for (int col = 1; col <= N; col++)
        {

            if (Board[row][col] == 0)
                qtdpartsChecked++;
        }
    }

    return qtdpartsChecked;
}

// Uses the function ConstructBoard() to avoid create scoring structures
void ReConstructBoard()
{
    ConstructBoard();
}

// Checks if the movement is valid
bool movementisvalid()
{
    movement move;

    int linesource = move.source.first;
    int columnsource = move.source.second;

    int linedestination = move.destination.first;
    int columndestination = move.destination.second;

    if ((abs(linedestination - linesource) == 1) ||
        (abs(columndestination - columnsource) == 1))
    {

        if ((abs(linedestination - linesource) == 1) &&
            (abs(columndestination - columnsource) == 1))
            return true;

        else if (Board[linedestination][columndestination] == EDGE ||
                 Board[linesource][columnsource] == EDGE)
            return false;

        else
            return true;
    }

    return true;
}

// Search movements valid.
bool ExistMovement()
{

    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {

            if (Scoringstructurexists(i + 1, j, Board[i][j]) ||
                Scoringstructurexists(i - 1, j, Board[i][j]) ||
                Scoringstructurexists(i, j + 1, Board[i][j]) ||
                Scoringstructurexists(i, j - 1, Board[i][j]))
                return true;
        }
    }

    return false;
}

// run the program
int main(int argc, char *argv[])
{

    system("color A0");
    cout << "  ____________________________________________________  " << endl;
    cout << "| .................................................... |" << endl;
    cout << "| .................... WELCOME TO .................... |" << endl;
    cout << "| .................. LEAGUE CRUSHER .................. |" << endl;
    cout << "| .................................................... |" << endl;
    cout << "  ____________________________________________________  " << endl << endl;


    // Board dimension reading
    cout << "The board dimension: " << endl;
    cin >> N;

    cout << "The maximum amount of color on the board: " << endl;
    cin >> D;

    cout << "Seed for generation of pseudo-random numbers, any integer value: " << endl;
    cin >> S;

    // Powering the pseudorandom number generator
    srand(S);
    allocateBoard();

    ConstructBoard();
    ImprimeBoard();

    movement move;
    do
    {
        cout << "Source row: ";
        cin >> line;
        cout << "Source column: ";
        cin >> column;
        move.source = make_pair(line, column);

        cout << "Target row: ";
        cin >> line;
        cout << "Target column: ";
        cin >> column;
        move.destination = make_pair(line, column);

        if (!movementisvalid())
        {
            cout << "Your movement is invalid.";
            cout << "Please, make another move." << endl;
            continue;
        }

        Movepart(move);
        point = calculatePunctuation();

        cout << "Score: " << point << endl;
        pointTotal += point;
        cout << "Total Point: " << pointTotal << endl<<endl;

        ImprimeBoard();
        ReConstructBoard();

        cout << "\nCurrent board: " << endl;
        ImprimeBoard();

    } while (ExistMovement());

    cout << "End of the game." << endl;
    cout << "Total score: " << pointTotal << endl;

    return 0;

}
