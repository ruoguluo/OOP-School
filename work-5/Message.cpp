#include <iostream>
#include <fstream>
#include <string>
#include "Message.h"

namespace w5 {
	// 1 - ifstream
	// 2 - char - is the character delimits each record; default - '\n'
	Message::Message(std::ifstream& fin, char c) {
		std::string line;
		if (fin) {
			std::getline(fin, line, c);
			if (line.size() > 0) {
				auto at = line.find('@');
				if (at != std::string::npos) {
					line.erase(at, 1);		
				}
				auto index = line.find(' ');
				if (index < std::string::npos) {
					name = line.substr(0, index);
					msg = line.substr(++index, line.size() - 1);
					if (at != std::string::npos) {
						index = msg.find(' ');
						reply = msg.substr(0, index);
						msg = msg.substr(++index);
					}
				}
				else {
					name = line;
					msg = "";
				}
			}
		}
		else {
			std::cerr << "Could not read entries\n";
		}
	}//Message();

	//return true if the object in a safe empty state
	bool Message::empty() const {
		return msg.empty();
	}

	//displays the message
	void Message::display(std::ostream& out) const {
		if (!msg.empty()) {
			out << "Message\n User  : " << name << std::endl;
			if (!reply.empty()) {
				out << " Reply : " << reply << "\n Tweet : " << msg << std::endl << std::endl;
			}
			else {
				out << " Tweet : " << msg << std::endl << std::endl;
			}
		}//outer if
	}//display();
}//namespace