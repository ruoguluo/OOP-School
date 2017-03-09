#pragma once
#include "Product.h"
namespace w7 {
	class TaxableProduct : public Product {
		char type;
	public:
		TaxableProduct() : Product(), type(' ') {};
		TaxableProduct(const size_t id, const double cost, const char t) : Product(id, cost), type(t) {};

		//returns the price chargable to the customer. 
		virtual double getCharge() const;

		//inserts the product information in the form of a single line into the output stream. 
		virtual void display(std::ostream&) const;
	};
}