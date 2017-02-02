#include "CString.h"
#include "Process.h"
int main(int argc, char* argv[]) {
	std::cout << "Commands Line :";
	for (int arg = 0; arg < argc; arg++) {
		std::cout << " " << argv[arg];
	}
	std::cout << "\n";
	//we don`t count for 0 arg because it is the first command.
	//We are interested only in given args
	if (argc == 1) {
		std::cout << "Insufficient number of arguments (min 1)\n";
		return 1;
	}
	std::cout << "Maximum number of characters stored : " << w1::MAX << "\n";
	for (int arg = 1; arg < argc; arg++) {
		--arg;
		std::cout << arg << ": ";
		++arg;
		Process proc;
		proc.process(argv[arg]);
	}
	//std::cout << "\n";
	//system("pause");
	return 0;
}