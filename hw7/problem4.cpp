#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>

using namespace std;

bool isvalid(std::map<char,int>::iterator it, int color, map<char, int>& key, map<char, set<char> > neighbor);

bool colors(std::map<char,int>::iterator it, map<char, int>& key, map<char, set<char> > neighbor) {
	//std::map<char,int>::iterator it;
	cout << "colors" << endl;
	if (it == key.end()) {
		return true;
	} 

	for (int i = 1; i <= 4; i++) {
		it->second = i;
		if (isvalid(it, i, key, neighbor) == true) {
			
			if (colors(++it, key, neighbor) == true) {
				
				return true;
			}

			else {
				it->second = 0;
			}

		}
		else {
			it->second = 0;
		}
		
	}
	return false;
}

bool isvalid(std::map<char,int>::iterator it, int color, map<char, int>& key, map<char, set<char> > neighbor) {
	bool valid = true;

	std::map<char,set<char> >::iterator it3 = (neighbor.find(it->first));
	std::set<char> temp = (it3)->second;
	std::set<char>::iterator it2;
	for (it2 = temp.begin(); it2 != temp.end(); ++it2) {
		
			if ((key.find(*it2))->second == color) {
				valid = false;
				//int hi = key.find(*it2)->second;
				//cout << color << "    " << hi <<" " << key.find(*it2)->first << endl;
			}
		
		
	}
	if (valid == true) {
		return true;
	}
	return false;
}





int main(int argc, char* argv[]) {
	int countries;
	int rows;
	int cols;
	ifstream text;
	text.open(argv[1]);
	text >> countries >> rows >> cols;
	//set<char> neighbor;
	char lands[rows][cols];
	map<char, int> key;
	map<char, set<char> > neighbor;
	set<char> people;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			text >> lands[i][j];
			key.insert(std::pair<char,int>(lands[i][j], 0));
			//cout << lands[i][j] << endl;
			neighbor.insert(std::pair<char,set<char> >(lands[i][j], people));


		}
	}

	for (int i = 1; i < rows-1; i++) {
		for (int j = 1; j < cols-1; j++) {
			if (lands[i][j] != lands[i-1][j]) {
				neighbor[lands[i][j]].insert(lands[i-1][j]);
				neighbor[lands[i-1][j]].insert(lands[i][j]);
			}
			if (lands[i][j] != lands[i+1][j]) {
				neighbor[lands[i][j]].insert(lands[i+1][j]);
				neighbor[lands[i+1][j]].insert(lands[i][j]);
				//cout << lands[i][j] << "  " << lands[i-1][j] << endl;
			}
			if (lands[i][j] != lands[i][j-1]) {
				neighbor[lands[i][j]].insert(lands[i][j-1]);
				neighbor[lands[i][j-1]].insert(lands[i][j]);
				//cout << lands[i][j] << "  " << lands[i-1][j] << endl;
			}
			if (lands[i][j] != lands[i][j+1]) {
				neighbor[lands[i][j]].insert(lands[i][j+1]);
				neighbor[lands[i][j+1]].insert(lands[i][j]);
				//cout << lands[i][j] << "  " << lands[i-1][j] << endl;
			}
		}
	}
std::map<char,int>::iterator it=key.begin();
 
	//int country[countries];
	if (colors(it, key, neighbor) == true) {
		std::map<char,int>::iterator it4;
		for (it4 = key.begin(); it4 != key.end(); ++it4) {
			cout << it4->first << "   " << it4->second << endl;
			
		}
		return 0;
}
		return 1;
}