#pragma once
#include <iostream>
namespace w1 {
	// Max number of character in an array, without null terminator
	const int MAX = 3;
	class CString {
		char str[MAX + 1];// +1 -> '\0'
	public:
		CString(const char* s);
		void display(std::ostream& os) const;
	};
	std::ostream& operator<<(std::ostream& os, const CString cs);
}
