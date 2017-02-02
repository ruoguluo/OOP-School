#pragma once
#include "Station.h"
namespace w2 {
	class Stations {
		size_t stationCount;
		Station *stationsTable;
		char *file_name;
		//upload data from the file
		void load(const char*);
		//save data into the file
		void save(const char*);
	public:
		Stations() {}
		Stations(const char*);
		~Stations();
		void update() const;
		void restock() const;
		void report() const;
	};//class
}//namespace