#include "Grepper.h"

Grepper::Grepper(const string& a) {
    word = a;
}

Base& Grepper::doWork(Base& text) const {
    if (text.getter_countread() == 0)
        throw std::logic_error("Invalid grepper work");

    vector <string>& fData = text.getter_base();

    if (!fData.empty()) {
        string searchString = word;
        std::transform(searchString.begin(), searchString.end(), searchString.begin(), ::toupper);

        string line;
        for (size_t i = 0; i < fData.size(); ++i) {
            line = fData[i];
            std::transform(line.begin(), line.end(), line.begin(), ::toupper);
            if (line.find(searchString) == string::npos)
                fData.erase(fData.begin() + i);
        }
    }

    return text;
}

