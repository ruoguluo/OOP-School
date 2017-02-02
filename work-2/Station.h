#pragma once
#include <string>
#include <fstream>
namespace w2 {
	enum PassType {PASS_ADULT, PASS_STUDENT, PASS_COUNT};

	class Station {
		std::string name;
		unsigned passes[PASS_COUNT]; 

		public:
			Station();
			Station(std::fstream&);

			void set(const std::string&, unsigned, unsigned);
			void update(PassType, int);
			const std::string& getName() const;
			unsigned inStock(PassType) const;

			void updateStation();
			void restockStation();
			void report();

			//reads user's input from console;
			//used in updateStation() & restockStation() functions
			int readInput();
	};//class
}//namespace