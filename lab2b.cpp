#include <iostream>
#include "parser.h"

using namespace workflow_executor;

int main(int argc, char* argv[]) {
    try {     
        Parcer::program_arguments(argc, argv);
        return 0;
    }

    catch (const std::logic_error& e) {
        std::cerr << e.what() << std::endl;
    }
}