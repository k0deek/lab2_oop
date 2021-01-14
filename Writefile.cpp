#include "Writefile.h"

Writefile::Writefile(const string& a) {
    output = a;
}

Base& Writefile::doWork(Base& text) const {
    if (text.getter_countread() == 0)
        throw std::logic_error("Invalid writefile work");

    std::ofstream outputFile;
    outputFile.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    outputFile.open(output);

    vector <string>& pData = text.getter_base();

    if (!pData.empty()) {
        for (size_t i = 0; i < pData.size() - 1; ++i)
            outputFile << pData[i] << std::endl;
        outputFile << pData[pData.size() - 1];
    }

    text.clear_base();
    outputFile.close();
    return text;
}