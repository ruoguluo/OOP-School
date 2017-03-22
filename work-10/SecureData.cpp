// Workshop 10 - Multi-Threading
// SecureData.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <functional> //std::bind(),..
#include <thread> 
#include <vector>
#include <exception>
#include <cstdlib>

#include "SecureData.h"

namespace w10 {

	void converter(char* t, char key, int n, const Cryptor& c) {
		for (int i = 0; i < n; i++)
			t[i] = c(t[i], key);
	}

	SecureData::SecureData(const char* file, char key) {
		// open text file
		std::fstream input(file, std::ios::in);
		if (!input)
			throw std::string("\n***Failed to open file ") +
			std::string(file) + std::string(" ***\n");

		// copy from file into memory
		nbytes = 0;
		input >> std::noskipws;
		while (input.good()) {
			char c;
			input >> c;
			nbytes++;
		}
		nbytes--;
		input.clear();
		input.seekg(0, std::ios::beg);
		text = new char[nbytes + 1];

		int i = 0;
		while (input.good())
			input >> text[i++];
		text[--i] = '\0'; 

		std::cout << "\n" << nbytes << " bytes copied from text "
			<< file << " into memory (null byte added)\n";
		encoded = false;

		// encode using key
		code(key);
		std::cout << "Data encrypted in memory\n";
	}

	SecureData::~SecureData() {
		delete[] text;
	}

	void SecureData::display(std::ostream& os) const {
		if (text && !encoded)
			os << text << std::endl;
		else if (encoded)
			throw std::string("\n***Data is encoded***\n");
		else
			throw std::string("\n***No data stored***\n");
	}

	/*====== CODE(char) ========*/
	void SecureData::code(char key) {
		//converter(text, key, nbytes, Cryptor()); // 0.013 - 0.015 =  Best Run
		try {
			//doesn't work on Matrix, causes exception because returns 0 // float point exception
			size_t cores = std::thread::hardware_concurrency();  // 0.005 - 0.007 = Best Run
			//int cores = 2; //uncomment if you want to run this on Matrix server;
			std::vector<std::thread> th;
			int portion = 0;
			int mod = std::div(nbytes, cores).rem;
			int last_thread = cores - 1;
			if (mod != 0) {
				portion = (nbytes - mod) / cores;
			}
			else {
				portion = nbytes / cores; // 936 / 4 = 234; //might be exception
			}
			int curr_index = 0;
			char* txt = new char[portion +1];
			for (size_t i = 0; i < cores; ++i) {
				if (i == last_thread) {
					memcpy(txt, text, portion + mod);
					txt[portion] = '\0';
					th.push_back(std::thread(std::bind(converter, text, key, portion, Cryptor())));
				}
				else {
					memcpy(txt, text, portion);
					txt[portion] = '\0';
					th.push_back(std::thread(std::bind(converter, text, key, portion, Cryptor())));
				}
			}

			//waiting for every thread to finish the job
			for (auto &i : th) {
				i.join();
			}

			if(txt) delete[] txt;

		} catch (std::exception& e) {
			std::cerr << e.what() << "\n";
		}
		encoded = !encoded;
	}

	void SecureData::backup(const char* file) {
		if (!text)
			throw std::string("\n***No data stored***\n");
		else if (!encoded)
			throw std::string("\n***Data is not encoded***\n");
		else {
			std::ofstream fout(file, std::ios::binary);
			if (!fout) throw std::string("*** Cannot open file '") + file + "'.\n";
			fout.write(text,nbytes);
			fout.close();
		}
	}

	void SecureData::restore(const char* file, char key) {
		// open binary file
		std::ifstream fin(file, std::ios::binary);
		if (!fin) {
			throw std::string("*** Could not open file '") + file + "'.\n";
		}
		else {
			if (text) delete[] text;

			//std::vector<char> vec(std::istreambuf_iterator<char>(fin),(std::istreambuf_iterator<char>())); //works, lets try something else

			fin.seekg(0,std::ios::end); // Sets the position of the next character to be extracted from the input stream.
			nbytes = (int)fin.tellg(); //tellg() - returns the position of the current character in the input stream.
			text = new char[nbytes +1];

			fin.seekg(std::ios::beg);
			fin.read(text, nbytes);
			text[nbytes] = '\0';
			fin.close();
		}
		std::cout << "\n" << nbytes + 1 << " bytes copied from binary file "
			<< file << " into memory (null byte included)\n";
		encoded = true;

		// decode using key
		code(key);
		std::cout << "Data decrypted in memory\n\n";
	}

	std::ostream& operator<<(std::ostream& os, const SecureData& sd) {
		sd.display(os);
		return os;
	}
}