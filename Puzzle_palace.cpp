#include <bits/stdc++.h>
using namespace std;
int m, n;
int board[4][4];                 // the board
int dirLine[] = {1, 0, -1, 0};   // mapping it with the values (i.e.) the change in the line/column at the value '0' (s--down) &&
int dirColumn[] = {0, 1, 0, -1}; // '1' (d--right) && '2' (w--up) && '3' (a--left)

class Game
{
public:
    pair<int, int> generateUnoccupiedPosition() // to generate unoccupied cells
    {
        int occupied = 1, line, column;

        while (occupied)
        {
            line = rand() % 4;
            column = rand() % 4;

            if (board[line][column] == 0)
                occupied = 0;
            else
                continue;
        }

        return make_pair(line, column);
    }

    void addPiece() //  to add the value to the board
    {
        pair<int, int> pos = generateUnoccupiedPosition();
        board[pos.first][pos.second] = 2;
    }

    void newGame() // after the user selects New Game option
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                board[i][j] = 0;

        addPiece();
    }

    bool canDoMove(int line, int column, int nextLine, int nextColumn)
    {
        if (nextLine < 0 || nextColumn < 0 || nextLine >= 4 || nextColumn >= 4 ||
            (board[line][column] != board[nextLine][nextColumn] && board[nextLine][nextColumn] != 0))
            return false;
        return true;
    }

    void printGUI() // to give values of the cells after the valid move
    {
        system("cls");
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (board[i][j] == 0)
                    cout << setw(4) << "*";
                else
                    cout << setw(4) << board[i][j];
            }
            cout << endl;
        }

        cout << "n:New Game || s:Down || d:Right || w:Up || a:Left || q:Quit \n";
    }

    void applyMove(int direction)
    {
        int startLine = 0, startColumn = 0, lineStep = 1, columnStep = 1;

        if (direction == 0)
        {
            startLine = 3;
            lineStep = -1;
        }

        if (direction == 1)
        {
            startColumn = 3;
            columnStep = -1;
        }

        int movePossible = 0, canAddPiece = 0;

        do
        {

            movePossible = 0;
            for (int i = startLine; i >= 0 && i < 4; i += lineStep)
                for (int j = startColumn; j >= 0 && j < 4; j += columnStep)
                {
                    int nextI = i + dirLine[direction], nextJ = j + dirColumn[direction];
                    if (canDoMove(i, j, nextI, nextJ) && board[i][j])
                    {
                        board[nextI][nextJ] += board[i][j];
                        board[i][j] = 0;
                        movePossible = canAddPiece = 1;
                    }
                }
            printGUI(); // to show the changing values
        } while (movePossible);

        if (canAddPiece)
        {
            addPiece();
        }
    }
    int game1()
    {
        char commandToDir[128];
        //   Controllers
        //   s--> to move the cells downward
        //   d--> to ove the cells right
        //   w--> to move the cells upward
        //   a--> to ove the cells left
        commandToDir['s'] = 0;
        commandToDir['d'] = 1;
        commandToDir['w'] = 2;
        commandToDir['a'] = 3;
        newGame();

        while (true)
        {
            printGUI();
            char command;
            cin >> command;

            if (command == 'q')
                break;
            else if (command == 'n')
                newGame();
            else
            {
                int currentDirection = commandToDir[command];
                applyMove(currentDirection);
            }
        }
        return 0;
    }

    // int m,n;
    bool dfs(vector<vector<int> > &dungeon, int i, int j, int h, vector<int> minHalive[], vector<int> maxHdead[])
    {
        if (i == m || j == n)
            return false;

        if (h >= minHalive[i][j])
            return true;

        if (h <= maxHdead[i][j])
            return false;

        int htmp = h + dungeon[i][j];
        if (htmp < 1)
        {
            maxHdead[i][j] = h;
            return false;
        }

        if (i == m - 1 && j == n - 1)
        {
            minHalive[i][j] = h;
            return true;
        }

        if (dfs(dungeon, i + 1, j, htmp, minHalive, maxHdead) || dfs(dungeon, i, j + 1, htmp, minHalive, maxHdead))
        {
            minHalive[i][j] = h;
            return true;
        }

        maxHdead[i][j] = h;
        return false;
    }

    int calculateMinimumHP(vector<vector<int> > &dungeon)
    {
        m = dungeon.size(), n = dungeon[0].size();

        vector<int> minHalive[m]; //minimum health can arrive the destination at dungeon[i][j]
        for (int i = 0; i < m; i++)
            minHalive[i].resize(n, INT_MAX);

        vector<int> maxHdead[m]; //maximum health can not arrive the destination at dungeon[i][j]
        for (int i = 0; i < m; i++)
            maxHdead[i].resize(n, 0);

        int l = 1, r = (m + n - 1) * 1000 + 1;
        while (l < r)
        {
            int m = (l + r) >> 1;
            if (dfs(dungeon, 0, 0, m, minHalive, maxHdead))
            {
                r = m;
            }
            else
            {
                l = m + 1;
            }
        }

        return l;
    }

    int game2()
    {
        // Taking Input.
        int m, n;
        cout << "Enter number of rows: ";
        cin >> m;
        cout << "Enter number of columns: ";
        cin >> n;
        cout << "Enter elements of dungeon: " << endl;
        vector<vector<int> > dungeon(m, vector<int>(n, 0));
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> dungeon[i][j];
            }
        }

        cout << "Minimum energy required in the beginning is: " << calculateMinimumHP(dungeon);
        return 0;
    }
};
class Screen : public Game
{

public:
    void Rules()
    {
        // cout << "__________________________________________*" << endl;
        cout << "\n\t\t\t____________________________________________________________________________________________\n";
        cout << "\n\t\t\t|\t\t\t\t\tRULES||INSTRUCTION\t\t\t\t\t   |";
        cout << "\n\t\t\t____________________________________________________________________________________________\n";

        cout << "\n\t\t\t|\t\t\t\t# HOW TO PLAY 2048 GAME ";
        cout << "\n\t\t\t|\t\t\t\tThe basic rules of the game 2048 is very simple. ";
        cout << "\n\t\t\t|\t\t\t\t 2048 puzzle game is played on a board of 4x4 square game board. ";
        cout << "\n\t\t\t|\t\t\t\tlthough there are now many variations of the 2048 game board like 5x5, 6x6, ";
        cout << "\n\t\t\t|\t\t\t\tetc the original 2048 game is shipped with a 4x4 16 squares board. ";
        cout << "\n\t\t\t|\t\t\t\t When the played swipes the tiles, if possible ";
        cout << "\n\t\t\t|\t\t\t\t all tiles on the game board move as many squares ";
        cout << "\n\t\t\t|\t\t\t\tahead on the same direction of your move.";
        cout << "\n\t\t\t|\t\t\t\tIf two tiles with the same numbers collide ";
        cout << "\n\t\t\t|\t\t\t\t, they join or merge into a single tile. ";
        cout << "\n\t\t\t|\t\t\t\tAnd the number on the new tile is the sum or double of each colliding tile.";
        cout << "\n\t\t\t|\t\t\t\tAfter the 2048 game player makes a move and swipe the tiles";
        cout << "\n\t\t\t|\t\t\t\t on the game board a new tile with number 2 or 4 ";
        cout << "\n\t\t\t|\t\t\t\t  is placed by the computer on the game board.\n\n";
        cout << "\n\t\t\t|\t\t\t\tThe coordination of the new tiles which are added ";
        cout << "\n\t\t\t|\t\t\t\ton the board after the player makes a move is randomly determined. ";
        cout << "\n\t\t\t|\t\t\t\tIf the boundaries of the board are empty,they are fist placed on a square";
        cout << "\n\t\t\t|\t\t\t\twhich is on the edge of the board. ";
        cout << "\n\t\t\t|\t\t\t\tThe player continues playing 2048 puzzle as long as there are ";
        cout << "\n\t\t\t|\t\t\t\tIf all tiles are occupied by tiles which do not join with its neighours ";
        cout << "\n\t\t\t|\t\t\t\t(on two direction left-to-right or top-to-bottom) the game ends for the player";
        cout << "\n\t\t\t|\t\t\t\tAll tiles on the board are either 2 or the power of 2 like ";
        cout << "\n\t\t\t|\t\t\t\tnumbers 2,4,8,16,32,64,128,256,512,1024 and 2048.";
        cout << "\n\t\t\t|\t\t\t\tOf course the puzzle solver can continue after 2048";
        cout << "\n\t\t\t|\t\t\t\ttile is created by merging two 1024 tiles. ";
        cout << "\n\t\t\t|\t\t\t\tIf it possible to form tiles with numbers 4096, 8192 and 16384 too.";
        cout << "\n\t\t\t|\t\t\t\t'I'm not sure but the maximum number that can be created on a 4 times 4 game board is 32768.";
        cout << "\n\t\t\t____________________________________________________________________________________________\n";

        cout << "\n\t\t\t|\t\t\t\t# HOW TO PLAY DUNGEON GAME";
        cout << "\n\t\t\t|\t\t\t\tThe demons had captured the princess and imprisoned ";
        cout << "\n\t\t\t|\t\t\t\ther in the bottom-right corner of a dungeon. ";
        cout << "\n\t\t\t|\t\t\t\tThe dungeon consists of m x n rooms laid out";
        cout << "\n\t\t\t|\t\t\t\tin a 2D grid.\n Our valiant knight ";
        cout << "\n\t\t\t|\t\t\t\twas initially positioned in the top-left room and  ";
        cout << "\n\t\t\t|\t\t\t\tmust fight his way through dungeon to rescue the princess.";
        cout << "\n\t\t\t|\t\t\t\tThe knight has an initial health point represented by a positive integer. ";
        cout << "\n\t\t\t|\t\t\t\tIf at any point his health point drops to 0 or";
        cout << "\n\t\t\t|\t\t\t\tbelow, he dies immediately. \n";
        cout << "\n\t\t\t|\t\t\t\tSome of the rooms are guarded by demons (represented by negative integers)";
        cout << "\n\t\t\t|\t\t\t\t so the knight loses health upon entering these rooms; ";
        cout << "\n\t\t\t|\t\t\t\tother rooms are either empty (represented as 0) or     ";
        cout << "\n\t\t\t|\t\t\t\tcontain magic orbs that increase the knight's health (represented by positive integers).\n\n";
        cout << "\n\t\t\t|\t\t\t\tTo reach the princess as quickly as possible, ";
        cout << "\n\t\t\t|\t\t\t\tthe knight decides to move only rightward or downward in each step. ";
        cout << "\n\t\t\t|\t\t\t\tand 1~5 (size of the bet, number of decks).\n";
        cout << "\n\t\t\t____________________________________________________________________________________________\n";

        cout << "\n\t\t\t|\t\t\t\tPRESS 1 FOR GOING BACK\n";
        cout << "\n\t\t\t|\t\t\t\t";
        int a;
        cin >> a;
        if (a == 1)
            WelcomeScreen();
    }

    void WelcomeScreen()
    {
        int choice;
        cout << "\n\n\t\t\t\t\t\t\tWelcome to Puzzle Palace!!!\n\n"
             << endl;
        cout << "\t\t\t------------------------------------------------------------------------------------------" << endl;
        cout << "\t\t\t------------------------------------------------------------------------------------------" << endl;
        cout << "\t\t\t******************************************************************************************" << endl;
        cout << "\t\t\t**\t\t\t\t\t1-Play 2048 Game\t\t\t\t**" << endl
             << "\t\t\t**\t\t\t\t\t2-Play Dungeon Game" << endl
             << "\t\t\t**\t\t\t\t\t3-Rules and Instructions" << endl
             << "\t\t\t**\t\t\t\t\t4-Quit Game\t\t\t\t\t**" << endl;
        cout << "\t\t\t******************************************************************************************" << endl;
        cout << "\t\t\t------------------------------------------------------------------------------------------" << endl;
        cout << "\t\t\t------------------------------------------------------------------------------------------" << endl;
        cout << "\t\t\t**\t\t\t\t\tEnter your choice" << endl;
        cout << "\t\t\t  \t\t\t\t\t";
        cin >> choice;
        if (choice == 1)

        {
            game1();
            WelcomeScreen();
        }
        else if (choice == 2)
        {
            game2();
            WelcomeScreen();
        }
        else if (choice == 3)
        {

            Rules();
        }
        else if (choice == 4)
        {

            WelcomeScreen();
        }
    }
};
int main()
{
    Screen s;
    s.WelcomeScreen();
}