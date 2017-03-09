#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <exception>
#include "Grades.h"
namespace w6 {
	Grades::Grades(const char* fname) : size(0) {
		std::fstream fin(fname, std::ios::in);
		student tmp;
		try {
			if (fin.is_open()) {
				while (!fin.fail()) { 
						fin >> tmp.id >> tmp.grade;
						if (fin.fail()) {
							break;
						}
					if (fin.good()) {
						students.push_back(tmp);
						size++;
					}
				}//while()
				fin.close();
			}
			else {
				throw std::invalid_argument("Cannot open | read file ");
			}
		}
		catch (const std::exception& e) {
			std::cerr << "Bad argument: " << e.what() << fname << std::endl;
		}
	}//Grades(const char*);

	void Grades::displayGrades(std::ostream& out, std::function<std::string(double)> f) const {
		for (auto a : students) {
			out << a.id << " " << a.grade << " " << f(a.grade) << std::endl;
		}
	}//displayGrades() const

}//namespace