#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <list>
#include <map>
#include <iterator>
#include <algorithm>

using std::string;
using std::vector;
namespace workflow_executor {

    class Worker
    {
    public:
        virtual void doWork(int id) = 0;
    };

    class Readfile : public Worker
    {

    public:
        friend class Parser;
        friend class Executor;
        friend class Replacer;
        friend class Sorter;
        friend class Writefile;
        friend class Grepper;
        friend class Dumper;
        Readfile();

    private:
        virtual void doWork(int id);
        void setInstructions(int id, string filename);
        int getLength();

        vector <string> getText();

        void changeText(vector <string> newText);
        ~Readfile();

        int getMaxLength();

        string fileToRead;
        int textLength;
        int maxLength;
        int id;
        vector <string> text;
    };

    class Writefile : public Worker
    {
    public:
        Writefile();
        ~Writefile();
        friend class Parser;
        friend class Executor;

    protected:
        virtual void doWork(int id);
        string returnFile();
        void setInstructions(int id, string filename, Readfile* p);

        string fileToWrite;
        vector <string> text;
        Readfile* read;
        int id;

    };

    class Dumper : public Worker
    {
    public:
        Dumper();
        ~Dumper();

        friend class Parser;
        friend class Executor;


    private:

        void setInstructions(int id, string filename, Readfile* r);

        void doWork(int id);

        Readfile* read;

        std::map<int, string> filesToDump;
    };

    class Grepper : public Worker
    {
    public:
        Grepper();
        ~Grepper();

        friend class Executor;
        friend class Parser;
    private:
        void doWork(int id);
        void setInstructions(int id, string word, Readfile* r);
        void setReadfile(Readfile* read);

        Readfile* read;
        vector <string> text;
        std::map<int, string> words;
    };


    class Replacer : public Worker
    {
    public:
        Replacer();
        ~Replacer();
        friend class Parser;
        friend class Executor;

    private:
        void setInstructions(int id, string word1, string word2, Readfile* r);
        void doWork(int id);
        std::map<int, string> commands;
        Readfile* read;
    };

    class Sorter : public Worker
    {
    public:
        Sorter();
        ~Sorter();
        void doWork(int id);
        void setFile(Readfile* r);
        friend class Parser;
        friend class Executor;

    private:
        Readfile* read;
    };

    class Validator
    {
    public:
        Validator();
        ~Validator();
        bool isCorrect(std::map <int, string> blocks, vector <string> words);
        bool isCorrect(std::map <int, string> blocks, vector <int> words);
        bool isCorrectScheme(vector <string> num, std::map <int, string> blocks);
    };

    class Parser
    {
    public:
        Parser();
        ~Parser();

        friend class Executor;

    private:
        void doWork(string workflow);

        std::map <int, string> blocks;
        vector <int> scheme;
        Writefile writefile;
        Sorter sorter;
        Grepper grepper;
        Dumper dumper;
        Readfile readfile;
        Replacer replacer;


        int lastId;
        int firstId;
        bool IsWriteHere;
        bool IsCorrect;
        bool IsReadHere;

        void setComInBlock(vector <string> curString, int id);
        vector <string> divLine(string str);
    };

    class Executor
    {
    public:
        Executor();
        bool doWork(int argv, char* argc[]);

    private:
        Parser parser;
        Validator valid;
    };

}