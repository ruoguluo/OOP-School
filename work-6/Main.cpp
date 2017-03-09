// Workshop 6 - Lambda Expression
// w6.cpp

#include <iostream>
#include <cmath>
#include "Grades.h"

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << argv[0] <<
			": incorrect number of arguments\n";
		std::cerr << "Usage: " << argv[0] << " file_name\n";
		return 1;
	}

	w6::Grades grades(argv[1]);
	auto letter = [](const double grade) -> std::string{
		std::string tmp;
		if (round(grade) >= 90) {
			tmp = "A+";
		}
		else if (round(grade) >= 80 && round(grade) <= 89) {
			tmp = "A";
		}
		else if (round(grade) >= 75 && round(grade) <= 79) {
			tmp = "B+";
		}
		else if (round(grade) >= 70 && round(grade) <= 74) {
			tmp = "B";
		}
		else if (round(grade) >= 65 && round(grade) <= 69) {
			tmp = "C+";
		}
		else if (round(grade) >= 60 && round(grade) <= 64) {
			tmp = "C";
		}
		else if (round(grade) >= 55 && round(grade) <= 59) {
			tmp = "D+";
		}
		else if (round(grade) >= 50 && round(grade) <= 54) {
			tmp = "D";
		}
		else {
			tmp = "F";
		}
		return tmp;
	};
	grades.displayGrades(std::cout, letter);
	std::cout << "Press any key to continue ... ";
	std::cin.get();
}