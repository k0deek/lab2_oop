#pragma once
#include "parser.h"

using namespace workflow_executor;

class Readfile : public Worker {
private:
    string input;
public:
    Readfile(const string& a);
    Base& doWork(Base& text) const override;
};