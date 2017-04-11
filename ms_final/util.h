#pragma once
#include <string>
#include <vector>

bool validSlots(std::string&);
bool validName(std::string&);
bool isCode(std::string&);
bool isItemName(std::string&);
bool isOrderName(const std::string&);
bool isCustomerName(const std::string&);
void readcsv(std::string&, const char, std::vector<std::vector<std::string>>&);
std::string& trim(std::string&);