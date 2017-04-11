#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <utility>

#include "util.h"
#include "i.h"
#include "o.h"
#include "t.h"
#include "m.h"

using namespace std;

class factory{
	ItemManager  im;
	orderManager om;
	TaskManager  tm;
	vector<Machine> ml;
public:
	factory(ItemManager &&imArg, orderManager &&omArg, TaskManager &&tmArg)
	  : im(move(imArg)), om(move(omArg)), tm(move(tmArg))
	{
		/*
			Step 1: Create a factory of machines
		*/
		for(size_t t = 0; t < tm.size(); t++){
			ml.push_back(Machine(tm.at(t),im));
		}
		/*
			Step 2: Find source for graph
		*/
		enum{SOURCE_NOT_FOUND = -1};
		int source = SOURCE_NOT_FOUND;
		for(size_t m = 0; m < ml.size(); m++){
			ml[m].setBSource(true);
		}
		for(size_t t = 0; t < tm.size(); t++){
			// flag accept as not source since we are the incoming task for accept
			string s;
			Machine* mPtr;
			auto find = [&] (std::string n) -> Machine* {
				for(size_t m = 0; m < ml.size(); m++) {
					if(ml[m].getName()  == n)
						return &ml[m];
				}
				return nullptr;
			};
			s = tm.at(t).getAccept();
			if(!s.empty()) {
				mPtr = find(s);
				if(mPtr)  // returns a Machine*
					mPtr->setBSource(false);  // set Machine* not source
			}
			s = tm.at(t).getReject();
			if(!s.empty()) {
				mPtr = find(s);
				if(mPtr)  // returns a Machine*
					mPtr->setBSource(false);  // set Machine* not source
			}
		}//for
		int sourceCount = 0;
		for(size_t m = 0; m < ml.size(); m++){
			if(ml[m].getBSource() && source == SOURCE_NOT_FOUND){
				source = m;
				sourceCount++;
			}
			if(sourceCount > 1){
				throw string("multiple sources, fix task data and re-run.");
			}
			//cout << count << "\n";
		}
		cout << ml[source].getBSink() << "\n"; // ERROR
		cout << "source = " << source << " name = '" << ml[source].getName() << "' slots = '" << ml[source].getSlots() << "' passed = '" << ml[source].getAccept()<<"'\n";
		
		/*
			Step 3: Load job to source machine
		*/
		for(size_t j = 0; j < om.size(); j++)
			ml[source].push( Job( om.getOrder(j) ) );
		
		cout << "Om size = " << om.size() << "\n";
		/*
			Step 4: time loop
		*/
		
		for(int time = 0; true ; time++) {
			cout << "TIME LOOP: time=" << time << "\n";
			/*
				Step 5: if all inputQ's are empty, we are done
			*/
			bool allDone = true;
			for(size_t m = 0; m < ml.size(); m++) {
				if(!ml[m].empty()) {
					cout << "machine " << m << " found job\n";
					allDone = false;
					break;
				}
			}
			if(allDone) break;  // allDone, break out of time loop
			
			cout << "allDone=" << allDone << "\n";
			
			/*
				Step 6: Mchine loop
			*/
			for(size_t m = 0 ; m < ml.size(); m++) {
				ml[m].run(im, ml);
			}
		}		
		cout << "**** ALL DONE --- RUN OVER ****\n";		
	}
};// Factory class END

int validate(ItemManager &im, orderManager &om, TaskManager &tm){
	int errors = 0;
	//for items
	for(size_t i = 0; i < im.size(); i++){
		string s = im.getInstaller(i);
		if(!tm.find(s)){
			cerr << "Cannot find installer task '" << s <<"'\n";
			errors++;
		}
		s = im.getRemover(i);
		if(!tm.find(s)){
			cerr << "Cannot find remover task '" << s <<"'\n";
			errors++;
		}
	}
	//for order
	for(size_t orderIndex = 0; orderIndex < om.size(); orderIndex++){
		for(size_t itemIndex = 0; itemIndex < om.itemListSize(orderIndex); itemIndex++){
			string s = om.getItem(orderIndex,itemIndex);
			if(!im.find(s)){
				cerr << "Cannot find item task '" << s <<"'\n";
				errors++;
			}
		}
	}
	errors += tm.validate();
	
	if(errors){
		cerr << "+++++++++++++++++++++++++++++++++++\n";
		cerr << "+    Integrity check failed       +\n";
		cerr << "+           NOT GOOD              +\n";
		cerr << "+++++++++++++++++++++++++++++++++++\n";
		cerr << "Not good. " << errors << " errors in data. Please fix and resubmit.\n";
	}else{
		cout << "+++++++++++++++++++++++++++++++++++\n";
		cout << "+    Integrity check passed       +\n";
		cout << "+          GOOD TO GO             +\n";
		cout << "+++++++++++++++++++++++++++++++++++\n";
	}
	return errors;
}//int validate(ItemManager &im, orderManager &om, TaskManager &tm);


/* ============ MAIN ============ */
int main(int argc, char*argv[]){
	if (argc != 5){
		std::cerr << "Usage: " << argv[0] << "item-csv order-csv task-csv separator-char\n";
		return 1;
	}

	std::string itemfile  = argv[1];
	std::string orderfile = argv[2];
	std::string taskfile  = argv[3];
	char       delimiter  = argv[4][0];

	try{	
		std::vector<std::vector<std::string>> itemcsv;
		std::vector<std::vector<std::string>> ordercsv;
		std::vector<std::vector<std::string>> taskcsv;
		
		readcsv(itemfile, delimiter, itemcsv);
		ItemManager im(itemcsv);
			
		readcsv(orderfile, delimiter, ordercsv);
		orderManager om(ordercsv);
		
		readcsv(taskfile, delimiter, taskcsv);
		TaskManager tm(taskcsv);
		
	std::cout << "--------------- Item [START] ---------------\n";
	std::cout << "The the content of file '" << itemfile <<"'.\n";
	std::cout << "--------------------------------------------\n\n";
	im.print();
	std::cout << "\nExecuting command:\n";
    im.graph(itemfile);
	std::cout << "\n---------------- Item [END] ---------------\n\n";


	std::cout << "--------------- Order [START] ---------------\n";
	std::cout << "The the content of file '" << orderfile << "'.\n";
	std::cout << "--------------------------------------------\n\n";
	om.print();
	std::cout << "\nExecuting command:\n";
    om.graph(orderfile); 
	std::cout << "\n---------------- Order [END] ---------------\n\n";

	std::cout << "--------------- Task [START] ---------------\n";
	std::cout << "The the content of file '" << taskfile << "'.\n";
	std::cout << "--------------------------------------------\n\n";
	tm.print();
	std::cout << "\nExecuting command:\n";
    tm.graph(taskfile);
	std::cout << "\n---------------- Task [END] ---------------\n\n";

	int errors = validate(im,om,tm);
	//factory f(move(im),move(om),move(tm));													//     <<==  DON't FORGET TO UNCOMMENT THIS!
	
	}
	catch (string & e){
		std::cerr << e << std::endl;
	}
	system("pause");
	return 0;
}//main()