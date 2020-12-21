#include "Worker.h"

using namespace workflow_executor;


Grepper::Grepper()
{
}

Grepper::~Grepper()
{
}


void Grepper::doWork(int id) {
	vector <string> newText;
	this->text = this->read->getText();
	std::map <int, string>::iterator ItMap = this->words.find(id);
	string word = ItMap->second;
	for (int i = 0; i < text.size(); i++) {
		if (this->text[i].find(word) != string::npos) {
			newText.push_back(this->text[i]);
		}
	}
	this->text = newText;
	this->read->changeText(newText);
}

void Grepper::setInstructions(int id, string word, Readfile* r) {
	this->words.insert(make_pair(id, word));
	this->read = r;
}

void Grepper::setReadfile(Readfile* r) {
	this->read = r;
}
