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
	
	double** grid = new double*[bignumber];
	for (int n = 0; n < bignumber; n++) {
		grid[n] = new double[row];
	}

	for (int n = 0; n < bignumber; n++) {
		for (int i = 0; i < row; i++){
			if (rowsize[n] >= i) {
				text >> grid[i][n];
			}
			else {
				grid[i][n] = NULL;
			}
		}
	}


	int longestchain = 0;
	int counter = 0;

	//for columns up to down
	for (int n = 0; n < bignumber; n++) {
		for (int i = 1; i < row; i++) {
			if (grid[n][i] > grid[n][i-1]) {
				counter++;
				if (counter > longestchain){
					longestchain = counter;
				}
			}

			else {
				if (counter > longestchain){
					longestchain = counter;
				}
				counter = 0;
			}
		}
	}

	//for rows left to right
	for (int n = 0; n < row; n++) {
		for (int i = 1; i < bignumber; i++) {
			if (grid[i][n] > grid[i-1][n]) {
				counter++;
				if (counter > longestchain){
					longestchain = counter;
				}
			}

			else {
				if (counter > longestchain){
					longestchain = counter;
				}
				counter = 0;
			}
		}
	}

	//for columns, down to up
	for (int n = 0; n < bignumber; n++) {
		for (int i = row - 2; i >= 0; i--) {
			if (grid[n][i] > grid[n][i+1]) {
				counter++;
				if (counter > longestchain){
					longestchain = counter;
				}
			}

			else {
				if (counter > longestchain){
					longestchain = counter;
				}
				counter = 0;
			}
		}
	}

	//for rows right to left
	for (int n = 0; n < row; n++) {
		for (int i = bignumber - 2; i >= 0; i--) {
			if (grid[i][n] > grid[i + 1][n]) {
				counter++;
				if (counter > longestchain){
					longestchain = counter;
				}
			}

			else {
				if (counter > longestchain){
					longestchain = counter;
				}
				counter = 0;
			}
		}
	}

	cout << longestchain << endl;
}