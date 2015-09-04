/*
Author: Chris Cognetta
email: ccognett@usc.edu

This program will dynamically create a grid and then search through it to find the longest thread of
numbers and then return that number to a text file.
*/

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
    	cout << "Please make sure to include an input file and an output file" << endl;
    	return 1;
    }

    ifstream text; //loading in the file
    text.open (argv[1]);

    int row;
    text >> row;

    int * rowsize;
    rowsize = new int [row];

    //store the row sizes in an array
    for (int n = 0; n < row; n++) {
        text >> rowsize[n];
    }

    //find the biggest row for for loop reference later
    int bignumber = 0;
    for (int n = 0; n < row; n++) {
        if (rowsize[n] > bignumber) {
            bignumber = rowsize[n];
        }
    }

    //dynamically allocate the array for the grid of numbers
    double** grid = new double*[row];
    for (int n = 0; n < row; n++) {
        grid[n] = new double[rowsize[n]];
    }

    //input the grid stuff
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

    //for loop to search rows left to right
    for (int n = 0; n < row; n++) {
        for (int i = 1; i < rowsize[n]; i++) {
            
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
                counter = 1;
            }
        }
    }

    //for columns up to down
    for (int n = 0; n < bignumber; n++) {
        for (int i = 1; i < row; i++) {
            if ((rowsize[i] >= n+1) && (rowsize[i-1] >= n + 1)) {
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
            else {

                if (counter > longestchain) {
                    longestchain = counter;
                }
                counter = 1;
            }
            
        }
        counter = 1;
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
                counter = 1;
            }
        }
    }

    //for cols down to up
    for (int n = 0; n < bignumber; n++) {
        for (int i = rowsize[n] - 2; i >= 0; i--) {
            if ((rowsize[i] > n+1) && (rowsize[i+1] > n+1)) {
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
                    counter = 1;
                }
            }
            else {
                
                if (counter > longestchain) {
                    longestchain = counter;
                }
                counter = 1;
            }
        }

    }

    //write to the new file the longest chain
    ofstream write;
    write.open(argv[2]);
    write << longestchain;

    //finally the deallocation
    write.close();
    for (int i = 0; i < row; i++) {
        delete[] grid[i];
    }
    delete[] grid;
    delete[] rowsize;
    //cout << longestchain << endl;
    return 0;
}