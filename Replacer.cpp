#include "Replacer.h"

 Replacer::Replacer(const string& a, const string& b) {
    word_1 = a;
    word_2 = b;
}

Base& Replacer::doWork(Base& text) const {
    if (text.getter_countread() == 0)
        throw std::logic_error("Invalid replacer work");

    vector <string>& pData = text.getter_base();

    if (!pData.empty()) {
        for (auto& line : pData) {
            line = std::regex_replace(line, std::regex(word_1), word_2);
        }
    }

    return text;
}