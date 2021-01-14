#include "Dumper.h"

Dumper::Dumper(const string& a){
    FilePath = a;
}

Base& Dumper::doWork(Base& text) const {
    if (text.getter_countread() == 0)
        throw std::logic_error("Invalid dumper work");

    std::ofstream newFile;
    newFile.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    newFile.open(FilePath);

    vector <string>& pData = text.getter_base();

    if (!pData.empty()) {
        for (size_t i = 0; i < pData.size() - 1; ++i)
            newFile << pData[i] << std::endl;
        newFile << pData[pData.size() - 1];
    }

    newFile.close();
    return text;
}
