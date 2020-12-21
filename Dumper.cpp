#include "Worker.h"

using namespace workflow_executor;


Dumper::Dumper()
{

}


Dumper::~Dumper()
{

}

void Dumper::setInstructions(int id, string str, Readfile* r) {
	this->filesToDump.insert(make_pair(id, str));
	this->read = r;
}

void Dumper::doWork(int id) {
	std::map <int, string>::iterator itStr;
	std::ofstream output;
	vector <string> text = this->read->getText();
	itStr = this->filesToDump.find(id);
	string filename = itStr->second;
	output.open(filename);
	copy(text.begin(), text.end(), std::ostream_iterator<string>(output, "\n"));
}

