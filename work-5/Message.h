#pragma once
#include <iostream>
#include <string>

namespace w5 {
	class Message {
		std::string name,  //sender
					reply, //receiver
					msg;   //message
		public:
			Message() : name(""), reply(""), msg("") {}
			// 1 - ifstream
			// 2 - char - is the character delimits each record; default - '\n'
			Message(std::ifstream&, char c = '\n');

			//return true if the object in a safe empty state
			bool empty() const;

			//displays the message
			void display(std::ostream&) const;
	};
}