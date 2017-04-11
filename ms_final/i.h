#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "util.h"

class Item{
	std::string name, installer, remover, code, description;
public:
	Item(std::vector<std::string> fields);
	void print();
	void graph(std::ofstream& os);
	std::string& getName(){return name;}
	std::string& getInstaller(){return installer;}
	std::string& getRemover(){return remover;}
};

class ItemManager{
	std::vector<Item> ItemList;
public:
	ItemManager(std::vector<std::vector<std::string>>& csvdata);
	void print();
	void graph(std::string filename);
	Item* find(std::string itemKey);
	size_t size()const{return ItemList.size();}
	std::string& getInstaller(size_t s){return ItemList[s].getInstaller();}
	std::string& getRemover(size_t s){return ItemList[s].getRemover();}
};