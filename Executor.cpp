#include "Worker.h"

using namespace workflow_executor;
using namespace std;

Executor::Executor()
{
}

bool Executor::doWork(int num, char* inStr[]) {
	try {
		if (num < 2 || num > 6)
			throw std::invalid_argument("Invalid count command line arguments!");

		string filename = inStr[1];
		this->parser.doWork(filename); //parsing strings and check valide
		vector <int> newScheme;
		if (num > 2) {
			if (!this->parser.IsReadHere || !this->parser.IsWriteHere) {
				for (int i = 2; i < num; i += 2) {
					if (this->parser.IsReadHere && this->parser.IsWriteHere) break;
					string str = inStr[i];
					if (str == "-o" && i <= num + 1) {
						int id = this->parser.lastId + 1;
						string write = inStr[i + 1];
						this->parser.blocks.insert({ id, "writefile" });
						this->parser.writefile.setInstructions(id, write, &this->parser.readfile);
						this->parser.IsWriteHere = true;
						this->parser.scheme.push_back(id);
					}
					else if (str == "-i" && i <= num + 1) {
						int id = this->parser.firstId - 1;
						string read = inStr[i + 1];
						this->parser.blocks.insert({ id, "readfile" });
						this->parser.readfile.setInstructions(id, read);
						this->parser.IsReadHere = true;
						newScheme.insert(newScheme.begin(), id);
						for (int j = 0; j < this->parser.scheme.size(); j++) {
							newScheme.push_back(this->parser.scheme.at(j));
						}
						this->parser.scheme.clear();
						this->parser.scheme = newScheme;

					}
					else throw - 1;
				}
				this->parser.IsCorrect = valid.isCorrect(this->parser.blocks, this->parser.scheme);
			}

		}


		if (!this->parser.IsCorrect) throw - 1;
		std::map <int, string> blocks = this->parser.blocks;
		vector <int> scheme = this->parser.scheme;
		int ind;
		string instr = "";

		for (int i = 0; i < scheme.size(); i++) { //do all work
			ind = scheme.at(i);
			instr = blocks.find(ind)->second;

			if (instr == "readfile") this->parser.readfile.doWork(ind);
			else if (instr == "replace") this->parser.replacer.doWork(ind);
			else if (instr == "writefile") this->parser.writefile.doWork(ind);
			else if (instr == "sort") this->parser.sorter.doWork(ind);
			else if (instr == "grep") this->parser.grepper.doWork(ind);
			else if (instr == "dump") this->parser.dumper.doWork(ind);
		}
	}
	catch (int) {
		cout << "Bad input (Incorrect workflow!)" << endl;
		return false;
	}
}

