#pragma once
#include <iostream>
#include <fstream>
#include "Message.h"

//#define MAX_NO_OF_MESSAGES 10
namespace w5 {
	static const size_t MAX_NO_OF_MESSAGES = 10;
	class Notifications {
		Message *messages;
		size_t count;
		public:
			Notifications() : messages(new Message[MAX_NO_OF_MESSAGES]), count (0) {} // default
			//Notifications(std::ifstream&, char);
	    /*--------------------------------------------------------------*/
			Notifications(const Notifications&); // copy
			Notifications& operator=(const Notifications&); // copy
		/*--------------------------------------------------------------*/
			Notifications(Notifications&&); //move
			Notifications&& operator=(Notifications&&);//move
		/*--------------------------------------------------------------*/
			~Notifications();
		/*--------------------------------------------------------------*/
			// adds message to the set
			void operator+=(const Message&);

			// inserts the Message obj to the COUT
			void display(std::ostream&) const; 
	};
}