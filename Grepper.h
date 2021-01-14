#pragma once
#include "parser.h"

using namespace workflow_executor;


class Grepper : public Worker {
private:
    string word;
public:
    Grepper(const string& a);
    Base& doWork(Base& text) const override;
};