#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <map>
#include <cmath>
#include <iterator>
#include <vector>
#include <algorithm>
#include <functional>

namespace w8 {
	template<typename T>
	class DataTable {
	/*	typedef struct Map {
			T first;
			T second;
			Map(T v1, T v2) : first(v1), second(v2) {}
		}map; */

		int width, 
			decimals;
		std::map<T, T> map;
	//	std::vector<std::pair<T,T>> vec;
	public:
		DataTable(std::ifstream& fin, const int w, const int d): width(w),decimals(d) {
			try {
				if (fin.is_open()) {
					std::string line;
					size_t count = 0;

					while (!fin.eof()) {
						T first, second;
						std::getline(fin, line);

						auto r = line.find('\r');
						if (r != std::string::npos) line.erase(r);
						
						first  = std::stod(line.substr(0,line.find(' ')));
						second = std::stod(line.substr(line.find(' ') + 1, line.size() - 1));

					//	vec.push_back(std::make_pair(first,second));

						//map.insert(std::map<T, T>::value_type(first,second));
						map.insert(std::make_pair(first, second));
						count++;
					}
					fin.close();
				}
				else {
					throw std::string("Stream is dead.Cannot read data.\n");
				}
			}
			catch (const std::string& e) {
				std::cerr << e << "\n";
			}
		}

		//  returns the mean value of the dependent coordinate 
		T mean() const {
			T t = 0;
			for (const auto i : map) { //vec
				t += i.second;
			}
			t /= map.size(); //vec
			return t;
		}

		// returns the standard deviation of the dependent coordinates
		T sigma() const {
			T t = 0;
			size_t m = mean();
			for (const auto i : map) { //vec
				t += std::pow(i.second - m,2);
			}
			t /= map.size() - 1; // -1 ?????	//vec	
			return std::sqrt(t);
		}
	/*	struct lesser {
			bool operator()(const std::pair<T, T> &left, const std::pair<T, T> &right) {
				return left.second > right.second;
			}
		} lesser; */

		// returns the median value of the dependent coordinate
		T median() const {
			T t = 0;
		/*	std::sort(vec.begin(), vec.end(), [](const std::pair<T, T> &left, const std::pair<T, T> &right) {
				return left.second > right.second;
			}); */
			auto middle = map.begin();//vec
			std::advance(middle, map.size() / 2);//vec
			t = (middle->second + (--middle)->second) / 2;
			return t ;
		}

		// returns the slope and intercept for the data set
		void regression(T& slope, T& y_intercept) const {
			T n = map.size(), xy = 0, //vec
				x  = 0, y  = 0,
				x2 = 0, y2 = 0;
			for (const auto i : map) {//vec
				x += i.first;
				y += i.second;
				xy += i.first * i.second;
				x2 += std::pow(i.first, 2);
				y2 += std::pow(i.second, 2);
			}
			slope = (n * xy - (x*y)) / (n *x2 - (std::pow(x,2)));
			y_intercept = (y - slope * x) / n;
		}

		// displays the data pairs as shown below
		void display(std::ostream& out) const {
			std::cout << std::setw(width)   << std::right << "x"
					  << std::setw(width+1) << std::right << " y\n";
			for (const auto i : map) {//vec
				std::cout << std::setw(width) << std::setprecision(decimals) << std::fixed << std::right << i.first
					      << std::setw(width) << std::setprecision(decimals) << std::fixed << std::right << i.second << std::endl;
			}
		}
	};//class
	template<typename T>
	std::ostream& operator << (std::ostream& out, const w8::DataTable<T>& dt) {
		dt.display(out);
		return out;
	} 
}//namespace