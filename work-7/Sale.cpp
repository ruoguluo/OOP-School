#include <iostream> 
#include <fstream>
#include <iomanip>
#include <string>
#include <algorithm> //count
#include <iterator> // istreambuf_iterator

#include "Sale.h"
#include "iProduct.h"
#include "Product.h"
#include "TaxableProduct.h"

namespace w7 {

	Sale::Sale(const char* fname) {
		if (fname) {
			std::ifstream fin(fname,std::ios::in);
			std::string line;
			size_t size = std::count(std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>(), '\n');
			fin.clear();
			fin.seekg(0); 
			++size;
			while (size > 0) {
				list.push_back(readProduct(fin));
				--size;
			}
			fin.close();
		}
		else {
			std::cerr << "Could not open file '" << fname << "' or it does not exist.\n";
		}
	}//c-tor;

	// displays the sale information as shown in the sample output above. 
	// The output includes column headings and the total sale amount including taxes paid.
	// The product number and cost occupy fields of width 10. 
	void Sale::display(std::ostream& out) const {
		std::cout << std::setw(10) << std::left << "Product No"
				  << std::setw(10) << std::right << "Cost"
				  << std::setw(10) << std::left << " Taxable" << std::endl;
		double total = 0;
		for (auto i : list) {
			std::cout << (*i);
			total += (*i).getCharge();
		}
		std::cout << std::setw(10) << std::right << "Total"
				  << std::setw(10) << std::right << total;
	}//display();

	Sale::~Sale() {
		if (!list.empty()) {
			for (auto i : list) {
				delete i;
			}
		}
	}//d-tor 


	std::vector<int> occurence(const std::string& str, const char find) {
		std::vector<int> indexes;
		if (!str.empty()) {
			for (size_t i = 0; i < str.size(); i++) {
				if (str.at(i) == find) {
					indexes.push_back(i);
				}
			}
		}
		else {
			std::cerr << "Empty string\n";
		}
		return indexes;
	}//occurence

	// reads the next record from the stream,
	// allocates memory for the corresponding iProduct object, 
	// copies the record information into that object and returns its address to the caller function. 
	iProduct* readProduct(std::ifstream& fin) {
		if (fin) {
			size_t id;
			double price;
			std::vector<int> vec;
			char tax;
			std::string line;
			getline(fin, line);
			if (!line.empty()) {
				vec = occurence(line, ' ');
				if (vec.size() == 1) {
					id = std::stoi(line.substr(0, vec[0]));
					price = std::stod(line.substr(vec[0] + 1, line.find('\n')));
					tax = ' ';
				}
				else if (vec.size() == 2) {
					id = std::stoi(line.substr(0, vec[0]));
					price = std::stod(line.substr(vec[0] + 1, vec[1]));
					tax = line.at(vec[1] + 1);
				}

				if (tax != ' ') {
					return new TaxableProduct(id, price, tax);
				}
				else {
					return new Product(id, price);
				}
			}
		}
		else {
			std::cerr << "Stream is dead.\n";
		}
		return nullptr;
	}//readProduct();

	std::ostream& operator<<(std::ostream& out, const iProduct& p) {
		p.display(out);
		return out;
	}// operator();
}//namespace