#include "Process.h"
#include "CString.h"

void Process::process(const char* s) const{
	w1::CString cs(s);
	cs.display(std::cout);
	std::cout << "\n";
} 