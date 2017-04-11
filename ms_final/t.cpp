#include <fstream>
#include <iostream>
#include <vector>
#include <string>

#include "util.h"
#include "t.h"	
Task::Task(std::vector<std::string> fields) :slots("1"){
	switch (fields.size()){
	case 4:
			reject = fields[3];
	case 3:
			accept = fields[2];
	case 2:
			slots = fields[1];
	case 1:
			name = fields[0];
		break;
	default:
		throw std::string("expected 1, 2, 3, or 4 fields, found ") + to_string(fields.size());
		break;
	}
}
void Task::print(){
	if (!name.empty()) {
		std::cout << "\"" << name << "\"";
		if (!slots.empty()) {
			std::cout << ",\"" << slots << "\"";
			if (!accept.empty()) {
				std::cout << ",\"" << accept << "\"";
				if (!reject.empty()) {
					std::cout << ",\"" << reject << "\"";
				}
			}
		}//2nd if
	}//1st if
	std::cout << std::endl;

}
void Task::graph(std::ofstream& out){

	if (!accept.empty()) {
		out << "\"" << name << "\"->\"" << accept << "\" [color=green];" << std::endl;
	}
	if (!reject.empty()) {
		out << "\"" << name << "\"->\"" << reject << "\" [color=red];" << std::endl;
	}
	if (accept.empty() && reject.empty()) {
		out << "\"" << name << "\" [shape=box];" << std::endl;
	}
}


TaskManager::TaskManager(vector<vector<string>>& csvdata){
	int line = 1;
	for(auto fields : csvdata){
		try{
			line++;
			TaskList.push_back(Task(fields));
		}catch(std::string& e){
			std::cerr << "Problem with line" << line << ":\n";
			std::cerr << e << "\n";
		}
	}
}
void TaskManager::print(){
	for(auto t : TaskList){
		t.print();
	}
}
void TaskManager::graph(std::string file_name){
	std::ofstream out;
	std::string gv_file = file_name + ".gv";
	std::string png_file = file_name + ".gv.png";
	try {
		out.open(gv_file, std::ios::out);
		if (out.good()) {
			out << "digraph task {" << std::endl;
			for (auto t : TaskList) {
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
}

int TaskManager::validate(){
	int errors = 0;
	
	for(int i = 0; i < TaskList.size(); i++){
		string s = TaskList[i].getAccept();
		if(!s.empty()){
			if(!find(s)){
				std::cerr << "Cannot find accept task" << s << "\n";
				errors++;
			}
		}
		
		s = TaskList[i].getReject();
		if(!s.empty()){
			if(!find(s)){
				std::cerr << "Cannot find reject task" << s << "\n";
				errors++;
			}
		}
	}
 return errors;
}

Task* TaskManager::find(std::string nameKey){
	for(int i = 0; i < TaskList.size(); i++){
		if(TaskList[i].getName() == nameKey)
			return &TaskList[i];
	}
	return nullptr;
}