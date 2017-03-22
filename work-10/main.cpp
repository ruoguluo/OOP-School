#include <iostream>
#include <string>
#include <chrono>
#include "SecureData.h"

using namespace std::chrono;

int main(int argc, char** argv) {
	std::cout << "\nCommand Line : ";
	for (int i = 0; i < argc; i++) {
		std::cout << argv[i] << ' ';
	}
	std::cout << std::endl;
	if (argc != 4) {
		std::cerr << "\n***Incorrect number of arguments***\n";
		return 1;
	}
	char key = argv[3][0];

	try {
	//	double time_s[50];
	//	high_resolution_clock::time_point start = high_resolution_clock::now();
		w10::SecureData sd(argv[1], key);
		sd.backup(argv[2]);
		sd.restore(argv[2], key);
	/*	for (int i = 0; i < 50; i++) {
			high_resolution_clock::time_point start = high_resolution_clock::now();
			w10::SecureData sd(argv[1], key);
			sd.backup(argv[2]);
			sd.restore(argv[2], key);
			std::cout << sd << std::endl;
			high_resolution_clock::time_point end = high_resolution_clock::now();
			duration<double> tmp = duration_cast<duration<double>>(end - start);
			time_s[i] = tmp.count();
		} */
//		high_resolution_clock::time_point end = high_resolution_clock::now();
//		duration<double> time_s = duration_cast<duration<double>>(end - start);
//		std::cout << "Executed in " << time_s.count() << " seconds.\n";
		std::cout << sd << std::endl;
/*		std::cout << "Experiment (running decryption function 50 times): \n";
		for (int i = 0; i < 50; ++i) {
			std::cout << "Executed in " << time_s[i] << " seconds.\n";
		} */
	}
	catch (const std::string& msg) {
		std::cerr << msg << std::endl;
	}

	std::cout << "\nPress any key to continue ... ";
	std::cin.get();
}