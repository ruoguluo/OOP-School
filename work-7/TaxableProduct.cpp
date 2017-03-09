#include <iomanip>
#include "TaxableProduct.h"

namespace w7 {
	//returns the price chargable to the customer. 
	double TaxableProduct::getCharge() const {
		return price;
	}

	//inserts the product information in the form of a single line into the output stream. 
	void TaxableProduct::display(std::ostream& out) const {
		out << std::setw(10) << std::right << prod_id
			<< std::setw(10) << std::right << price
			<< std::setw(10) << std::left  << ((type == 'H' || type == 'h') ? " HTS": " PTS") << std::endl;
	}
}