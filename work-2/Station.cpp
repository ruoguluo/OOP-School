#include <string>
#include <limits>
#include <climits>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <fstream>
#include "Station.h"

namespace w2 {

	Station::Station(){
		name = "";
		passes[PASS_STUDENT] = 0;
		passes[PASS_STUDENT] = 0;
	}

	Station::Station(std::fstream& fin) {
		std::string line;
		size_t index; // iterating index
			std::getline(fin, line); // next line
			std::string tmp_name, //holds the name of the station
				        first, //holds the first number
				        second;//holds the second number
			char c;
			index = 0;
			while ((c = line[index]) != ';') {
				if (isalpha(c)) {
					tmp_name += c;
				}
				else {
					std::cerr << "Encountered non-alphabetic character, exiting the program\n";
					exit(1);
				}
				index++;
			}
			
			index++;//skip the ';' character
			while ((c = line[index]) != ' ' && c != '\0') {
				if (isdigit(c)) {
					first += c;
				}
				else {
					std::cerr << "Encountered non-numeric character(first number), exiting the program\n";
					exit(2);
				}
				index++;
			}

			index++;//skip the ' '(whitespace) character
			// trying to avoid "\r\n" combo
			while(isdigit(line[index])){		
				second += line[index];
				index++;
			}
			set(tmp_name, std::stoi(first), std::stoi(second));
		
	}

	void Station::set(const std::string& station_name, unsigned student, unsigned adult) {
		name = station_name;
		passes[PASS_STUDENT] = student;
		passes[PASS_ADULT] = adult;
	}

	void Station::update(PassType type, int val) {
		int tmp = inStock(type);
		if (val < 0 && (tmp - val) < 0) {
				passes[type] = 0;
		}
		else {
			passes[type] += val;
		}
	}

	const std::string& Station::getName() const {
		return name;
	}

	unsigned Station::inStock(PassType type) const {
		return passes[type];
	}

	void Station::updateStation() {
		std::cout << std::left << name << std::endl << " Student Passes sold : ";
		update(PASS_STUDENT, (readInput() * (-1)));

		std::cout << " Adult   Passes sold : ";
		update(PASS_ADULT, (readInput() * (-1)));
	}//update

	void Station::restockStation() {
		std::cout << std::left << name << std::endl << " Student Passes added : ";
		update(PASS_STUDENT, readInput());

		std::cout << " Adult   Passes added : ";
		update(PASS_ADULT, readInput()); 
	}//restock

	void Station::report() {
		std::cout  << std::left   << std::setw(18) << name
			       << std::right  << std::setw(7)  << inStock(PASS_STUDENT)
			       << std::right  << std::setw(6)  << inStock(PASS_ADULT) << std::endl;
	}//report

	//reads user's input
	int Station::readInput() {
		int number = 0;
		while (!(std::cin >> number)) {
			if (!std::cin) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "  Invalid data, try one more time : ";
			}
		}
		return (number > 0) ? number : ((UINT_MAX - number) + 1);
	}//readInput
}