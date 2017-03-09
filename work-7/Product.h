#pragma once
#include "iProduct.h"
namespace w7 {
	class Product : public iProduct {
	protected:
		size_t prod_id;
		double price;
	public:
		Product() : prod_id(0), price(0.00) {}
		Product(const size_t id, const double cost) : prod_id(id), price(cost) {}

		//returns the price chargable to the customer. 
		virtual double getCharge() const;

		//inserts the product information in the form of a single line into the output stream. 
		virtual void display(std::ostream&) const;
	};
}