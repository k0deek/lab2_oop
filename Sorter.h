#pragma once
#include "parser.h"

using namespace workflow_executor;

class Sorter : public Worker {
private:
public:
    Base& doWork(Base& text) const override;
};

