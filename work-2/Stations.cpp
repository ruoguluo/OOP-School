#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "Stations.h"

namespace w2 {

	Stations::Stations(const char* fname) {
		load(fname);
	}

	// number of passes sold
	void Stations::update() const {
		std::cout << "\nPasses Sold : \n-------------\n";
		for (size_t i = 0; i < stationCount; i++) {
			stationsTable[i].updateStation();
		}
	}// update

	//number of passes added
	void Stations::restock() const {
		std::cout << "\nPasses Added : \n--------------\n";
		for (size_t i = 0; i < stationCount; i++) {
			stationsTable[i].restockStation();
		}
	}//restock

	//total passes available at each station
	void Stations::report() const {
		std::cout << "\nPasses in Stock : Student Adult\n"
				  << "-------------------------------\n";
		for (size_t i = 0; i < stationCount; i++) {
			stationsTable[i].report();
		}
	}

	//savs the result and cleans the memory 
	Stations::~Stations() {
		save(file_name); // dont forget uncomments this piece
		if (stationsTable) delete[] stationsTable;
	}

	//upload data from file
	void Stations::load(const char* fname) {
		if (fname != nullptr) {
			size_t size = strlen(fname);
			file_name = new char[size];
			strcpy(file_name, fname);
		}
		std::fstream fin(fname, std::ios::in);
		if (fin.is_open()) {
			std::string line;
			std::getline(fin, line);// consume first line '4;'
			if (line.size() > 0 && isdigit(line[0])) {
				stationCount = line[0] - '0';
			}
			else {
				std::cerr << "Invalid file format or the file is empty\n";
				exit(4);
			}
			stationsTable =  new Station[stationCount];
			for (size_t i = 0; i <stationCount; i++) {
				stationsTable[i] = Station(fin);
			}
			fin.close();
		}
		else {
			std::cerr << "Could not open file '" << fname << "'\n";
			exit(5);
		}
	}//load

	//save data to file
	void Stations::save(const char* fname) {
		std::fstream out(fname, std::ios::out);
		if (out) {
			out << stationCount << ";\n";
			for (int i = 0; i < stationCount; i++) {
				out << stationsTable[i].getName() << ";" 
					<< stationsTable[i].inStock(PASS_STUDENT) << " " 
					<< stationsTable[i].inStock(PASS_ADULT) << "\n";
			}
			out.close();
		}
		else {
			std::cerr << "Coult not open|find the file '" << fname <<"\n";
			exit(6);
		}
	}
}