#include <iostream>
#include <random>
#include <algorithm>
#include <time.h>
#include <cstdlib>
#include <stdlib.h>
#define N 9

using namespace std;

int arr[N][N];

bool checkBox(int row, int col, int num);
bool checkCol(int j, int num);
bool checkRow(int i, int num);
bool isSafeGen(int i, int j, int num);
void genBox(int row, int col);
bool genOtherBoxs(int i, int j);
void sudokuGen(int d);
bool isSafe(int row, int col, int num);
bool FindUnassignedLocation(int& row, int& col);
bool solver(int newarr[9][9]);



int main()
{
    srand(time(NULL));

    int newarr[9][9];

    //genarating the sudoku puzzle with all the numbers
    fill_n(&arr[0][0], 81, 0);

    for (int i = 0; i < 9; i += 3)
        genBox(i, i);

    genOtherBoxs(0, 3);
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            newarr[i][j] = arr[i][j];
        }

    }
    int d;
    cout << " Input No of Empty columns or rows you want (should be between 1 and 5) : ";
    cin >> d;
    cout << endl;
    system("cls");
    if (d > 1 && d < 5) {
        sudokuGen(d);
        cout << endl;
        cout << endl;
        cout << " Solved Sudoku Puzzle " << endl;
        cout << endl;
        cout << endl;

        if (solver(arr) == true) {
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                    cout << arr[i][j] << " ";
                cout << endl;
            }
        }

        else
            cout << "No solution exists";
    
    }
    else
    {
        cout << "ERROR IN INPUT ";
    }

    


}

//check whether its used in box
bool checkBox(int row, int col, int num)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (arr[row + i][col + j] == num)
                return false;

    return true;
}

//check whether its used in col
bool checkCol(int col, int num)
{
    for (int i = 0; i < 9; i++)
        if (arr[i][col] == num)
            return false;
    return true;
}
//check whether its used in row
bool checkRow(int row, int num)
{
    for (int j = 0; j < 9; j++)
        if (arr[row][j] == num)
            return false;
    return true;
}

//check the availability of number to input into the puzzle;
bool isSafeGen(int row, int col, int num)
{
    int boxRow1 = row - row % 3;
    int boxCol1 = col - col % 3;
    return (checkRow(row, num) && checkCol(col, num) && checkBox(boxRow1, boxCol1, num));
}

//genarate diaganal 3x3x matrices in the sudoku puzzle
void genBox(int row, int col)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int nums[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
            random_device rd;
            mt19937 g(rd());

            int rndm = rand() % 20 + 5;
            for (int c = 0; c <= rndm; c++)
                shuffle(nums, nums + 9, g);

            for (int k = 0; k < 9; k++)
            {
                if (checkBox(row, col, nums[k] + 1))
                {
                    arr[(row + i)][(col + j)] = nums[k] + 1;
                    break;
                }
            }
        }
    }
}

//genarate other 3x3 matrices according to the avalability
bool genOtherBoxs(int i, int j)
{
    if (j >= N && i < N - 1)
    {
        i = i + 1;
        j = 0;
    }

    if (i >= N && j >= N)
        return true;

    if (i < 3 && j < 3)
        j = 3;

    else if (i < N - 3)
    {
        if (j == (i / 3) * 3)
            j = j + 3;
    }
    else if (j == N - 3)
    {
        i = i + 1;
        j = 0;
        if (i >= N)
            return true;
    }

    for (int num = 1; num <= 9; num++)
    {
        if (isSafeGen(i, j, num))
        {
            arr[i][j] = num;
            if (genOtherBoxs(i, j + 1))
                return true;

            arr[i][j] = 0;
        }
    }
    return false;
}

//genarate final sudoku puzzle by removing numbers randomly
void sudokuGen(int d) {
    
    cout << " Genarated Sudoku Puzzle with " << d << " columns or rows "<<endl;
        cout << endl;
        cout << endl;

        if (d == 2) {
            int randPos1, randPos2;

            for (int row = 0; row < 9; row++) {
                randPos1 = (rand() % 9 + 1);
                randPos2 = (rand() % 9 + 1);
                for (int col = 0; col < 9; col++)
                {
                    if (col == randPos1) {
                        arr[row][randPos1] = 0;
                    }
                    if (col == randPos2)
                        arr[row][randPos2] = 0;
                }

            }

            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                    cout << arr[i][j] << " ";
                cout << endl;
            }
        }

        if (d == 3) {
            int randPos1, randPos2, randPos3;

            for (int row = 0; row < 9; row++) {
                randPos1 = (rand() % 9 + 1);
                randPos2 = (rand() % 9 + 1);
                randPos3 = (rand() % 9 + 1);

                for (int col = 0; col < 9; col++)
                {
                    if (col == randPos1)
                        arr[row][randPos1] = 0;
                    if (col == randPos2)
                        arr[row][randPos2] = 0;
                    if (col == randPos3)
                        arr[row][randPos3] = 0;
                }

            }

            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                    cout << arr[i][j] << " ";
                cout << endl;
            }


        }

        if (d == 4) {
            int randPos1, randPos2, randPos3, randPos4;

            for (int row = 0; row < 9; row++) {
                randPos1 = (rand() % 9 + 1);
                randPos2 = (rand() % 9 + 1);
                randPos3 = (rand() % 9 + 1);
                randPos4 = (rand() % 9 + 1);
                for (int col = 0; col < 9; col++)
                {
                    if (col == randPos1)
                        arr[row][randPos1] = 0;
                    if (col == randPos2)
                        arr[row][randPos2] = 0;
                    if (col == randPos3)
                        arr[row][randPos3] = 0;
                    if (col == randPos4)
                        arr[row][randPos4] = 0;
                }

            }
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                    cout << arr[i][j] << " ";
                cout << endl;
            }


        }
    
    
}

//check avalability of sudoku puzzle
bool isSafe(int row, int col, int num) {
    int boxRow1 = row - row % 3;
    int boxCol1 = col - col % 3;

    return (checkRow(row, num) && checkCol(col, num) && checkBox(boxRow1, boxCol1, num));

}

//check whether ther are any un ussingend locations in the solved puzzle 
bool FindUnassignedLocation(int& row, int& col)
{
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (arr[row][col] == 0)
                return true;
    return false;
}

//genarating the solved sudoku puzzle using backtracking
bool solver(int newarr[9][9])
{
    int row, col;


    if (!FindUnassignedLocation( row, col))

        return true;


    for (int num = 1; num <= 9; num++)
    {


        if (isSafe( row, col, num))
        {

           
            arr[row][col] = num;

            
            if (solver(newarr))
                return true;

            else {
                arr[row][col] = 0;

            }

        }

    }

    return false;
}


