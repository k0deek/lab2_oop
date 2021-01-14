#include "Sorter.h"

Base& Sorter::doWork(Base& text) const {
    if (text.getter_countread() == 0)
        throw std::logic_error("Invalid sorter work");

    vector <string>& pData = text.getter_base();

    if (!pData.empty()) {
        std::sort(pData.begin(), pData.end());
    }

    return text;
}