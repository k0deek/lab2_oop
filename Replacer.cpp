
#include "Worker.h"

using namespace workflow_executor;


Replacer::Replacer()
{
}


Replacer::~Replacer()
{
}

void Replacer::setInstructions(int id, string word1, string word2, Readfile* r) {
	this->commands.insert({ id, word1 + (char)0 + word2 });
	this->read = r;
}

void Replacer::doWork(int id) {
	std::map <int, string>::iterator ItCom;
	vector <string> text = this->read->getText();
	vector <string> newText;
	ItCom = this->commands.find(id);
	string words = ItCom->second;
	int ind = 0;
	string curString = "";
	char* saveFirst = nullptr, * saveSecond = nullptr;

	string word1 = "", word2 = "";
	for (int i = 0; i < words.length(); i++) {
		if (words[i] != (char)0) word1 += words[i];
		else {
			ind = i + 1;
			break;
		}
	}

	while (ind < words.length())
	{
		word2 += words[ind];
		ind++;
	}

	int len = this->read->getLength();
	string changedStr;

	saveFirst = new char(this->read->getMaxLength());
	saveSecond = new char(this->read->getMaxLength());

	for (int i = 0; i < len; i++) {
		curString = text[i];
		if (curString.find(word1) == string::npos) {
			newText.push_back(curString);
			continue;
		}
		int beg = curString.find(word1);
		int end = beg + word1.length() - 1;

		memset(saveFirst, 0, curString.length());
		memset(saveSecond, 0, curString.length());

		curString.copy(saveFirst, beg, 0);
		curString.copy(saveSecond, curString.length() - end, end + 1);
		changedStr += saveFirst;
		changedStr += word2;
		curString = saveSecond;
		while (curString.find(word1) != string::npos) {
			memset(saveFirst, 0, curString.length());
			memset(saveSecond, 0, curString.length());
			int beg = curString.find(word1);
			int end = beg + word1.length() - 1;
			curString.copy(saveFirst, beg, 0);
			curString.copy(saveSecond, curString.length() - end + 1, end + 1);
			changedStr += saveFirst;
			changedStr += word2;
			curString = saveSecond;
		}
		changedStr += saveSecond;
		newText.push_back(changedStr);
		changedStr = "";
	}

	this->read->changeText(newText);

}