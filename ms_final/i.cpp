#include <fstream>
#include <iostream>
#include <vector>
#include <string>

#include "i.h"
#include "util.h"

Item::Item(std::vector<std::string> fields){
	switch (fields.size()){
	case 5:
		description = fields[4];
	case 4:
			code = fields[3];
	case 3:
			remover = fields[2];
	case 2:
			installer = fields[1];
	case 1:
			name = fields[0];
		break;
	default:
		throw std::string("expected 4 or 5 fields, found ") + std::to_string(fields.size());
		break;
	}
}//Item()

void Item::print(){
	if (!name.empty()) {
		std::cout << "\"" << name << "\"";
		if (!installer.empty()) {
			std::cout << ",\"" << installer << "\"";
			if (!remover.empty()) {
				std::cout << ",\"" << remover << "\"";
				if (!code.empty()) {
					std::cout << ",\"" << code << "\"";
					if (!description.empty()) {
						std::cout << ",\"" << description << "\"";
					}
				}
			}
		}//2nd if
	}//1st if
	std::cout << std::endl;
}//print()

void Item::graph(std::ofstream& out){
	out << '"' << name << "\"->\"" << installer << "\" [color=green];" << std::endl;
	out << '"' << name << "\"->\"" << remover << "\" [color=red];" << std::endl;
}//graph()


ItemManager::ItemManager(std::vector<std::vector<std::string>>& csvdata){
	int line = 1;
	for(auto fields : csvdata){
		try{
			line++;
			ItemList.push_back(Item(fields));
		}catch(std::string& e){
			std::cerr << "Problem with line" << line << ":\n";
			std::cerr << e << "\n";
		}
	}
}//ItemManager()

void ItemManager::print(){
	for(auto t : ItemList){
		t.print();
	}
}//print()

void ItemManager::graph(std::string file_name){
	std::ofstream out;
	std::string gv_file = file_name + ".gv";
	std::string png_file = file_name + ".gv.png";
	try {
		out.open(gv_file, std::ios::out);
		if (out.good()) {
			out << "digraph task {" << std::endl;
			for (auto t : ItemList) {
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
	std::string cmd = "dot -Tpng " + gv_file + " -o " + png_file;
#ifdef _WIN32
	cmd = "\"C:\\Program Files (x86)\\Graphviz2.38\\bin\\dot.exe\" -Tpng " + gv_file + " -o " + png_file;
#endif // _WIN32
	std::cout << ">" << cmd << std::endl;
	system(cmd.c_str());

}//graph()

Item* ItemManager::find(std::string itemKey){
	for(int i = 0; i < ItemList.size(); i++){
		if(ItemList[i].getName() == itemKey)
			return &ItemList[i];
	}
	return nullptr;
}//find()