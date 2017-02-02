#include <iostream>
#include <cstring>
#include "CString.h"

namespace w1 {
	//constructor with c-string param
	CString::CString(const char* s) {
		if (s == nullptr) {
			str[0] = '\0';
			return;
		}
		strncpy(str, s, MAX);
		str[MAX] = '\0';
	}

	void CString::display(std::ostream& os) const {
		os << str;
	}

	std::ostream& operator<<(std::ostream& os, const CString cs) {
		int count = 0;
		os << count << ": ";
		count++;
		cs.display(os);
		return os;
	}
}