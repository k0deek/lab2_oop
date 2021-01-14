#pragma once
#include "parser.h"

using namespace workflow_executor;

class Replacer : public Worker {
private:

    string word_1;
    string word_2;
public:
    Replacer(const string& a, const string& b);
    Base& doWork(Base& text) const override;
};