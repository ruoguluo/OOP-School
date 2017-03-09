#include <iomanip>
#include "Product.h"

namespace w7 {
	//returns the price chargable to the customer. 
	double Product::getCharge() const {
		return price;
	}

	//inserts the product information in the form of a single line into the output stream. 
	void Product::display(std::ostream& out) const {
		out << std::setw(10) << std::right << prod_id
			<< std::setw(10) << std::right << std::setprecision(2) << std::fixed<< price << std::endl;
	}
};