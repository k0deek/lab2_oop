#pragma once
#include <string>
#include <list>
#include "Worker.h"

using namespace workflow_executor;
using namespace std;


Writefile::Writefile()
{
	this->id = -1;
}

Writefile::~Writefile()
{
}

void Writefile::setInstructions(int id, string filename, Readfile* p) {
	this->fileToWrite = filename;
	this->id = id;
	this->read = p;
}

void Writefile::doWork(int id) {
	ofstream output;
	this->text = this->read->getText();
	vector <string>::iterator ItVec;
	output.open(this->fileToWrite);
	copy(this->text.begin(), this->text.end(), ostream_iterator<string>(output, "\n"));
}

string Writefile::returnFile() {
	return this->fileToWrite;
}