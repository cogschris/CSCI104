#include <iostream>
#include <fstream>
#include <string>
#include "minheap.h"
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

//struct Node {

//};

//so basiclaly going to make a function wehre i search through and fin
//words that are closer to the target, and then Ill make note of them
//and then at the very end of the loop ill calculate out all their 
//a star values and then check which has the lowest and run the function
// on that guy
/*
void converting(string look, string end, string terms[], MinHeap &store, int priority, int iterations) {
	int analysis = 0;
	
	while (look[analysis] == end[analysis]) {
		analysis++;
	}

	if (analysis - 1 == end.size()) {
		return;
	}

	vector<int> possible;
	for (int i = 0; i < int(terms.size()); i++) {
		bool okay = true;
		for (int j = 0; j < analysis) {
			if (terms[i][j] != look[j]) {
				okay = false;
			}
		}
		if (terms[i][analysis] == end[analysis] && okay == true) {
			possible.push_back(i);
		}
	}
	lowest = end.size() + iterations + 5;
	int special = 0;
	
	for (int i = 0; i < int(possible.size()); i++) {
		int wrong = 0;
		for (int j = 0; j < terms[possible]; j++) {
			if (terms[possible][j] != end[j]) {
				wrong++;
			}
		}
		if (iterations + wrong < lowest) {
			lowest = iterations + wrong;
			special = possible;
		}

		else if(iterations + wrong == lowest) {
			int wrong_old = 0;
			for (int j = 0; j < terms[special]; j++){
				if (terms[special][j] != end[j]) {
					wrong_old++;
				}
			}
			if ((iterations + wrong)*(terms[possible].size() + 1) + wrong < lowest*(terms[special].size()+1) + wrong_old) {
				special = possible;
			}
		}
	}
	store.add(terms[special], priority);
	priority++;
	iterations++;
	converting(terms[possible], end, terms, store, priority, iterations);
}
*/

vector<string> get_cousins(string start, vector<string> terms, vector<string> check) {
	//cout << "damn to hell" << endl;
	vector<string> answers;
	//cout << start << "    okay     ";
	for (int i = 0; i < int(terms.size()); i++) {
		int wrong = 0;
		if (start.size() != terms[i].size()) {
			wrong = 2;
		}
		else {
			//cout << terms[i] << endl; 
			for (int j = 0; j < int(terms[i].size()); j++) {
				if (start[j] != terms[i][j]) {
					wrong++;
				}
			}
		}
		//cout << terms[i] << "  " << wrong << endl;
		if (wrong == 1 && std::find(check.begin(), check.end(), terms[i]) == check.end()) {
			//cout << terms[i] << " i push this  " ;
			answers.push_back(terms[i]);
			
		}
		
	}
	
	
	return answers;
}

int get_priority(string guy, string begin, string end, map<string,string> parents, string par) {
	int wrong = 0;
	int away = 1;
	for (int i = 0; i < int(end.size()); i++) {
		if (guy[i] != end[i]) {
			wrong++;
		}
	}
	while (par != begin) {
		cout << "shiiiiiit" << endl;
		par = parents[par];
		away++;
	}
	return (away+wrong)*(int(end.size()) + 1) + wrong;
}

int main (int argc, char* argv[]) {
	if (argc < 4) {
		cout << "Please enter the proper amount of arguments!" << endl;
		return 1;
	}

	int wrong = 0;
	string begin = argv[1];
	string end = argv[2];
	for (int j = 0; j < int(begin.size()); j++) {
		if (begin[j] < 90) {
			begin[j] = begin[j] + 32;
		}
		if (end[j] < 90) {
			end[j] = end[j] + 32;
		}

		if (begin[j] != end[j]) {
			wrong++;
		}
	}

	ifstream file;
	file.open(argv[3]);
	int size;
	file >> size;
	vector<string> terms;
	
	string temp;
	for (int i = 0; i < size; i++) {
		file >> temp;
		for (int j = 0; j < int(temp.size()); j++) {
			if (temp[j] < 90) {
				temp[j] = temp[j] + 32;
			}
		}
		if (std::find(terms.begin(), terms.end(), temp) == terms.end()) {
			terms.push_back(temp);
		}
	}
	
	MinHeap openlist(2);
	vector<string> closedlist;
	vector<string> added;
	int priority = wrong*(begin.size() + 1) + wrong;
	openlist.add(begin, priority);
	added.push_back(begin);
	temp.clear();
	map<string,string> backtrack;
	map<string,int> priorities;
	priorities.insert(std::pair<string,int>(begin, priority));
	//string temp;
	//int step = 0;
	int expansion = 1;
	//cout << openlist.isEmpty() << endl;
	while (!openlist.isEmpty()) {
		
		
		temp = openlist.peek();
		closedlist.push_back(temp);
		openlist.remove();
		//cout << temp << "  i check this" << endl;
		if (temp == end) {
			cout << "I broke the code" << endl;
			break;
		}

			if (temp == "coves") {
					cout << "loaded it" << endl;
				}
		vector<string> neighbor = get_cousins(temp, terms, closedlist);
		for (int i = 0; i < int(neighbor.size()); i++) {
			
			int prio = get_priority(neighbor[i], begin, end, backtrack, temp);
			cout << neighbor[i] << "    " << prio << endl;
			if (std::find(added.begin(), added.end(), neighbor[i]) == added.end()) {
				//cout << "so the real ones  " <<neighbor[i] << "    " << prio << endl;
				openlist.add(neighbor[i], prio);
				if (neighbor[i] == "coves") {
					cout << "hit it" << endl;
				}
				added.push_back(neighbor[i]);
				priorities.insert(std::pair<string,int>(neighbor[i], prio));
			}
			else {
				cout << "well then" << prio << "   " << priorities[neighbor[i]] << endl;
				if (prio < priorities[neighbor[i]]) {
					priorities[neighbor[i]] = prio;
					openlist.update(neighbor[i], priorities[neighbor[i]]);

				}
			}
			expansion++;

				backtrack.insert(std::pair<string,string>(neighbor[i], temp));
				//cout << "Hello!  "  << neighbor[i] << "     " << temp << endl;
		}
	}
cout << "oops i ened" << endl;
	vector<string> final;

	string temps = end;
	while (temps != begin) {
		
		final.push_back(temps);
		temps = backtrack[temps];
		cout << temps;
	}
	cout << "Here is the conversion:" << endl;
	cout << begin;
	for (int i = int(final.size()) - 1; i >= 0; i--) {
		cout << " " << final[i];
	}

	cout << endl << "Expansions: " << expansion << endl;




return 0;
}
