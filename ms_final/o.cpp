#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "util.h"
#include "o.h"

order::order(std::vector<std::string> fields){
	if (fields.size() < 2) {
		throw std::string("expected 2 or more fields, found ") + std::to_string(fields.size());
	}//if

	if (isCustomerName(fields[0])) {
		customer = fields[0];
	}

	if (!fields[1].empty()) {
		product = fields[1];
	}

	for(int i = 2; i < fields.size(); i++){
		//if(isItemName(fields[i]))
		if (!fields[i].empty()) {
			itemList.push_back(fields[i]);
		}
	}//for
}//order()

void order::print(){
	std::cout << "Customer Name: \"" << customer
		<< "\",\n Product Name: \"" << product
		<< "\",\n Item List: ";

	for (int i = 0; i < itemList.size(); i++) {
		if (i != itemList.size() - 1)
			std::cout << '"' << itemList[i] << '"' << ", ";
		else
			std::cout << '"' << itemList[i] << '"' << std::endl;
	}
	std::cout << std::endl;
}//print()

void order::graph(std::ofstream& out){
	for (const auto &o : itemList) {
		out << "\"" << customer << "\"->\"" << o << "\"[color=green];" << std::endl;
	} 
}//graph

orderManager::orderManager(std::vector<std::vector<std::string>>& csvdata){
int line = 1;
		for(auto fields : csvdata){
			try{
				line++;
				OrderList.push_back(order(fields));
			}catch(std::string& e){
				std::cerr << "Problem with line" << line << ":\n";
				std::cerr << e << "\n";
			}
		}
}// orderManager

void orderManager::print(){
	for(auto t : OrderList){
		t.print();
	}
}//print

void orderManager::graph(std::string file_name){
	std::ofstream out;
	std::string gv_file = file_name + ".gv";
	std::string png_file = file_name + ".gv.png";
	try {
		out.open(gv_file, std::ios::out);
		if (out.good()) {
			out << "digraph task {" << std::endl;
			for (auto t : OrderList) {
				t.graph(out);
			}
			out << "}";
			out.close();
		}//if
		else {
			throw std::string("Could not create file '") + file_name + "'. Might be due system privilege.\n";
		}
	}//try
	catch (std::exception& e) {
		std::cerr << "Something went wrong in OrderManager.cpp>>graph(string): " << e.what() << std::endl;
	}
	//	out.close();
	std::string cmd = "dot -Tpng " + gv_file + " -o " + png_file;
#ifdef _WIN32
	cmd = "\"C:\\Program Files (x86)\\Graphviz2.38\\bin\\dot.exe\" -Tpng " + gv_file + " -o " + png_file;
#endif // _WIN32
	std::cout << ">" << cmd << std::endl;
	system(cmd.c_str());
}//graph

//g++ -std=c++11 csvdump.cpp util.cpp -o csvdump
//dot -Tpng OrderList.dat.gv > OrderList.data.gv.png