#pragma once
#include <vector>
#include <iostream>

#include "iProduct.h"
#include "Product.h"
#include "TaxableProduct.h"

namespace w7 {

	class Sale {
		std::vector<iProduct*> list;
	public:
		Sale() {};
		Sale(const char* fname);

		// displays the sale information as shown in the sample output above. 
		// The output includes column headings and the total sale amount including taxes paid.
		// The product number and cost occupy fields of width 10. 
		void display(std::ostream&) const;
		~Sale();
	};
}