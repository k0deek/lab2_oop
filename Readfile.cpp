#include "Readfile.h"

Readfile::Readfile(const string& a) {
    input = a;
}

Base& Readfile::doWork(Base& text) const {
    std::ifstream inputFile;
    inputFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    inputFile.open(input);

    if (text.getter_countread() != 0)
        throw std::logic_error("Invalid readfile work");

    if (inputFile.peek() == std::ifstream::traits_type::eof()) {
        text.inc_read();
        return text;
    }

    vector <string>& pData = text.getter_base();

    string temp;
    while (!inputFile.eof() && getline(inputFile, temp))
        pData.emplace_back(temp);

    inputFile.close();
    text.inc_read();
    return text;
}
