#pragma once
#include <string>

namespace w3 {

	class Text {
		//No of records inside file
		size_t count;
		std::string *table;
	public:
		Text() : count(0), table(nullptr) {} // default constructor
		Text(const char*); //assepts a file name as a parametr
/*--------------------------------------------------------------------*/
		Text(const Text&); //copy constructor
		Text& operator=(const Text&); //assignment operator
/*--------------------------------------------------------------------*/
		Text(Text&&); //move constructor 
		Text&& operator=(Text&&); //move assignment operator
/*--------------------------------------------------------------------*/
		~Text(); //destructor
/*--------------------------------------------------------------------*/
		size_t size() const;
	};//class
}//namespace
