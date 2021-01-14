#pragma once
#include "parser.h"

using namespace workflow_executor;


class Writefile : public Worker {
private:
    string output;
public:
    Writefile(const string& a);
    Base& doWork(Base& text) const override;
};