#include <utility>
#include <iostream>
#include "Notifications.h"
#include "Message.h"

namespace w5 {

	Notifications::Notifications(const Notifications& note) {
		std::cout << "Copy-constructor called\n";
		if (this != &note) {
			*this = note;
		}
	}//copy-constructor

	Notifications& Notifications::operator=(const Notifications& note) {
		std::cout << "Copy-assignment operator called\n";
		if (this != &note) {
			if (messages != nullptr) {
				delete[] messages;
				messages = nullptr;
			}
			messages = new Message[MAX_NO_OF_MESSAGES];
			for (int i = 0; i < MAX_NO_OF_MESSAGES; i++) {
				messages[i] = note.messages[i];
			}
		}
		return *this;
	}//copy-assign operator

	Notifications::Notifications(Notifications&& note) {
		std::cout << "Move-constructor called\n";
		if (this != &note) {
			messages = note.messages;
			note.messages = nullptr;

			count = note.count;
			note.count = 0;
		}
	}// move constructor

	Notifications&& Notifications::operator=(Notifications&& note) {
		std::cout << "move-assignment operator called\n";
		if (this != &note) {
			if (messages != nullptr) {
				delete[] messages;
				messages = nullptr;
			}
			messages = note.messages;
			note.messages = nullptr;

			count = note.count;
			note.count = 0;
		}
		return std::move(*this);
	}// move-assign operator

	Notifications::~Notifications() {
		if (messages != nullptr) {
			delete[] messages;
			messages = nullptr;
		}
	}// destructor

	void Notifications::operator+=(const Message& msg) {
		if (count < MAX_NO_OF_MESSAGES) {
			messages[count] = msg;
			count++;
		}
	}//operator


	void Notifications::display(std::ostream& out) const {
		for (size_t i = 0; i < count; i ++ ) {
			messages[i].display(out);
		}
	}//display
}