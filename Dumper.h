#pragma once
#include "parser.h"

using namespace workflow_executor;


class Dumper : public Worker {
private:
    string FilePath;
public:
    Dumper(const string& a);
    Base& doWork(Base& text) const override;
};