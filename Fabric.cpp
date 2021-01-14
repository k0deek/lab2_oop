#include "parser.h"
#include "Replacer.h"
#include "Readfile.h"
#include "Writefile.h"
#include "Dumper.h"
#include "Grepper.h"
#include "Sorter.h"

using namespace workflow_executor;

std::shared_ptr<Worker> Parcer::createNewBlock(const WorkerDesc& function) {
    int a = function.id();
    if (a == 0)
    {
        if (function.countArg() == 1) {
            return std::shared_ptr<Worker>(new Readfile(function.argument(0)));
        }
        else
            throw std::invalid_argument("Invalid argument in readfile");
    }
    else if (a == 1)
    {
        if (function.countArg() == 1) {
            return std::shared_ptr<Worker>(new Writefile(function.argument(0)));
        }
        else
            throw std::invalid_argument("Invalid argument in writefile");
    }
    else if (a == 2)
    {
        if (function.countArg() == 1) {
            return std::shared_ptr<Worker>(new Grepper(function.argument(0)));
        }
        else {
            throw std::invalid_argument("Invalid argument in grep");
        }
    }
    else if (a == 3)
    {
        if (function.countArg() == 0) {
            return std::shared_ptr<Worker>(new Sorter());
        }
        else {
            throw std::invalid_argument("Invalid argument in sort");
        }
    }
    else if (a == 4)
    {
        if (function.countArg() == 2) {
            return std::shared_ptr<Worker>(new Replacer(function.argument(0), function.argument(1)));
        }
        else {
            throw std::invalid_argument("Invalid arguments in replace");
        }
    }
    else if (a == 5)
    {
        if (function.countArg() == 1) {
            return std::shared_ptr<Worker>(new Dumper(function.argument(0)));
        }
        else {
            throw std::invalid_argument("Invalid argument in dump");
        }
    }
    else
    {
        throw std::logic_error("Unknown name");
    }
}

WorkerDesc::WorkerDesc(const vector<string>& workers) {
    if (workers[2] == "readfile")
        command = readfile;
    else if (workers[2] == "writefile")
        command = writefile;
    else if (workers[2] == "grep")
        command = grepper;
    else if (workers[2] == "sort")
        command = sorter;
    else if (workers[2] == "replace")
        command = replacer;
    else if (workers[2] == "dump")
        command = dumper;
    else
        command = unknown;
   
    for (size_t i = 3; i < workers.size(); ++i)
        arguments.emplace_back(workers[i]);
}


size_t WorkerDesc::countArg() const {
    return arguments.size();
}

functions WorkerDesc::id() const {
    return command;
}

string WorkerDesc::argument(const size_t& index) const {
    if (index <= arguments.size()) {
        return arguments[index];
    }
    else {
        return " ";
    }
}