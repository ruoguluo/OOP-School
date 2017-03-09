#pragma once
// Workshop 7 - STL Containers
// iProduct.h

#include <iostream>
#include <fstream>

namespace w7 {

	class iProduct {
	public:
		//returns the price chargable to the customer. 
		virtual double getCharge() const = 0;

		//inserts the product information in the form of a single line into the output stream. 
		virtual void display(std::ostream&) const = 0;
	};

	std::ostream& operator<<(std::ostream&, const iProduct&);

	// reads the next record from the stream,
	// allocates memory for the corresponding iProduct object, 
	// copies the record information into that object and returns its address to the caller function. 
	iProduct* readProduct(std::ifstream& fin);
}