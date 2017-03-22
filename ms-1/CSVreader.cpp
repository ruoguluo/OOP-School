#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "CSVreader.h"
namespace ms {

	std::string& CSVreader::trim(std::string& s, char trimChar) {
		while (!s.empty() && s[0] == trimChar)
			s.erase(0, 1);

		while (!s.empty() && s[s.size() - 1] == trimChar)
			s.erase(s.size() - 1, 1);

		return s;
	}//trim();

	void CSVreader::csvReader(char* filename, char delim, std::vector< std::vector<std::string> > &csv) {
		std::ifstream is(filename);
		if (is) {
			std::string line;
			std::vector<std::string> fields;

			while (getline(is, line)) {
				auto cr = line.find('\r');
				if (cr != std::string::npos) line.erase(cr, 1);

				std::string field;
				for (size_t i = 0; i < line.size(); i++) {
					if (line[i] == '"') {
						field += line[i];        // copy 1st "
						for (i++; i < line.size(); i++) {
							field += line[i];
							if (line[i] == '"')     // found 2nd "
								break;
						}
					}
					else
						if (line[i] != delim) {
							field += line[i];
						}
						else {
							trim(field);
							fields.push_back(move(field));
							// field.clear(); // not needed if we do a move
						}
				}
				trim(field);
				fields.push_back(field);
				csv.push_back(move(fields));
				// field.clear(); // not needed if we do a move
			}
			is.close();
		}
		else {
			std::cerr << "cannot open file " << filename << "\n";
		}
	}
}//namespace