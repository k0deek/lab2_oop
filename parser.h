#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <list>
#include <map>

using std::string;
using std::vector;

namespace workflow_executor {
    
    class Base {
    private:
        vector<string> base;
        size_t countRead;

    public:
        Base();
        vector<string>& getter_base();
        size_t getter_countread() const;
        void inc_read();
        void dec_read();
        void clear_base();
    };

    class Worker {
    public:
        virtual Base& doWork(Base& text) const = 0;
    };

    enum functions {
        readfile, writefile, grepper, sorter, replacer, dumper, unknown
    };
    
    class WorkerDesc {
    private:
        functions command;
        vector<string> arguments;

    public:
        WorkerDesc(const vector<string>& partsOfLines);
        string argument(const size_t& index) const;
        size_t countArg() const;
        functions id() const;
    };

    struct FilePaths {
        string workflow_file;
        string input_file;
        string output_file;
    };


    class Parcer {
    private:
        static vector<string> splitLine(const string& line);
        static bool isNumber(const string& s);
        static bool isCommandBlock(const vector<string>& partsOfLine);
        static std::shared_ptr<Worker> createNewBlock(const WorkerDesc& element);
        static std::list<std::shared_ptr<Worker>> getToDoList(const std::map<int, WorkerDesc>& commandList, const string& line, const string& defaultInputFilePath, const string& defaultOutputFilePath);

    public:
        static bool program_arguments(const int& argc, char* argv[]);
        static std::list<std::shared_ptr<Worker>> scheme(const FilePaths& filePaths);
    };
}

