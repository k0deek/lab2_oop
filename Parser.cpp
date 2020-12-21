//#pragma once
#include "Worker.h"
using namespace workflow_executor;
using namespace std;

Parser::Parser()
{
	this->lastId = 0;
	this->firstId = 1000000;
	this->IsReadHere = false;
	this->IsWriteHere = false;
}


Parser::~Parser() {

}

void Parser::doWork(string filename) {
	ifstream workflow;
	Validator valid;
	vector <string> curString;
	string curWord;
	int id = 0;;
	workflow.open(filename);
	IsCorrect = true;
	try {
		if (!workflow.is_open()) throw - 1;
		getline(workflow, curWord);
		if (curWord != "desc") throw - 1;
		while (!workflow.eof()) {
			getline(workflow, curWord);
			if (curWord == "csed") break;
			curString = divLine(curWord); //get the words from input string

			if (!valid.isCorrect(blocks, curString)) throw - 1; //wrong blocks or arguments

			string block = curString[2];
			id = 0;
			for (int i = 0; i < curString[0].length(); i++) {
				id = id * 10 + (curString[0].at(i) - '0');
			}
			if (this->blocks.count(id) == 1) throw - 1;
			this->blocks.insert({ id, block });
			this->setComInBlock(curString, id);
			this->lastId = this->lastId > id ? this->lastId : id;
			this->firstId = this->firstId < id ? this->firstId : id;



		}
		if (curWord != "csed") throw - 1;
		if (workflow.eof()) throw - 1;
		getline(workflow, curWord);

		vector <string> scheme = divLine(curWord);
		if (!valid.isCorrectScheme(scheme, blocks)) this->IsCorrect = false;


		int k = 0;
		for (int i = 0; i < scheme.size(); i += 2) {
			for (int j = 0; j < scheme[i].length(); j++) {
				if (!isdigit(scheme[i].at(j))) throw - 1;
				k = k * 10 + scheme[i].at(j) - '0';
			}
			this->scheme.push_back(k);
			k = 0;
		}
		workflow.close();
	}
	catch (int) {
		//cout << "Incorrect workflow!";
		IsCorrect = false;
	}
}


vector <string> Parser::divLine(string str) {
	string buf = "";
	vector <string> words;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == ' ') {
			words.push_back(buf);
			buf = "";
			continue;
		}
		buf += str[i];
	}
	words.push_back(buf);
	return words;
}


void Parser::setComInBlock(vector <string> curString, int id) {
	if (curString[2] == "readfile") {
		this->readfile.setInstructions(id, curString[3]);
		this->IsReadHere = true;
	}
	else if (curString[2] == "writefile") {
		this->writefile.setInstructions(id, curString[3], &this->readfile);
		this->IsWriteHere = true;
	}
	else if (curString[2] == "dump") this->dumper.setInstructions(id, curString[3], &this->readfile);
	else if (curString[2] == "grep") this->grepper.setInstructions(id, curString[3], &this->readfile);
	else if (curString[2] == "sort") this->sorter.setFile(&this->readfile);
	else if (curString[2] == "replace") this->replacer.setInstructions(id, curString[3], curString[4], &this->readfile);

}

