#pragma once
#include <ostream>
#include <vector>
#include <functional>
namespace w6 {
	class Grades {
	//holds info about the Student:
	// id    - Student id;
	// grade -  grade
	typedef	struct Student {
		Student() {}
		    size_t id;
			double grade;
		} student;

	std::vector<student> students;
	size_t size;// No of entries inside the file
	public:
		Grades() : size(0) {}
		Grades(const char*);

		Grades(const Grades&) = delete;
		Grades(Grades&&) = delete;
		Grades& operator=(const Grades&) = delete;
		Grades&& operator=(Grades&&) = delete;

	//	void displayGrades(std::ostream& out, const std::string (*)(double)) const; //c-style function pointer
		void displayGrades(std::ostream& out, std::function<std::string(double)>) const;
	};
}//namespace