#include "parser.h"
#include "Readfile.h"
#include "Writefile.h"

using namespace workflow_executor;

bool Parcer::program_arguments(const int& argc, char* argv[]) {
    FilePaths filePaths;
    if (argc < 2 || argc > 6)
        throw std::invalid_argument("Invalid arguments");

    std::regex flag_regex("-[ioIO]");
    std::regex filePath_regex("[\\w]+\\.txt");
    std::cmatch result;

    if (!std::regex_match(argv[1], result, filePath_regex))
        throw std::logic_error("Wrong workflow filename");
    filePaths.workflow_file = argv[1];

    if (argc > 2) {
        for (int i = 2; i < argc; i += 2) {

            if (!std::regex_match(argv[i], result, flag_regex))
                throw std::invalid_argument("Syntax error1");
 
            if (!std::regex_match(argv[i + 1], result, filePath_regex))
                throw std::invalid_argument("Wrong file");

            if ((string)argv[i] == "-i" || (string)argv[i] == "-I") {
                filePaths.input_file = argv[i + 1];
            }
            else {
                filePaths.output_file = argv[i + 1];
            }
        }
    }
    Base text;
    std::list <std::shared_ptr<Worker>> machine = Parcer::scheme(filePaths);

    for (const auto& it : machine) {
        text = it->doWork(text);
    }

    return true;
}

std::list<std::shared_ptr<Worker>> Parcer::scheme(const FilePaths& filePaths) {
    std::ifstream workflowFile;

    workflowFile.open(filePaths.workflow_file);

    std::map<int, WorkerDesc> commandList;
    std::list<std::shared_ptr<Worker>> machine;

    string line;
    vector<string> partsOfLine;

    while (getline(workflowFile, line)) {
        if (line == "desc")
            break;
    }

    if (line != "desc")
        throw std::logic_error("Wrong desc");

    while (getline(workflowFile, line)) {
        if (!line.empty()) {
            if (line == "csed") {
                break;
            }
            else {
                partsOfLine = Parcer::splitLine(line);
                if (!isCommandBlock(partsOfLine))
                    throw std::logic_error("Syntax error2");
                int num = stoi(partsOfLine[0]);
                commandList.insert(std::pair<int, WorkerDesc>(num, WorkerDesc(partsOfLine)));
            }
        }
    }

    if (line != "csed")
        throw std::logic_error("Wrong csed");


    while (getline(workflowFile, line)) {
        if (!line.empty())
            break;
    }

    if (line.empty() || line == "csed")
        throw std::logic_error("Wrong scheme");

    machine = getToDoList(commandList, line, filePaths.input_file, filePaths.output_file);
    workflowFile.close();

    return machine;
}


std::list<std::shared_ptr<Worker>>
Parcer::getToDoList(const std::map<int, WorkerDesc>& commandList, const string& line, const string& input_file, const string& output_file) {
    std::list<std::shared_ptr<Worker>> machine;
    vector<string> partsOfLine = Parcer::splitLine(line);

    if (!Parcer::isNumber(partsOfLine[0]))
        throw std::logic_error("Syntax error3");

    int numBlock = stoi(partsOfLine[0]);
    auto it = commandList.find(numBlock);

    if (it == commandList.end())
        throw std::logic_error("Wrong workflow");

    if (it->second.id() != readfile) {
        if (input_file.empty())
            throw std::logic_error("Wrong input");
        machine.push_back(std::shared_ptr<Worker>(new Readfile(input_file)));
    }
    machine.push_back(createNewBlock(it->second));
    bool wasArrow = false;

    for (size_t i = 1; i < partsOfLine.size(); ++i) {
        if (i % 2 == 1) {
            if (partsOfLine[i] != "->")
                throw std::logic_error("Syntax error4");
            wasArrow = true;
        }
        else {
            if (!wasArrow || !Parcer::isNumber(partsOfLine[i]))
                throw std::logic_error("Syntax error5");

            numBlock = stoi(partsOfLine[i]);
            it = commandList.find(numBlock);

            if (it == commandList.end())
                throw std::logic_error("Wrong workflow");

            machine.push_back(createNewBlock(it->second));
            wasArrow = false;
        }
    }

    if (wasArrow) {
        throw std::logic_error("Syntax error6");
    }

    if (it->second.id() != writefile) {
        if (output_file.empty())
            throw std::logic_error("Wrong output");
        machine.push_back(std::shared_ptr<Worker>(std::shared_ptr<Worker>(new Writefile(output_file))));
    }

    return machine;
}


bool Parcer::isNumber(const string& s) {
    return !s.empty() && std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

bool Parcer::isCommandBlock(const vector<string>& partsOfLine) {
    if (partsOfLine.size() < 3 || partsOfLine.size() > 5)
        return false;

    if (!isNumber(partsOfLine[0]))
        return false;

    if (partsOfLine[1] != "=")
        return false;

    return true;
}

vector<string> Parcer::splitLine(const string& line) {
    vector<string> words;
    string word;

    for (char symbol : line) {
        if (symbol != ' ') {
            word += symbol;
        }
        else {
            if (!word.empty()) {
                words.emplace_back(word);
                word = "";
            }
        }
    }

    if (!word.empty())
        words.emplace_back(word);

    return words;
}

vector<string>& Base::getter_base() {
    return base;
}

void Base::clear_base() {
    base.clear();
    --countRead;
}

void Base::inc_read() {
    ++countRead;
}

void Base::dec_read() {
    --countRead;
}

Base::Base() {
    countRead = 0;
}

size_t Base::getter_countread() const {
    return countRead;
}