#include <string>
#include "Worker.h"
using namespace workflow_executor;
using namespace std;

int main(int argc, char* argv[])
{
	Executor exe;
	exe.doWork(argc, argv);
	return 0;
}
