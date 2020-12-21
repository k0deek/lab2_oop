#include "Worker.h"

using namespace workflow_executor;


Sorter::Sorter()
{
}


Sorter::~Sorter()
{
}

void Sorter::doWork(int id) {
	vector <string> sorted;
	sorted = this->read->getText();
	sort(sorted.begin(), sorted.end());
	this->read->changeText(sorted);
}

void Sorter::setFile(Readfile* r) {
	this->read = r;
}
