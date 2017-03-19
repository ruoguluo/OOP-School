#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

extern const int FWC;
extern const int FWD;
extern const int FWP;

namespace w9 {
	/*
	 * Holds a product code and a user-friendly description;
	 */
	struct Description {
		unsigned code;
		std::string desc;
		bool load(std::ifstream& f) {
			f >> code >> desc;
			return f.good();
		}
		void display(std::ostream& os) const {
			os << std::setw(FWC) << code << std::setw(FWD)
				<< desc << std::endl;
		}
	};

	/*
	* Holds a product code and the current price;
	*/
	struct Price {
		unsigned code;
		double price;
		bool load(std::ifstream& f) {
			f >> code >> price;
			return f.good();
		}
		void display(std::ostream& os) const {
			os << std::setw(FWC) << code << std::setw(FWP)
				<< price << std::endl;
		}
	};

	/*
	* Holds a user-friendly description and the current price of a product;
	*/
	struct Product {
		std::string desc;
		double price;
		Product() {}
		Product(const std::string& str, double p) : desc(str), price(p) {}
		void display(std::ostream& os) const {
			os << std::setw(FWD) << desc << std::setw(FWP)
				<< price << std::endl;
		}
		void validate() const {
			if (price < 0.00)
				throw "*** Negative prices are invalid ***";
		}
	};
}