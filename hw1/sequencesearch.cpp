#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
    ifstream text;
    text.open (argv[1]);

    int row;
    text >> row;

    int * rowsize;
    rowsize = new int [row];

    for (int n = 0; n < row; n++) {
        text >> rowsize[n];
    }

    int bignumber = 0;
    for (int n = 0; n < row; n++) {
        if (rowsize[n] > bignumber) {
            bignumber = rowsize[n];
        }
    }

    double** grid = new double*[row];
    for (int n = 0; n < row; n++) {
        grid[n] = new double[rowsize[n]];
    }

    for (int n = 0; n < row; n++) {
        for (int i = 0; i < rowsize[n]; i++) {
            text >> grid[n][i];
            /*if (rowsize[n] >= i) {
            	text >> grid[i][n];
            }
            else {
            	grid[i][n] = double(NULL);
            }*/
        }
    }
    text.close();

    int longestchain = 0;
    int counter = 0;

    //for rows left to right
    for (int n = 0; n < row; n++) {
        for (int i = 1; i < rowsize[n]; i++) {
            //cout << grid[n][i] << " "<< grid[n][i-1] << endl;
            if (grid[n][i] > grid[n][i-1]) {

                counter++;
                if (counter > longestchain) {
                    longestchain = counter;
                }
            }

            else {
                if (counter > longestchain) {
                    longestchain = counter;
                }
                counter = 0;
            }
        }
    }

    //for columns up to down
    for (int n = 0; n < bignumber; n++) {
        for (int i = 1; i < row; i++) {
            if (rowsize[i] < n+1) {
                if (counter > longestchain) {
                    longestchain = counter;
                }
                counter = 0;
            }
            else {


                if (grid[i][n] > grid[i-1][n]) {
                    counter++;
                    if (counter > longestchain) {
                        longestchain = counter;
                    }
                }

                else {
                    if (counter > longestchain) {
                        longestchain = counter;
                    }

                }
            }
            
        }
        counter = 0;
    }



    //for rows, right to left
    for (int n = 0; n < row; n++) {
        for (int i = rowsize[n] - 2; i >= 0; i--) {
            //cout << grid[n][i] << " "<< grid[n][i+1] << endl;
            if (grid[n][i] > grid[n][i+1]) {
                counter++;
                if (counter > longestchain) {
                    longestchain = counter;
                }
            }

            else {
                if (counter > longestchain) {
                    longestchain = counter;
                }
                counter = 0;
            }
        }
    }

    //for cols right to left
    for (int n = 0; n < bignumber; n++) {
        for (int i = rowsize[n] - 2; i >= 0; i--) {
            if (rowsize[i] < n+1) {
                if (counter > longestchain) {
                    longestchain = counter;
                }
                counter = 0;
            }
            else {
                if (grid[i][n] > grid[i + 1][n]) {
                    counter++;
                    if (counter > longestchain) {
                        longestchain = counter;
                    }
                }

                else {
                    if (counter > longestchain) {
                        longestchain = counter;
                    }
                    counter = 0;
                }
            }
        }

    }
    ofstream write;
    write.open(argv[2]);

    write << longestchain;

    write.close();
    for (int i = 0; i < bignumber; i++) {
        delete[] grid[i];
    }
    delete[] grid;
    cout << longestchain << endl;
    return 0;
}