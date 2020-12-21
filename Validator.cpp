#include "Worker.h"

using namespace workflow_executor;
using namespace std;


Validator::Validator()
{
}


Validator::~Validator()
{
}


bool Validator::isCorrect(std::map <int, string> blocks, vector <string> words) {
	int id = 0;
	try {
		for (int i = 0; i < words.at(0).length(); i++) {
			if (isdigit(words.at(0)[i])) id = id * 10 + (words.at(0)[i] - '0');
			else throw - 1;
		}
		if (blocks.count(id) != 0) throw - 1; //this id already used

		if (words.at(1) != "=") throw - 1; //wrong format

		//wrong number of arguments:
		if (words.at(2) == "readfile") {
			if (words.size() != 4) throw - 1;
			ifstream file(words.at(3));
			if (!file.is_open()) throw - 1;
			else file.close();
		}
		if (words.at(2) == "writefile")	if (words.size() != 4) throw - 1;
		if (words.at(2) == "sort") if (words.size() != 3) throw - 1;
		if (words.at(2) == "grep") if (words.size() != 4) throw - 1;
		if (words.at(2) == "dump") if (words.size() != 4) throw - 1;
		if (words.at(2) == "replace") if (words.size() != 5) throw - 1;

		map <int, string>::iterator ItMap = blocks.begin();
		for (int i = 0; i < blocks.size(); i++) {
			if (ItMap->second == "readfile" && words.at(2) == "readfile") throw - 1;
			if (ItMap->second == "writefile" && words.at(2) == "writefile") throw - 1;
		}

	}
	catch (int) {
		return false;
	}
	return true;
}

bool Validator::isCorrectScheme(vector <string> num, map <int, string> blocks) {
	map <int, string>::iterator IT;
	int read = -1, write = -1;
	vector <int> scheme;
	int k = 0;

	IT = blocks.begin();
	try {

		for (int i = 0; i < num.size(); i++) {
			for (int j = 0; j < num[i].length(); j++) {
				if (isdigit(num[i].at(j))) k = k * 10 + num[i].at(j) - '0';
				else if (num[i] == "->") {
					scheme.push_back(k);
					k = 0;
					break;
				}
				else throw - 1;
				if (num[num.size() - 1] == "->") throw - 1;
			}
		}

		scheme.push_back(k);

		for (int i = 0; i < scheme.size(); i++) {
			if (blocks.count(scheme[i]) == 0)
				throw - 1;
			if (i == scheme.size() - 1 && blocks.find(scheme[i])->second != "writefile") throw - 1;
			if (i == 0 && blocks.find(scheme[i])->second != "readfile") throw - 1;
		}
	}
	catch (int) {
		return false;
	}
	return true;

}


bool Validator::isCorrect(map <int, string> blocks, vector <int> words) {
	map <int, string>::iterator IT;
	int read = -1, write = -1;
	IT = blocks.begin();
	try {

		for (int i = 0; i < words.size(); i++) {
			if (blocks.count(words[i]) == 0)
				throw - 1;
			if (i == words.size() - 1 && blocks.find(words[i])->second != "writefile") throw - 1;
			if (i == 0 && blocks.find(words[i])->second != "readfile") throw - 1;
		}
	}
	catch (int) {
		return false;
	}
	return true;
}
