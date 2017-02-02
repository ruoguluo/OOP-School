#include <iostream>
#include <fstream>
#include <string>
#include "Text.h"

namespace w3 {

	size_t Text::size() const {
		return count;
	}

	Text::Text(const char* fname): count(0), table(nullptr) {
		std::fstream fin(fname, std::ios::in);
		std::string line;
		if (fin.is_open()) {
			//counting No of lines in file
			while (std::getline(fin, line)) {
				count++;
			}
		//	std::cout << "No of records in file: " << count << "\n";
			table = new std::string[count];
			fin.seekp(0);

			for (int i = 0; i < count; i++) {
				std::getline(fin, table[i]);
				auto cr = table[i].find('\r');
				if (cr != std::string::npos) {
					table[i].erase(cr);
				}
			}
			fin.close();
		}
		else {
			std::cerr << "Could not open|find file \"" << fname << "\"\n";
		}
	}//Text(const char*)

	Text::Text(const Text& other) {
		if (this != &other) {
			*this = other;
		}
	}//copy

	Text& Text::operator=(const Text& other) {
		if (this != &other) {
			if (table != nullptr) {
				delete[] table;
			}
			table = nullptr;
			count = other.count;

			table = new std::string[count];
			for (int i = 0; i < count; i++) {
				table[i] = other.table[i];
			}
		}
		return *this;
	}//copy-assignment operator

	Text::Text(Text&& other) : count(0), table(nullptr) {
		if (this != &other) {
			*this = std::move(other);
		}
	}//move constructor

	Text& Text::operator=(Text&& other) {
		if (this != &other) {
			if (table != nullptr) {
				delete[] table;
				table = nullptr; // +/-
			}
			count = other.count;
			table = other.table;
			other.count = 0;
			other.table = nullptr;
		}
		return *this;
	}//move assignment operator

	Text::~Text(){
		if (table != nullptr) {
			delete[] table;
		}
	}//destructor
}//namespace