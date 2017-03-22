#include <iostream>
#include <vector>
#include "CSVreader.h"

int main(int argc, char **argv) {

	char *filename;
	char delim;

	if (argc != 3) {
		std::cerr << "usage: " << argv[0] << " file delimiter-char\n";
		return 2;
	}

	filename = argv[1];
	delim = argv[2][0];

	std::vector< std::vector<std::string> > csv;
	ms::CSVreader rdr;
	rdr.csvReader(filename, delim, csv);

	for (size_t line = 0; line < csv.size(); line++) {

		std::cout << csv[line].size() << " fields:";
		for (size_t field = 0; field < csv[line].size(); field++) {
			std::cout << " <<" << csv[line][field] << ">>";
		}
		std::cout << "\n";
	}
	system("pause");
	return 0;
}