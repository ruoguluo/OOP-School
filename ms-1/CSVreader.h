#pragma once
#include <string>
#include <vector>

namespace ms {
	class CSVreader {
	public:
		std::string& trim(std::string& s, char trimChar = ' ');
		void csvReader(char* filename, char delim, std::vector< std::vector<std::string> > &csv);
	};
}//namespace