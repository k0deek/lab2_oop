#pragma once
#include "Worker.h"
#include <iostream>
#include <fstream>
#include <map>
using namespace workflow_executor;
using namespace std;

Readfile::Readfile()
{
	this->id = -1;
	this->textLength = 0;
	this->maxLength = 0;
}

//Method realize reading text from doc to memory
void Readfile::doWork(int id) {
	this->textLength = 0;
	ifstream input;
	string curWord;
	int i = 0;
	vector <string> curWordVec;
	input.open(this->fileToRead);
	while (!input.eof()) {
		getline(input, curWord);
		int k = curWord.size();
		this->text.push_back(curWord);
		if (curWord.size() > this->maxLength)
			this->maxLength = curWord.length();
	}
	this->textLength = this->text.size();
	input.close();
}

//setter
void Readfile::setInstructions(int id, string filename) {
	this->fileToRead = filename;
	this->id = id;
}

//getter
vector <string> Readfile::getText() {
	return this->text;
}
//returns length of list of text 
int Readfile::getLength() {
	return this->text.size();
}

void Readfile::changeText(vector <string> newText) {
	this->textLength = newText.size();
	this->text = newText;
	this->maxLength = 0;
	for (int i = 0; i < this->textLength; i++)
		this->maxLength = this->maxLength < this->text[i].size() ?
		this->text[i].size() : this->maxLength;
}

int Readfile::getMaxLength() {
	return this->maxLength;
}

//Destructor
Readfile::~Readfile()
{
}
