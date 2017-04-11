#include <iostream>
#include <fstream>

#include "util.h"

bool validSlots(std::string& slot) {
	for (auto s : slot) {
		if (!isalnum(s) || s == ' ' || s == '0') {
			return false;
		}
	}
	return true;
}

bool validName(std::string& slot) {
	for (auto i : slot) {
		if (!isalpha(i)) {
			return false;
		}
	}
	return true;
}

bool isCode(std::string& s) {
	for (auto i : s) {
		if (!isalnum(i)) {
			return false;
		}
	}
	return true;
}

bool isItemName(std::string& s) {
	for (auto i : s) {
		if (!isalpha(i)) {
			return false;
		}
	}
	return true;
}

bool isOrderName(const std::string& s) {
	for (const auto& i : s) {
		if (!isalpha(i) && i != ' ') {
			return false;
		}
	}
	return true;
}

bool isCustomerName(const std::string& s) {
	for (const auto& i : s) {
		if (!isalpha(i) && i != ' ') {
			return false;
		}
	}
	return true;
}

void readcsv(std::string& file_name, const char delim, std::vector<std::vector<std::string>>& list) {
	std::fstream is(file_name, std::ios::in);
	if (!is.is_open()) {
		throw std::string("cannot open file") + file_name;
	}
	std::string line;
//	size_t line_counter = 0;
	while (std::getline(is, line)) {
		auto cr = line.find('\r');
		if (cr != std::string::npos)
			line.erase(cr);

		//std::cout << "line"<< line_counter << " ==>" << line << "<==\n";
	//	line_counter++;
		std::vector <std::string> fields;
		std::string field;
		size_t i = 0;

		while (i < line.size()) {
			if (line[i] != delim) {
				field += line[i];
			}
			else { // found delimeter
				trim(field);
				fields.push_back(std::move(field)); 
			}
			i++;
		} // end of processing line
		if (!field.empty()) {
			trim(field);
			fields.push_back(std::move(field));
			//add line fields to csvData
			list.push_back(std::move(fields));
			fields.clear();
		}
	}
	is.close();  
}//readcsv

std::string& trim(std::string& s) {
	while (!s.empty() && s[0] == ' ') { //delete leading space
		s.erase(0, 1);
	}

	while (!s.empty() && s[s.size() - 1] == ' ') // delete trailing spaces
		s.erase((s.size() - 1), 1);

	return s;
}//trim(); 